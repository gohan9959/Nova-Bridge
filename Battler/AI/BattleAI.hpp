#pragma once
#include <vector>
#include <array>
#include "../LiveData/LiveData.hpp"
#include "../Include/json.hpp"

class BattleAI {
    private:
        static bool gotPokemonData;
        static bool gotItemData;
        std::array<Pokemon, 6> partyData; // Assuming a maximum of 6 Pokemon in battle
        std::array<Pokemon, 6> opponentPartyData; // Assuming a maximum of 6 Pokemon in battle
        std::vector<Item> itemData; // List of items in the player's inventory
        nlohmann::json jsonData; // Temporary JSON object for reading/writing data

    public:
        BattleAI(){};
        void run();
        void decideNextMove();
        void battleLogic();
};