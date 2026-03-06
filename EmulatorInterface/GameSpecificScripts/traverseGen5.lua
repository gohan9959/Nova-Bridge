require("controllerInputs")
MENU_OPTIONS = require("menuOptions")

function traverseBattleMenu(current, target)
    if current == nil then clickUp() end
    if current == target then return end -- Already there!

    if current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then
        -- In Gen 5, pressing DOWN from Fight takes you to the last used bottom button.
        -- If we don't know the last one, pressing Down is the first step.
        clickDown()
        
    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then clickUp()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then clickRight() clickRight()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then clickRight() end

    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then clickUp()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then clickLeft() clickLeft()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then clickLeft() end

    elseif current == MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN then
        if target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT then clickLeft() clickUp()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG then clickLeft()
        elseif target == MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON then clickRight() end
    end
end

function traverseSubMenus(current, target)
    if not current and not target then 
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
    if current == nil then joypad.set(1, {up=true}) end
    local curr_pos = {current % 2, math.floor(current / 2)}
    local target_pos = {target % 2, math.floor(target / 2)}
    while curr_pos[1] ~= target_pos[1] or curr_pos[2] ~= target_pos[2] do
        if curr_pos[1] < target_pos[1] then 
            clickRight() -- Tap right to move, then release to avoid overshooting
            curr_pos[1] = curr_pos[1] + 1
        elseif curr_pos[1] > target_pos[1] then 
            clickLeft() -- Tap left to move, then release to avoid overshooting 
            curr_pos[1] = curr_pos[1] - 1
        end
        if curr_pos[2] < target_pos[2] then 
            clickDown() -- Tap down to move, then release to avoid overshooting
            curr_pos[2] = curr_pos[2] + 1
        elseif curr_pos[2] > target_pos[2] then 
            clickUp() -- Tap up to move, then release to avoid overshooting
            curr_pos[2] = curr_pos[2] - 1
        end
    end
end
