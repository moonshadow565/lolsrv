#pragma once
#include <span.hpp>
#include <string>

enum LogLevel : int32_t {
    LLOG_FATAL = 0,
    LLOG_INFO,
    LLOG_ERROR,
    LLOG_WARNING,
    LLOG_VERBOSE,
    LLOG_DEBUG,
    LLOG_TRACE,
    LLOG_MAXLEVEL
};

namespace Logger {
    inline constexpr const char* allLevels[] = {"FATAL", "INFO", "ERROR", "WARNING", "VERBOSE", "DEBUG", "TRACE"};
    extern int currentLevel;
    extern void Log(int const level, const char* const func, const char* const format, ...) noexcept;
    [[noreturn]] extern void panic_impl() noexcept;
} // namespace Logger

extern std::string to_hex(Span<char const> data) noexcept;

#define LOG_FATAL(...) Logger::Log(LLOG_FATAL, __func__, __VA_ARGS__)
#define LOG_INFO(...) Logger::Log(LLOG_INFO, __func__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Log(LLOG_ERROR, __func__, __VA_ARGS__)
#define LOG_WARNING(...) Logger::Log(LLOG_WARNING, __func__, __VA_ARGS__)
#define LOG_VERBOSE(...) Logger::Log(LLOG_VERBOSE, __func__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::Log(LLOG_DEBUG, __func__, __VA_ARGS__)
#define LOG_TRACE(...) Logger::Log(LLOG_TRACE, __func__, __VA_ARGS__)

#define panic(...)              \
    do {                        \
        LOG_FATAL(__VA_ARGS__); \
        Logger::panic_impl();   \
    } while (false)
