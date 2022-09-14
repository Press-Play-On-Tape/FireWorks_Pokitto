#pragma once

namespace Images {

    #include "title/Title.h"
    #include "title/TargetScore.h"
    #include "title/ShowOver.h"
    #include "title/Options.h"
    #include "title/High.h"

    #include "title/TargetAchieved_00.h"
    #include "title/TargetAchieved_01.h"
    #include "title/TargetAchieved_02.h"

    #include "title/TargetRow_2.h"
    #include "title/TargetRow_3.h"
    #include "title/TargetRow_4.h"
    #include "title/TargetRow_5.h"

    const uint8_t * const TargetAchieved[] = { 
        TargetAchieved_00,
        TargetAchieved_02,
        TargetAchieved_01,
        TargetAchieved_02,
    };

    const uint8_t * const TargetRows[] = { 
        TargetRow_2,
        TargetRow_2,
        TargetRow_2,
        TargetRow_3,
        TargetRow_4,
        TargetRow_5,
    };

};