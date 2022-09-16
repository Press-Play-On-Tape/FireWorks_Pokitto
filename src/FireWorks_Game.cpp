#include "FireWorks.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// Encapsulates the rocket selection ..

void Game::game_Init() {

    this->gameState = GameState::ShowTarget_Init;
    this->gameScreenVars.reset();

    PC::frameCount = 0;

}   


void Game::game() {

    if (this->countdown > 0)             this->countdown--;


    // Handle movements ..

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) { 

        if (PC::buttons.pressed(BTN_B)) { 

            this->player.decAng(15);
            this->countdown = 32;

        }
        else {

            this->player.decAng(1);
            this->countdown = 32;

        }

    }         

    else if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) { 

        if (PC::buttons.pressed(BTN_B)) { 

            this->player.incAng(15);
            this->countdown = 32;

        }
        else {

            this->player.incAng(1);
            this->countdown = 32;

        }

    }         

    else if (PC::buttons.pressed(BTN_UP)) { 

        this->player.incAng(15);
        this->countdown = 32;

    }         

    if (PC::buttons.pressed(BTN_DOWN)) { 

        this->player.decAng(15);
        this->countdown = 32;

    }       

    if (PC::buttons.pressed(BTN_A) && this->gameScreenVars.rocketIdx != Constants::Rocket_None) { 

        Rocket &rocket = this->rockets.rockets[this->gameScreenVars.rocketIdx];
        this->countdown = 32;

        if (rocket.getColor() != ExplosionColor::Black) {

            this->gameScreenVars.selectedRocketIdx = this->gameScreenVars.rocketIdx;
            this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].setSelected(true);
            this->rocketSelection.set(this->rockets.rockets[this->gameScreenVars.rocketIdx].getColor(), this->gameScreenVars.rocketIdx);

        }
        else {

            this->explode(static_cast<int16_t>(rocket.getX()) + 3, static_cast<int16_t>(rocket.getY()) + 3, rocket.getShape(), rocket.getColor());
            rocket.reset();

            this->gameScreenVars.timeLeft = this->gameScreenVars.timeLeft - 5;
            if (this->gameScreenVars.timeLeft < 0) this->gameScreenVars.timeLeft = 0;

            //SJH sound effect

        }

    }         

    if (PC::buttons.pressed(BTN_B)) { 


        // Have any rockets been selected? 

        bool selected = false;

        for (Rocket &rocket : this->rockets.rockets) {

            if (rocket.getSelected()) {

                selected = true;
                break;

            }

        }

        if (selected) {


            // If there is a rainbow selected, then set the flag to trigger chain explosions ..

            this->rockets.setChainExplosions(this->rocketSelection.hasRainbowSelected());



            uint8_t scoreX = 0;
            uint8_t scoreY = 0;
            this->gameScreenVars.scoreThisRound = this->rocketSelection.getScore();

            this->player.setX(static_cast<uint8_t>(this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getX()) + 2);
            this->player.setY(static_cast<uint8_t>(this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getY()) + 2);

            uint8_t floatingScoreIdx = this->floatingScores.getInactiveFlotatingScore();
            uint8_t sequenceLength = this->rocketSelection.getSelectedColorsCount();            

            #ifdef LEVELS
            if (sequenceLength >= this->gameScreenVars.getSequenceLength()) {
            #endif
                
                if (floatingScoreIdx != Constants::FloatingScore_None) {

                    FloatingScore &floatingScore = this->floatingScores.floatingScores[floatingScoreIdx];
                    floatingScore.setScore((1 << sequenceLength) * 100);
                    floatingScore.setAge(18);



                    // Position score ..

                    switch (this->player.getY()) {

                        case 0 ... 20:
                            scoreY = this->player.getY() + 10;
                            break;

                        default:
                            scoreY = this->player.getY() - 14;
                            break;

                    }

                    switch (this->player.getX()) {

                        case 0 ... 15:
                            scoreX = this->player.getX() + 16;
                            break;

                        case 95 ... 110:
                            scoreX = this->player.getX() - 9 - floatingScore.getLength();
                            break;

                        default:
                            scoreX = this->player.getX() - (floatingScore.getLength() / 2);
                            break;

                    }

                    floatingScore.setX(scoreX);
                    floatingScore.setY(scoreY);
                    floatingScore.setScore(this->rocketSelection.getScore());
                    floatingScore.setAge(30);

                }

                this->gameScreenVars.score = this->gameScreenVars.score + (this->rocketSelection.getScore());
                if (this->gameScreenVars.score > this->cookie->getScore()) { this->cookie->setScore(this->gameScreenVars.score); }

            #ifdef LEVELS
            }
            #endif

            for (Rocket &rocket : this->rockets.rockets) {

                if (rocket.getSelected()) {

                    this->explode(static_cast<int16_t>(rocket.getX()) + 3, static_cast<int16_t>(rocket.getY()) + 3, rocket.getShape(), rocket.getColor());
                    rocket.reset();

                }

            }

            this->gameScreenVars.selectedRocketIdx = Constants::Rocket_None;
            this->rocketSelection.clearSelections();
            this->playSoundEffect(SoundEffect::Fireworks);

        }

    }      


    // Left adjust next colors ..

    this->gameScreenVars.leftAdjustNextColours();
    

    // Determine the next color to launch ..

    for (uint8_t i = 0; i < 4; i++) {

        if (this->gameScreenVars.nextColors[i] == ExplosionColor::None) {

            uint8_t selected = this->rocketSelection.getSelectedColorsCount();
            uint8_t unselectedSameColor = 0;
            ExplosionColor selectedColor = this->rocketSelection.getColor(0);
            


            // Test to see if the user has chosen a color they cannot complete ..

            if (this->gameScreenVars.lastColor == ExplosionColor::Rainbow) {

                this->gameScreenVars.nextColors[i] = ExplosionColor::Black;

            }
            else {

                if (selected > 0) {
                    unselectedSameColor = this->getUnselectedColorCount(selectedColor);
                }

                if (selected == 2 && unselectedSameColor == 0) {
                    this->gameScreenVars.nextColors[i] = selectedColor;
                }

                else if (selected == 1 && this->getUnselectedColorCount(selectedColor) <= 1) {
                    this->gameScreenVars.nextColors[i] = selectedColor;
                }

                else {

                    if (random(0, Constants::RainbowFreq) == 0) {
                        this->gameScreenVars.nextColors[i] = ExplosionColor::Rainbow;
                    }
                    else {
                        this->gameScreenVars.nextColors[i] = static_cast<ExplosionColor>(random(0, static_cast<uint8_t>(ExplosionColor::Max)));
                    }

                }

            }

            this->gameScreenVars.lastColor = this->gameScreenVars.nextColors[i];

        }

    }


    if (this->gameScreenVars.launchDelay > 0) this->gameScreenVars.launchDelay--;

    if (this->rockets.getActiveCount() < 4 || (this->rockets.getActiveCount() < Constants::Rocket_Count && this->gameScreenVars.launchDelay == 0)) { 

        uint8_t idx = this->rockets.getInactiveRocketIndex();

        if (idx != Constants::Rocket_None) {

            Rocket &rocket = this->rockets.rockets[idx];

            bool launchLocations[8] = { false, false, false, false, false, false, false, false, };
            uint8_t launchLocationsIdx[8] = { 0, 0, 0, 0, 0, 0, 0, 0, };
            uint8_t launchLocationsAvailable = 0;


            // Which launch locations are already used ?

            for (Rocket &rocket : this->rockets.rockets) {

                if (rocket.getActive() && rocket.getY() == 0) {

                    launchLocations[(static_cast<uint8_t>(rocket.getX()) - 10) / 10] = true;

                }

            }



            for (uint8_t i = 0; i < 8; i++) {

                if (!launchLocations[i]) {
                    launchLocationsIdx[launchLocationsAvailable] = i;
                    launchLocationsAvailable++;
                }

            }


            if (launchLocationsAvailable > 0) {

                uint8_t endPoint = 90 - (this->gameScreenVars.targetScoreLevel * 2);

                if (endPoint < 65) endPoint = 65;

                rocket.setActive(true);
                rocket.setColor(this->gameScreenVars.nextColors[0]);
                rocket.setShape(static_cast<ExplosionShape>(random(0, 3)));
                rocket.setX(10 + (launchLocationsIdx[random(0, launchLocationsAvailable)] * 10));
                rocket.setDirection(Direction::Up);
                rocket.setEndPoint(random(55, endPoint));
                rocket.skipSteps(random(4, 12));

                switch (static_cast<uint8_t>(rocket.getX())) {

                    case 10:
                        rocket.setDeltaX(this->getRandomFloat(Constants::Float_Zero, Constants::Float_Wide));
                        break;

                    case 20 ... 30:
                        rocket.setDeltaX(this->getRandomFloat(-Constants::Float_Narrow, Constants::Float_Wide));
                        break;

                    case 40 ... 60:
                        rocket.setDeltaX(this->getRandomFloat(-Constants::Float_Wide, Constants::Float_Wide));
                        break;

                    case 70 ... 90:
                        rocket.setDeltaX(this->getRandomFloat(-Constants::Float_Wide, Constants::Float_Narrow));
                        break;

                    case 100:
                        rocket.setDeltaX(this->getRandomFloat(-Constants::Float_Wide, Constants::Float_Zero));
                        break;
                    
                }

                this->gameScreenVars.nextColors[0] = ExplosionColor::None;

                switch (random(0, 20)) {

                    case 0:
                        this->gameScreenVars.launchDelay = random(300, 500);
                        break;

                    default:
                        this->gameScreenVars.launchDelay = random(90, 280);
                        break;

                }


                // Play sound effects ..

                this->playSoundEffect(SoundEffect::Whistle);

            }

        }

    }        



    // Check if explosions are touching other rockets ..

    if (this->rockets.getChainExplosions()) {

        this->chainExplosions(); 

    }



    // Render stuff ..

    this->renderBackground();
    this->renderHUD_Top();
    this->renderSelectionLine();
    this->renderRockets();
    this->renderHUD_Bot(true, true);
    this->renderParticles();
    this->renderFloatingScores();

    if (PC::frameCount % 60 == 0) {

        this->gameScreenVars.timeLeft--;

    }

    if (this->gameScreenVars.timeLeft == 0) {
        
        if (this->gameScreenVars.targetScore <= gameScreenVars.score) {

            this->gameState = GameState::TargetAchieved_Init;

        }
        else {

            this->gameState = GameState::ShowOver_Init;

        }

    }

}


uint8_t Game::getUnselectedColorCount(ExplosionColor color) {

    uint8_t unselected = 0;

    for (uint8_t i = 0; i < Constants::Rocket_Count; i++) {

        Rocket &rocket = this->rockets.rockets[i];

        if (rocket.getActive() && !rocket.getSelected() && (rocket.getColor() == color || rocket.getColor() == ExplosionColor::Rainbow)) {

            unselected++;

        }

    }

    return unselected;

}
