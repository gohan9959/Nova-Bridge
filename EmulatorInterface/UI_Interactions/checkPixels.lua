function checkPixels(pixels, color)
    local result = true
    local color_match = false
    for _, pixel in pairs(pixels) do
        print(string.format("Checking pixel at (%s, %s)", pixel["X"], pixel["Y"]))
        local r, g, b, a = gui.getpixel(tonumber(pixel["X"]), tonumber(pixel["Y"]))
        print(string.format("Pixel color: R=%d, G=%d, B=%d", r, g, b))
        for _, color in pairs(color) do
            print(string.format("Comparing against color: R=%s, G=%s, B=%s", color["R"], color["G"], color["B"]))
            color_match = color_match or (r == tonumber(color["R"]) and g == tonumber(color["G"]) and b == tonumber(color["B"]))
        end
        result = result and color_match -- Check for the specific color of the battle menu
        color_match = false -- Reset for the next pixel
    end
    
    return result
end