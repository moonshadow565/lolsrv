#include "options.hpp"
#include <argparse.hpp>
#include <log.hpp>

Options::Options(int argc, char** argv) {
    argparse::ArgumentParser program("progname");
    program.add_argument("protocol")
            .help("Protocol version")
            .default_value(std::string(protocol));
    program.add_argument("-p", "--player")
            .help("Player name")
            .default_value(std::string(PlayerName));
    program.add_argument("-c", "--champion")
            .help("Champion name")
            .default_value(std::string(ChampionName));
    program.add_argument("-s", "--skin")
            .help("Skin id")
            .action([](std::string const& v) {
                return std::stoi(v);
            })
            .default_value((int)SkinID);
    program.add_argument("-m", "--map")
            .help("Map id")
            .action([](std::string const& v) {
                return std::stoi(v);
            })
            .default_value((int)MapID);
    program.add_argument("--port")
            .help("Port")
            .action([](std::string const& v) {
                return (uint16_t)std::stoul(v);
            })
            .default_value((uint16_t)port);
    program.add_argument("--key")
            .help("Encryption key")
            .default_value(std::string(key));
    program.add_argument("-b", "--blackscreen")
            .help("Black loading screen")
            .implicit_value((bool)true)
            .default_value((bool)black_screen);
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
            .default_value((int)LLOG_WARNING);
    try {
        program.parse_args(argc, argv);
        protocol = program.get<std::string>("protocol");
        PlayerName = program.get<std::string>("-p");
        ChampionName = program.get<std::string>("-c");
        SkinID = program.get<int>("-s");
        MapID = program.get<int>("-m");
        MapName = "Map" + std::to_string(MapID);
        port = program.get<uint16_t>("--port");
        key = program.get<std::string>("--key");
        black_screen = program.get<bool>("-b");
        Logger::currentLevel = program.get<int>("-l");
    } catch(std::exception const& error) {
        panic(error.what());
    }
}
