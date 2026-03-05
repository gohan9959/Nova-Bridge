local json = require("Require.dkjson")

function readJSON(filename)
    local file = io.open(filename, "r") -- Open for reading
    if not file then 
        print("Could not open file: " .. filename)
        return nil 
    end

    local content = file:read("*all") -- Read the entire file string
    file:close()

    -- Convert string back to table
    -- 'pos' is the position where parsing ended, 'err' is any error message
    local data, pos, err = json.decode(content)

    if err then
        print("JSON Decode Error: " .. err)
        return nil
    end

    return data
end