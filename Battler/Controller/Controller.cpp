#pragma once
#include <fstream>
#include "CommandType.hpp"
#include "Command.hpp"

int Command::globalCommandCounter = 0;


namespace Controller {

    static Command activeCommand;
    static std::string buffer;

    void sendCommand(CommandType type, int slot, const std::string& filePath) {
        activeCommand.globalCommandCounter++;
        activeCommand.type = type;
        activeCommand.slotIndex = static_cast<uint8_t>(slot);

        std::string tempPath = filePath + ".tmp";
        
        std::ofstream file(tempPath);
        if (file.is_open()) {
            file << activeCommand.toJson().dump();
            file.close();
        }
        std::remove(filePath.c_str());
        std::rename(tempPath.c_str(), filePath.c_str());
    }
}