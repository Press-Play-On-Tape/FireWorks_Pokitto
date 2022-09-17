#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"


struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 20;

};


struct TitleScreenVariables {

    MenuOptions menu = MenuOptions::Play;

    void reset() {

    }

};


struct InstructionScreenVariables {

    uint8_t page = 0;

    void reset() {

        this->page = 0;

    }

};


struct GameScreenVars {

    uint32_t score = 0;
    uint32_t scoreThisRound = 0;
    int8_t timeLeft = 0;
    uint32_t targetScore = Constants::Target_Start - Constants::Target_Increase;
    uint32_t targetScore_Init = Constants::Target_Start - Constants::Target_Increase;
    uint8_t targetScoreLevel = 0;
    uint8_t counter = 0;

    uint8_t rocketIdx = Constants::Rocket_None;
    uint8_t selectedRocketIdx = Constants::Rocket_None;

    ExplosionColor nextColors[4];
    ExplosionColor lastColor = ExplosionColor::None;

    uint8_t nextPos = 0;
    uint16_t launchDelay = 0;
    
    ExplosionColor explosionColor = ExplosionColor::Blue;

    #ifdef LEVELS
    uint8_t getSequenceLength() {

        return Constants::Levels[this->targetScoreLevel];

    }
    #endif

    ExplosionColor getColor() {

        switch (this->explosionColor) {

            case ExplosionColor::Blue:
                this->explosionColor = ExplosionColor::Red;
                break;

            case ExplosionColor::Red:
                this->explosionColor = ExplosionColor::Green;
                break;

            case ExplosionColor::Green:
                this->explosionColor = ExplosionColor::Blue;
                break;
                
        }

        return this->explosionColor;

    }

    void reset() {

        this->score = 0;
        this->scoreThisRound = 0;
        this->timeLeft = Constants::Target_Time;
        this->targetScore = Constants::Target_Start - Constants::Target_Increase;
        this->targetScore_Init = Constants::Target_Start - Constants::Target_Increase;
        this->targetScoreLevel = 0;
        this->counter = 0;

        this->rocketIdx = Constants::Rocket_None;
        this->selectedRocketIdx = Constants::Rocket_None;
        this->nextPos = 0;
        this->launchDelay = 0;
        
        ExplosionColor explosionColor = ExplosionColor::Blue;

    }


    void leftAdjustNextColours() {

        for (uint8_t j = 0; j < 4; j++) {

            for (uint8_t i = 0; i < 3; i++) {

                if (this->nextColors[i] == ExplosionColor::None) {

                    this->nextColors[i] = this->nextColors[i + 1];
                    this->nextColors[i + 1] = ExplosionColor::None;

                }

            }

        }

    }


    void startRound() {

        this->timeLeft = Constants::Target_Time;
        this->targetScore_Init = this->targetScore_Init + Constants::Target_Increase;
        this->targetScore = this->score + this->targetScore_Init;
        this->targetScoreLevel++;
        this->selectedRocketIdx = Constants::Rocket_None;
        this->rocketIdx = Constants::Rocket_None;

    }

};