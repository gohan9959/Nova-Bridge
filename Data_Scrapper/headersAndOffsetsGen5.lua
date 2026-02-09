local HO = {}

-- Anchors and Ranges
HO.SEARCH_START = 0x02200000
HO.SEARCH_END   = 0x02300000
HO.ITEM_BASE    = 0x02233FCC
HO.ITEM_SIZE    = 2492 -- 623 items * 4 bytes each
HO.BATTLE_ANCHOR = {0x4E, 0x19, 0x62, 0x74, 0x6C, 0x5F, 0x70, 0x6F, 0x6B, 0x65, 0x70, 0x61, 0x72, 0x61, 0x6D, 0x2E, 0x63}

-- Battle-State Offsets
HO.BATTLE_OFFS = {
    SPECIES_ID = 0x26,
    MAX_HP = 0x28,
    CUR_HP = 0x2A,
    LEVEL  = 0x32,
    MOVES  = 0x11E, -- Moves start
    MOVE_STRIDE = 0xE, -- Each move is 14 bytes apart
    IS_PLAYER = 0x163, -- Value is 10 27 for player, 00 00 for opponent
    ATTACK = 0x108,
    DEFENSE = 0x10A,
    SPEED = 0x10C,
    SP_ATTACK = 0x10E,
    SP_DEFENSE = 0x110,
    HELD_ITEM = 0x2C,
    ABILITY = 0x30

}

-- Status condition offsets (relative to the combatant base)
HO.STATUS_OFFS = {
    BURNED = 0x45,
    POISONED = 0x49, -- Value set to 01 for regular poison
    PARALYZED = 0x3A,
    SLEEP = 0x3E
}

return HO