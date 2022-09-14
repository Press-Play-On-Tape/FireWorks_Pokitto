
#pragma once

#include "Rocket.h"

class Rockets {

    public:

        Rocket rockets[Constants::Rocket_Count];
        bool chainExplosions = false;

    public:
        
        bool getChainExplosions()               { return this->chainExplosions; }
        void setChainExplosions(bool val)       { this->chainExplosions = val; }

        void reset() {

            for (Rocket &rocket : this->rockets) {

                rocket.reset();

            }

        }

        uint8_t getInactiveRocketIndex() {

            for (uint8_t i = 0; i < Constants::Rocket_Count; i++) {

                Rocket &rocket = this->rockets[i];

                if (!rocket.getActive()) {

                    return i;

                }

            }

            return Constants::Rocket_None;

        }

        uint8_t getActiveCount() {

            uint8_t numberOfActiveRockets = 0;

            for (uint8_t i = 0; i < Constants::Rocket_Count; i++) {

                Rocket &rocket = this->rockets[i];

                if (rocket.getActive()) {

                    numberOfActiveRockets++;

                }

            }

            return numberOfActiveRockets;

        }

        uint8_t getSpeed(uint8_t level) {

            switch (level) {

                case 0 ... 3:
                    return 5;

                case 4 ... 8:
                    return 4;

                case 9 ... 255:
                    return 3;
                    
            }
        
        }


};
