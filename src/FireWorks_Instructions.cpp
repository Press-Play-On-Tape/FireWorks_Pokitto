#include "FireWorks.h"
#include "images/images.h"
#include "utils/Utils.h"
#include "utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::instructions_Init() {

    this->gameState = GameState::Instructions;
    this->instructionScreenVars.reset();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::instructions() {


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_RIGHT)) { 

        #ifdef LEVELS
        if (this->instructionScreenVars.page < 5) {
            this->instructionScreenVars.page++;
        }
        else {
            this->gameState = GameState::Title;
        }
        #else
        if (this->instructionScreenVars.page < 4) {
            this->instructionScreenVars.page++;
        }
        else {
            this->gameState = GameState::Title;
        }
        #endif

    }         

    if (PC::buttons.pressed(BTN_LEFT)) { 

        if (this->instructionScreenVars.page > 0) {
            this->instructionScreenVars.page--;
        }
        else {
            this->gameState = GameState::Title;
        }

    }         


    PD::drawBitmap(0, 0, Images::Instructions[this->instructionScreenVars.page]);

    if (this->instructionScreenVars.page == 2) {

        switch (static_cast<ExplosionColor>((PC::frameCount % 18) / 6)) {

            case ExplosionColor::Red:
                PD::drawBitmap(51, 79, Images::Rocket_Moving_Up_Red[1]);
                break;

            case ExplosionColor::Green:
                PD::drawBitmap(51, 79, Images::Rocket_Moving_Up_Green[1]);
                break;

            case ExplosionColor::Blue:
                PD::drawBitmap(51, 79, Images::Rocket_Moving_Up_Blue[1]);
                break;

            default:
                break;
                
        }

        PD::setColor(0);
        PD::drawFastHLine(0, 85, 110);
        PD::setColor(8);
        PD::drawFastHLine(0, 86, 110);
        PD::setColor(2);
        PD::drawFastHLine(0, 87, 110);

    }

}
