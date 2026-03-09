#include "DataManager.hpp"

void DataManager::initialize() {
    DataManager::pokeDex.load(config->getPokemonDataFilePath());
    std::cout << "Pokemon data loaded" << std::endl;
    DataManager::moveDex.load(config->getMoveDataFilePath());
    std::cout << "Move data loaded" << std::endl;
    DataManager::itemDex.load(config->getItemDataFilePath());
    std::cout << "Item data loaded" << std::endl;
}

void DataManager::loadPokemonData(const nlohmann::json& jsonData, std::array<Pokemon, 6>& partyData, std::array<Pokemon, 6>& opponentPartyData) {
    int i = 0; // This will be used to construct the keys "Pokemon 1", "Pokemon 2", etc.
    int partyCount = 0;
    int opponentPartyCount = 0; 
    std::cout << "Loading Pokemon data from JSON..." << std::endl;
    for (const auto& entry : jsonData) {
        // Construct the key dynamically: "Pokemon 1", "Pokemon 2", etc.
        std::string key = "Pokemon " + std::to_string(i);
        // Extract the data table using that key
        nlohmann::json pokemon = entry.value(key, nlohmann::json::object());
        if (!pokemon.empty()) {
            nlohmann::json statsJson = pokemon.value("stats", nlohmann::json::object());
            Pokemon& target = (static_cast<PARTY_TYPE>(pokemon.value("party", 0)) == PARTY_TYPE::PLAYER) ? partyData[partyCount++] : opponentPartyData[opponentPartyCount++];
            pokemon.contains("speciesId") && !pokemon["speciesId"].is_null() ? target.id = pokemon["speciesId"].get<uint16_t>() : target.id = 0;
            target.name = DataManager::pokeDex.get(target.id)->getName();
            target.primaryType = DataManager::pokeDex.get(target.id)->getType1();
            target.secondaryType = DataManager::pokeDex.get(target.id)->getType2();
            pokemon.contains("level") && !pokemon["level"].is_null() ? target.level = pokemon["level"].get<uint8_t>() : target.level = 0;
            pokemon.contains("hp") && !pokemon["hp"].is_null() ? target.currentHp = pokemon["hp"].get<uint16_t>() : target.currentHp = 0;
            pokemon.contains("maxHp") && !pokemon["maxHp"].is_null() ? target.maxHp = pokemon["maxHp"].get<uint16_t>() : target.maxHp = 0;
            statsJson.contains("ATTACK") && !statsJson["ATTACK"].is_null() ? target.attack = statsJson["ATTACK"].get<uint16_t>() : target.attack = 0;
            statsJson.contains("DEFENSE") && !statsJson["DEFENSE"].is_null() ? target.defense = statsJson["DEFENSE"].get<uint16_t>() : target.defense = 0;
            statsJson.contains("SPEED") && !statsJson["SPEED"].is_null() ? target.speed = statsJson["SPEED"].get<uint16_t>() : target.speed = 0;
            statsJson.contains("SP_ATTACK") && !statsJson["SP_ATTACK"].is_null() ? target.specialAttack = statsJson["SP_ATTACK"].get<uint16_t>() : target.specialAttack = 0;
            statsJson.contains("SP_DEFENSE") && !statsJson["SP_DEFENSE"].is_null() ? target.specialDefense = statsJson["SP_DEFENSE"].get<uint16_t>() : target.specialDefense = 0;
            target.moves = std::array<Move, 4>(); // Placeholder moves, will be loaded separately
            pokemon.contains("party") && !pokemon["party"].is_null() ? target.partyType = static_cast<PARTY_TYPE>(pokemon["party"].get<int>()) : target.partyType = PARTY_TYPE::PLAYER;
            target.statusCondition = setStatusCondition(pokemon.value("statusConditions", nlohmann::json::object()));
            pokemon.contains("heldItem") && !pokemon["heldItem"].is_null() ? target.heldItem = pokemon["heldItem"].get<uint16_t>() : target.heldItem = 0;
            loadMoveData(pokemon.value("moves", nlohmann::json::array()), target.moves); // Load moves for this Pokemon
        } else {
            std::cout << "Warning: Could not find key " << key << " in JSON entry." << std::endl;
        }
        i++; // Move to the next Pokemon label
    }
}

void DataManager::loadMoveData(const nlohmann::json& jsonData, std::array<Move, 4>& moves) {
    int i = 0;
    for (const auto& moveEntry : jsonData) {
        Move& move = moves[i];
        moveEntry.contains("id") && !moveEntry["id"].is_null() ? move.id = moveEntry["id"].get<uint16_t>() : move.id = 0;
        move.name = DataManager::moveDex.get(move.id)->getName();
        move.type = DataManager::moveDex.get(move.id)->getType();
        moveEntry.contains("power") && !moveEntry["power"].is_null() ? move.power = moveEntry["power"].get<uint16_t>() : move.power = 0;
        moveEntry.contains("accuracy") && !moveEntry["accuracy"].is_null() ? move.accuracy = moveEntry["accuracy"].get<uint16_t>() : move.accuracy = 0;
        moveEntry.contains("pp") && !moveEntry["pp"].is_null() ? move.currPP = moveEntry["pp"].get<uint16_t>() : move.currPP = 0;
        moveEntry.contains("maxPp") && !moveEntry["maxPp"].is_null() ? move.maxPP = moveEntry["maxPp"].get<uint16_t>() : move.maxPP = 0;
        moveEntry.contains("slot") && !moveEntry["slot"].is_null() ? move.slot = moveEntry["slot"].get<uint16_t>() : move.slot = 0;
        move.category = DataManager::moveDex.get(move.id)->getCategory();
        i++;
        if (i >= 4) break; // We only have 4 move slots
    }
}

void DataManager::loadItemData(const nlohmann::json& jsonData, std::vector<Item>& itemData) {
    for (const auto& itemJson : jsonData) {
        Item item(
            itemJson.contains("id") && !itemJson["id"].is_null() ? itemJson["id"].get<uint16_t>() : 0,
            itemJson.contains("quantity") && !itemJson["quantity"].is_null() ? itemJson["quantity"].get<uint16_t>() : 0,
            DataManager::itemDex.get(itemJson.contains("id") && !itemJson["id"].is_null() ? itemJson["id"].get<uint16_t>() : 0)->getName(),
            DataManager::itemDex.get(itemJson.contains("id") && !itemJson["id"].is_null() ? itemJson["id"].get<uint16_t>() : 0)->getCategory()
        );
        itemData.push_back(item);
    }
}

StatusCondition DataManager::setStatusCondition(const nlohmann::json& jsonData) {
    if(!jsonData.is_null()){
        if(jsonData.contains("BURNED") && jsonData["BURNED"] != 0) return StatusCondition::BURNED;
        if(jsonData.contains("FROZEN") && jsonData["FROZEN"] != 0) return StatusCondition::FROZEN;
        if(jsonData.contains("PARALYZED") && jsonData["PARALYZED"] != 0) return StatusCondition::PARALYZED;
        if(jsonData.contains("POISONED") && jsonData["POISONED"] != 0) return StatusCondition::POISONED;
        if(jsonData.contains("SLEEP") && jsonData["SLEEP"] != 0) return StatusCondition::SLEEP;
    }
    return StatusCondition::NONE;
}
