#include "FireWorks.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderBackground() {

    uint16_t x = (PC::frameCount % 6600) / 60;
    uint8_t i = (PC::frameCount % 60) / 10;

    PD::drawBitmap(x - 110, 49, Images::City_Top);
    PD::drawBitmap(x, 49, Images::City_Top);
    PD::drawBitmap(x - 110, 75, Images::City_Bot[i]);
    PD::drawBitmap(x, 75, Images::City_Bot[i]);

}

void Game::renderHUD_Top() {

    PD::drawBitmap(0, 0, Images::Player_01);
    PD::drawBitmap(93, 0, Images::Top);


    // Render current score ..

    {
        uint8_t digits[7] = {};
        extractDigits(digits, this->gameScreenVars.score);

        uint8_t location = 48;

        for (uint8_t j = 0; j < 7; ++j, location -= 5) {

            PD::drawBitmap(location, 2, Images::Numbers_Orange[digits[j]]);

        }

    }


    // Render high score ..

    {
        uint8_t digits[7] = {};
        extractDigits(digits, this->cookie->getScore());

        uint8_t location = 87;

        for (uint8_t j = 0; j < 7; ++j, location -= 5) {

            PD::drawBitmap(location, 2, Images::Numbers_Orange[digits[j]]);

        }

    }


    // Render selected colours ..

    for (uint8_t i = 0; i < this->rocketSelection.getIndex(); i++) {

        switch (this->rocketSelection.getColor(i)) {

            case ExplosionColor::Red:
                PD::drawBitmap(i * 7, 11, Images::Rocket_Stationary_Red[this->rocketSelection.getDestroyCountdown(i) / 4]);
                break;

            case ExplosionColor::Green:
                PD::drawBitmap(i * 7, 11, Images::Rocket_Stationary_Green[this->rocketSelection.getDestroyCountdown(i) / 4]);
                break;

            case ExplosionColor::Blue:
                PD::drawBitmap(i * 7, 11, Images::Rocket_Stationary_Blue[this->rocketSelection.getDestroyCountdown(i) / 4]);
                break;

            case ExplosionColor::Rainbow:
                PD::drawBitmap(i * 7, 11, Images::Rocket_Stationary_Rainbow[this->rocketSelection.getDestroyCountdown(i) / 4]);
                break;
                
        }

        if (this->rocketSelection.getDestroyCountdown(i) > 0) {

            this->rocketSelection.incDestroyCountdown(i);

            if (this->rocketSelection.getDestroyCountdown(i) == 16) {

                this->rocketSelection.setDestroyCountdown(i, 0);

                for (uint8_t j = 0; j < this->rocketSelection.getIndex(); j--) {

                    for (uint8_t shuffle = j; shuffle < Constants::SelectedColor_Count - 1; shuffle++) {

                        this->rocketSelection.setColor(shuffle, this->rocketSelection.getColor(shuffle + 1));
                        this->rocketSelection.setIndexes(shuffle, this->rocketSelection.getIndexes(shuffle + 1));

                    }

                    this->rocketSelection.setColor(Constants::SelectedColor_Count - 1, ExplosionColor::None);
                    this->rocketSelection.setIndexes(Constants::SelectedColor_Count - 1, Constants::Rocket_None);
                    this->rocketSelection.setIndex(this->rocketSelection.getIndex() - 1);

                    if (this->rocketSelection.getIndexes(j) == i) {

                        break;

                    }

                }

            }

        }

    }

}

void Game::renderHUD_Bot(bool hideNext, bool flashScore) {

    PD::setColor(3);
    PD::drawFastHLine(0, 85, 91);
    PD::setColor(0);
    PD::drawFastHLine(0, 86, 91);
    PD::drawFastHLine(0, 87, 91);

    for (uint8_t i = 0; i < 4; i++) {

        switch (this->gameScreenVars.nextColors[i]) {

            case ExplosionColor::Blue:
                PD::setColor(12);
                PD::drawFastHLine(36 + (10 * i), 87, 8);
                break;

            case ExplosionColor::Red:
                PD::setColor(8);
                PD::drawFastHLine(36 + (10 * i), 87, 8);
                break;

            case ExplosionColor::Green:
                PD::setColor(11);
                PD::drawFastHLine(36 + (10 * i), 87, 8);
                break;

            case ExplosionColor::Black:
                PD::setColor(5);
                PD::drawFastHLine(36 + (10 * i), 87, 8);
                break;

            case ExplosionColor::Rainbow:
                PD::drawBitmap(36 + (10 * i), 87, Images::RainbowNext);
                break;

            default: break;
                
        }
               
    }


    // Render time left ..

    PD::drawBitmap(92, 78, Images::Time);

    if ((!flashScore || this->gameScreenVars.timeLeft < 10 && PC::frameCount % 60 < 30) || this->gameScreenVars.timeLeft >= 10)  {

        uint8_t digits[4] = {};
        extractDigits(digits, static_cast<uint16_t>(this->gameScreenVars.timeLeft < 0 ? 0 : this->gameScreenVars.timeLeft));

        uint8_t location = 105;

        for (uint8_t j = 0; j < 3; ++j, location -= 5) {

            PD::drawBitmap(location, 80, Images::Numbers_Orange[digits[j]]);

        }

    }



    // Render Next Sign if its visible ..

    if (hideNext && this->gameScreenVars.nextPos <= 64 + 10 && PC::frameCount % 2 == 0) this->gameScreenVars.nextPos++;

    if (this->gameScreenVars.nextPos <= 64) {
        PD::drawBitmap(0, 78, Images::Next);
    } 
    else if (this->gameScreenVars.nextPos > 64 && this->gameScreenVars.nextPos < 64 + 10) {
        PD::drawBitmap(0, this->gameScreenVars.nextPos - 64 + 78, Images::Next);
    }


}


void Game::renderSelectionLine() {


    // Render selection line

    uint8_t x = (this->gameScreenVars.selectedRocketIdx == Constants::Rocket_None ? this->player.getX() : this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getX() + 2);
    uint8_t y = (this->gameScreenVars.selectedRocketIdx == Constants::Rocket_None ? this->player.getY() : this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getY() + 2);
    int8_t angle = this->player.getAng();
    int16_t l2 = angle >= 45 ? -1 : 1;
    
    angle = (angle >= 45 ? angle - 45 : angle);

    int32_t x2 = x + (Constants::Sin[angle] * l2);
    int32_t y2 = y + (Constants::Cos[angle] * l2);

    switch (this->countdown) {

        case 1 ... 8:
            PD::setColor(5);
            break;

        case 9 ... 20:
            PD::setColor(6);
            break;

        case 21 ... 32:
            PD::setColor(7);
            break;
            
    }

    if (this->countdown != 0) {
        PD::drawLine(x, y, x2, y2);
    }

    PD::drawBitmap(x - 4, y - 4, Images::Source);

}


void Game::renderRockets() {

    ExplosionColor nextColor = this->rocketSelection.getValidColor();


    // Render rockets ..

    bool oneRocketHit = false;
    this->gameScreenVars.rocketIdx = Constants::Rocket_None;

    uint8_t x = (this->gameScreenVars.selectedRocketIdx == Constants::Rocket_None ? this->player.getX() : this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getX() + 2);
    uint8_t y = (this->gameScreenVars.selectedRocketIdx == Constants::Rocket_None ? this->player.getY() : this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getY() + 2);

    for (uint8_t i = 0; i < Constants::Rocket_Count; i++) {

        Rocket &rocket = this->rockets.rockets[i];

        if (rocket.getActive()) {

            if (rocket.getDirection() == Direction::Up) {

                switch (rocket.getColor()) {

                    case ExplosionColor::Red:
                        PD::drawBitmap(rocket.getX(), rocket.getY(), Images::Rocket_Moving_Up_Red[PC::frameCount % 8 < 4]);
                        break;

                    case ExplosionColor::Green:
                        PD::drawBitmap(rocket.getX(), rocket.getY(), Images::Rocket_Moving_Up_Green[PC::frameCount % 8 < 4]);
                        break;

                    case ExplosionColor::Blue:
                        PD::drawBitmap(rocket.getX(), rocket.getY(), Images::Rocket_Moving_Up_Blue[PC::frameCount % 8 < 4]);
                        break;

                    case ExplosionColor::Rainbow:
                        PD::drawBitmap(rocket.getX(), rocket.getY(), Images::Rocket_Moving_Up_Rainbow[PC::frameCount % 8 < 4]);
                        break;

                    case ExplosionColor::Black:
                        PD::drawBitmap(rocket.getX(), rocket.getY(), Images::Rocket_Moving_Up_Black[PC::frameCount % 8 < 4]);
                        break;

                }

            }
            else {

                switch (rocket.getColor()) {

                    case ExplosionColor::Red:

                        switch (rocket.stepsToGo()) {

                            case 5 ... 6:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Red[2 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 3 ... 4:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Red[4 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 1 ... 2:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Red[6 + (PC::frameCount % 8 < 4)]);
                                break;

                            default:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Red[PC::frameCount % 8 < 4]);
                                break;

                        }

                        break;

                    case ExplosionColor::Green:

                        switch (rocket.stepsToGo()) {

                            case 5 ... 6:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Green[2 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 3 ... 4:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Green[4 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 1 ... 2:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Green[6 + (PC::frameCount % 8 < 4)]);
                                break;

                            default:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Green[PC::frameCount % 8 < 4]);
                                break;

                        }

                        break;

                    case ExplosionColor::Blue:

                        switch (rocket.stepsToGo()) {

                            case 5 ... 6:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Blue[2 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 3 ... 4:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Blue[4 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 1 ... 2:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Blue[6 + (PC::frameCount % 8 < 4)]);
                                break;

                            default:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Blue[PC::frameCount % 8 < 4]);
                                break;

                        }
                        
                        break;

                    case ExplosionColor::Rainbow:

                        switch (rocket.stepsToGo()) {

                            case 5 ... 6:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Rainbow[2 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 3 ... 4:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Rainbow[4 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 1 ... 2:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Rainbow[6 + (PC::frameCount % 8 < 4)]);
                                break;

                            default:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Rainbow[PC::frameCount % 8 < 4]);
                                break;

                        }
                        
                        break;

                    case ExplosionColor::Black:

                        switch (rocket.stepsToGo()) {

                            case 5 ... 6:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Black[2 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 3 ... 4:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Black[4 + (PC::frameCount % 8 < 4)]);
                                break;

                            case 1 ... 2:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Black[6 + (PC::frameCount % 8 < 4)]);
                                break;

                            default:
                                PD::drawBitmap(rocket.getX(), rocket.getY() - 13, Images::Rocket_Moving_Down_Black[PC::frameCount % 8 < 4]);
                                break;

                        }
                        
                        break;


                }

            }



            // Draw selected box ..

            if (rocket.getSelected() && i != this->gameScreenVars.selectedRocketIdx) {

                PD::setColor(10);
                PD::drawBitmap(rocket.getX() - 2, rocket.getY() - 2, Images::Selected );

            }



            // Draw selection box if rocket is being crossed by line ..

            if (this->countdown != 0) {
                    
                if (!oneRocketHit && this->gameScreenVars.selectedRocketIdx != i && !rocket.getSelected() && (nextColor == ExplosionColor::Rainbow || rocket.getColor() == ExplosionColor::Rainbow || rocket.getColor() == nextColor)) {

                    Rect rocketRect = { rocket.getX(), rocket.getY(), 4, 4 };

                    int8_t angle = this->player.getAng();
                    angle = (angle >= 45 ? angle - 45 : angle);

                    for (uint16_t l = 2; l < 140; l = l + 4) {

                        int16_t l2 = this->player.getAng() >= 45 ? -l : l;
                        int32_t xRect = x + ((Constants::Sin[angle] * l2) / 256);
                        int32_t yRect = y + ((Constants::Cos[angle] * l2) / 256);

                        if (xRect < -11 || xRect > 110 || yRect < -11 || yRect > 88) {

                            break;

                        }
                        else {

                            Rect hitRect = { xRect - 5, yRect - 5, 9, 9 };
                            
                            if (this->collide(rocketRect, hitRect)) {

                                PD::setColor(7);
                                PD::drawBitmap(rocket.getX() - 2, rocket.getY() - 2, Images::Target);
                                oneRocketHit = true;
                                this->gameScreenVars.rocketIdx = i;

                                break;

                            }

                        }

                    }

                }

            }


            // Update rocket position ..

            if (PC::frameCount % (this->rockets.getSpeed(this->gameScreenVars.targetScoreLevel) + (i % 3)) == 0) {

                ExplosionColor explosionColor = rocket.getColor();
                bool selected = rocket.getSelected();
                uint8_t x = static_cast<uint8_t>(this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getX());
                uint8_t y = static_cast<uint8_t>(this->rockets.rockets[this->gameScreenVars.selectedRocketIdx].getY());

                bool deactivateRocket = rocket.update();


                // If the rocket was deactivated and it was selected then

                if (deactivateRocket && selected) {

                    for (uint8_t j = 0; j < this->rocketSelection.getIndex(); j++) {

                        this->rocketSelection.setDestroyCountdown(j, 4);
                        this->rockets.rockets[this->rocketSelection.getIndexes(j)].setSelected(false);

                        if (this->rocketSelection.getIndexes(j) == i) {

                            break;

                        }

                    }


                    // Selected rocket is the one that disappeared?

                    if (this->gameScreenVars.selectedRocketIdx == i) {

                        this->player.setX(x + 2);
                        this->player.setY(y + 2);
                        this->gameScreenVars.selectedRocketIdx = Constants::Rocket_None;

                    }
                
                }
            
            }
                
        }

    }

}

void Game::renderFloatingScores() {

    for (FloatingScore &floatingScore: this->floatingScores.floatingScores) {
            
        if (floatingScore.getAge() > 0) {

            floatingScore.decAge();

            uint8_t digits[7] = {};
            uint8_t location = floatingScore.getX() + floatingScore.getLength() - 5 + 1;
            extractDigits(digits, floatingScore.getScore());

            PD::setColor(0);
            PD::fillRect(floatingScore.getX() - 3, floatingScore.getY() - 3, floatingScore.getLength() + 6, 10);

            switch (floatingScore.getAge()) {

                case 0 ... 10:
                    {

                        PD::setColor(5);

                        for (uint8_t j = 0; j < floatingScore.getChars(); ++j, location -= 5) {

                            PD::drawBitmap(location, floatingScore.getY(), Images::Numbers_DarkGrey[digits[j]]);

                        }

                    }
                    break;

                case 11 ... 20:
                    {

                        PD::setColor(6);

                        for (uint8_t j = 0; j < floatingScore.getChars(); ++j, location -= 5) {

                            PD::drawBitmap(location, floatingScore.getY(), Images::Numbers_LightGrey[digits[j]]);

                        }

                    }
                    break;

                case 21 ... 30:
                    {

                        PD::setColor(7);

                        for (uint8_t j = 0; j < floatingScore.getChars(); ++j, location -= 5) {

                            PD::drawBitmap(location, floatingScore.getY(), Images::Numbers_White[digits[j]]);

                        }

                    }
                    break;
                    
            }

            PD::drawFastHLine(floatingScore.getX() - 2, floatingScore.getY() - 2, floatingScore.getLength() + 4);
            PD::drawFastHLine(floatingScore.getX() - 2, floatingScore.getY() + 6, floatingScore.getLength() + 4);

        }

    }

}