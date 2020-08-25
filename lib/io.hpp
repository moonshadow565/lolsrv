#pragma once
#include <cinttypes>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>
#include <r3d.hpp>
#include <stdexcept>

struct IOError : std::exception {
    ptrdiff_t position = {};
    inline IOError(ptrdiff_t aposition) : position(aposition) {};
};

template<typename C, size_t S, typename T>
struct Field {
    using cast = C;
    static inline constexpr auto size = S;
    using type = std::remove_cvref_t<T>;
    static_assert(std::is_integral_v<type> || std::is_enum_v<type>);
    static_assert(std::is_integral_v<cast>);
    static_assert(size <= (sizeof(cast) * 8));
    static inline constexpr auto bits_left = (sizeof(cast) * 8) - size;
    static inline constexpr auto mask = std::numeric_limits<std::make_unsigned_t<cast>>::max() >> bits_left;
    T value;
};

template<typename C, size_t S, typename T>
inline constexpr auto field(T&& value) { return Field<C, S, T>{value}; }

struct Data_in {
    char const* start = {};
    char const* cur = {};
    char const* end = {};

    inline constexpr Data_in(char const* data, size_t size) noexcept
        : start(data), cur(data), end(data + size) {}

    inline ptrdiff_t left() const noexcept {
        return end - cur;
    }

    inline ptrdiff_t position() const noexcept {
        return cur - start;
    }

    inline void check_space(size_t size) const {
        if ((ptrdiff_t)size > left()) {
            throw IOError(position());
        }
    }

    template<typename C, typename T>
    inline void read_num(T& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        check_space(sizeof(C));
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            std::memcpy(&value, cur, sizeof(C));
        } else {
            C result = {};
            std::memcpy(&result, cur, sizeof(C));
            value = static_cast<std::remove_cvref_t<T>>(result);
        }
        cur += sizeof(C);
    }

    inline void read_point2d(r3dPoint2D& value) {
        check_space(sizeof(r3dPoint2D));
        std::memcpy(&value, cur, sizeof(r3dPoint2D));
        cur += sizeof(r3dPoint2D);
    }

    inline void read_point3d(r3dPoint3D& value) {
        check_space(sizeof(r3dPoint3D));
        std::memcpy(&value, cur, sizeof(r3dPoint3D));
        cur += sizeof(r3dPoint3D);
    }

    template<typename C, typename T, size_t S>
    inline void read_num_array(T(&array)[S]) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        check_space(sizeof(C) * S);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            std::memcpy(array, cur, sizeof(C) * S);
            cur += sizeof(C) * S;
        } else {
            for(auto& value: array) {
                C result = {};
                std::memcpy(&result, cur, sizeof(C));
                cur += sizeof(C);
                value = static_cast<std::remove_cvref_t<T>>(result);
            }
        }
    }

    template<typename C, typename T, size_t S>
    inline void read_num_array(std::array<T, S>& array) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        check_space(sizeof(C) * S);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            std::memcpy(array.data(), cur, sizeof(C) * S);
            cur += sizeof(C) * S;
        } else {
            for(auto& value: array) {
                C result = {};
                std::memcpy(&result, cur, sizeof(C));
                cur += sizeof(C);
                value = static_cast<std::remove_cvref_t<T>>(result);
            }
        }
    }

    template<size_t S>
    inline void read_pad() {
        check_space(S);
        cur += S;
    }

    inline void read_zstr(std::string& value) {
        value.clear();
        while (cur != end) {
            char c = *cur;
            cur++;
            if (c == '\0') {
                break;
            }
            value.push_back(c);
        }
    }

    template<size_t S>
    inline void read_fstr(std::string& value) {
        check_space(S);
        value.resize(S);
        value.clear();
        std::memcpy(value.data(), cur, S);
        cur += S;
        auto const zero = value.find('\0');
        if (zero != std::string::npos) {
            value.resize((size_t)zero);
        }
    }

    template<typename S>
    inline void read_sstr(std::string& value) {
        S size = {};
        read_num<S>(size);
        value.resize(size);
        value.clear();
        if (size > 0) {
            std::memcpy(value.data(), cur, size);
        }
        cur += size;
        auto const zero = value.find('\0');
        if (zero != std::string::npos) {
            value.resize((size_t)zero);
        }
    }

    template<typename S>
    inline void read_szstr(std::string& value) {
        return read_sstr<S>(value);
    }

    template<typename B, typename...C, size_t...S, typename...T>
    inline void read_bit(Field<C, S, T>...values) {
        static_assert(sizeof(B) * 8 >= (S + ...));
        B buffer = {};
        read_num<B>(buffer);
        auto read_one = [&buffer] (auto field) mutable {
            using F = decltype(field);
            auto result = static_cast<typename F::cast>(buffer & F::mask);
            if constexpr(std::is_signed_v<typename F::cast>) {
                result <<= F::bits_left;
                result >>= F::bits_left;
            }
            field.value = static_cast<typename F::type>(result);
            buffer >>= F::size;
        };
        (read_one(values), ...);
    };

    template<typename F>
    inline void read_until_end(F func) {
        while(cur != end) {
            func();
        }
    }
};

struct Data_out {
    std::vector<char> buffer = {};

    template<typename C, typename T>
    inline void write_num(T const& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        size_t const cur = buffer.size();
        buffer.resize(cur + sizeof(C));
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            std::memcpy(buffer.data() + cur, &value, sizeof(C));
        } else {
            C result = static_cast<C>(value);
            std::memcpy(buffer.data() + cur, &result, sizeof(C));
        }
    }

    inline void write_point2d(r3dPoint2D const& value) {
        size_t const cur = buffer.size();
        buffer.resize(cur + sizeof(r3dPoint2D));
        std::memcpy(buffer.data() + cur, &value, sizeof(r3dPoint2D));
    }

    inline void write_point3d(r3dPoint3D const& value) {
        size_t const cur = buffer.size();
        buffer.resize(cur + sizeof(r3dPoint3D));
        std::memcpy(buffer.data() + cur, &value, sizeof(r3dPoint3D));
    }

    template<typename C, typename T, size_t S>
    inline void write_num_array(T const(&array)[S]) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            size_t const cur = buffer.size();
            buffer.resize(cur + sizeof(C) * S);
            std::memcpy(buffer.data() + cur, array, sizeof(C) * S);
        } else {
            for(auto const& value: array) {
                C result = static_cast<C>(value);
                size_t const cur = buffer.size();
                buffer.resize(cur + sizeof(C));
                std::memcpy(buffer.data() + cur, &result, sizeof(C));
            }
        }
    }

    template<typename C, typename T, size_t S>
    inline void write_num_array(std::array<T, S> const& array) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            size_t const cur = buffer.size();
            buffer.resize(cur + sizeof(C) * S);
            std::memcpy(buffer.data() + cur, array.data(), sizeof(C) * S);
        } else {
            for(auto const& value: array) {
                C result = static_cast<C>(value);
                size_t const cur = buffer.size();
                buffer.resize(cur + sizeof(C));
                std::memcpy(buffer.data() + cur, &result, sizeof(C));
            }
        }
    }

    template<size_t S>
    inline void write_pad() {
        size_t const cur = buffer.size();
        buffer.resize(cur + S);
    }

    inline void write_zstr(std::string const& value) {
        size_t const cur = buffer.size();
        size_t const size = value.size() + 1;
        buffer.resize(cur + size);
        std::memcpy(buffer.data() + cur, value.data(), size);
    }

    template<size_t S>
    inline void write_fstr(std::string const& value) {
        size_t const cur = buffer.size();
        size_t const size = value.size();
        if ((size + 1) > S) {
            throw IOError(cur);
        }
        buffer.resize(cur + S);
        std::memcpy(buffer.data() + cur, value.data(), size);
        std::memset(buffer.data() + cur + size, 0, S - size);
    }

    template<typename S>
    inline void write_sstr(std::string const& value) {
        size_t const size = value.size();
        write_num<S>(size);
        size_t const cur = buffer.size();
        buffer.resize(cur + size);
        std::memcpy(buffer.data() + cur, value.data(), size);
    }

    template<typename S>
    inline void write_szstr(std::string const& value) {
        size_t const size = value.size() + 1;
        write_num<S>(size);
        size_t const cur = buffer.size();
        buffer.resize(cur + size);
        std::memcpy(buffer.data() + cur, value.data(), size);
    }

    template<typename B, typename...C, size_t...S, typename...T>
    inline void write_bit(Field<C, S, T>...values) {
        static_assert(sizeof(B) * 8 >= (S + ...));
        B buffer = {};
        auto write_one = [&buffer, done = size_t{0}] (auto field) mutable {
            using F = decltype(field);
            buffer |= static_cast<B>(static_cast<typename F::cast>(field.value) & F::mask) << done;
            done += F::size;
        };
        (write_one(values), ...);
        write_num<B>(buffer);
    }
};
