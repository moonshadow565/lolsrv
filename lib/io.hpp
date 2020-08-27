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

    void read_raw(void* data, size_t size);

    template<typename C, typename T>
    inline void read_num(T& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            read_raw(&value, sizeof(value));
        } else {
            C result;
            read_raw(&result, sizeof(result));
            value = static_cast<std::remove_cvref_t<T>>(result);
        }
    }

    void read_point2d(r3dPoint2D& value);

    void read_point3d(r3dPoint3D& value);

    template<typename C, typename T, size_t S>
    inline void read_num_array(T(&array)[S]) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            read_raw(array, sizeof(array));
        } else {
            for(auto& value: array) {
                read_num<C>(value);
            }
        }
    }

    void read_pad(size_t S);

    void read_zstr(std::string& value);

    void read_fstr(std::string& value, size_t S);

    void read_sstr(std::string& value);

    void read_szstr(std::string& value);

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

    void write_raw(void const* data, size_t size);

    template<typename C, typename T>
    inline void write_num(T const& value) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            write_raw(&value, sizeof(value));
        } else {
            C result = static_cast<C>(value);
            write_raw(&result, sizeof(result));
        }
    }

    void write_point2d(r3dPoint2D const& value);

    void write_point3d(r3dPoint3D const& value);

    template<typename C, typename T, size_t S>
    inline void write_num_array(T const(&array)[S]) {
        static_assert (std::is_arithmetic_v<T> || std::is_enum_v<T>);
        static_assert (std::is_arithmetic_v<C> || std::is_enum_v<C>);
        if constexpr(std::is_same_v<C, std::remove_cvref_t<T>>) {
            write_raw(array, sizeof(array));
        } else {
            for(auto const& value: array) {
                write_num<C>(value);
            }
        }
    }

    void write_pad(size_t S);

    void write_zstr(std::string const& value) {
        size_t const cur = buffer.size();
        size_t const size = value.size() + 1;
        buffer.resize(cur + size);
        std::memcpy(buffer.data() + cur, value.data(), size);
    }

    void write_fstr(std::string const& value, size_t S);

    void write_sstr(std::string const& value);

    void write_szstr(std::string const& value);

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
