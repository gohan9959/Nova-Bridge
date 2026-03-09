#include <iostream>
#include <thread> 
#include <chrono>
#include "BattleAI.hpp"
#include "../Controller/Controller.hpp"
#include "../Global.hpp"
#include "../Common/Common.hpp"
#include "../DataManager/DataManager.hpp"



bool BattleAI::gotPokemonData = false;
bool BattleAI::gotItemData = false;

void BattleAI::run() {
    DataManager::initialize(); // Load all Dex data into memory at the start of the program
    std::cout << "Battle AI Started..." << std::endl;
    while (true) {
        std::cout << "Checking battle status..." << std::endl;
        Controller::readScriptStatus(config->getScriptStatusFilePath());
        std::cout << "Current Script Status - Last Command ID: " << static_cast<int>(Controller::currentScriptStatus.last_command_id) 
                  << ", Receive Command: " << Controller::currentScriptStatus.recieve_command 
                  << ", In Battle Menu: " << Controller::currentScriptStatus.in_battle_menu << std::endl;

        if (Controller::currentScriptStatus.in_battle_menu && Controller::currentScriptStatus.recieve_command) {
            decideNextMove();
        } 
        else if (Controller::currentScriptStatus.in_battle_menu && !Controller::currentScriptStatus.recieve_command) {
            std::cout << "Waiting for emulator to execute command..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        std::cout << "Not in battle menu, waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    }
}

void BattleAI::decideNextMove() {
    if (!gotPokemonData) {
        Controller::sendCommand(CommandType::FIND_POKEMON, MenuOptions::NONE, 0, 0, config->getCommandFilePath());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Controller::readFile(config->getPokemonFilePath(), jsonData);
        DataManager::loadPokemonData(jsonData, partyData, opponentPartyData); // Parse jsonData to populate partyData and opponentPartyData
        for(const auto& pokemon : partyData) {
            std::cout << "Loaded Pokemon: " << pokemon.getName() << " (ID: " << pokemon.getId() << ", HP: " << pokemon.getCurrentHp() << "/" << pokemon.getMaxHp() << ", Status: " << static_cast<int>(pokemon.getStatusCondition()) << ")" << std::endl;
        }
        for(const auto& pokemon : opponentPartyData) {
            std::cout << "Loaded Opponent Pokemon: " << pokemon.getName() << " (ID: " << pokemon.getId() << ", HP: " << pokemon.getCurrentHp() << "/" << pokemon.getMaxHp() << ", Status: " << static_cast<int>(pokemon.getStatusCondition()) << ")" << std::endl;
        }
        gotPokemonData = true;
        return;
    }
    if (!gotItemData) {
        Controller::sendCommand(CommandType::FIND_ITEMS, MenuOptions::NONE, 0, 0, config->getCommandFilePath());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Controller::readFile(config->getItemFilePath(), jsonData);
        DataManager::loadItemData(jsonData, itemData); // Parse jsonData to populate itemData
        for(const auto& item : itemData) {
            std::cout << "Loaded Item: " << item.getName() << " (ID: " << item.getId() << ", Name: " << item.getName() << ", Quantity: " << static_cast<int>(item.getQuantity()) << ")" << std::endl;
        }
        gotItemData = true;
        return; 
    }
    if (gotPokemonData && gotItemData) {
        battleLogic(); 
        // Reset flags so we fetch fresh data for the NEXT turn
        gotPokemonData = false; 
        gotItemData = false;
    }
}

void BattleAI::battleLogic() {
    // Placeholder for battle logic implementation
    std::cout << "Deciding next move based on current battle state..." << std::endl;
    Controller::sendCommand(CommandType::NAVIGATE_BATTLE_MENU, MenuOptions::FIGHT, static_cast<uint8_t>(FightMenuOptions::MOVE1), 0, config->getCommandFilePath());
    // Here you would analyze partyData, opponentPartyData, and itemData to make an informed decision
    // For example, you might check the health of your Pokemon and decide to use a healing item or switch Pokemon
    // Or you might analyze the opponent's Pokemon types and choose a move that is super effective
}

