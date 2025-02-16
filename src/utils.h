#pragma once

#include <cstdint>
#include <cstdlib>

static uint32_t generateId() {
    randomSeed(time(NULL));
    return random(0, 1000);
}
