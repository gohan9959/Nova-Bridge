#pragma once
#include <map>
#include <string>
#include "../Common/Type.hpp"
#include "../Common/MoveCategory.hpp"
#include "../Include/json.hpp"

struct MoveDex {
    uint16_t id;
    std::string name;
    Type type;
    uint16_t power;
    uint8_t accuracy;
    uint8_t priority;
    MoveCategory category;
    uint8_t effectId; // ID for the move's secondary effect, 0 if no secondary effect
    uint8_t effectChance; // Chance for secondary effect to occur, 0 if no secondary effect

    static MoveDex fromJson(const nlohmann::json& j) {
        return {
            j.at("id").get<uint16_t>(),
            j.at("identifier").get<std::string>(),
            static_cast<Type>(j.at("type_id").get<int>()),
            (!j.at("power").is_null()) ? j.at("power").get<uint16_t>() : ((uint16_t)0),
            (!j.at("accuracy").is_null()) ? j.at("accuracy").get<uint8_t>() : ((uint8_t)0),
            j.at("priority").get<uint8_t>(),
            static_cast<MoveCategory>(j.at("damage_class_id").get<int>()),
            (!j.at("effect_id").is_null()) ? j.at("effect_id").get<uint8_t>() : ((uint8_t)0),
            (!j.at("effect_chance").is_null()) ? j.at("effect_chance").get<uint8_t>() : ((uint8_t)0)
        };
    }

    // The "Error Handler" helper
    static MoveDex makeEmpty() {
        return { 0, "Unknown Move", Type::NONE, 0, 0, 0, MoveCategory::STATUS, 0, 0 };
    }

};