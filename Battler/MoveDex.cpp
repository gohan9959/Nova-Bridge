#include <fstream>
#include <iostream>
#include "MoveDex.hpp"
#include "json.hpp"

// Initialize static members
std::map<uint16_t, MoveData> MoveDex::moveDex;
MoveData MoveDex::nullResult = {"MissingNo", Type::NONE, 0, 0, 0, MoveCategory::STATUS, 0, 0};

void MoveDex::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "CRITICAL: Could not load MoveDex JSON at " << path << std::endl;
        return;
    }

    nlohmann::json data = nlohmann::json::parse(file);

    for (const auto& entry : data) {
        uint16_t id = entry["id"];
        
        MoveData m;
        m.name = entry["identifier"];
        m.type = static_cast<Type>(entry["type_id"]);
        m.power = (!entry["power"].is_null()) ? entry["power"] : 0;
        m.accuracy = (!entry["accuracy"].is_null()) ? entry["accuracy"] : 0;
        m.priority = entry["priority"];
        m.category = static_cast<MoveCategory>(entry["damage_class_id"]);
        m.effectId = (!entry["effect_id"].is_null()) ? entry["effect_id"] : 0;
        m.effectChance = (!entry["effect_chance"].is_null()) ? entry["effect_chance"] : 0;

        moveDex[id] = m;
    }
}

const MoveData& MoveDex::get(uint16_t id) {
    auto it = moveDex.find(id);
    if (it != moveDex.end()) {
        return it->second;
    }
    return nullResult; // Return a default MoveData if the ID is not found
}