#pragma once
#include <map>
#include <string>
#include "Type.hpp" 

struct PokemonData {
    std::string name;
    Type type1;
    Type type2;
};

class Pokedex {
private:
    static std::map<uint16_t, PokemonData> pokeDex;
    static PokemonData nullResult;
public:
    Pokedex() = delete; // Prevent instantiation of the Pokedex class
    static void load(const std::string& path);
    static const PokemonData& get(uint16_t id);
};