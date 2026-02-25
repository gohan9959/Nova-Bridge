#pragma once
#include <cstdint>

enum class CommandType : uint8_t {
    NONE = 0,
    USE_MOVE,
    USE_ITEM,
    SWITCH_POKEMON,
    RUN,
    TALK_OR_CONFIRM // For clearing dialogue boxes
};