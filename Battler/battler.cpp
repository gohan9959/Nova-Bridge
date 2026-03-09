#include <iostream>
#include <fstream>
#include "Global.hpp"
#include "./Include/json.hpp"
#include "Configuration.hpp"
#include "./AI/BattleAI.hpp"

std::string configFilePath = "../configurations.json";
const Configuration* config = nullptr;

void Battler() {
    std::ifstream configFile(configFilePath);
    nlohmann::json configData;
    if (configFile.is_open() && configFile.peek() != std::ifstream::traits_type::eof()) {
        try {
            configFile >> configData;
            configFile.close();
            if (!configData.is_null() && configData.is_object()) {
                nlohmann::json commonPathsJson = configData.value("COMMON_PATHS", nlohmann::json::object());
                nlohmann::json aiPathsJson = configData.value("AI_PATHS", nlohmann::json::object());
                config = new Configuration(
                    commonPathsJson.value("COMMANDS", ""),
                    commonPathsJson.value("CONFIG", ""),
                    commonPathsJson.value("SCRIPT_STATUS", ""),
                    commonPathsJson.value("POKEMON", ""),
                    commonPathsJson.value("ITEMS", ""),
                    aiPathsJson.value("LOGS", ""),
                    aiPathsJson.value("POKEMON_DATA", ""),
                    aiPathsJson.value("ITEM_DATA", ""),
                    aiPathsJson.value("MOVE_DATA", "")
                );
            }
            std::cout << "Configuration loaded successfully." << std::endl;
            std::cout << "Command File Path: " << config->getCommandFilePath() << std::endl;
            std::cout << "Game Config File Path: " << config->getGameConfigFilePath() << std::endl;
            std::cout << "Script Status File Path: " << config->getScriptStatusFilePath() << std::endl;
            std::cout << "Pokemon File Path: " << config->getPokemonFilePath() << std::endl;
            std::cout << "Item File Path: " << config->getItemFilePath() << std::endl;
            std::cout << "Log File Path: " << config->getLogFilePath() << std::endl;
            std::cout << "Pokemon Data File Path: " << config->getPokemonDataFilePath() << std::endl;
            std::cout << "Item Data File Path: " << config->getItemDataFilePath() << std::endl;
            std::cout << "Move Data File Path: " << config->getMoveDataFilePath() << std::endl;
        }
        catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "Unable to open configuration file: " << configFilePath << ", or it is empty." <<std::endl;
    }
}

int main() {
    Battler();
    BattleAI battleAI;
    battleAI.run();
    return 0;
}