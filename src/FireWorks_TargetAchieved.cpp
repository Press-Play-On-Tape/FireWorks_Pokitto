#include "FireWorks.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::targetAchieved_Init() {

    this->playTheme(Themes::StageComplete);
    this->gameState = GameState::TargetAchieved;
    this->rocketSelection.clearSelections();
    this->gameScreenVars.counter = 0;

    for (Rocket &rocket : this->rockets.rockets) {

        if (rocket.getActive()) {

            this->explode(static_cast<int16_t>(rocket.getX()) + 3, static_cast<int16_t>(rocket.getY()) + 3, rocket.getShape(), rocket.getColor());
            rocket.reset();

        }

    }

}   

void Game::targetAchieved() {

    this->gameScreenVars.counter++;

    if (this->gameScreenVars.counter == 255) {

        this->gameState = GameState::ShowTarget_Init;

    }

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::ShowTarget_Init;

    }   



    // Render HUD top ..

    this->renderBackground();
    this->renderHUD_Top();
    this->renderHUD_Bot(false, false);
    this->renderParticles();


    PD::drawBitmap(34, 36, Images::TargetScore);
    PD::drawBitmap(37, 45, Images::TargetAchieved[(PC::frameCount % 84) / 12]);

}
