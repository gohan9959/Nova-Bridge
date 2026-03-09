#pragma once
#include <cstdint>

enum class CommandType : uint8_t {
    NONE = 0,
    FIND_POKEMON = 1,
    FIND_ITEMS = 2,
    NAVIGATE_BATTLE_MENU = 3
};

enum class MenuOptions : uint8_t {
    NONE = 255,
    FIGHT = 0,
    BAG = 1,
    POKEMON = 2,
    RUN = 3 
};

enum class FightMenuOptions : uint8_t {
    NONE = 255,
    MOVE1 = 0,
    MOVE2 = 1,
    MOVE3 = 2,
    MOVE4 = 3
};


enum class PokemonMenuOptions : uint8_t {
    NONE = 255,
    POKEMON1 = 0,
    POKEMON2 = 1,
    POKEMON3 = 2,
    POKEMON4 = 3,
    POKEMON5 = 4,
    POKEMON6 = 5
    
};

enum class BagMenuOptions : uint8_t{
    NONE = 255,
    HP_PP = 0,
    POKEBALLS = 1,
    STATUS_RESTORE = 2,
    BATTLE_ITEMS = 3
};