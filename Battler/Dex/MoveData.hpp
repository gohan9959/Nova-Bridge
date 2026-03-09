#pragma once
#include <map>
#include <string>
#include "../Common/Type.hpp"
#include "../Common/MoveCategory.hpp"
#include "../Include/json.hpp"

struct MoveData {
    private:
        uint16_t id;
        std::string name;
        Type type;
        uint16_t power;
        uint8_t accuracy;
        uint8_t priority;
        MoveCategory category;
        uint8_t effectId; // ID for the move's secondary effect, 0 if no secondary effect
        uint8_t effectChance; // Chance for secondary effect to occur, 0 if no secondary effect
        void setId(uint16_t newId) { id = newId; };
        void setName(const std::string& newName) { name = newName; };
        void setType(Type newType) { type = newType; };
        void setPower(uint16_t newPower) { power = newPower; };
        void setAccuracy(uint8_t newAccuracy) { accuracy = newAccuracy; };
        void setPriority(uint8_t newPriority) { priority = newPriority; };
        void setCategory(MoveCategory newCategory) { category = newCategory; };
        void setEffectId(uint8_t newEffectId) { effectId = newEffectId;};
        void setEffectChance(uint8_t newEffectChance) { effectChance = newEffectChance; };

    public:
        MoveData() = default;
        uint16_t getId() const { return id; };
        std::string getName() const { return name; };
        Type getType() const { return type; };
        uint16_t getPower() const { return power; };
        uint8_t getAccuracy() const { return accuracy; };
        uint8_t getPriority() const { return priority; };
        MoveCategory getCategory() const { return category; };
        uint8_t getEffectId() const { return effectId; };
        uint8_t getEffectChance() const { return effectChance; };
    
    static MoveData fromJson(const nlohmann::json& j) {
        MoveData data;
        j.contains("id") && !j["id"].is_null() ? data.setId(j["id"].get<uint16_t>()) : data.setId(0);
        j.contains("identifier") && !j["identifier"].is_null() ? data.setName(j["identifier"].get<std::string>()) : data.setName("Unknown");
        j.contains("type") && !j["type"].is_null() ? data.setType(static_cast<Type>(j["type"].get<int>())) : data.setType(Type::NONE);
        j.contains("power") && !j["power"].is_null() ? data.setPower(j["power"].get<uint16_t>()) : data.setPower(0);
        j.contains("accuracy") && !j["accuracy"].is_null() ? data.setAccuracy(j["accuracy"].get<uint8_t>()) : data.setAccuracy(0);
        j.contains("priority") && !j["priority"].is_null() ? data.setPriority(j["priority"].get<uint8_t>()) : data.setPriority(0);
        j.contains("damage_class") && !j["damage_class"].is_null() ? data.setCategory(static_cast<MoveCategory>(j["damage_class"].get<int>())) : data.setCategory(MoveCategory::STATUS);
        j.contains("effect_id") && !j["effect_id"].is_null() ? data.setEffectId(j["effect_id"].get<uint8_t>()) : data.setEffectId(0);
        j.contains("effect_chance") && !j["effect_chance"].is_null() ? data.setEffectChance(j["effect_chance"].get<uint8_t>()) : data.setEffectChance(0);
        return data;
    }
};
