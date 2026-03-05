require("traverseGen5")
require("selectionStatus")
MENU_OPTIONS = require("menuOptions")



function battleMenuNavigation(menu_option, slot, sub_slot)
    if not menu_option then 
        print("Error: Menu option is nil")
        return 
    end
    if not slot then 
        print("Error: Slot is nil")
        return 
    end
    navigateToSelection(menu_option, battleMenuSelectionStatus, traverseBattleMenu)
    if menu_option == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then
        print("Navigating to FIGHT menu option")
        navigateToSelection(slot, fightMenuSelectionStatus, traverseSubMenus)
    elseif menu_option == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then
        print("Navigating to BAG menu option")
        navigateToSelection(slot, bagMenuSelectionStatus, traverseSubMenus)
        if sub_slot then
            navigateToSelection(sub_slot, bagSubmenuSelectionStatus, traverseSubMenus)
        else
            print("Error: Sub-slot is nil for BAG menu option")
        end
    elseif menu_option == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then
        print("Navigating to POKEMON menu option")
        navigateToSelection(slot, pokemonMenuSelectionStatus, traverseSubMenus)
    end
end

function navigateToSelection(menu_option, selectionStatus, traverseMenu)
    if not menu_option or not selectionStatus or not traverseMenu then 
        print("Error: One or more required arguments are nil")
        return 
    end
    local current_selection = selectionStatus()
    while current_selection ~= menu_option do
        traverseMenu(current_selection, menu_option)
        current_selection = selectionStatus() -- Update the current selection after the input
        print("Current selection: " .. tostring(current_selection) .. ", Target selection: " .. tostring(menu_option))
    end
    confirmSelection() -- Press A to confirm the selection once we're on the right option
    for i = 1, 60 do emu.frameadvance() end -- Wait a few frames for the menu to react
end


function confirmSelection()
    print("Pressing A...")
    -- Hold A for 3 frames to ensure the game engine polls it
    for i = 1, 3 do
        joypad.set(1, {A=true})
        emu.frameadvance()
    end
    
    -- Release A and wait for the menu to react
    joypad.set(1, {A=false})
    for i = 1, 10 do emu.frameadvance() end 
end