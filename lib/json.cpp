/*
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.
In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
For more information, please refer to <http://unlicense.org/>
✂--------------------------------[ Cut here ]----------------------------------
*/
#include "json.hpp"

#include <algorithm>
#include <bit>
#include <charconv>
#include <cmath>
#include <cstring>
#include <cuchar>
#include <numeric>
#include <span>
#include <utility>

using Null = Json::Null;
using Boolean = Json::Boolean;
using Number = Json::Number;
using String = Json::String;
using StringView = Json::StringView;
using Array = Json::Array;
using Object = Json::Object;
using ReadError = Json::ReadError;

// Unicode functions
namespace JsonImpl {
    struct Word {
    private:
        uint8_t size_ = {};
        char8_t data_[4] = {};

    public:
        template <size_t N>
        inline constexpr Word(char8_t const (&array)[N]) noexcept {
            for (size_t i = 0; i != N - 1; ++i) {
                data_[i] = array[i];
            }
            size_ = N - 1;
        }
        inline constexpr operator StringView() const noexcept { return {data_, (size_t)size_}; }
        inline constexpr size_t size() const noexcept { return size_; }
    };

    static Word const WHITESPACE[] = {
        {u8"\x09"},   {u8"\x0A"},   {u8"\x0B"},   {u8"\x0C"},   {u8"\x0D"},   {u8"\x20"},   {u8"\u00A0"},
        {u8"\u1680"}, {u8"\u2000"}, {u8"\u2001"}, {u8"\u2002"}, {u8"\u2003"}, {u8"\u2004"}, {u8"\u2005"},
        {u8"\u2006"}, {u8"\u2007"}, {u8"\u2008"}, {u8"\u2009"}, {u8"\u200A"}, {u8"\u2028"}, {u8"\u2029"},
        {u8"\u202F"}, {u8"\u205F"}, {u8"\u3000"}, {u8"\uFEFF"},
    };

    static Word const NEWLINE[] = {
        {u8"\x0A"},
        {u8"\u2028"},
        {u8"\u2029"},
    };

    static Word const NEWLINE_TERMINATOR[] = {
        {u8"\x0A"},
        {u8"\x0B"},
        {u8"\x0C"},
        {u8"\x0D"},
        {u8"\u2028"},
        {u8"\u2029"},
    };

    static char8_t const IDENT_ASCII[] = u8"$_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static char8_t const NUMBER_PART[] = u8"+-.0123456789ABCDEFXabcdefx";

    struct StringIterator {
    protected:
        StringView remaining = {};
        StringView consumed = {};

    public:
        inline constexpr StringIterator(StringView view) noexcept : remaining(view), consumed(view.data(), 0) {}

        inline constexpr bool empty() const noexcept { return remaining.empty(); }

        inline constexpr char8_t const* data() const noexcept { return remaining.data(); }

        inline constexpr size_t size() const noexcept { return remaining.size(); }

        inline constexpr StringView view_consumed() const noexcept { return consumed; }

        inline constexpr StringView view_remaining() const noexcept { return remaining; }

        constexpr StringIterator& operator+=(ptrdiff_t n) noexcept {
            remaining = {remaining.data() + n, remaining.size() - n};
            consumed = {consumed.data(), consumed.size() + n};
            return *this;
        }

        constexpr StringIterator& operator-=(ptrdiff_t n) noexcept {
            remaining = {remaining.data() - n, remaining.size() + n};
            consumed = {consumed.data(), consumed.size() - n};
            return *this;
        }

        constexpr char32_t pop_character() noexcept {
            if (!remaining.empty()) {
                auto const first = remaining.front();
                if (first < 0b1000'0000u) {
                    *this += 1;
                    return first;
                } else if (first < 0xC2 || first > 0xF4) {
                    *this += 1;
                    return 0xFFFD;
                } else {
                    unsigned hibits = 0;
                    for (auto i = first; i & 0b1000'0000u; i <<= 1u) {
                        ++hibits;
                    }
                    if (hibits > remaining.size()) {
                        *this += 1;
                        return U'\uFFFD';
                    }
                    char32_t result = first % (1u << (8u - hibits));
                    for (auto i = remaining.data() + 1; i != remaining.data() + hibits; ++i) {
                        if (*i < 0b1000'0000u || *i >= 0b1100'0000u) {
                            *this += 1;
                            return U'\uFFFD';
                        }
                        result <<= 6u;
                        result |= *i & 0b0011'1111u;
                    }
                    *this += hibits;
                    return result;
                }
            } else {
                return 0xFFFF'FFFFu;
            }
        }

        constexpr bool is_ascii() const noexcept { return !remaining.empty() && remaining.front() <= 0x7Fu; }

        constexpr bool is_word(StringView word) const noexcept {
            if (remaining.starts_with(word)) {
                return true;
            }
            return false;
        }

        constexpr bool is_word(std::span<Word const> word_list) const noexcept {
            if (!remaining.empty()) {
                for (auto const& word : word_list) {
                    if (remaining.starts_with(word)) {
                        return true;
                    }
                }
            }
            return false;
        }

        constexpr bool is_one_of(StringView list) const noexcept {
            if (!remaining.empty()) {
                for (auto const c : list) {
                    if (remaining.front() == c) {
                        return true;
                    }
                }
            }
            return false;
        }

        constexpr bool consume_word(StringView word) noexcept {
            if (is_word(word)) {
                *this += word.size();
                return true;
            }
            return false;
        }

        constexpr bool consume_word(std::span<Word const> word_list) noexcept {
            if (!remaining.empty()) {
                for (auto const& word : word_list) {
                    if (remaining.starts_with(word)) {
                        *this += word.size();
                        return true;
                    }
                }
            }
            return false;
        }

        constexpr char8_t consume_one_of(StringView list) noexcept {
            if (!remaining.empty()) {
                for (auto const c : list) {
                    if (remaining.front() == c) {
                        *this += 1;
                        return c;
                    }
                }
            }
            return 0x00u;
        }

        constexpr StringView take(size_t n) noexcept {
            if (size() < n) {
                return remaining.substr(0, 0);
            } else {
                auto result = remaining.substr(0, n);
                *this += n;
                return result;
            }
        }
    };

    static void write_utf8(String& out, char32_t value) noexcept {
        if (value < 0x80) {
            out += {(char8_t)value};
        } else if (value < 0x800) {
            out += {
                (char8_t)(((value >> 6) & 0b000011111) | 0b11000000),
                (char8_t)(((value)&0b00111111) | 0b10000000),
            };
        } else if (value < 0x10000) {
            out += {
                (char8_t)(((value >> 12) & 0b000001111) | 0b11100000),
                (char8_t)(((value >> 6) & 0b00111111) | 0b10000000),
                (char8_t)(((value)&0b00111111) | 0b10000000),
            };
        } else if (value < 0x10FFFF) {
            out += {
                (char8_t)(((value >> 18) & 0b00000111) | 0b11110000),
                (char8_t)(((value >> 12) & 0b00111111) | 0b10000000),
                (char8_t)(((value >> 6) & 0b00111111) | 0b10000000),
                (char8_t)(((value)&0b00111111) | 0b10000000),
            };
        } else {
            out += {(char8_t)0xEF, (char8_t)0xBF, (char8_t)0xBD};
        }
    }
} // namespace JsonImpl

// Reader
namespace JsonImpl {
    struct JsonReader {
        StringIterator iter;
        int depth;
        std::string copy = {};

    private:
        void assert(bool what, char const* msg, ptrdiff_t back = 0) {
            if (!what) {
                if (back) {
                    iter -= back;
                }
                throw msg;
            }
        }

        void skip_whitespace() {
            while (!iter.empty()) {
                if (iter.consume_word(u8"//") || iter.consume_word(u8"#")) {
                    while (!iter.empty() && !iter.consume_word(NEWLINE_TERMINATOR)) {
                        iter += 1;
                    }
                } else if (iter.consume_word(u8"/*")) {
                    size_t comments = 1;
                    while (comments) {
                        assert(!iter.empty(), "Unexpected EOF in multiline comment!");
                        if (iter.consume_word(u8"*/")) {
                            --comments;
                        } else if (iter.consume_word(u8"/*")) {
                            ++comments;
                        } else {
                            iter += 1;
                        }
                    }
                } else if (iter.consume_word(u8"/")) {
                    assert(false, "Incomplete comment start!");
                } else if (!iter.consume_word(WHITESPACE)) {
                    break;
                }
            }
        }

        uint32_t read_hex_escape(size_t size) {
            auto const data = iter.take(size);
            assert(data.size() == size, "Unexpected EOF in hex escape!");
            auto const start = (char const*)data.data();
            auto const end = (char const*)data.data() + size;
            uint32_t value = {};
            auto const p = std::from_chars(start, end, value, 16);
            assert(p.ec == std::errc{} && p.ptr == end, "Bad hex escape!", end - p.ptr);
            return value;
        }

        void read_unicode_escapes(String& result) {
            char32_t last = 0;
            while (!iter.empty() && iter.consume_word(u8"\\u")) {
                uint32_t value = read_hex_escape(4);
                if (value >= 0xDC00u && value <= 0xDFFFu) {
                    if (last) {
                        write_utf8(result, (((last - 0xD800u) << 10) | (value - 0xDC00u)) + 0x10000u);
                        last = 0;
                    } else {
                        write_utf8(result, value);
                    }
                } else {
                    if (last) {
                        write_utf8(result, last);
                        last = 0;
                    }
                    if (value >= 0xD800u && value <= 0xDBFFu) {
                        last = value;
                    } else {
                        write_utf8(result, value);
                    }
                }
            }
            if (last) {
                write_utf8(result, last);
            }
        }

        String read_quoted_string(StringView quote) {
            String result = {};
            for (;;) {
                read_unicode_escapes(result);
                assert(!iter.empty(), "Unexpected EOF in string!");
                if (iter.consume_word(u8"\\0")) {
                    result.push_back(u8'\0');
                } else if (iter.consume_word(u8"\\a")) {
                    result.push_back(u8'\a');
                } else if (iter.consume_word(u8"\\b")) {
                    result.push_back(u8'\b');
                } else if (iter.consume_word(u8"\\f")) {
                    result.push_back(u8'\f');
                } else if (iter.consume_word(u8"\\n")) {
                    result.push_back(u8'\n');
                } else if (iter.consume_word(u8"\\r")) {
                    result.push_back(u8'\r');
                } else if (iter.consume_word(u8"\\t")) {
                    result.push_back(u8'\t');
                } else if (iter.consume_word(u8"\\v")) {
                    result.push_back(u8'\v');
                } else if (iter.consume_word(u8"\\x")) {
                    uint32_t value = read_hex_escape(2);
                    write_utf8(result, value);
                } else if (iter.consume_word(quote)) {
                    break;
                } else {
                    if (iter.consume_word(u8"\\")) {
                        assert(!iter.empty(), "Unexpected EOF in string escape!");
                        if (iter.consume_word(u8"\r")) {
                            iter.consume_word(NEWLINE);
                            continue;
                        } else if (iter.consume_word(NEWLINE)) {
                            continue;
                        }
                    }
                    auto character = iter.pop_character();
                    write_utf8(result, character);
                }
            }
            return result;
        }

        String read_ident() {
            String result = {};
            for (;;) {
                read_unicode_escapes(result);
                if (iter.empty() || iter.is_word(WHITESPACE)) {
                    break;
                } else if (auto one = iter.consume_one_of(IDENT_ASCII)) {
                    result.push_back(one);
                } else if (iter.is_ascii()) {
                    break;
                } else {
                    auto const character = iter.pop_character();
                    write_utf8(result, character);
                }
            }
            assert(!result.empty(), "Bad identifier!");
            return result;
        }

        String read_quoted_string_or_ident() {
            if (iter.consume_word(u8"'")) {
                return read_quoted_string(u8"'");
            } else if (iter.consume_word(u8"\"")) {
                return read_quoted_string(u8"\"");
            } else if (iter.consume_word(u8"`")) {
                return read_quoted_string(u8"`");
            } else {
                return read_ident();
            }
        }

        Json read_num() {
            // TODO: properly consume number characters
            copy.clear();
            while (!iter.empty()) {
                if (auto one = iter.consume_one_of(NUMBER_PART)) {
                    copy.push_back((char)one);
                } else {
                    break;
                }
            }
            assert(!copy.empty(), "Bad character!");
            Number out = {};
            unsigned int count = {};
            auto result = sscanf(copy.data(), "%lg%n", &out, &count);
            assert(result == 1 && count == copy.size(), "Bad number!", copy.size() - count);
            return out;
        }

        void next_token(char const* msg) {
            skip_whitespace();
            assert(!iter.empty(), msg);
        }

        Array read_array() {
            assert(depth > 0, "Max depth reached!");
            auto array = Json::Array();
            depth--;
            for (;;) {
                next_token("Unexpected EOF in array!");
                if (iter.consume_word(u8"]")) {
                    break;
                }
                array.emplace_back(read_value());
                next_token("Unexpected EOF in array!");
                if (!iter.consume_word(u8",")) {
                    assert(iter.consume_word(u8"]"), "Bad array value separator!");
                    break;
                }
            }
            depth++;
            return array;
        }

        Object read_object() {
            assert(depth > 0, "Max depth reached!");
            auto object = Json::Object();
            depth--;
            for (;;) {
                next_token("Unexpected EOF in object!");
                if (iter.consume_word(u8"}")) {
                    break;
                }
                auto key = read_quoted_string_or_ident();
                next_token("Unexpected EOF in object!");
                assert(iter.consume_word(u8":"), "Bad object key separator!");
                next_token("Unexpected EOF in object!");
                object.insert_or_assign(key, read_value());
                next_token("Unexpected EOF in object!");
                if (!iter.consume_word(u8",")) {
                    assert(iter.consume_word(u8"}"), "Bad object separator!");
                    break;
                }
            }
            depth++;
            return object;
        }

        Json read_value() {
            if (iter.consume_word(u8"null")) {
                return Null{};
            } else if (iter.consume_word(u8"false")) {
                return Json(false);
            } else if (iter.consume_word(u8"true")) {
                return Json(true);
            } else if (iter.consume_word(u8"[")) {
                return read_array();
            } else if (iter.consume_word(u8"{")) {
                return read_object();
            } else if (iter.consume_word(u8"'")) {
                return read_quoted_string(u8"'");
            } else if (iter.consume_word(u8"\"")) {
                return read_quoted_string(u8"\"");
            } else if (iter.consume_word(u8"`")) {
                return read_quoted_string(u8"`");
            } else if (iter.consume_word(u8"NaN") || iter.consume_word(u8"-NaN") || iter.consume_word(u8"+NaN")) {
                return std::numeric_limits<Json::Number>::quiet_NaN();
            } else if (iter.consume_word(u8"Infinity")) {
                return std::numeric_limits<Json::Number>::infinity();
            } else if (iter.consume_word(u8"-Infinity")) {
                return -std::numeric_limits<Json::Number>::infinity();
            } else {
                return read_num();
            }
        }

    public:
        Json read() {
            next_token("Unexpected EOF in json!");
            auto result = read_value();
            skip_whitespace();
            if (!iter.empty()) {
                throw "Unread data remaining!";
            }
            return result;
        }
    };
} // namespace JsonImpl

Json Json::loads(StringView data, int max_depth) {
    JsonImpl::JsonReader reader{data, max_depth};
    try {
        return reader.read();
    } catch (char const* msg) {
        JsonImpl::StringIterator iter = reader.iter.view_consumed();
        size_t line = 0;
        size_t column = 0;
        while (!iter.empty()) {
            if (iter.consume_word(JsonImpl::NEWLINE)) {
                ++line;
                column = 0;
            } else {
                ++column;
            }
            iter.pop_character();
        }
        throw ReadError(msg, line, column);
    }
}

// Writer
namespace JsonImpl {
    struct JsonWriter {
    public:
        String buffer = {};
        size_t indent_size = 4;
        size_t indent_level = 0;

    private:
        void indent() {
            if (indent_size) {
                buffer.push_back('\n');
                buffer.insert(buffer.end(), indent_level, ' ');
            }
        }

        void write_raw(StringView str) noexcept { buffer.insert(buffer.end(), str.cbegin(), str.cend()); }

        void write_value(Null) noexcept { write_raw(u8"null"); }

        void write_value(Boolean const& value) noexcept { write_raw(value ? u8"true" : u8"false"); }

        void write_value(Number const& value) noexcept {
            char8_t tmp[128] = {};
            if (std::isnan(value)) {
                write_raw(u8"NaN");
            } else if (std::isinf(value)) {
                if (value < 0.0) {
                    write_raw(u8"-Infinity");
                } else {
                    write_raw(u8"Infinity");
                }
            } else if (int64_t simple = (int64_t)value; (Number)simple == value) {
                auto const result = std::to_chars((char*)tmp, (char*)(tmp + sizeof(tmp)), simple, 10);
                write_raw({tmp, (size_t)(result.ptr - (char*)tmp)});
            } else {
                auto const size = sprintf((char*)tmp, "%.15lg", value);
                write_raw({tmp, (size_t)size});
            }
        }

        void write_value(String const& value) noexcept {
            write_raw(u8"\"");
            StringIterator iter(value);
            while (!iter.empty()) {
                if (iter.consume_word(u8"\t")) {
                    write_raw(u8"\\t");
                } else if (iter.consume_word(u8"\v")) {
                    write_raw(u8"\\v");
                } else if (iter.consume_word(u8"\n")) {
                    write_raw(u8"\\n");
                } else if (iter.consume_word(u8"\r")) {
                    write_raw(u8"\\r");
                } else if (iter.consume_word(u8"\b")) {
                    write_raw(u8"\\b");
                } else if (iter.consume_word(u8"\f")) {
                    write_raw(u8"\\f");
                } else if (iter.consume_word(u8"\a")) {
                    write_raw(u8"\\a");
                } else if (iter.consume_word(u8"\\")) {
                    write_raw(u8"\\\\");
                } else if (iter.consume_word(u8"\"")) {
                    write_raw(u8"\\\"");
                } else {
                    constexpr char8_t const digits[] = u8"0123456789ABCDEF";
                    auto c = iter.pop_character();
                    if (c < 0x20u) {
                        char8_t const hex[] = {u8'\\', u8'x', digits[(c >> 4) & 0x0Fu], digits[c & 0x0Fu], u8'\0'};
                        write_raw(hex);
                    } else if (c <= 0x7Fu) {
                        char8_t const raw[] = {(char8_t)c, u8'\0'};
                        write_raw(raw);
                    } else if (c <= 0xFFFFu) {
                        char8_t const hex[] = {u8'\\',
                                               u8'u',
                                               digits[(c >> 12) & 0x0Fu],
                                               digits[(c >> 8) & 0x0Fu],
                                               digits[(c >> 4) & 0x0Fu],
                                               digits[c & 0x0Fu],
                                               u8'\0'};
                        write_raw(hex);
                    } else {
                        auto l = ((c - 0x10000u) >> 10u) + 0xD800u;
                        auto h = ((c - 0x10000u) & 0x3FFu) + 0xDC00u;
                        char8_t const hex[] = {u8'\\',
                                               u8'u',
                                               digits[(l >> 12) & 0x0Fu],
                                               digits[(l >> 8) & 0x0Fu],
                                               digits[(l >> 4) & 0x0Fu],
                                               digits[l & 0x0Fu],
                                               u8'\\',
                                               u8'u',
                                               digits[(h >> 12) & 0x0Fu],
                                               digits[(h >> 8) & 0x0Fu],
                                               digits[(h >> 4) & 0x0Fu],
                                               digits[h & 0x0Fu],
                                               u8'\0'};
                        write_raw(hex);
                    }
                }
            }
            write_raw(u8"\"");
        }

        void write_value(Array const& value) noexcept {
            if (value.empty()) {
                write_raw(u8"[]");
            } else {
                write_raw(u8"[");
                indent_level += indent_size;
                for (auto i = value.begin(); i != value.end();) {
                    indent();
                    write_value(*i);
                    i++;
                    if (i != value.end()) {
                        write_raw(u8",");
                    }
                }
                indent_level -= indent_size;
                indent();
                write_raw(u8"]");
            }
        }

        void write_value(Object const& value) noexcept {
            if (value.empty()) {
                write_raw(u8"{}");
            } else {
                write_raw(u8"{");
                indent_level += indent_size;
                for (auto i = value.begin(); i != value.end();) {
                    indent();
                    write_value(i->first);
                    write_raw(indent_size ? u8": " : u8":");
                    write_value(i->second);
                    i++;
                    if (i != value.end()) {
                        write_raw(u8",");
                    }
                }
                indent_level -= indent_size;
                indent();
                write_raw(u8"}");
            }
        }

    public:
        void write_value(Json const& json) noexcept {
            json.visit([this](auto const& value) { write_value(value); });
        }
    };
} // namespace JsonImpl
String Json::dumps(size_t indent) const noexcept {
    JsonImpl::JsonWriter writer{{}, indent, {}};
    writer.write_value(*this);
    return writer.buffer;
}
