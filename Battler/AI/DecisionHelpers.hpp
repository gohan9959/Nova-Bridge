#pragma once
#include<cstdint>
#include "TypeEffectiveness.hpp"
#include "../LiveData/LiveData.hpp"

static const TypeEffectiveness typeEngine(TypeCharts::Gen5);

uint16_t calculateDamage(const Pokemon& attacker, const Move& move, const Pokemon& defender) {
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

bool canSafelySwitch(const Pokemon& candidate, const Pokemon& opponent) {
    // 1. Calculate the theoretical max damage this opponent can do to our candidate
    // We'll assume the opponent uses their strongest STAB move for the 'Worst Case'
    float primaryThreat = calculateDangerScore(candidate, opponent); 
    
    // 2. Estimate damage based on threat multiplier
    // A threat of 2.0 (Super Effective) is roughly 25-50% of HP in Gen 5
    // If opponent is faster, we must survive 2 hits (the switch-in and the first turn)
    int hitsToSurvive = (opponent.getSpeed() > candidate.getSpeed()) ? 2 : 1;

    // 3. Simple heuristic: If we take 2x Super Effective hits, we need a lot of HP
    // You can fine-tune this multiplier based on your playtesting
    float survivalThreshold = primaryThreat * hitsToSurvive * 0.25f; 
    float currentHpPercent = static_cast<float>(candidate.getCurrentHp()) / candidate.getMaxHp();

    return currentHpPercent > survivalThreshold;
}

float calculateDangerScore(const Pokemon& Player, const Pokemon& Opponent) {
    // Check how the Opponent's primary type hits the Player
    float primaryThreat = typeEngine.getEffectiveness(Opponent.getPrimaryType(), Player.getPrimaryType()) * typeEngine.getEffectiveness(Opponent.getPrimaryType(), Player.getSecondaryType());

    // Check how the Opponent's secondary type (if it exists) hits the Player
    float secondaryThreat = 1.0f;
    if (Opponent.getSecondaryType() != Type::NONE) {
        secondaryThreat = typeEngine.getEffectiveness(Opponent.getSecondaryType(), Player.getPrimaryType()) * typeEngine.getEffectiveness(Opponent.getSecondaryType(), Player.getSecondaryType());
    }

    // Return the maximum danger (we assume the opponent will use their most effective type)
    return std::max(primaryThreat, secondaryThreat);
}

int findBestSwitch(const std::array<Pokemon, 6>& party, const Pokemon& Opponent, float currerntDanger) {
    int bestSlot = -1;
    uint8_t currentBest = getBestMove(party[0].getMoves());
    // Start high, looking for the lowest threat

    // Start from index 1 because index 0 is the current active Pokemon
    for (size_t i = 1; i < party.size(); ++i) {
        const auto& pokemon = party[i];

        // 1. Safety Check: Don't switch to a fainted Pokemon!
        if (pokemon.getCurrentHp() <= 0) continue;

        // 2. Use your "Flipped" logic to calculate threat
        float threat = calculateDangerScore(pokemon, Opponent);

        if(canSafelySwitch(pokemon, Opponent)){
            uint8_t switchBest = getBestMove(party[i].getMoves());
             // 3. Keep track of the "Safest" switch
            if (threat < currerntDanger) {
                currerntDanger = threat;
                bestSlot = static_cast<int>(i);
                currentBest = switchBest;
            }
            else if (threat == currerntDanger){
                if(bestSlot == -1){
                    if(party[0].getMoves().at(currentBest).getCurrentDamage() < party[i].getMoves().at(switchBest).getCurrentDamage()){
                        bestSlot = i;
                        currentBest = switchBest;
                    }
                }
                else{
                    if(party[bestSlot].getMoves().at(currentBest).getCurrentDamage() < party[i].getMoves().at(switchBest).getCurrentDamage()){
                        bestSlot = i;
                        currentBest = switchBest;
                    }
                }
            }

        }
    }
    return bestSlot;
}

void calculatePartyMovesDamage(std::array<Pokemon, 6>& party, const Pokemon& Opponent) {
    for(Pokemon& pokemon : party) { // Added &
        for(Move& move : pokemon.getMoves()) { // Added &
            move.setCurrentDamage(calculateDamage(pokemon, move, Opponent));
        }
    }
}