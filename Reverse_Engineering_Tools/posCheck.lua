local px = 100
local py = 80

print("--- 1-PIXEL PRECISION PROBE ---")
print("Arrows: Move | Hold Shift: Slow (1px) | Hold Ctrl: Fast (5px)")

while true do
    local keys = input.get()
    
    -- Precise movement logic
    local speed = 2 -- Default
    if keys["shift"]   then speed = 1 end
    if keys["control"] then speed = 5 end
    
    if keys["up"]    then py = py - speed end
    if keys["down"]  then py = py + speed end
    if keys["left"]  then px = px - speed end
    if keys["right"] then px = px + speed end
    
    -- 1. READ PIXEL (Do this before drawing anything)
    local r,g,b,a = gui.getpixel(px, py)
    
    -- 2. DRAW CROSSHAIR WITH 1-PIXEL HOLE
    -- We draw lines up to the pixel but stop exactly 1 pixel away
    gui.drawline(px - 4, py, px - 1, py, "red") -- Left
    gui.drawline(px + 1, py, px + 4, py, "red") -- Right
    gui.drawline(px, py - 4, px, py - 1, "red") -- Top
    gui.drawline(px, py + 1, px, py + 4, "red") -- Bottom

    -- 3. INTERFACE
    --gui.drawbox(16, 100, 30, "black", "black")
    gui.text(5, 170,  string.format("X:%d Y:%d", px, py))
    gui.text(5, 185, string.format("RGB: %d,%d,%d", r, g, b))

    emu.frameadvance()
end