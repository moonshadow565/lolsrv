#pragma once
#include <string>
#include <stdexcept>
#include "argparse.hpp"
#include "log.hpp"

struct Options {
    std::string PlayerName = "Test";
    std::string ChampionName = "Annie";
    int SkinID = 0;
    int MapID = 1;
    std::string MapName = "Map1";
    uint16_t port = 5119;
    std::string key = "GLzvuWtyCfHyGhF2";
    inline Options(int argc, char** argv) noexcept {
        argparse::ArgumentParser program("progname");
        program.add_argument("-p", "--player")
                .help("Player name")
                .default_value(std::string("Test"));
        program.add_argument("-c", "--champion")
                .help("Champion name")
                .default_value(std::string("Annie"));
        program.add_argument("-s", "--skin")
                .help("Skin id")
                .action([](std::string const& v) {
                    return std::stoi(v);
                })
                .default_value((int)0);
        program.add_argument("-m", "--map")
                .help("Map id")
                .action([](std::string const& v) {
                    return std::stoi(v);
                })
                .default_value((int)1);
        program.add_argument("--port")
                .help("Port")
                .action([](std::string const& v) {
                    return (uint16_t)std::stoul(v);
                })
                .default_value((uint16_t)5119);
        program.add_argument("--key")
                .help("Encryption key")
                .default_value(std::string("GLzvuWtyCfHyGhF2"));
        program.add_argument("-l", "--log")
                .help("Log level")
                .action([](std::string const& v) {
                    for(auto i = 0; i != LLOG_MAXLEVEL; i++) {
                        if (v == Logger::allLevels[i]) {
                            return i;
                        }
                    }
                    return std::stoi(v);
                })
                .default_value((int)LLOG_ERROR);
        try {
            program.parse_args(argc, argv);
            PlayerName = program.get<std::string>("-p");
            ChampionName = program.get<std::string>("-c");
            SkinID = program.get<int>("-s");
            MapID = program.get<int>("-m");
            MapName = "Map" + std::to_string(MapID);
            port = program.get<uint16_t>("--port");
            key = program.get<std::string>("--key");
            Logger::currentLevel = program.get<int>("-l");
        } catch(std::exception const& error) {
            panic(error.what());
        }
    }
};
