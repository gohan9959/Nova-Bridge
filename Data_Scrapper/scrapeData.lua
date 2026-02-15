require("findPokemon")
require("findItems")
require("writeToFile")
require("loadConfig")

local configurations_path = "../configurations.cfg"

function scrapeData()
    local config = loadConfig(configurations_path)
    if not config then
        print("Failed to load configuration file.")
        return
    end
    local check_interval = tonumber(config.INTERVAL) or 60
    local commands_file = config.GAME_COMMANDS
    local pokemon_file = config.POKEMON_DATA
    local items_file = config.ITEMS_DATA
    local frame_count = 0
    while true do
        frame_count = frame_count + 1
        if frame_count >= check_interval then
            -- This code runs every x/60 second(s), where x is defined in the configurations.cfg file
            local f = io.open(commands_file, "r")
            if f then
                local content = trim(f:read("*all"))
                if content and content:match("FIND_POKEMON") then
                    print("Command received: FIND_POKEMON")
                    writeToFile(pokemon_file, findPokemon())
                    print("Pokemon data written to " .. pokemon_file)
                elseif content and content:match("FIND_ITEMS") then
                    print("Command received: FIND_ITEMS")
                    writeToFile(items_file, findItems())
                    print("Item data written to " .. items_file)
                else
                    print("No valid command found in commands.txt")
                end
                f:close()
            end
            frame_count = 0 -- Reset the counter
        end
        emu.frameadvance() -- Tells DeSmuME to run the next frame
    end
end

function main()
    print("Starting Data Scraper...")
    scrapeData()
end
main()