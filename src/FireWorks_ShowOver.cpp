#include "FireWorks.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::showOver_Init() {

    this->cookie->saveCookie();
    this->playTheme(Themes::ShowOver);
    this->gameState = GameState::ShowOver;
    this->rocketSelection.clearSelections();
    this->gameScreenVars.counter = 0;

    for (Rocket &rocket : this->rockets.rockets) {

        if (rocket.getActive()) {

            this->explode(static_cast<int16_t>(rocket.getX()) + 3, static_cast<int16_t>(rocket.getY()) + 3, rocket.getShape(), rocket.getColor());
            rocket.reset();

        }

    }

}   

void Game::showOver() {

    if (this->gameScreenVars.counter < 64) {

        this->gameScreenVars.counter++;

    }

    if (PC::buttons.pressed(BTN_A) && this->gameScreenVars.counter >= 64) { 

        this->gameState = GameState::Title_Init;

    }   


    // Render HUD top ..

    this->renderHUD_Top();
    // this->renderSelectionLine();


    // Render HUD bottom ..

    this->renderHUD_Bot(false, true);
    this->renderParticles();

    PD::drawBitmap(21, 30, Images::ShowOver);


}
