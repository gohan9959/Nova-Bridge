#pragma once
#include <fstream>
#include <iostream>
#include "Command.hpp"
#include "CommandParameterStructs.hpp"
#include "ScriptStatus.hpp"
#include "../LiveData/LiveData.hpp"
#include "../Include/json.hpp"

int Command::globalCommandCounter = 0;


namespace Controller {

    static Command activeCommand;
    static ScriptStatus currentScriptStatus;


    void readFile(const std::string& filePath, nlohmann::json& jsonData) {
        std::ifstream file(filePath);
        if (file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
            file >> jsonData;
            file.close();
        }
        else{
            std::cerr << "Unable to open file: " << filePath << ", or it is empty." << std::endl;
            jsonData = nlohmann::json::object(); // Set to empty object if file can't be read
        }
    }

    void writeFile(const std::string& filePath, const nlohmann::json& jsonData) {
        std::string tempPath = filePath + ".tmp";
        std::ofstream file(tempPath);
        if (file.is_open()) {
            file << jsonData.dump();
            file.close();
            std::remove(filePath.c_str());
            std::rename(tempPath.c_str(), filePath.c_str());
        }
    }

    void sendCommand(CommandType type, MenuOptions menuOption, uint8_t slot, uint8_t subSlot, const std::string& filePath) {
        activeCommand.globalCommandCounter++;
        activeCommand.type = type;
        activeCommand.menuOption = menuOption,
        activeCommand.slotIndex = slot;
        activeCommand.subSlotIndex = subSlot;
        nlohmann::json jsonData = activeCommand.toJson();
        writeFile(filePath, jsonData);
    }

    void readScriptStatus (const std::string& filePath){
        std::ifstream file(filePath);
        nlohmann::json jsonData;
        readFile(filePath, jsonData);
        try{
            jsonData.contains("LAST_COMMAND_ID") && jsonData["LAST_COMMAND_ID"].is_number_unsigned() ? currentScriptStatus.last_command_id = jsonData["LAST_COMMAND_ID"].get<uint8_t>() : currentScriptStatus.last_command_id = 0;
            jsonData.contains("RECIEVE_COMMAND") && jsonData["RECIEVE_COMMAND"].is_boolean() ? currentScriptStatus.recieve_command = jsonData["RECIEVE_COMMAND"].get<bool>() : currentScriptStatus.recieve_command = false;
            jsonData.contains("IN_BATTLE_MENU") && jsonData["IN_BATTLE_MENU"].is_boolean() ? currentScriptStatus.in_battle_menu = jsonData["IN_BATTLE_MENU"].get<bool>() : currentScriptStatus.in_battle_menu = false;
        }
        catch (const nlohmann::json::exception& e) {
            // Handle JSON parsing errors
            std::cerr << "It's failing here JSON Error: " << e.what() << std::endl;
        }
        
    }

    void readItemData(const std::string& filePath, nlohmann::json& jsonData) {
        readFile(filePath, jsonData);
    }
}