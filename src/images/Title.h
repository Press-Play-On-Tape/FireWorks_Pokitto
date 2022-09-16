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

    #include "title/Play_Highlighted_00.h"
    #include "title/Play_Highlighted_01.h"
    #include "title/Play_Highlighted_02.h"
    #include "title/Play_Highlighted_03.h"
    #include "title/Play_Highlighted_04.h"

    #include "title/Rules_Highlighted_00.h"
    #include "title/Rules_Highlighted_01.h"
    #include "title/Rules_Highlighted_02.h"
    #include "title/Rules_Highlighted_03.h"
    #include "title/Rules_Highlighted_04.h"

    #include "title/Sound_Music_Highlighted_00.h"
    #include "title/Sound_Music_Highlighted_01.h"
    #include "title/Sound_Music_Highlighted_02.h"
    #include "title/Sound_Music_Highlighted_03.h"
    #include "title/Sound_Music_Highlighted_04.h"

    #include "title/Sound_Both_Highlighted_00.h"
    #include "title/Sound_Both_Highlighted_01.h"
    #include "title/Sound_Both_Highlighted_02.h"
    #include "title/Sound_Both_Highlighted_03.h"
    #include "title/Sound_Both_Highlighted_04.h"

    #include "title/Sound_None_Highlighted_00.h"
    #include "title/Sound_None_Highlighted_01.h"
    #include "title/Sound_None_Highlighted_02.h"
    #include "title/Sound_None_Highlighted_03.h"
    #include "title/Sound_None_Highlighted_04.h"

    #include "title/Sound_SFX_Highlighted_00.h"
    #include "title/Sound_SFX_Highlighted_01.h"
    #include "title/Sound_SFX_Highlighted_02.h"
    #include "title/Sound_SFX_Highlighted_03.h"
    #include "title/Sound_SFX_Highlighted_04.h"


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

    const uint8_t * const Play_Highlighted[] = { 
        Play_Highlighted_00,
        Play_Highlighted_01,
        Play_Highlighted_02,
        Play_Highlighted_03,
        Play_Highlighted_04,
    };
    
    const uint8_t * const Rules_Highlighted[] = { 
        Rules_Highlighted_00,
        Rules_Highlighted_01,
        Rules_Highlighted_02,
        Rules_Highlighted_03,
        Rules_Highlighted_04,
    };
    
    const uint8_t * const Sound_Both_Highlighted[] = { 
        Sound_Both_Highlighted_00,
        Sound_Both_Highlighted_01,
        Sound_Both_Highlighted_02,
        Sound_Both_Highlighted_03,
        Sound_Both_Highlighted_04,
    };
    
    const uint8_t * const Sound_None_Highlighted[] = { 
        Sound_None_Highlighted_00,
        Sound_None_Highlighted_01,
        Sound_None_Highlighted_02,
        Sound_None_Highlighted_03,
        Sound_None_Highlighted_04,
    };

    const uint8_t * const Sound_Music_Highlighted[] = { 
        Sound_Music_Highlighted_00,
        Sound_Music_Highlighted_01,
        Sound_Music_Highlighted_02,
        Sound_Music_Highlighted_03,
        Sound_Music_Highlighted_04,
    };

    const uint8_t * const Sound_SFX_Highlighted[] = { 
        Sound_SFX_Highlighted_00,
        Sound_SFX_Highlighted_01,
        Sound_SFX_Highlighted_02,
        Sound_SFX_Highlighted_03,
        Sound_SFX_Highlighted_04,
    };    

    const uint8_t Highlight_Seq[]= { 0, 1, 2, 3, 4, 3, 2, 1, };


};