local PLAYER_HEADER = 0x0226D6AC
local ENEMY_HEADER  = 0x0226D8D0

function get_battle_summary(base, label)
    if not base or memory.readbyte(base) == 0 then return label .. ": Not in Battle" end

    -- Base offsets we discovered
    local start_offset = 0x11C
    local stride = 0x0E
    
    local move_data = {}

    for i = 0, 3 do
        local move_base = base + start_offset + (i * stride)
        
        local id     = memory.readword(move_base)
        local cur_pp = memory.readbyte(move_base + 2) -- Offset +2 from move ID
        local max_pp = memory.readbyte(move_base + 3) -- Offset +3 from move ID
        
        table.insert(move_data, {id = id, cur = cur_pp, max = max_pp})
    end

    local hp     = memory.readword(base + 0x28)
    local max_hp = memory.readword(base + 0x26)
    local lvl    = memory.readbyte(base + 0x30)

    -- Formatting for C++ log parsing
    local move_str = ""
    for i, m in ipairs(move_data) do
        move_str = move_str .. string.format("[%d: %d/%dPP] ", m.id, m.cur, m.max)
    end

    return string.format("%s | Lvl: %d | HP: %d/%d\n  %s", 
                         label, lvl, hp, max_hp, move_str)
end

while true do
    print(get_battle_summary(PLAYER_HEADER, "PLAYER"))
    print(get_battle_summary(ENEMY_HEADER,  "ENEMY "))
    emu.frameadvance()
end