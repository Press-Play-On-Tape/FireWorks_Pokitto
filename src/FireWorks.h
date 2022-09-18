#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include "Utils/SFXVolumeSource.hpp"
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
#include "sounds/Sounds.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        TitleScreenVariables titleScreenVars;
        GameScreenVars gameScreenVars;
        InstructionScreenVariables instructionScreenVars;
        Particles particles;
        Rockets rockets;
        RocketSelection rocketSelection;
        Player player;
        FloatingScores floatingScores;

        GameState gameState = GameState::Splash;
        GameCookie *cookie;

        File mainThemeFile;      
        uint8_t countdown = 0;
        bool pause = false;

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void title_Init();
        void title();
        void showTarget_Init();
        void showTarget();
        void game_Init();
        void game();
        void targetAchieved_Init();
        void targetAchieved();
        void showOver_Init();
        void showOver();
        void instructions_Init();
        void instructions();

        bool collide(Rect rect1, Rect rect2);
        bool collide(Point point, Rect rect);

        uint8_t getUnselectedColorCount(ExplosionColor color);

        void renderBackground();
        void renderHUD_Top();
        void renderHUD_Bot(bool hideNext, bool flashScore);
        void renderSelectionLine();
        void renderRockets();
        void renderFloatingScores();


        // Music and sounds ..

        void playTheme(Themes theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);


        // Explosions ..

        void explode(int16_t x, int16_t y, ExplosionShape explosionShape, ExplosionColor color);
        void renderParticles();
        float getRandomFloat(int8_t min, uint8_t max);
        float getRandomFloat(float min, float max);
        uint8_t getBlueShade(uint8_t page);
        uint8_t getRedShade(uint8_t page);
        uint8_t getGreenShade(uint8_t page);
        void chainExplosions();

};

