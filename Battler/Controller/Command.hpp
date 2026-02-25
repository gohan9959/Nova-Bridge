#pragma once
#include <cstdint>
#include "CommandType.hpp"
#include "../Include/json.hpp"

struct Command {
    static int globalCommandCounter; // Shared across all commands
    CommandType type;
    uint8_t slotIndex;

    Command(CommandType t = CommandType::NONE, uint8_t slot = 0) 
        : type(t), slotIndex(slot) {}

    nlohmann::json toJson() const {
        return nlohmann::json{
            {"commandId", globalCommandCounter},
            {"type", static_cast<int>(type)},
            {"slotIndex", slotIndex},
        };
    }
};