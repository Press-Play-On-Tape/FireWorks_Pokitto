#pragma once

namespace Images {

    #include "rockets/Rocket_Red_00.h"
    #include "rockets/Rocket_Red_01.h"
    #include "rockets/Rocket_Red_02.h"
    #include "rockets/Rocket_Red_03.h"
    #include "rockets/Rocket_Red_04.h"
    #include "rockets/Rocket_Red_05.h"
    #include "rockets/Rocket_Red_06.h"
    #include "rockets/Rocket_Red_07.h"
    #include "rockets/Rocket_Red_08.h"
    #include "rockets/Rocket_Red_09.h"
    #include "rockets/Rocket_Red_10.h"

    #include "rockets/Rocket_Green_00.h"
    #include "rockets/Rocket_Green_01.h"
    #include "rockets/Rocket_Green_02.h"
    #include "rockets/Rocket_Green_03.h"
    #include "rockets/Rocket_Green_04.h"
    #include "rockets/Rocket_Green_05.h"
    #include "rockets/Rocket_Green_06.h"
    #include "rockets/Rocket_Green_07.h"
    #include "rockets/Rocket_Green_08.h"
    #include "rockets/Rocket_Green_09.h"
    #include "rockets/Rocket_Green_10.h"

    #include "rockets/Rocket_Blue_00.h"
    #include "rockets/Rocket_Blue_01.h"
    #include "rockets/Rocket_Blue_02.h"
    #include "rockets/Rocket_Blue_03.h"
    #include "rockets/Rocket_Blue_04.h"
    #include "rockets/Rocket_Blue_05.h"
    #include "rockets/Rocket_Blue_06.h"
    #include "rockets/Rocket_Blue_07.h"
    #include "rockets/Rocket_Blue_08.h"
    #include "rockets/Rocket_Blue_09.h"
    #include "rockets/Rocket_Blue_10.h"

    #include "rockets/Rocket_Black_00.h"
    #include "rockets/Rocket_Black_01.h"
    #include "rockets/Rocket_Black_02.h"
    #include "rockets/Rocket_Black_03.h"
    #include "rockets/Rocket_Black_04.h"
    #include "rockets/Rocket_Black_05.h"
    #include "rockets/Rocket_Black_06.h"
    #include "rockets/Rocket_Black_07.h"
    #include "rockets/Rocket_Black_08.h"
    #include "rockets/Rocket_Black_09.h"
    #include "rockets/Rocket_Black_10.h"

    #include "rockets/Rocket_Grey_09.h"
    #include "rockets/Rocket_Grey_10.h"
    #include "rockets/Rocket_Placeholder.h"


    const uint8_t * const Rocket_Stationary_Red[] = { 
        Rocket_Red_00,
        Rocket_Red_09,
        Rocket_Red_10,
        Rocket_Placeholder,
    };

    const uint8_t * const Rocket_Stationary_Green[] = { 
        Rocket_Green_00,
        Rocket_Green_09,
        Rocket_Green_10,
        Rocket_Placeholder,
    };

    const uint8_t * const Rocket_Stationary_Blue[] = { 
        Rocket_Blue_00,
        Rocket_Blue_09,
        Rocket_Blue_10,
        Rocket_Placeholder,
    };

    const uint8_t * const Rocket_Stationary_Black[] = { 
        Rocket_Black_00,
        Rocket_Black_09,
        Rocket_Black_10,
        Rocket_Placeholder,
    };

    const uint8_t * const Rocket_Moving_Up_Red[] = { 
        Rocket_Red_01,
        Rocket_Red_02,
    };

    const uint8_t * const Rocket_Moving_Up_Green[] = { 
        Rocket_Green_01,
        Rocket_Green_02,
    };

    const uint8_t * const Rocket_Moving_Up_Blue[] = { 
        Rocket_Blue_01,
        Rocket_Blue_02,
    };

    const uint8_t * const Rocket_Moving_Up_Black[] = { 
        Rocket_Black_01,
        Rocket_Black_02,
    };

    const uint8_t * const Rocket_Moving_Down_Red[] = { 
        Rocket_Red_03,
        Rocket_Red_04,
        Rocket_Red_05,
        Rocket_Red_06,
        Rocket_Red_07,
        Rocket_Red_08,
        Rocket_Grey_09,
        Rocket_Grey_10,
    };

    const uint8_t * const Rocket_Moving_Down_Green[] = { 
        Rocket_Green_03,
        Rocket_Green_04,
        Rocket_Green_05,
        Rocket_Green_06,
        Rocket_Green_07,
        Rocket_Green_08,
        Rocket_Grey_09,
        Rocket_Grey_10,
    };

    const uint8_t * const Rocket_Moving_Down_Blue[] = { 
        Rocket_Blue_03,
        Rocket_Blue_04,
        Rocket_Blue_05,
        Rocket_Blue_06,
        Rocket_Blue_07,
        Rocket_Blue_08,
        Rocket_Grey_09,
        Rocket_Grey_10,
    };

    const uint8_t * const Rocket_Moving_Down_Black[] = { 
        Rocket_Black_03,
        Rocket_Black_04,
        Rocket_Black_05,
        Rocket_Black_06,
        Rocket_Black_07,
        Rocket_Black_08,
        Rocket_Grey_09,
        Rocket_Grey_10,
    };

};