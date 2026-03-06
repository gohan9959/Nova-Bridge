function clickLeft()
    -- 1. Press and Hold
    for i = 1, 3 do
        joypad.set(1, {left=true})
        emu.frameadvance()
    end
    
    -- 2. Release and Wait (The Cooldown)
    joypad.set(1, {left=false})
    for i = 1, 10 do 
        emu.frameadvance() 
    end
end

function clickRight()
    -- 1. Press and Hold
    for i = 1, 3 do
        joypad.set(1, {right=true})
        emu.frameadvance()
    end
    
    -- 2. Release and Wait (The Cooldown)
    joypad.set(1, {right=false})
    for i = 1, 10 do 
        emu.frameadvance() 
    end
end

function clickUp()
    -- 1. Press and Hold
    for i = 1, 3 do
        joypad.set(1, {up=true})
        emu.frameadvance()
    end
    
    -- 2. Release and Wait (The Cooldown)
    joypad.set(1, {up=false})
    for i = 1, 10 do 
        emu.frameadvance() 
    end
end

function clickDown()
    -- 1. Press and Hold
    for i = 1, 3 do
        joypad.set(1, {down=true})
        emu.frameadvance()
    end
    
    -- 2. Release and Wait (The Cooldown)
    joypad.set(1, {down=false})
    for i = 1, 10 do 
        emu.frameadvance() 
    end
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