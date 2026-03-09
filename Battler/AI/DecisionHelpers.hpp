#pragma once
#include<cstdint>
#include "TypeEffectiveness.hpp"
#include "../LiveData/LiveData.hpp"

uint16_t calculateDamage(const Pokemon& attacker, const Move& move, const Pokemon& defender, const TypeEffectiveness& typeEngine) {
    // 1. Base Damage Calculation
    // Using float for precision during the intermediate steps
    float attack = (move.getCategory() == MoveCategory::PHYSICAL) ? attacker.getAttack() : attacker.getSpecialAttack();
    float defence = (move.getCategory() == MoveCategory::PHYSICAL) ? defender.getDefense() : defender.getSpecialDefense();
    float baseDamage = 1.0f;
    // The core Gen 5 Formula: ((2*L/5 + 2) * Power * A/D) / 50 + 2
    if(defence != 0.0f) baseDamage = ((((2.0f * attacker.getLevel() / 5.0f) + 2.0f) * move.getPower() * (attack / defence)) / 50.0f) + 2.0f;

    // 2. Modifiers (The "Multipliers")
    
    // STAB (Same Type Attack Bonus)
    float stab = (move.getType() == attacker.getPrimaryType() || move.getType() == attacker.getSecondaryType()) ? 1.5f : 1.0f;
    
    // Type Effectiveness (Using your pointer-based engine)
    float typeEff = typeEngine.getEffectiveness(move.getType(), defender.getPrimaryType());
    if (defender.getSecondaryType() != Type::NONE) {
        typeEff *= typeEngine.getEffectiveness(move.getType(), defender.getSecondaryType());
    }

    // 3. Final Result
    // In actual games, there's a random roll (0.85 to 1.0), 
    // but for an AI, calculating the "Max" or "Average" is usually better.
    return static_cast<uint16_t>(baseDamage * stab * typeEff);
}

uint8_t getBestMove(const std::array<Move, 4>& moves) {
    // 1. std::max_element finds the largest value using our custom comparison
    auto it = std::max_element(moves.begin(), moves.end(), 
        [](const Move& a, const Move& b) {
            return a.getCurrentDamage() < b.getCurrentDamage();
        }
    );

    // 2. We return the address (&) of the object the iterator points to (*)
    return it->getSlot(); 
}