function traverseBattleMenu(current, target)
    if current == nil then joypad.set(1, {up=true}) end
    if current == target then return end -- Already there!

    if current == menu_selection.FIGHT then
        -- In Gen 5, pressing DOWN from Fight takes you to the last used bottom button.
        -- If we don't know the last one, pressing Down is the first step.
        joypad.set(1, {down=true})
        
    elseif current == menu_selection.BAG then
        if target == menu_selection.FIGHT then joypad.set(1, {up=true})
        elseif target == menu_selection.POKEMON then joypad.set(1, {right=true}) -- Skip Run
        elseif target == menu_selection.RUN then joypad.set(1, {right=true}) end

    elseif current == menu_selection.POKEMON then
        if target == menu_selection.FIGHT then joypad.set(1, {up=true})
        elseif target == menu_selection.BAG then joypad.set(1, {left=true}) -- Skip Run
        elseif target == menu_selection.RUN then joypad.set(1, {left=true}) end

    elseif current == menu_selection.RUN then
        if target == menu_selection.FIGHT then joypad.set(1, {left=true}) emu.frameadvance() joypad.set(1, {up=true})
        elseif target == menu_selection.BAG then joypad.set(1, {left=true})
        elseif target == menu_selection.POKEMON then joypad.set(1, {right=true}) end
    end
    emu.frameadvance()
end