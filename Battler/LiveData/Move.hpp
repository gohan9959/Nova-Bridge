#pragma once
#include <string>
#include <cstdint>
#include "../Common/Type.hpp"
#include "../Common/MoveCategory.hpp"


class Move {
private:
    uint16_t id;
    std::string name;
    Type type; 
    uint16_t power;
    uint8_t accuracy;
    uint8_t currPP;
    uint8_t maxPP;
    MoveCategory category;

public:
    Move();
    Move(uint16_t id, const std::string& name, Type type, uint16_t power, uint8_t accuracy, uint8_t currPP, uint8_t maxPP, bool isPhysical, MoveCategory category)
        : id(id), name(name), type(type), power(power), accuracy(accuracy), currPP(currPP), maxPP(maxPP), category(category) {};

    uint16_t getId() const { return id; };
    const std::string& getName() const { return name; };
    Type getType() const { return type; };
    uint16_t getPower() const { return power; };
    uint8_t getAccuracy() const { return accuracy; };
    void setPP(uint8_t pp) { currPP = pp; };
    uint8_t getPP() const { return currPP; };
    uint8_t getMaxPP() const { return maxPP; };
    MoveCategory getCategory() const { return category; };

};
