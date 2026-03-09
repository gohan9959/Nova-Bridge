#pragma once
#include <cstdint>

enum class StatusCondition : uint8_t {
    NONE = 0,
    BURNED = 1,
    FROZEN = 2,
    PARALYZED = 3,
    POISONED = 4,
    SLEEP = 5
};