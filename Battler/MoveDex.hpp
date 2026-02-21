#include <map>
#include <string>
#include "Type.hpp" 
#include "MoveCategory.hpp"

struct MoveData {
    std::string name;
    Type type;
    uint16_t power;
    uint8_t accuracy;
    uint8_t priority;
    MoveCategory category;
    uint8_t effectId; // ID for the move's secondary effect, 0 if no secondary effect
    uint8_t effectChance; // Chance for secondary effect to occur, 0 if no secondary effect

};

class MoveDex {
private:
    static std::map<uint16_t, MoveData> moveDex;
    static MoveData nullResult;
public:
    MoveDex() = delete; // Prevent instantiation of the MoveDex class
    static void load(const std::string& path);
    static const MoveData& get(uint16_t id);
};