#pragma once
#include <array>
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <r3d.hpp>
#include <span.hpp>

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

    void check_space(size_t size) const;

    void raw(void* data, size_t size);

    template<typename C, typename T>
    inline void num(T& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            raw(&value, sizeof(value));
        } else {
            C result;
            raw(&result, sizeof(result));
            value = static_cast<std::remove_cvref_t<T>>(result);
        }
    }

    void point2d(r3dPoint2D& value);

    void point3d(r3dPoint3D& value);

    template<typename C, typename T, size_t S>
    inline void num_array(std::array<T, S> &array) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            raw(array.data(), sizeof(array));
        } else {
            for(auto& value: array) {
                num<C>(value);
            }
        }
    }

    void pad(size_t S);

    void zstr(std::string& value);

    void fstr(std::string& value, size_t S);

    void sstr(std::string& value);

    void szstr(std::string& value);

    template<typename B, typename...C, size_t...S, typename...T>
    inline void bit(Field<C, S, T>...values) {
        static_assert(sizeof(B) * 8 >= (S + ...));
        B buffer = {};
        num<B>(buffer);
        auto one = [&buffer] (auto field) mutable {
            using F = decltype(field);
            auto result = static_cast<typename F::cast>(buffer & F::mask);
            if constexpr(std::is_signed_v<typename F::cast>) {
                result <<= F::bits_left;
                result >>= F::bits_left;
            }
            field.value = static_cast<typename F::type>(result);
            buffer >>= F::size;
        };
        (one(values), ...);
    };

    template<typename F>
    inline void until_end(F func) {
        while(cur != end) {
            func();
        }
    }
};

struct Data_out {
    std::vector<char> buffer = {};

    void raw(void const* data, size_t size);

    template<typename C, typename T>
    inline void num(T const& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            raw(&value, sizeof(value));
        } else {
            C result = static_cast<C>(value);
            raw(&result, sizeof(result));
        }
    }

    void point2d(r3dPoint2D const& value);

    void point3d(r3dPoint3D const& value);

    template<typename C, typename T, size_t S>
    inline void num_array(std::array<T, S> const& array) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            raw(array.data(), sizeof(array));
        } else {
            for(auto const& value: array) {
                num<C>(value);
            }
        }
    }

    void pad(size_t S);

    void zstr(std::string const& value);

    void fstr(std::string const& value, size_t S);

    void sstr(std::string const& value);

    void szstr(std::string const& value);

    template<typename B, typename...C, size_t...S, typename...T>
    inline void bit(Field<C, S, T>...values) {
        static_assert(sizeof(B) * 8 >= (S + ...));
        B buffer = {};
        auto one = [&buffer, done = size_t{0}] (auto field) mutable {
            using F = decltype(field);
            buffer |= static_cast<B>(static_cast<typename F::cast>(field.value) & F::mask) << done;
            done += F::size;
        };
        (one(values), ...);
        num<B>(buffer);
    }
};
