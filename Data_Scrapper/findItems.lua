local headersAndOffsets = require("headersAndOffsetsGen5")

function findItems()
    local item = ""
    -- Parse Items
    for i = 0, headersAndOffsets.ITEM_SIZE, 4 do
        local id = memory.readword(headersAndOffsets.ITEM_BASE + i)
        local qty = memory.readword(headersAndOffsets.ITEM_BASE + i + 2)
        if id > 0 then
            item = item .. string.format("-------------------\nITEM|ID:%d|QTY:%d\n-------------------\n", id, qty)
        end
    end
    if item == "" then
        item = "No items found in inventory."
    end
    return item
end