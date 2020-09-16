#include "game_replacer.hpp"

#include "game.hpp"
#include "json.hpp"

GameReplacer::GameReplacer(Game* agame, int32_t acid) : game(agame), cid(acid), clientData(&agame->clientData[cid]) {}

std::optional<Json> GameReplacer::replace_impl(Json::StringView str) {
    if (str == u8"cid") {
        return cid;
    } else if (str == u8"newNetID") {
        return game->nextNetID++;
    } else if (str == u8"heroNetID") {
        return clientData->heroNetID;
    } else if (str == u8"lastPingX") {
        return clientData->lastPingPos.x;
    } else if (str == u8"lastPingY") {
        return clientData->lastPingPos.y;
    } else if (str == u8"lastOrderX") {
        return clientData->lastOrderPos.x;
    } else if (str == u8"lastOrderY") {
        return clientData->lastOrderPos.y;
    } else if (str == u8"lastOrderZ") {
        return clientData->lastOrderPos.z;
    } else if (str == u8"lastPingNetID") {
        return clientData->lastPingNetID;
    } else if (str == u8"lastSelectNetID") {
        return clientData->lastSelectNetID;
    } else if (str == u8"lastOrderNetID") {
        return clientData->lastOrderNetID;
    } else {
        return std::nullopt;
    }
};

GameReplacerWithArgs::GameReplacerWithArgs(Game* agame, int32_t acid, std::string_view args)
    : GameReplacer(agame, acid) {
    if (!args.empty()) {
        try {
            std::u8string buffer;
            buffer.push_back(u8'{');
            buffer.append(args.begin(), args.end());
            buffer.push_back(u8'}');
            auto json = Json::loads(buffer);
            lookup = json.get<Json::Object>();
        } catch (std::exception const& err) {
            throw std::runtime_error(std::string("Bad args: ") + err.what());
        }
    }
}

std::optional<Json> GameReplacerWithArgs::replace_impl(Json::StringView str) {
    if (auto i = lookup.find(Json::String(str)); i != lookup.end()) {
        return i->second;
    }
    return GameReplacer::replace_impl(str);
};
