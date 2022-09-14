#include "FireWorks.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::showTarget_Init() {

    this->gameState = GameState::ShowTarget;
    this->particles.reset();
    this->rockets.reset();
    this->rocketSelection.clearSelections();

    this->gameScreenVars.nextPos = 0;

    for (uint8_t i = 0; i < 4; i++) {

        this->gameScreenVars.nextColors[i] = static_cast<ExplosionColor>(random(0, static_cast<uint8_t>(ExplosionColor::Max)));

    }

    this->player.reset();
    this->gameScreenVars.startRound();
    this->floatingScores.reset();

    PC::frameCount = 0;
    this->gameScreenVars.counter = 0;


    switch (this->gameScreenVars.targetScoreLevel) {

        case 1:
        case 4 ... 5:
            PC::setFrameRate(60);
            break;

        case 2:
        case 6 ... 7:
            PC::setFrameRate(65);
            break;

        case 3:
        case 8 ... 255:
            PC::setFrameRate(70);
            break;

        default:
            PC::setFrameRate(70);
            break;

    }

}   

void Game::showTarget() {

    if (this->gameScreenVars.counter < 64) {

        this->gameScreenVars.counter++;

    }

    if (PC::buttons.pressed(BTN_A) && this->gameScreenVars.counter >= 64) { 

        this->gameState = GameState::Game;

    }   


    // Render HUD top ..

    this->renderHUD_Top();


    // Render HUD bottom ..

    this->renderHUD_Bot(false, true);
    this->renderParticles();

    PD::drawBitmap(34, 36, Images::TargetScore);

    if (this->gameScreenVars.getSequenceLength() > 1 && PC::frameCount % 160 < 80) {

        PD::drawBitmap(37, 45, Images::TargetRows[this->gameScreenVars.getSequenceLength() - 1]);

    }
    else {

        uint8_t digits[7] = {};
        extractDigits(digits, this->gameScreenVars.targetScore);

        uint8_t location = 68;

        for (uint8_t j = 0; j < 7; ++j, location -= 5) {

            PD::drawBitmap(location, 45, Images::Numbers_Orange[digits[j]]);

        }

    }

}
