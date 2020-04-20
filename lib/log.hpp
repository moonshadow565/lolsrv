#pragma once

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>

enum LogLevel : int {
    LLOG_FATAL = 0,
    LLOG_INFO,
    LLOG_ERROR,
    LLOG_WARNING,
    LLOG_DEBUG,
    LLOG_TRACE,
    LLOG_MAXLEVEL
};

namespace Logger {
  inline constexpr const char* allLevels[] = {"FATAL", "INFO", "ERROR", "WARNING", "DEBUG", "TRACE"};
  extern int currentLevel;

  template<typename...A>
  inline static void Log(int const level, const char* const func, const char* const format, A&&...args) noexcept
  {
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

#define LOG_FATAL(...) Logger::Log(LLOG_FATAL, __func__, __VA_ARGS__)
#define LOG_INFO(...) Logger::Log(LLOG_INFO, __func__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Log(LLOG_ERROR, __func__, __VA_ARGS__)
#define LOG_WARNING(...) Logger::Log(LLOG_WARNING, __func__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::Log(LLOG_DEBUG, __func__, __VA_ARGS__)
#define LOG_TRACE(...) Logger::Log(LLOG_TRACE, __func__, __VA_ARGS__)

[[noreturn]] inline void panic_impl() noexcept {
    exit(-1);
}

#define panic(...) do { LOG_FATAL(__VA_ARGS__); panic_impl(); } while(false)

