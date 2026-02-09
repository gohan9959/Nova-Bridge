local headersAndOffsets = require("headersAndOffsetsGen5")
function find_all_anchors()
    local found_headers = {}
    local found = false
    print("--- Starting Memory Scan ---")
    for addr = headersAndOffsets.SEARCH_START, headersAndOffsets.SEARCH_END do
        local match = true
        for i = 1, #headersAndOffsets.BATTLE_ANCHOR do
            if memory.readbyte(addr + i - 1) ~= headersAndOffsets.BATTLE_ANCHOR[i] then
                match = false
                break
            end
        end

        if match then
            print(string.format("Found header at: 0x%08X", addr))
            table.insert(found_headers, addr)
            found = true
        end
    end
    print("--- Scan Complete ---")
    return found_headers
end

function parse_pokemon_data(anchor, starter)
    local species = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.SPECIES_ID) -- offset for Species ID
    local hp = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.CUR_HP) -- offset for HP
    local max_hp = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.MAX_HP) -- offset for Max HP
    local level = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.LEVEL) -- offset for Level
    local party = ""
    local status = ""
    local pokemon_stats = ""
    local held_item = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.HELD_ITEM)
    local moves = ""
    if starter then
        party = "Player"
    else
        party = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.IS_PLAYER) ~= 0 and "Player" or "Opponent"
    end
    for m = 0, 3 do
        local move_id = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE))
        if move_id > 0 then
            local pp = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE) + 2)
            local max_pp = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE) + 3)
            moves = moves .. string.format("MOVE|SLOT:%d|ID:%d|PP:%d|MAXPP:%d\n", m, move_id, pp, max_pp)
        end
    end
    for s, status_name in pairs(headersAndOffsets.STATUS_OFFS) do
        local status_value = memory.readword(anchor + headersAndOffsets.STATUS_OFFS[s])
        status = status .. string.format("%s:%d|", s, status_value)
    end
    for _, stat_name in pairs({"ATTACK", "DEFENSE", "SPEED", "SP_ATTACK", "SP_DEFENSE", "ABILITY"}) do
        local stat_value = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS[stat_name])
        pokemon_stats = pokemon_stats .. string.format("%s:%d|", stat_name, stat_value)
    end

    return string.format("----------------------------------------------------------\nSpecies:%d\nHP:%d|Max HP:%d\nLevel:%d\nParty:%s\nStats:%s\nStatus:%s\nHeld Item:%d\nMoves:\n%s----------------------------------------------------------\n", species, hp, max_hp, level, party, pokemon_stats, status, held_item, moves)
end

function find_pokemon()
    local anchors = find_all_anchors()
    local pokemon_data = ""
    if #anchors == 0 then
        return "No battle headers found. Cannot parse Pokemon data."
    end
    for i, anchor in ipairs(anchors) do
        if i > #anchors/2 then break end -- Just in case, but should not be needed
        pokemon_data = pokemon_data .. parse_pokemon_data(anchor, i == 1)
    end
    return pokemon_data
end