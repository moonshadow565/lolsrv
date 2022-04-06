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
For more information, please geter to <http://unlicense.org/>
✂--------------------------------[ Cut here ]----------------------------------
*/
#pragma once
#include <array>
#include <cmath>
#include <compare>
#include <functional>
#include <initializer_list>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

struct Json final {
public: // Basic json values
    using Null = std::nullptr_t;
    using Boolean = bool;
    using Number = double;
    using String = std::u8string;
    using StringView = std::u8string_view;
    using Array = std::vector<Json>;
    using Object = std::map<String, Json>;
    template <typename T>
    static inline constexpr bool is_basic_type() noexcept {
        return std::is_same_v<T, Null> || std::is_same_v<T, Boolean> || std::is_same_v<T, Number> ||
               std::is_same_v<T, String> || std::is_same_v<T, Array> || std::is_same_v<T, Object>;
    }

private: // Discriminated union
    enum class Tag {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object,
    } tag = {Tag::Null};
    union Value {
        Null null;
        Boolean boolean;
        Number number;
        String* string;
        Array* array;
        Object* object;
    } value = {.null = nullptr};

public: // Value semantics with deep copy
    constexpr inline Json() noexcept = default;
    inline ~Json() noexcept {
        switch (tag) {
        default:
        case Tag::Null:
        case Tag::Boolean:
        case Tag::Number:
            break;
        case Tag::String:
            delete value.string;
            break;
        case Tag::Array:
            delete value.array;
            break;
        case Tag::Object:
            delete value.object;
            break;
        }
        tag = Tag::Null;
        value.null = Null{};
    }
    inline Json(Json&& other) noexcept : tag{other.tag}, value{other.value} {
        other.tag = Tag::Null;
        other.value.null = Null{};
    }
    inline Json(Json const& other) noexcept : tag{other.tag} {
        switch (tag) {
        case Tag::Null:
        case Tag::Boolean:
        case Tag::Number:
            value = other.value;
            break;
        case Tag::String:
            value.string = new String(*other.value.string);
            break;
        case Tag::Array:
            value.array = new Array(*other.value.array);
            break;
        case Tag::Object:
            value.object = new Object(*other.value.object);
            break;
        }
    }
    inline Json& operator=(Json&& other) noexcept {
        Json tmp(std::move(other));
        std::swap(tag, tmp.tag);
        std::swap(value, tmp.value);
        return *this;
    }
    inline Json& operator=(Json const& other) noexcept {
        Json tmp(other);
        std::swap(tag, tmp.tag);
        std::swap(value, tmp.value);
        return *this;
    }

public: // Basic value conversion and assignment
    template <typename T>
    Json(T const*) = delete;
    inline Json(Null) noexcept : tag{Tag::Null}, value{.null = nullptr} {}
    inline Json(bool other) noexcept : tag{Tag::Boolean}, value{.boolean = other} {}
    inline Json(Number other) noexcept : tag{Tag::Number}, value{.number = other} {}
    template <typename T>
    inline Json(T other) noexcept requires(std::is_arithmetic_v<T>) : Json(static_cast<Number>(other)) {}
    inline Json(String&& other) noexcept : tag{Tag::String}, value{.string = new String(std::move(other))} {}
    inline Json(String const& other) noexcept : tag{Tag::String}, value{.string = new String(other)} {}
    inline Json(StringView other) noexcept : tag{Tag::String}, value{.string = new String(other)} {}
    inline Json(Array&& other) noexcept : tag{Tag::Array}, value{.array = new Array(std::move(other))} {}
    inline Json(Array const& other) noexcept : tag{Tag::Array}, value{.array = new Array(other)} {}
    inline Json(Object&& other) noexcept : tag{Tag::Object}, value{.object = new Object(std::move(other))} {}
    inline Json(Object const& other) noexcept : tag{Tag::Object}, value{.object = new Object(other)} {}

    template <typename T>
    Json& operator=(T const*) = delete;
    inline Json& operator=(Null) noexcept {
        if (tag == Tag::Null) {
            return *this;
        }
        return *this = Json();
    }
    inline Json& operator=(bool other) noexcept {
        if (tag == Tag::Boolean) {
            value.boolean = other;
            return *this;
        }
        return *this = Json(other);
    }
    inline Json& operator=(Number other) noexcept {
        if (tag == Tag::Number) {
            value.number = other;
            return *this;
        }
        return *this = Json(other);
    }
    template <typename T>
    inline Json& operator=(T other) noexcept requires(std::is_arithmetic_v<T>) {
        return *this = static_cast<Number>(other);
    }
    inline Json& operator=(String&& other) noexcept {
        if (tag == Tag::String) {
            *value.string = std::move(other);
            return *this;
        }
        return *this = Json(std::move(other));
    }
    inline Json& operator=(String const& other) noexcept {
        if (tag == Tag::String) {
            *value.string = other;
            return *this;
        }
        return *this = Json(other);
    }
    inline Json& operator=(StringView other) noexcept {
        if (tag == Tag::String) {
            *value.string = other;
            return *this;
        }
        return *this = Json(other);
    }
    inline Json& operator=(Array&& other) noexcept {
        if (tag == Tag::Array) {
            *value.array = std::move(other);
            return *this;
        }
        return *this = Json(std::move(other));
    }
    inline Json& operator=(Array const& other) noexcept {
        if (tag == Tag::Array) {
            *value.array = other;
            return *this;
        }
        return *this = Json(other);
    }
    inline Json& operator=(Object&& other) noexcept {
        if (tag == Tag::Object) {
            *value.object = std::move(other);
            return *this;
        }
        return *this = Json(std::move(other));
    }
    inline Json& operator=(Object const& other) noexcept {
        if (tag == Tag::Object) {
            *value.object = other;
            return *this;
        }
        return *this = Json(other);
    }

    template <typename... T>
    static inline Json make_array(T&&... values) {
        return Array{{std::forward<decltype(values)>(values)...}};
    }

public: // Value access and manipulation
    template <typename T>
    requires(is_basic_type<T>()) inline bool is() const noexcept {
        if constexpr (std::is_same_v<T, Null>) {
            return tag == Tag::Null;
        } else if constexpr (std::is_same_v<T, Boolean>) {
            return tag == Tag::Boolean;
        } else if constexpr (std::is_same_v<T, Number>) {
            return tag == Tag::Number;
        } else if constexpr (std::is_same_v<T, String>) {
            return tag == Tag::String;
        } else if constexpr (std::is_same_v<T, Array>) {
            return tag == Tag::Array;
        } else {
            return tag == Tag::Object;
        }
    }

    template <typename T>
    inline T* ptr() noexcept requires(is_basic_type<T>()) {
        if constexpr (std::is_same_v<T, Null>) {
            return &value.null;
        } else if constexpr (std::is_same_v<T, Boolean>) {
            return &value.boolean;
        } else if constexpr (std::is_same_v<T, Number>) {
            return &value.number;
        } else if constexpr (std::is_same_v<T, String>) {
            return value.string;
        } else if constexpr (std::is_same_v<T, Array>) {
            return value.array;
        } else {
            return value.object;
        }
    }
    template <typename T>
    inline T const* ptr() const noexcept requires(is_basic_type<T>()) {
        if constexpr (std::is_same_v<T, Null>) {
            return &value.null;
        } else if constexpr (std::is_same_v<T, Boolean>) {
            return &value.boolean;
        } else if constexpr (std::is_same_v<T, Number>) {
            return &value.number;
        } else if constexpr (std::is_same_v<T, String>) {
            return value.string;
        } else if constexpr (std::is_same_v<T, Array>) {
            return value.array;
        } else {
            return value.object;
        }
    }

    template <typename T>
    inline T& ref() noexcept requires(is_basic_type<T>()) {
        return *ptr<T>();
    }
    template <typename T>
    inline T const& ref() const noexcept requires(is_basic_type<T>()) {
        return *ptr<T>();
    }

    template <typename T>
    inline T& get() requires(is_basic_type<T>()) {
        if (!is<T>()) {
            throw std::bad_cast();
        }
        return ref<T>();
    }
    template <typename T>
    inline T const& get() const requires(is_basic_type<T>()) {
        if (!is<T>()) {
            throw std::bad_cast();
        }
        return ref<T>();
    }

    template <typename T>
    inline T* get_if() noexcept requires(is_basic_type<T>()) {
        return is<T>() ? ptr<T>() : nullptr;
    }
    template <typename T>
    inline T const* get_if() const noexcept requires(is_basic_type<T>()) {
        return is<T>() ? ptr<T>() : nullptr;
    }

    template <typename F>
    inline auto visit(F&& func) -> decltype(auto) {
        switch (tag) {
        default:
        case Tag::Null:
            return std::forward<F>(func)(ref<Null>());
        case Tag::Boolean:
            return std::forward<F>(func)(ref<Boolean>());
        case Tag::Number:
            return std::forward<F>(func)(ref<Number>());
        case Tag::String:
            return std::forward<F>(func)(ref<String>());
        case Tag::Array:
            return std::forward<F>(func)(ref<Array>());
        case Tag::Object:
            return std::forward<F>(func)(ref<Object>());
        }
    }
    template <typename F>
    inline auto visit(F&& func) const -> decltype(auto) {
        switch (tag) {
        default:
        case Tag::Null:
            return std::forward<F>(func)(ref<Null>());
        case Tag::Boolean:
            return std::forward<F>(func)(ref<Boolean>());
        case Tag::Number:
            return std::forward<F>(func)(ref<Number>());
        case Tag::String:
            return std::forward<F>(func)(ref<String>());
        case Tag::Array:
            return std::forward<F>(func)(ref<Array>());
        case Tag::Object:
            return std::forward<F>(func)(ref<Object>());
        }
    }

    template <typename T, typename... Args>
    inline T& emplace(Args&&... args) noexcept requires(is_basic_type<T>()) {
        *this = T(std::forward<Args>(args)...);
        return ref<T>();
    }

public: // Container operations
    inline bool contains(String const& key) const noexcept { return is<Object>() && ref<Object>().contains(key); }
    inline bool contains(size_t index) const noexcept { return is<Array>() && ref<Array>().size() < index; }

    inline Json& at(String const& key) { return get<Object>().at(key); }
    inline Json const& at(String const& key) const { return get<Object>().at(key); }

    inline Json& at(size_t index) { return get<Array>().at(index); }
    inline Json const& at(size_t index) const { return get<Array>().at(index); }

    inline Json& operator[](String const& key) { return get<Object>()[key]; }
    inline Json& operator[](size_t index) {
        auto& array = get<Array>();
        if (array.size() <= index) {
            array.resize(index + 1);
        }
        return array[index];
    }

public: // Comparison
    inline bool operator!() const noexcept {
        switch (tag) {
        default:
        case Tag::Null:
            return true;
        case Tag::Boolean:
            return !value.boolean;
        case Tag::Number:
            return value.number == 0.0 || std::isnan(value.number);
        case Tag::String:
            return value.string->empty();
        case Tag::Array:
            return false;
        case Tag::Object:
            return false;
        }
    }
    inline bool operator==(Null) const noexcept { return is<Null>(); }
    inline bool operator==(Boolean other) const noexcept { return is<Boolean>() && ref<Boolean>() == other; }
    inline bool operator==(Number other) const noexcept { return is<Number>() && ref<Number>() == other; }
    template <typename T>
    inline bool operator==(T other) const noexcept requires(std::is_arithmetic_v<T>) {
        return is<Number>() && ref<Number>() == (Number)other;
    }
    inline bool operator==(String const& other) const noexcept { return is<String>() && ref<String>() == other; }
    inline bool operator==(StringView other) const noexcept { return is<String>() && ref<String>() == other; }
    inline bool operator==(Array const& other) const noexcept { return is<Array>() && ref<Array>() == other; }
    inline bool operator==(Object const& other) const noexcept { return is<Object>() && ref<Object>() == other; }
    inline bool operator==(Json const& other) const noexcept {
        return visit([&other](auto const& self) { return self == other; });
    }

private: // auto cast implementation
    struct IntoRef {
        Json const& json;
        template <typename T>
        inline operator T() const&& {
            T result{};
            json >> result;
            return result;
        }
    };

public: // conversion helpers
    template <typename T>
    inline static Json from(T&& other) {
        Json result;
        result << std::forward<T>(other);
        return result;
    }
    inline auto into() const { return IntoRef{*this}; }
    template <typename T>
    inline T into() const {
        T result{};
        *this >> result;
        return result;
    };

public: // Read write
    struct ReadError : public std::runtime_error {
        ReadError(char const* what, size_t aline, size_t acolumn) noexcept
            : std::runtime_error(std::string(what) + " @ " + std::to_string(aline) + ":" + std::to_string(acolumn)) {}
    };

    static Json loads(StringView buffer, int max_depth = 32);

    String dumps(size_t indent = 2) const noexcept;
};

inline void operator>>(Json const& json, Json::Null& value) { value = json.get<Json::Null>(); }
inline void operator<<(Json& json, Json::Null value) { json = value; }

inline void operator>>(Json const& json, Json::Boolean& value) { value = json.get<Json::Boolean>(); }
inline void operator<<(Json& json, Json::Boolean value) { json = value; }

template <typename T>
inline void operator>>(Json const& json, T& value) requires(std::is_arithmetic_v<T>) {
    value = static_cast<T>(json.get<Json::Number>());
}
template <typename T>
inline void operator<<(Json& json, T value) requires(std::is_arithmetic_v<T>) {
    json = static_cast<Json::Number>(value);
}

inline void operator>>(Json const& json, Json::String& value) { value = json.get<Json::String>(); }
inline void operator<<(Json& json, Json::String const& value) { json = value; }

inline void operator>>(Json const& json, Json::Array& value) { value = json.get<Json::Array>(); }
inline void operator<<(Json& json, Json::Array const& value) { json = value; }

template <typename T>
inline void operator>>(Json const& json, std::optional<T>& value) {
    if (json.is<Json::Null>()) {
        value = std::nullopt;
    } else {
        json >> value.emplace();
    }
}
template <typename T>
inline void operator<<(Json& json, std::optional<T> const& value) {
    if (!value) {
        json = Json::Null{};
    } else {
        json << *value;
    }
}

template <typename T>
inline void operator>>(Json const& json, std::shared_ptr<T>& value) {
    if (json.is<Json::Null>()) {
        value = nullptr;
    } else {
        json >> *(value = std::make_shared<T>());
    }
}
template <typename T>
inline void operator<<(Json& json, std::shared_ptr<T> const& value) {
    if (!value) {
        json = Json::Null{};
    } else {
        json << *value;
    }
}

template <typename T>
inline void operator>>(Json const& json, std::unique_ptr<T>& value) {
    if (json.is<Json::Null>()) {
        value = nullptr;
    } else {
        json >> *(value = std::make_unique<T>());
    }
}
template <typename T>
inline void operator<<(Json& json, std::unique_ptr<T> const& value) {
    if (!value) {
        json = Json::Null{};
    } else {
        json << *value;
    }
}

template <typename T>
inline void operator>>(Json const& json, std::vector<T>& value) {
    auto const& array = json.get<Json::Array>();
    value.clear();
    value.reserve(array.size());
    for (auto const& item : array) {
        item >> value.emplace_back();
    }
}
template <typename T>
inline void operator<<(Json& json, std::vector<T> const& value) {
    auto& array = json.emplace<Json::Array>();
    array.reserve(value.size());
    for (auto const& item : value) {
        array.emplace_back() << item;
    }
}

template <typename T>
inline void operator>>(Json const& json, std::list<T>& value) {
    auto const& array = json.get<Json::Array>();
    value.clear();
    for (auto const& item : array) {
        item >> value.emplace_back();
    }
}
template <typename T>
inline void operator<<(Json& json, std::list<T> const& value) {
    auto& array = json.emplace<Json::Array>();
    array.reserve(value.size());
    for (auto const& item : value) {
        array.emplace_back() << item;
    }
}

template <typename T, size_t S>
inline void operator>>(Json const& json, std::array<T, S>& value) {
    auto const& array = json.get<Json::Array>();
    if (array.size() != S) {
        throw std::out_of_range("Array >> std::array");
    }
    auto* data = value.data();
    for (auto const& item : array) {
        item >> (*data++);
    }
}
template <typename T, size_t S>
inline void operator<<(Json& json, std::array<T, S> const& value) {
    auto& array = json.emplace<Json::Array>();
    array.reserve(value.size());
    for (auto const& item : value) {
        array.emplace_back() << item;
    }
}

template <typename... T>
inline void operator>>(Json const& json, std::tuple<T...>& value) {
    auto const& array = json.get<Json::Array>();
    if (array.size() != sizeof...(T)) {
        throw std::out_of_range("Array >> std::tuple");
    }
    std::apply([item = array.data()](auto& data) mutable { (*item++) >> data; }, value);
}
template <typename... T>
inline void operator<<(Json& json, std::tuple<T...> const& value) {
    auto& array = json.emplace<Json::Array>();
    array.reserve(sizeof...(T));
    std::apply([&array](auto const& data) mutable { array.emplace_back() << data; }, value);
}

template <typename T>
inline void operator>>(Json const& json, std::map<Json::String, T>& value) {
    auto const& object = json.get<Json::Object>();
    value.clear();
    for (auto const& [key, item] : object) {
        item >> value[key];
    }
}
template <typename T>
inline void operator<<(Json& json, std::map<Json::String, T> const& value) {
    auto& object = json.emplace<Json::Object>();
    for (auto const& [key, item] : value) {
        object[key] << item;
    }
}

template <typename T>
inline void operator>>(Json const& json, std::unordered_map<Json::String, T>& value) {
    auto const& object = json.get<Json::Object>();
    value.clear();
    value.reserve(object.size());
    for (auto const& [key, item] : object) {
        item >> value[key];
    }
}
template <typename T>
inline void operator<<(Json& json, std::unordered_map<Json::String, T> const& value) {
    auto& object = json.emplace<Json::Object>();
    for (auto const& [key, item] : value) {
        object[key] << item;
    }
}
