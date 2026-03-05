require("checkPixels")
require("config")
MENU_OPTIONS = require("menuOptions")

function battleMenuSelectionStatus()
    if checkPixels(getConfig("BATTLE_MENU", "FIGHT_BUTTON"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BATTLE_MENU_OPTIONS.FIGHT
    elseif checkPixels(getConfig("BATTLE_MENU", "BAG_BUTTON"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BATTLE_MENU_OPTIONS.BAG
    elseif checkPixels(getConfig("BATTLE_MENU", "POKEMON_BUTTON"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BATTLE_MENU_OPTIONS.POKEMON
    elseif checkPixels(getConfig("BATTLE_MENU", "RUN_BUTTON"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BATTLE_MENU_OPTIONS.RUN
    else
        return nil
    end
end

function fightMenuSelectionStatus()
    if checkPixels(getConfig("FIGHT_MENU", "MOVE1"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.FIGHT_MENU_OPTIONS.MOVE_1
    elseif checkPixels(getConfig("FIGHT_MENU", "MOVE2"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.FIGHT_MENU_OPTIONS.MOVE_2
    elseif checkPixels(getConfig("FIGHT_MENU", "MOVE3"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.FIGHT_MENU_OPTIONS.MOVE_3
    elseif checkPixels(getConfig("FIGHT_MENU", "MOVE4"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.FIGHT_MENU_OPTIONS.MOVE_4
    else
        return nil
    end
end

function pokemonMenuSelectionStatus()
    if checkPixels(getConfig("POKEMON_MENU", "POKEMON1"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON1
    elseif checkPixels(getConfig("POKEMON_MENU", "POKEMON2"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON2
    elseif checkPixels(getConfig("POKEMON_MENU", "POKEMON3"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON3
    elseif checkPixels(getConfig("POKEMON_MENU", "POKEMON4"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON4
    elseif checkPixels(getConfig("POKEMON_MENU", "POKEMON5"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON5
    elseif checkPixels(getConfig("POKEMON_MENU", "POKEMON6"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.POKEMON_MENU_OPTIONS.POKEMON6
    else
        return nil
    end
end

function bagMenuSelectionStatus()
    if checkPixels(getConfig("BAG_MENU", "HP_PP"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BAG_MENU_OPTIONS.HP_PP
    elseif checkPixels(getConfig("BAG_MENU", "STATUS_RESTORE"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BAG_MENU_OPTIONS.STATUS_RESTORE
    elseif checkPixels(getConfig("BAG_MENU", "POKEBALLS"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BAG_MENU_OPTIONS.POKEBALLS
    elseif checkPixels(getConfig("BAG_MENU", "BATTLE_ITEMS"), getConfig("SELECTION_MARKER_COLORS")) then
        return MENU_OPTIONS.BAG_MENU_OPTIONS.BATTLE_ITEMS
    else
        return nil
    end
end