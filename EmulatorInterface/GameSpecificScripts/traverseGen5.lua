MENU_OPTIONS = require("menuOptions")

function traverseBattleMenu(current, target)
    if current == nil then joypad.set(1, {up=true}) print("Up button pressed") end
    if current == target then return end -- Already there!

    if current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then
        -- In Gen 5, pressing DOWN from Fight takes you to the last used bottom button.
        -- If we don't know the last one, pressing Down is the first step.
        joypad.set(1, {down=true})
        
    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then joypad.set(1, {up=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then joypad.set(1, {right=true}) emu.frameadvance() joypad.set(1, {right=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then joypad.set(1, {right=true}) end

    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then joypad.set(1, {up=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then joypad.set(1, {left=true}) emu.frameadvance() joypad.set(1, {left=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then joypad.set(1, {left=true}) end

    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then joypad.set(1, {left=true}) emu.frameadvance() joypad.set(1, {up=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then joypad.set(1, {left=true})
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then joypad.set(1, {right=true}) end
    end
    emu.frameadvance()
end

function traverseSubMenus(current, target)
    if not current or not target then 
        print("Navigation Error: Current or Target is nil")
        return 
    end
    if current < 0 or current > 5 then
        print("Navigation Error: Current selection is not a valid submenu option")
        return
    end
    if target < 0 or target > 5 then
        print("Navigation Error: Target selection is not a valid submenu option")
        return
    end
    local curr_pos = {current % 2, math.floor(current / 2)}
    local target_pos = {target % 2, math.floor(target / 2)}
    while curr_pos[1] ~= target_pos[1] or curr_pos[2] ~= target_pos[2] do
        if curr_pos[1] < target_pos[1] then 
            joypad.set(1, {right=true})
            curr_pos[1] = curr_pos[1] + 1
        elseif curr_pos[1] > target_pos[1] then 
            joypad.set(1, {left=true}) 
            curr_pos[1] = curr_pos[1] - 1
        end
        emu.frameadvance()
        if curr_pos[2] < target_pos[2] then 
            joypad.set(1, {down=true})
            curr_pos[2] = curr_pos[2] + 1
        elseif curr_pos[2] > target_pos[2] then 
            joypad.set(1, {up=true})
            curr_pos[2] = curr_pos[2] - 1
        end
        emu.frameadvance()
    end
end
