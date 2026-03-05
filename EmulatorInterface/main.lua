-- Get the current directory path
local base_path = ";../?.lua;"
local ui_interactions   = "./UI_Interactions/?.lua;"
local file_Operations = "./FileOperations/?.lua;"
local game_specific = "./GameSpecificScripts/?.lua;"
local data_scrapper = "./DataScrapper/?.lua;"

-- Inject these into Lua's search list
package.path = package.path .. base_path .. ui_interactions .. file_Operations .. game_specific .. data_scrapper

require("findPokemon")
require("findItems")
require("battleMenuNavigation")
require("config")
require("readJSON")
require("writeToFile")
require("checkPixels")

function main()
    loadConfig()
    local check_interval = tonumber(getConfig("INTERVAL")) or 60
    local commands_file = getConfig("PATHS", "COMMANDS")
    local pokemon_file = getConfig("PATHS", "POKEMON")
    local items_file = getConfig("PATHS", "ITEMS")
    local current_command_id = -1
    local frame_count = 0
    while true do
        frame_count = frame_count + 1
        if frame_count >= check_interval then
            frame_count = 0 -- Reset the counter
            local content = readJSON(commands_file)
            if content then
                if checkPixels(getConfig("BATTLE_MENU","MENU_CHECK_COORDINATES"), getConfig("BATTLE_MENU","MENU_CHECK_COLORS")) then
                    print("In battle menu, checking for commands...")
                    if content["COMMAND_ID"] > current_command_id then
                        current_command_id = content["COMMAND_ID"]
                        if content["COMMAND"] == "FIND_POKEMON" then
                            print("Command received: FIND_POKEMON")
                            writeToFile(pokemon_file, findPokemon())
                            print("Pokemon data written to " .. pokemon_file)
                        elseif content["COMMAND"] == "FIND_ITEMS" then
                            print("Command received: FIND_ITEMS")
                            writeToFile(items_file, findItems())
                            print("Items data written to " .. items_file)
                        elseif content["COMMAND"] == "NAVIGATE_BATTLE_MENU" then
                            print("Command received: NAVIGATE_BATTLE_MENU")
                            local menu_option = content["MENU_OPTION"]
                            local slot = content["SLOT"]
                            local sub_slot = content["SUB_SLOT"]
                            battleMenuNavigation(menu_option, slot, sub_slot)
                            print("Navigation command executed.")
                        else
                            print("No valid command found in commands.txt")
                        end
                    end
                else
                    print("Not in battle menu, skipping command check.")
                end
            end
        end
        emu.frameadvance() -- Tells DeSmuME to run the next frame
    end
end

main()
