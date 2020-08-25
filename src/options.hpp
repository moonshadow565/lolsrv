#pragma once
#include <string>

struct Options {
    std::string protocol = "";
    std::string PlayerName = "Test";
    std::string ChampionName = "Annie";
    int32_t SkinID = 0;
    int32_t MapID = 1;
    std::string MapName = "Map1";
    uint16_t port = 5119;
    std::string key = "GLzvuWtyCfHyGhF2";
    bool black_screen = false;

    Options(int argc, char** argv);
};
