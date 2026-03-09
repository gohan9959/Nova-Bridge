-- Get the current directory path
local base_path = ";../?.lua;"
local ui_interactions   = "./UI_Interactions/?.lua;"
local file_Operations = "./FileOperations/?.lua;"
local game_specific = "./GameSpecificScripts/?.lua;"
local data_scrapper = "./DataScrapper/?.lua;"
local require_path = "./Require/?.lua;"

-- Inject these into Lua's search list
package.path = package.path .. base_path .. ui_interactions .. file_Operations .. game_specific .. data_scrapper .. require_path

require("findPokemon")
require("findItems")
require("battleMenuNavigation")
require("config")
require("readJSON")
require("writeToFile")
require("checkPixels")
require("commandTypes")
local json = require("dkjson")

function main()
    loadConfig()
    local check_interval = tonumber(getConfig("INTERVAL")) or 60
    local commands_file = getConfig("COMMON_PATHS", "COMMANDS")
    local pokemon_file = getConfig("COMMON_PATHS", "POKEMON")
    local items_file = getConfig("COMMON_PATHS", "ITEMS")
    local script_status_file = getConfig("COMMON_PATHS", "SCRIPT_STATUS")
    local current_command_id = -1
    local frame_count = 0
    local script_status = {
        IN_BATTLE_MENU = false,
        LAST_COMMAND_ID = current_command_id,
        RECIEVE_COMMAND = false
    }
    writeToFile(script_status_file, json.encode(script_status, { indent = true })) -- Initialize the script status file
    while true do
        frame_count = frame_count + 1
        if frame_count >= check_interval then
            frame_count = 0 -- Reset the counter
            if checkPixels(getConfig("BATTLE_MENU","MENU_CHECK_COORDINATES"), getConfig("BATTLE_MENU","MENU_CHECK_COLORS")) then
                print("In battle menu, checking for commands...")
                script_status.IN_BATTLE_MENU = true
                script_status.LAST_COMMAND_ID = current_command_id
                script_status.RECIEVE_COMMAND = true
                writeToFile(script_status_file, json.encode(script_status, { indent = true }))
                local content = readJSON(commands_file)
                if content then
                    if content["COMMAND_ID"] > current_command_id then
                        current_command_id = content["COMMAND_ID"]
                        script_status.LAST_COMMAND_ID = current_command_id
                        script_status.RECIEVE_COMMAND = false
                        writeToFile(script_status_file, json.encode(script_status, { indent = true }))
                        if content["COMMAND"] == COMMAND_TYPES.FIND_POKEMON then
                            print("Command received: FIND_POKEMON")
                            writeToFile(pokemon_file, findPokemon())
                            print("Pokemon data written to " .. pokemon_file)
                        elseif content["COMMAND"] == COMMAND_TYPES.FIND_ITEMS then
                            print("Command received: FIND_ITEMS")
                            writeToFile(items_file, findItems())
                            print("Items data written to " .. items_file)
                        elseif content["COMMAND"] == COMMAND_TYPES.NAVIGATE_BATTLE_MENU then
                            print("Command received: NAVIGATE_BATTLE_MENU")
                            local menu_option = content["MENU_OPTION"]
                            local slot = content["SLOT"]
                            local sub_slot = content["SUB_SLOT"]
                            battleMenuNavigation(menu_option, slot, sub_slot)
                            print("Navigation command executed.")
                        else
                            print("No valid command found in commands.txt")
                        end
                        script_status.RECIEVE_COMMAND = true
                        writeToFile(script_status_file, json.encode(script_status, { indent = true }))
                    else
                        print("No new command found. Current command ID: " .. current_command_id)
                    end
                else
                    print("Failed to read commands file or file is empty.")
                end
            else
                script_status.IN_BATTLE_MENU = false
                script_status.LAST_COMMAND_ID = current_command_id
                script_status.RECIEVE_COMMAND = false
                writeToFile(script_status_file, json.encode(script_status, { indent = true }))
                print("Not in battle menu, skipping command check.")
            end
        end
        emu.frameadvance() -- Tells DeSmuME to run the next frame
    end
end

main()
