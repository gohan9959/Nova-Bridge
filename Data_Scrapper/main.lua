require("checkPixels")
require("readJSON")
require("traverseGen5")

local configurations_path = "../configurations.json"

config = readJSON(configurations_path)

menu_selection = {
    FIGHT = 0,
    BAG = 1,
    POKEMON = 2,
    RUN = 3
} -- Options: FIGHT, BAG, POKEMON, RUN

function battleMenuNavigation(menu_option, slot, sub_slot)
    navigateToSelection(menu_option)
    if menu_option == menu_selection.FIGHT then
        --navigateToMove(slot)
    elseif menu_option == menu_selection.BAG then
        --navigateToItem(slot, sub_slot)
    elseif menu_option == menu_selection.POKEMON then
        --navigateToPokemon(slot)
    end
end

function navigateToSelection(menu_option)
    local current_selection = currentBattleMenuSelectionStatus()
    while current_selection ~= menu_option do
        traverseBattleMenu(current_selection, menu_option)
        current_selection = currentBattleMenuSelectionStatus() -- Update the current selection after the input
    end
    joypad.set(1, {A=true}) -- Press A to confirm the selection
end

function currentBattleMenuSelectionStatus()
    if checkPixels(config["BATTLE_MENU"]["FIGHT_BUTTON_SELECTED"], config["SELECTION_MARKER_COLORS"]) then
        return menu_selection.FIGHT
    elseif checkPixels(config["BATTLE_MENU"]["BAG_BUTTON_SELECTED"], config["SELECTION_MARKER_COLORS"]) then
        return menu_selection.BAG
    elseif checkPixels(config["BATTLE_MENU"]["POKEMON_BUTTON_SELECTED"], config["SELECTION_MARKER_COLORS"]) then
        return menu_selection.POKEMON
    elseif checkPixels(config["BATTLE_MENU"]["RUN_BUTTON_SELECTED"], config["SELECTION_MARKER_COLORS"]) then
        return menu_selection.RUN
    else
        return nil
    end
end

function battleMenuCheck()
    return checkPixels(config["BATTLE_MENU"]["MENU_CHECK_COORDINATES"], config["BATTLE_MENU"]["MENU_CHECK_COLORS"])
end

function main()
    local frame_count = 0
    while true do
        frame_count = frame_count + 1
        if frame_count >= 120 then
            -- This code runs every x/60 second(s), where x is defined in the configurations.cfg file
            if battleMenuCheck() then
                print("In battle menu, navigating to FIGHT...")
                battleMenuNavigation(menu_selection.FIGHT, 1)
            else
                print("Not in battle menu.")
            end
            
            frame_count = 0 -- Reset the counter
        end
        emu.frameadvance() -- Tells DeSmuME to run the next frame
    end
end

main()