#pragma once
#include <map>
#include <iostream> 
#include <string>
#include <cstdint>
#include "../Common/ItemCategory.hpp"
#include "../Include/json.hpp"


struct ItemData {
    private:
        uint16_t id;
        std::string name;
        ItemCategory category;
        uint16_t cost;
        void setId(uint16_t newId) { id = newId; };
        void setName(const std::string& newName) { name = newName; };
        void setCategory(ItemCategory newCategory) { category = newCategory; };
        void setCost(uint16_t newCost) { cost = newCost; };

    public:
        ItemData() = default;
        uint16_t getId() const { return id; };
        std::string getName() const { return name; };
        ItemCategory getCategory() const { return category; };
        uint16_t getCost() const { return cost; };

    static ItemData fromJson(const nlohmann::json& j) {
        ItemData data;
        j.contains("id") && !j["id"].is_null() ? data.setId(j["id"].get<uint16_t>()) : data.setId(0);
        j.contains("identifier") && !j["identifier"].is_null() ? data.setName(j["identifier"].get<std::string>()) : data.setName("Unknown");
        j.contains("category") && !j["category"].is_null() ? data.setCategory(static_cast<ItemCategory>(j["category"].get<int>())) : data.setCategory(ItemCategory::NONE);
        j.contains("cost") && !j["cost"].is_null() ? data.setCost(j["cost"].get<uint16_t>()) : data.setCost(0);
        return data;
    }
};

