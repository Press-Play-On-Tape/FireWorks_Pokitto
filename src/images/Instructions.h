#pragma once

#include "../utils/Enums.h"

namespace Images {

    #include "instructions/Instructions_00.h"
    #include "instructions/Instructions_01.h"
    #include "instructions/Instructions_02.h"
    #include "instructions/Instructions_03.h"
    #include "instructions/Instructions_04.h"
    #include "instructions/Instructions_05.h"
    #include "instructions/Instructions_06.h"

    #ifdef LEVELS
    const uint8_t * const Instructions[] = { 
        Instructions_00,
        Instructions_01,
        Instructions_02,
        Instructions_03,
        Instructions_04,
        Instructions_05,
        Instructions_06,
    };
    #else
    const uint8_t * const Instructions[] = { 
        Instructions_00,
        Instructions_01,
        Instructions_02,
        Instructions_03,
        Instructions_04,
        Instructions_05,
    };
    #endif

};