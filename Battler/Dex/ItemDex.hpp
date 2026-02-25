#pragma once
#include <map>
#include <string>
#include <cstdint>
#include "../Common/ItemCategory.hpp"
#include "../Include/json.hpp"


struct ItemDex {
    uint16_t id;
    std::string name;
    ItemCategory category;
    uint16_t cost;

    static ItemDex fromJson(const nlohmann::json& j) {
        return {
            j.at("id").get<uint16_t>(),
            j.at("name").get<std::string>(),
            // Map the integer category_id to your Enum
            static_cast<ItemCategory>(j.at("category_id").get<int>()),
            j.at("cost").get<uint16_t>()
        };
    }

    // The "Error Handler" helper
    static ItemDex makeEmpty() {
        return { 0, "Unknown Item", ItemCategory::NONE };
    }
};

