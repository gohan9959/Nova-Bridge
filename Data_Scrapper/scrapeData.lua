local check_interval = 60 -- 60 frames = ~1 second
local frame_count = 0

require("findPokemon")
require("findItems")
require("writeToFile")

function main()
    while true do
        frame_count = frame_count + 1
        if frame_count >= check_interval then
            -- This code runs every 1 second
            local f = io.open("commands.txt", "r")
            if f then
                local content = f:read("*all")
                if content and content:match("FIND_POKEMON") then
                    print("Command received: FIND_POKEMON")
                    writeToFile("pokemon_data.txt", find_pokemon())
                    print("Pokemon data written to pokemon_data.txt")
                elseif content and content:match("FIND_ITEMS") then
                    print("Command received: FIND_ITEMS")
                    writeToFile("Item_List.txt", find_Items())
                    print("Item data written to Item_List.txt")
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

main()