
#pragma once

#include "FloatingScore.h"

class FloatingScores {

    public:

        FloatingScore floatingScores[Constants::FloatingScore_Count];

    public:
        
        void reset() {

            for (FloatingScore &floatingScore : this->floatingScores) {

                floatingScore.reset();

            }

        }

        uint8_t getInactiveFlotatingScore() {

            for (uint8_t i = 0; i < Constants::FloatingScore_Count; i++) {

                FloatingScore &floatingScore = this->floatingScores[i];

                if (!floatingScore.getAge() > 0) {

                    return i;

                }

            }

            return Constants::FloatingScore_None;

        }

};
