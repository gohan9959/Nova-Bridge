#pragma once
#include <cstdint>

enum class ItemCategory : uint8_t {
    NONE = 0,
    STANDARD_BALLS = 9,
    SPECIAL_BALLS = 34,
    HEALING = 27,        // Potions, Ethers
    STATUS_CURES = 28,   // Antidotes, Full Heals
    STAT_BOOSTS = 21,    // X-Attack, X-Defend
    EV_STAT_BOOSTS = 26, // Proteins, Irons (Permanent)
    HELD_ITEMS = 12,     // Leftovers, Choice Band
    REVIVAL = 29,        // Revive, Max Revive
    KEY_ITEMS = 1,       // Bicycle, Town Map
    ALL_MACHINES = 37    // TMs and HMs
};