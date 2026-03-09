#pragma once
#include <cstdint>
#include "CommandParameterStructs.hpp"
#include "../Include/json.hpp"

struct Command {
    static int globalCommandCounter; // Shared across all commands
    CommandType type;
    MenuOptions menuOption; // For NAVIGATE_BATTLE_MENU, indicates which menu option to select
    uint8_t slotIndex;
    uint8_t subSlotIndex; // For NAVIGATE_BATTLE_MENU, indicates which sub-option to select (if applicable)

    nlohmann::json toJson() const {
        return nlohmann::json{
            {"COMMAND_ID", globalCommandCounter},
            {"COMMAND", static_cast<int>(type)},
            {"MENU_OPTION", static_cast<int>(menuOption)},
            {"SLOT", slotIndex},
            {"SUB_SLOT", subSlotIndex}
        };
    }
};

