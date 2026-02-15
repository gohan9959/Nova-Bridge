function trim(s)
   return s:match("^%s*(.-)%s*$")
end

function loadConfig(filename)
    local config = {}
    local f = io.open(filename, "r")
    if not f then return nil end
    for line in f:lines() do
        local key, val = line:match("([^=]+)=(.+)")
        if key and val then
            config[trim(key)] = trim(val)
        end
    end
    f:close()
    return config
end