#pragma once
#include <iostream>
#include <map>
#include <string>
#include "../Common/Type.hpp"
#include "../Include/json.hpp"

struct PokemonData {
    private:
        uint16_t id;
        std::string name;
        Type type1;
        Type type2;
        void setId(uint16_t newId) { id = newId; };
        void setName(const std::string& newName) { name = newName; };
        void setType1(Type newType1) { type1 = newType1; };
        void setType2(Type newType2) { type2 = newType2; };
    public:
        PokemonData() = default;
        uint16_t getId() const { return id; };              
        std::string getName() const { return name; };
        Type getType1() const { return type1; };
        Type getType2() const { return type2; };

    static PokemonData fromJson(const nlohmann::json& j) {
        PokemonData data;
        j.contains("id") && !j["id"].is_null() ? data.setId(j["id"].get<uint16_t>()) : data.setId(0);
        j.contains("identifier") && !j["identifier"].is_null() ? data.setName(j["identifier"].get<std::string>()) : data.setName("Unknown");
        j.contains("type1") && !j["type1"].is_null() ? data.setType1(static_cast<Type>(j["type1"].get<int>())) : data.setType1(Type::NONE);
        j.contains("type2") && !j["type2"].is_null() ? data.setType2(static_cast<Type>(j["type2"].get<int>())) : data.setType2(Type::NONE);
        return data;
    }
};