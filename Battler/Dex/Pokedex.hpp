#pragma once
#include <map>
#include <string>
#include "../Common/Type.hpp"
#include "../Include/json.hpp"

struct PokemonData {
    uint16_t id;
    std::string name;
    Type type1;
    Type type2;

    static PokemonData fromJson(const nlohmann::json& j) {
        return {
            j.at("id").get<uint16_t>(),
            j.at("identifier").get<std::string>(),
            static_cast<Type>(j.at("type1").get<int>()),
            (!j.at("type2").is_null()) ? static_cast<Type>(j.at("type2").get<int>()) : Type::NONE
        };
    }

    // The "Error Handler" helper
    static PokemonData makeEmpty() {
        return { 0, "Unknown Pokemon", Type::NONE, Type::NONE };
    }
};