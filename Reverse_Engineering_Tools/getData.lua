local search_value = 10 -- your Pokémon’s current HP
local start = 0x02000000
local stop  = 0x02400000

for addr = start, stop, 2 do
    if memory.readshortunsigned(addr) == search_value then
        print(string.format("Possible HP at 0x%X", addr))
    end
end

while true do
    memory.writebyte(0x2233FD2, 100) -- Example: Set the first byte to 0
    emu.frameadvance() -- Advance to the next frame
end