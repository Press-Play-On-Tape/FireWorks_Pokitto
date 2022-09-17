#pragma once

#define _DEBUG
#define SOUNDS
#define COOKIE_INITIALISED 17
#define _LEVELS

namespace Constants {

    constexpr uint16_t Particle_Count = 250;
    constexpr uint16_t Particle_None = 2000;
    constexpr uint8_t Rocket_Count = 10;
    constexpr uint8_t Rocket_None = 255;

    constexpr uint8_t FloatingScore_Count = 5;
    constexpr uint8_t FloatingScore_None = 255;

    constexpr uint8_t Next_Delay = 48;

    constexpr float Float_Zero = 0;
    constexpr float Float_Wide = 0.25;
    constexpr float Float_Narrow = 0.1;

    constexpr uint8_t SelectedColor_Count = 12;
    constexpr uint8_t RainbowFreq = 12;

    constexpr uint16_t Target_Start = 2000;
    constexpr uint16_t Target_Increase = 500;
    constexpr uint16_t Target_Time = 60;

    #ifdef LEVELS
    constexpr uint8_t Levels[] = {
        0, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    };
    #endif

    constexpr uint8_t Sin[] {
        0, 17, 35, 53, 70, 87, 104, 120, 135, 
        150, 164, 177, 190, 201, 212, 221, 230, 
        237, 243, 248, 252, 254, 255, 255, 254, 
        252, 248, 243, 237, 230, 221, 212, 201, 
        190, 177, 164, 150, 135, 120, 104, 87, 
        70, 53, 35, 17, 
    };

    constexpr int16_t Cos[] {
        256, 255, 253, 250, 246, 240, 233, 226, 
        217, 207, 196, 184, 171, 157, 143, 128, 
        112, 95, 79, 61, 44, 26, 8, -8, -26, -44, 
        -61, -79, -95, -112, -127, -143, -157, 
        -171, -184, -196, -207, -217, -226, -233, 
        -240, -246, -250, -253, -255, 
    };

    constexpr uint8_t RocketTrajectory[] {
        87, 86, 85, 84, 83, 82, 81, 80,
        79, 78, 77, 76, 75, 74, 73, 72, 
        71, 70, 69, 68, 67, 66, 65, 64, 
        63, 62, 61, 61, 60, 59, 58, 57, 
        56, 55, 54, 53, 53, 52, 51, 50, 
        49, 48, 47, 46, 45, 44, 44, 43, 
        42, 41, 40, 39, 38, 37, 37, 36, 
        35, 34, 33, 32, 32, 31, 30, 29, 
        28, 27, 27, 26, 25, 24, 23, 22, 
        22, 21, 20, 19, 19, 18, 17, 16, 
        16, 15, 14, 13, 13, 12, 11, 11, 
        10,  9,  9,  8,  7,  7,  6,  6, 
        5,  5,  5,  4,  4,  4,  4,  3, 
        3,  3,  3,  2,  2,  2,  2,  1,
        1,  1,  1,  1,  0,  0,  0,  
    };


};


enum class GameState : uint8_t {
    Splash_Init,
    Splash,
    Title_Init,
    Title,
    ShowTarget_Init,
    ShowTarget,
    Game_Init,
    Game,
    TargetAchieved_Init,
    TargetAchieved,
    ShowOver_Init,
    ShowOver,
    Instructions_Init,
    Instructions
};

enum class EnemyType : uint8_t {
    Rocket,
    FuelDepot,
    GroundPod,
    SurfaceAir,
    Mine,
    City_00,
    City_01,
    City_02,
    FuelCan,
    Eighter,
    Circler,
};

enum class Themes : uint8_t {
    Main,
    StageComplete,
    ShowOver
};

enum class ExplosionShape : int8_t {
    Normal,
    Line,
    Gravity,
};

enum class ExplosionSize : int8_t {
    Small,
    Medium,
    Large,
    Huge
};

enum class ExplosionColor : int8_t {
    Red,
    Blue,
    Green,
    None,
    Max = None,
    Rainbow,
    Black,
};

enum class Direction : uint8_t {
    Left,
    Up,
    Right,
    Down,
    None,
};

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class SoundEffect : uint8_t {
    Whistle,
    Fireworks,
    // Fireworks_1,
    // Fireworks_2,
    // Fireworks_3
};

enum class MenuOptions : uint8_t {
    Play,
    Instructions,
    Sounds
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}