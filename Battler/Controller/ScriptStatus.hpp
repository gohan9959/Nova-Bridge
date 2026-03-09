#pragma once
#include <cstdint>
#include "../Include/json.hpp"

struct ScriptStatus {
    uint8_t last_command_id; // The ID of the last command that was read by the emulator
    bool recieve_command; // Indicates whether the command can been read by the emulator
    bool in_battle_menu; // Indicates whether the player is currently in the battle menu

};
