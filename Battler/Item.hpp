#pragma once
#include <string>
#include <cstdint>

class Item {
private:
    uint16_t id;
    uint8_t quantity;
    std::string name;
    std::string description;

public:
    Item();
    Item(uint16_t id, uint8_t quantity, const std::string& name, const std::string& description)
        : id(id), quantity(quantity), name(name), description(description) {}

    uint16_t getId() const { return id; }
    uint8_t getQuantity() const { return quantity; }
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }

    ~Item() {}
};