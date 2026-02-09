function writeToFile(filename, content)
    local file = io.open(filename, "w")
    if file then
        file:write(content)
        file:close()
    else
        print(string.format("Error: Could not open file %s for writing.", filename))
    end
end