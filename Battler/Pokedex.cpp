#include <fstream>
#include <iostream>
#include "Pokedex.hpp"
#include "json.hpp"

// Initialize static members
std::map<uint16_t, PokemonData> Pokedex::pokeDex;
PokemonData Pokedex::nullResult = {"MissingNo", Type::NONE, Type::NONE};

void Pokedex::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "CRITICAL: Could not load Pokedex JSON at " << path << std::endl;
        return;
    }

    nlohmann::json data = nlohmann::json::parse(file);

    for (const auto& entry : data) {
        uint16_t id = entry["id"];
        
        PokemonData p;
        p.name = entry["identifier"];
        p.type1 = static_cast<Type>(entry["type1"]);
        p.type2 = (!entry["type2"].is_null()) ? static_cast<Type>(entry["type2"]) : Type::NONE;

        pokeDex[id] = p;
    }
}

const PokemonData& Pokedex::get(uint16_t id) {
    auto it = pokeDex.find(id);
    if (it != pokeDex.end()) {
        return it->second;
    }
    return nullResult; // Return a default PokemonData if the ID is not found
}