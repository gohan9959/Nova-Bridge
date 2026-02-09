-- Define the signatures we are looking for in Hex
local signatures = {
    ["btl_pokeparam.c"] = {0x4E, 0x19, 0x62, 0x74, 0x6C, 0x5F, 0x70, 0x6F, 0x6B, 0x65, 0x70, 0x61, 0x72, 0x61, 0x6D, 0x2E, 0x63}
}

function find_all_headers()
    print("--- Starting Memory Scan ---")
    local start_addr = 0x02200000
    local end_addr   = 0x02300000
    local found_headers = {}

    for name, sig in pairs(signatures) do
        local found = false
        for addr = start_addr, end_addr do
            local match = true
            for i = 1, #sig do
                if memory.readbyte(addr + i - 1) ~= sig[i] then
                    match = false
                    break
                end
            end

            if match then
                print(string.format("FOUND [%s] at: 0x%08X", name, addr))
                table.insert(found_headers, addr)
                found = true
                -- We don't 'break' here in case there are multiple hits 
                -- (like player and opponent btl_pokeparam)
            end
        end
        if not found then
            print(string.format("NOT FOUND: [%s]", name))
        end
    end
    print("--- Scan Complete ---")
    return found_headers
end

-- Run once on startup
find_all_headers()

-- Keep the script alive
while true do
    -- Optional: Add a gui text to show the script is ready
    gui.text(10, 10, "Header Hunter Active")
    emu.frameadvance()
end