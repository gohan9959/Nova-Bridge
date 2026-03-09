#pragma once
#include <iostream>
#include "../Global.hpp"
#include "../Include/json.hpp"
#include "../LiveData/LiveData.hpp"
#include "../Dex/Dex.hpp"

class DataManager {
    private:
        static BaseDex<PokemonData> pokeDex;
        static BaseDex<MoveData> moveDex;
        static BaseDex<ItemData> itemDex;
    public:
        DataManager() = delete; // Prevent instantiation of this class
        static void initialize();
        static void loadPokemonData(const nlohmann::json& jsonData, std::array<Pokemon, 6>& partyData, std::array<Pokemon, 6>& opponentPartyData);
        static void loadMoveData(const nlohmann::json& jsonData, std::array<Move, 4>& moves);
        static void loadItemData(const nlohmann::json& jsonData, std::vector<Item>& itemData);
        static StatusCondition setStatusCondition(const nlohmann::json& jsonData);
};