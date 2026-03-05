function writeToFile(filename, content)
    local tempName = filename .. ".tmp"
    local file = io.open(tempName, "w")
    
    if file then
        file:write(content)
        file:close()
        
        -- Remove the old file and rename the new one
        os.remove(filename)
        os.rename(tempName, filename)
    else
        print(string.format("Error: Could not open file %s for writing.", tempName))
    end
end