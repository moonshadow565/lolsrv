#pragma once
#include "proto_json.hpp"

#include <json.hpp>

struct Game;
struct ClientData;

struct GameReplacer : IReplacer {
    Game* game;
    int32_t cid;
    ClientData* clientData;
    GameReplacer(Game* agame, int32_t acid);

protected:
    virtual std::optional<Json> replace_impl(Json::StringView str) override;
};

struct GameReplacerWithArgs : GameReplacer {
    Json::Object lookup = {};
    GameReplacerWithArgs(Game* agame, int32_t acid, std::string_view args);

protected:
    virtual std::optional<Json> replace_impl(Json::StringView str) override;
};
