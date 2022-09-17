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

}
