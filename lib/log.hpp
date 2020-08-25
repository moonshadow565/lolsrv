#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <string>
#include <span.hpp>
#include <charconv>

enum LogLevel : int32_t {
    LLOG_FATAL = 0,
    LLOG_INFO,
    LLOG_ERROR,
    LLOG_WARNING,
    LLOG_DEBUG,
    LLOG_TRACE,
    LLOG_MAXLEVEL
};

namespace Logger {
    inline constexpr const char* allLevels[] = { "FATAL", "INFO", "ERROR", "WARNING", "DEBUG", "TRACE" };
    extern int currentLevel;

    template<typename...A>
    inline void Log(int const level, const char* const func, const char* const format, A&&...args) noexcept {
        if (level > currentLevel) {
            return;
        }
        printf("[%s][%s]: ", allLevels[level], func);
        if (sizeof...(A) == 0)  {
            puts(format);
        } else {
            printf(format, std::forward<A>(args)...);
            putc('\n', stdout);
        }
        fflush(stdout);
    }
}

inline std::string to_hex(Span<char const> data) noexcept {
    std::string result = {};
    result.reserve(data.size() * 4);
    while(!data.empty()) {
        auto line_size = std::min((size_t)data.size(), (size_t)16);
        for (auto byte : data.subspan(0, line_size)) {
            auto value = (uint8_t)byte;
            char buffer[8] = {};
            char* start = buffer;
            if (value < 0x10) {
                *start = '0';
                start++;
            }
            auto conv = std::to_chars(start, buffer + sizeof(buffer), value, 16);
            *conv.ptr = ' ';
            result.append(buffer);
        }
        result.push_back('\n');
        data = data.subspan(line_size);
    }
    return result;
}

#define LOG_X(LEVEL, FUNC, ...) do { \
    if (LEVEL <= Logger::currentLevel) { \
        Logger::Log(LEVEL, FUNC, __VA_ARGS__); \
    } \
} while(false)

#define LOG_FATAL(...) LOG_X(LLOG_FATAL, __func__, __VA_ARGS__)
#define LOG_INFO(...) LOG_X(LLOG_INFO, __func__, __VA_ARGS__)
#define LOG_ERROR(...) LOG_X(LLOG_ERROR, __func__, __VA_ARGS__)
#define LOG_WARNING(...) LOG_X(LLOG_WARNING, __func__, __VA_ARGS__)
#define LOG_DEBUG(...) LOG_X(LLOG_DEBUG, __func__, __VA_ARGS__)
#define LOG_TRACE(...) LOG_X(LLOG_TRACE, __func__, __VA_ARGS__)

[[noreturn]] inline void panic_impl() noexcept {
    exit(-1);
}

#define panic(...) do { LOG_FATAL(__VA_ARGS__); panic_impl(); } while(false)

