#include "FireWorks.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

float Game::getRandomFloat(int8_t min, uint8_t max) {

    return min + ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (max - min));

}


float Game::getRandomFloat(float min, float max) {

    return min + ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (max - min));

}

void Game::explode(int16_t x, int16_t y, ExplosionShape explosionShape, ExplosionColor explosionColor) {

    bool isBlue = false;

    const uint8_t sizeMax = 4;
    const uint8_t deltaMax = 2;
    const uint8_t ageMax_Main = 12;
    const uint8_t ageMax_Parts = 18;
    const uint8_t ageStart = 3;
    const uint8_t particlesToLaunch = 50;

    int8_t xDirection = 0;
    int8_t yDirection = 0;

    switch (explosionShape) {

        case ExplosionShape::Normal:
            break;

        case ExplosionShape::Line:
            xDirection = random(0, 2) == 0 ? -1 : 1;
            yDirection = random(0, 2) == 0 ? -1 : 1;
            break;

    }


    for (uint8_t i = 0; i < particlesToLaunch; i++) {

        uint8_t particleIdx = this->particles.getInactiveParticle();

        if (particleIdx != Constants::Particle_None) {

            Part &particle = this->particles.particles[particleIdx];

            particle.setActive(true);
            particle.setX(x);
            particle.setY(y);
            particle.setAge(random(0, ageStart));
            particle.setColor(explosionColor);

            if (i > particlesToLaunch / 4) {

                // Particles ..

                switch (explosionShape) {

                    case ExplosionShape::Normal:
                        particle.setMaxAge(ageMax_Parts + random(0, ageMax_Parts));
                        particle.setDeltaX(6 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setDeltaY(6 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setSize(1);
                        particle.setGravity(true);
                        break;

                    case ExplosionShape::Line:
                        particle.setMaxAge(ageMax_Parts + random(0, ageMax_Parts));
                        particle.setDeltaX(4 * this->getRandomFloat(0, deltaMax) * xDirection * (i % 2 == 0 ? -1 : 1));
                        particle.setDeltaY(4 * this->getRandomFloat(0, deltaMax) * yDirection * (i % 2 == 0 ? -1 : 1));
                        particle.setSize(1);
                        particle.setGravity(true);
                        break;

                    case ExplosionShape::Gravity:
                        particle.setMaxAge(ageMax_Parts + random(0, ageMax_Parts));
                        particle.setDeltaX(4 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setDeltaY(4 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setSize(1);
                        particle.setGravity(true);
                        break;

                }

            }
            else {

                // Large circles ..

                switch (explosionShape) {

                    case ExplosionShape::Normal:
                        particle.setMaxAge(ageMax_Main + random(0, ageMax_Main));
                        particle.setDeltaX(3 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setDeltaY(3 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setSize(this->getRandomFloat(1, sizeMax));
                        particle.setGravity(true);
                        break;

                    case ExplosionShape::Line:
                        particle.setMaxAge(ageMax_Main + random(0, ageMax_Main));
                        particle.setDeltaX(3 * this->getRandomFloat(0, deltaMax) * xDirection * (i % 2 == 0 ? -1 : 1));
                        particle.setDeltaY(3 * this->getRandomFloat(0, deltaMax) * yDirection * (i % 2 == 0 ? -1 : 1));
                        particle.setSize(this->getRandomFloat(1, sizeMax));
                        particle.setGravity(true);
                        break;

                    case ExplosionShape::Gravity:
                        particle.setMaxAge(ageMax_Main + random(0, ageMax_Main));
                        particle.setDeltaX(3 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setDeltaY(3 * this->getRandomFloat(-deltaMax, deltaMax));
                        particle.setSize(this->getRandomFloat(1, sizeMax));
                        particle.setGravity(true);
                        break;

                }

            }

        }

    }
    
}


void Game::renderParticles() {

    for (Part &particle : this->particles.particles) {

        if (particle.getActive()) {

            uint8_t color = 7;

            switch (particle.getColor()) {

                case ExplosionColor::Blue:
                    color = this->getBlueShade(particle.getAge());
                    break;

                case ExplosionColor::Red:
                    color = this->getRedShade(particle.getAge());
                    break;

                case ExplosionColor::Green:
                    color = this->getGreenShade(particle.getAge());
                    break;

            }
            
            if (static_cast<uint8_t>(particle.getSize()) <= 1) {

                PD::setColor(color);
                PD::drawPixel(particle.getX(), particle.getY());

            }
            else {

                uint8_t radius = static_cast<uint8_t>(particle.getSize());

                PD::setColor(color);
                PD::fillCircle(particle.getX(), particle.getY(), radius);

            }


            particle.setX(particle.getX() + particle.getDeltaX());
            particle.setY(particle.getY() + particle.getDeltaY() + (particle.getGravity() ? -1 + particle.getGravityY() : 0));

            particle.setDeltaX(particle.getDeltaX() * 0.75);
            particle.setDeltaY(particle.getDeltaY() * 0.75);
            particle.setGravityY(particle.getGravityY() * 1.02);
            particle.incAge();

            if (particle.getAge() > particle.getMaxAge()) {

                particle.setSize(particle.getSize() - 0.5);

            }

            if (particle.getSize() < 0) {

                particle.reset();

            }
  
        }

    }  

}

uint8_t Game::getRedShade(uint8_t page) {

    switch (page) {

        case 6 ... 7:
            return 10;              // Yellow

        case 8 ... 10:
            return 9;               // Orange

        case 11 ... 12:
            return 8;               // Red

        case 13 ... 15:
            return 2;               // Burgundy

        case 16 ... 255:
            return 5;               // Dark Grey

        default:
            return 7;               // White
    }

}

uint8_t Game::getBlueShade(uint8_t page) {

    switch (page) {

        case 6 ... 7:
            return 6;               // Light Grey

        case 8 ... 10:
            return 12;              // Light Blue

        case 11 ... 12:
            return 13;              // Purple

        case 13 ... 15:
            return 1;               // Dark Blue

        case 16 ... 255:
            return 5;               // Dark Grey

        default:
            return 7;               // WHite

    }

}

uint8_t Game::getGreenShade(uint8_t page) {

    switch (page) {

        case 6 ... 7:
            return 6;               // Light Grey

        case 8 ... 10:
            return 10;              // Yellow

        case 11 ... 12:
            return 11;              // Light Green

        case 13 ... 15:
            return 3;               // Dark Green

        case 16 ... 255:
            return 5;               // Dark Grey

        default:
            return 7;               // WHite

    }

}

void Game::chainExplosions() {

    bool activeParticles = false;

    for (Part &particle : this->particles.particles) {

        if (particle.getActive()) {
            
            activeParticles = true;

            if (static_cast<uint8_t>(particle.getSize()) > 1) {

                uint8_t radius = static_cast<uint8_t>(particle.getSize());

                Rect particleRect = { particle.getX() - radius, particle.getY() - radius, radius * 2 , radius * 2 };

                for (Rocket &rocket : this->rockets.rockets) {

                    if (rocket.getActive() && rocket.getY() < 86) {

                        Rect rocketRect = { rocket.getX(), rocket.getY(), 4, 4 };

                        if (this->collide(particleRect, rocketRect)) {

                            uint8_t scoreX = 0;
                            uint8_t scoreY = 0;
                            uint8_t rocketX = static_cast<uint8_t>(rocket.getX());
                            uint8_t rocketY = static_cast<uint8_t>(rocket.getY());
                            ExplosionColor color = rocket.getColor();

                            this->explode(static_cast<int16_t>(rocket.getX()) + 3, static_cast<int16_t>(rocket.getY()) + 3, rocket.getShape(), rocket.getColor());
                            rocket.reset();

                            if (color != ExplosionColor::Black) {

                                uint8_t floatingScoreIdx = this->floatingScores.getInactiveFlotatingScore();
                                uint8_t sequenceLength = this->rocketSelection.getSelectedColorsCount();

                                if (sequenceLength >= this->gameScreenVars.getSequenceLength() && floatingScoreIdx != Constants::FloatingScore_None) {

                                    FloatingScore &floatingScore = this->floatingScores.floatingScores[floatingScoreIdx];
                                    floatingScore.setScore((1 << sequenceLength) * 100);
                                    floatingScore.setAge(18);


                                    // Position score ..

                                    switch (rocketY) {

                                        case 0 ... 20:
                                            scoreY =rocketY + 10;
                                            break;

                                        default:
                                            scoreY = rocketY - 14;
                                            break;

                                    }

                                    switch (rocketX) {

                                        case 0 ... 15:
                                            scoreX = rocketX + 16;
                                            break;

                                        case 95 ... 110:
                                            scoreX = rocketX - 9 - floatingScore.getLength();
                                            break;

                                        default:
                                            scoreX = rocketX - (floatingScore.getLength() / 2);
                                            break;

                                    }

                                    floatingScore.setX(scoreX);
                                    floatingScore.setY(scoreY);
                                    floatingScore.setScore(this->gameScreenVars.scoreThisRound);
                                    floatingScore.setAge(30);

                                    this->gameScreenVars.score = this->gameScreenVars.score + this->gameScreenVars.scoreThisRound;
                                    if (this->gameScreenVars.score > this->cookie->getScore()) { this->cookie->setScore(this->gameScreenVars.score); }
                                    this->gameScreenVars.scoreThisRound = this->gameScreenVars.scoreThisRound * 2;

                                }

                            }
                            else {

                                this->gameScreenVars.timeLeft = this->gameScreenVars.timeLeft - 5;
                                if (this->gameScreenVars.timeLeft < 0) this->gameScreenVars.timeLeft = 0;

                                //SJH sound effect
                            }

                        }

                    }

                }

            }
  
        }

    }  


    if (!activeParticles) {
        this->rockets.setChainExplosions(false);
    }

}