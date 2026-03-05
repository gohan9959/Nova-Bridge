local headersAndOffsets = require("headersAndOffsetsGen5")

local json = require("Require.dkjson")

function findItems()
    local inventory = {} -- This table will hold our list of item objects

    -- Parse Items
    -- We loop through the item memory block
    for i = 0, headersAndOffsets.ITEM_SIZE, 4 do
        local id = memory.readword(headersAndOffsets.ITEM_BASE + i)
        local qty = memory.readword(headersAndOffsets.ITEM_BASE + i + 2)
        
        -- Only add valid items (ID > 0) to our list
        if id > 0 then
            table.insert(inventory, {
                id = id,
                quantity = qty
            })
        end
    end

    -- If the inventory is empty, return an empty JSON array []
    -- This is much easier for C++ to handle than a "No items found" string
    return json.encode(inventory, { indent = true })
end