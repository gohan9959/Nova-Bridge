require("readJSON")

local configurations_path = "../configurations.json"
local config

function loadConfig()
    config = readJSON(configurations_path)
    if not config then
        print("Failed to load configuration file.")
    else
        print("Configuration file loaded successfully.")
    end
end

function getConfig(key, subkey)
    if not config then 
        print("ERROR: getConfig called but no config is loaded.")
        return nil 
    end

    if subkey then
        local section = config[key]
        return section and section[subkey]
    end
    
    return config[key]
end