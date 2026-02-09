function dump_memory_to_file()
    local filename = "full_ram_dump.bin"
    local file = io.open(filename, "wb") -- Open for writing in binary mode
    
    if not file then
        print("Error: Could not create file!")
        return
    end

    print("Dumping memory to " .. filename .. "...")

    -- We are focusing on the 0x02XXXXXX range (Main RAM)
    -- This is where your btl_pokeparam.c addresses live.
    for addr = 0x02000000, 0x02FFFFFF do
        local byte = memory.readbyte(addr)
        file:write(string.char(byte))
        
        -- Optional: Progress indicator in console
        if addr % 0x100000 == 0 then
            print(string.format("Progress: 0x%08X", addr))
        end
    end

    file:close()
    print("Dump Complete! Check your emulator folder.")
end

-- Call the function once
dump_memory_to_file()