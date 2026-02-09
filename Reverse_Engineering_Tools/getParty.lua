-- Replace these with the actual values from your Hex Editor at the poke_party.c address
local pid = 0x02259EF4      -- Read the 4 bytes at 0x00659EF4
local checksum = 0x02259EFA     -- Read the 2 bytes at 0x00659EFA
local first_word = 0x02259EFC    -- Read the 2 bytes at 0x00659EFC

function test_decrypt(pid, seed, encrypted_val)
    local LCG_MULT = 0x41C64E6D
    local LCG_ADD = 0x0000605D
    
    -- Step the LCG once using the checksum as the seed
    seed = (seed * LCG_MULT + LCG_ADD) % 0x100000000
    local key = math.floor(seed / 0x10000) -- Get upper 16 bits
    
    local decrypted = bit.bxor(encrypted_val, key)
    return decrypted
end

print(string.format("Decrypted Word: %04X", test_decrypt(pid, checksum, first_word)))