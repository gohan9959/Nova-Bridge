function checkPixels(pixels, color)
    local check = true
    for _, pixel in pairs(pixels) do
        print(string.format("Checking pixel at (%s, %s)", pixel["X"], pixel["Y"]))
        local r, g, b, a = gui.getpixel(tonumber(pixel["X"]), tonumber(pixel["Y"]))
        print(string.format("Pixel color: R=%d, G=%d, B=%d", r, g, b))
        check = check and ((r == tonumber(color["COLOR1"]["R"]) and g == tonumber(color["COLOR1"]["G"]) and b == tonumber(color["COLOR1"]["B"])) or (r == tonumber(color["COLOR2"]["R"]) and g == tonumber(color["COLOR2"]["G"]) and b == tonumber(color["COLOR2"]["B"]))) -- Check for the specific color of the battle menu
    end
    
    return check
end
    