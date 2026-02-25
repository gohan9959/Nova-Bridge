#pragma once
#include <string>
#include <cstdint>
#include "../Common/ItemCategory.hpp"

class Item {
private:
    uint16_t id;
    uint8_t quantity;
    std::string name;
    ItemCategory category;

public:
    Item();
    Item(uint16_t id, uint8_t quantity, const std::string& name, ItemCategory category)
        : id(id), quantity(quantity), name(name), category(category) {}

    uint16_t getId() const { return id; }
    uint8_t getQuantity() const { return quantity; }
    const std::string& getName() const { return name; }
    ItemCategory getCategory() const { return category; }

    ~Item() {}
};