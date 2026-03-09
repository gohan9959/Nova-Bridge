#pragma once
#include <array>
#include <cstdint>
#include "../Common/Common.hpp"
#include "Move.hpp"
#include "Item.hpp"

class Pokemon {
    friend class DataManager; // Allow DataManager to access private members for loading data
private:
    uint16_t id;
    std::string name;
    Type primaryType;
    Type secondaryType;
    uint8_t level;
    uint16_t currentHp;
    uint16_t maxHp;
    uint16_t attack;
    uint16_t defense;
    uint16_t speed;
    uint16_t specialAttack;
    uint16_t specialDefense;
    PARTY_TYPE partyType; // 0 = Player, 1 = Opponent, 2 = Wild
    StatusCondition statusCondition; // 0 = None, 1 = Poisoned, 2 = Burned, 3 = Paralyzed, 4 = Frozen, 5 = Asleep, 6 = Confused
    uint16_t heldItem;
    std::array<Move, 4> moves; // Assuming a Pokemon can have up to 4 moves
public:
    Pokemon(){id = 0; name = ""; primaryType = Type::NONE; secondaryType = Type::NONE; level = 0; currentHp = 0; maxHp = 0; attack = 0; defense = 0; speed = 0; specialAttack = 0; specialDefense = 0; partyType = PARTY_TYPE::PLAYER; statusCondition = StatusCondition::NONE; heldItem = 0; moves.fill(Move());};
    Pokemon(uint16_t id, const std::string& name, Type primaryType, Type secondaryType, uint8_t level, uint16_t currentHp, uint16_t maxHp, uint16_t attack, uint16_t defense, uint16_t speed, uint16_t specialAttack, uint16_t specialDefense, std::array<Move, 4>& moves, PARTY_TYPE partyType, StatusCondition statusCondition, uint16_t heldItem)
        : id(id), name(name), primaryType(primaryType), secondaryType(secondaryType), level(level), currentHp(currentHp), maxHp(maxHp), attack(attack), defense(defense), speed(speed), specialAttack(specialAttack), specialDefense(specialDefense), partyType(partyType), statusCondition(statusCondition), heldItem(heldItem), moves(moves)   {};
    uint16_t getId() const { return id; };
    std::string getName() const { return name; };
    Type getPrimaryType() const { return primaryType; };
    Type getSecondaryType() const { return secondaryType; };
    uint8_t getLevel() const { return level; };
    void setCurrentHp(uint16_t hp) { currentHp = hp;};
    uint16_t getCurrentHp() const { return currentHp; };
    uint16_t getMaxHp() const { return maxHp; };
    uint16_t getAttack() const { return attack; };
    uint16_t getDefense() const { return defense; };
    uint16_t getSpeed() const { return speed; };
    uint16_t getSpecialAttack() const { return specialAttack; };
    uint16_t getSpecialDefense() const { return specialDefense; };                                                      
    PARTY_TYPE getPartyType() const { return partyType; };
    StatusCondition getStatusCondition() const { return statusCondition; };
    void setStatusCondition(StatusCondition condition) { statusCondition = condition; };
    uint16_t getHeldItem() const { return heldItem; };
    const std::array<Move, 4>& getMoves() const { return moves; };
    ~Pokemon() {};
};