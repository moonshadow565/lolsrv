#pragma once
#include <array>
#include <cinttypes>
#include <string_view>

struct BlowFish {
    struct State {
        using PIKey = std::array<uint32_t, 18>;
        using SBoxes = std::array<std::array<uint32_t, 256>, 4>;
        PIKey pikey = {};
        SBoxes sboxes = {};
    };
    State state = {};

    inline constexpr BlowFish() noexcept = default;
    BlowFish(std::string_view key) noexcept;
    void encrypt(char* data, size_t size) const noexcept;
    void decrypt(char* data, size_t size) const noexcept;
};
