local headersAndOffsets = require("headersAndOffsetsGen5")
local json = require("Require.dkjson")

function findAllAnchors()
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

function parsePokemonData(anchor, starter)
    local data = {
        speciesId = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.SPECIES_ID),
        hp = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.CUR_HP),
        maxHp = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.MAX_HP),
        level = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.LEVEL),
        heldItem = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.HELD_ITEM),
        party = (starter or memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.IS_PLAYER) ~= 0) and "Player" or "Opponent",
        moves = {},  -- Nested table for moves
        status = {}, -- Nested table for status
        stats = {}   -- Nested table for stats
    }

    -- 1. Parse Moves as a list of objects
    for m = 0, 3 do
        local move_id = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE))
        if move_id > 0 then
            table.insert(data.moves, {
                slot = m,
                id = move_id,
                pp = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE) + 2),
                maxPp = memory.readbyte(anchor + headersAndOffsets.BATTLE_OFFS.MOVES + (m * headersAndOffsets.BATTLE_OFFS.MOVE_STRIDE) + 3)
            })
        end
    end

    -- 2. Parse Status
    for s, _ in pairs(headersAndOffsets.STATUS_OFFS) do
        data.status[s] = memory.readword(anchor + headersAndOffsets.STATUS_OFFS[s])
    end

    -- 3. Parse Stats
    for _, stat_name in pairs({"ATTACK", "DEFENSE", "SPEED", "SP_ATTACK", "SP_DEFENSE", "ABILITY"}) do
        data.stats[stat_name] = memory.readword(anchor + headersAndOffsets.BATTLE_OFFS[stat_name])
    end

    return data -- Return the TABLE, not a string
end

function findPokemon()
    local anchors = findAllAnchors()
    local all_pokemon = {} -- This will be our master array

    if #anchors == 0 then
        return json.encode({ error = "No battle headers found" })
    end

    for i, anchor in ipairs(anchors) do
        if i > #anchors/2 then break end 
        
        local p_data = parsePokemonData(anchor, i == 1)
        table.insert(all_pokemon, p_data)
    end

    -- Encode the entire master list into one JSON string
    return json.encode(all_pokemon, { indent = true })
end