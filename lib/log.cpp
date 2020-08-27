#include "log.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>
#include <charconv>

int Logger::currentLevel = LLOG_DEBUG;

void Logger::Log(int const level, char const* const func, char const* const format, ...) noexcept {
    if (level > currentLevel) {
        return;
    }
    printf("[%s][%s]: ", allLevels[level], func);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    putc('\n', stdout);
    fflush(stdout);
}

[[noreturn]] void Logger::panic_impl() noexcept {
    exit(-1);
}

std::string to_hex(Span<char const> data) noexcept {
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
