#pragma once
#include "proto_pkt.hpp"

#include <json.hpp>

struct IReplacer {
    IReplacer() = default;
    IReplacer(IReplacer const&) = delete;
    IReplacer(IReplacer&&) = delete;
    IReplacer& operator=(IReplacer const&) = delete;
    IReplacer& operator=(IReplacer&&) = delete;
    void run(Json& json);

protected:
    virtual std::optional<Json> replace_impl(Json::StringView str) = 0;

private:
    std::optional<Json> replace(Json::StringView str);
};

extern std::vector<PKT_S2C> pkts_from_json(std::u8string_view data, IReplacer& replacer);
