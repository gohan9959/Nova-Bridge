#pragma once
#include <string>
#include <cstdint>
#include "../Common/Type.hpp"
#include "../Common/MoveCategory.hpp"


class Move {
    friend class DataManager; // Allow DataManager to access private members for loading data
private:
    uint16_t id;
    std::string name;
    Type type; 
    uint16_t power;
    uint8_t accuracy;
    uint8_t currPP;
    uint8_t maxPP;
    uint8_t slot;
    MoveCategory category;
    uint16_t currentDamage;

public:
    Move(){id = 0; name = ""; type = Type::NONE; power = 0; accuracy = 0; currPP = 0; maxPP = 0; slot = -1; category = MoveCategory::PHYSICAL;};
    Move(uint16_t id, const std::string& name, Type type, uint16_t power, uint8_t accuracy, uint8_t currPP, uint8_t maxPP, uint8_t slot, MoveCategory category)
        : id(id), name(name), type(type), power(power), accuracy(accuracy), currPP(currPP), maxPP(maxPP), slot(slot), category(category) {};

    uint16_t getId() const { return id; };
    const std::string& getName() const { return name; };
    Type getType() const { return type; };
    uint16_t getPower() const { return power; };
    uint8_t getAccuracy() const { return accuracy; };
    void setPP(uint8_t pp) { currPP = pp; };
    uint8_t getPP() const { return currPP; };
    uint8_t getMaxPP() const { return maxPP; };
    uint8_t getSlot() const { return slot; };
    MoveCategory getCategory() const { return category; };
    void setCurrentDamage(uint16_t damage){ currentDamage = damage; };
    uint16_t getCurrentDamage() const { return currentDamage; };

};
