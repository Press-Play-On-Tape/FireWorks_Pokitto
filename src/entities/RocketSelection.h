#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

class RocketSelection {

    private:

        ExplosionColor rocketColors[Constants::SelectedColor_Count];
        uint8_t indexes[Constants::SelectedColor_Count];
        uint8_t destroyCountdown[Constants::SelectedColor_Count];
        uint8_t index = 0;

    public:

        ExplosionColor getColor(uint8_t i)                      { return this->rocketColors[i]; }
        uint8_t getIndexes(uint8_t i)                           { return this->indexes[i]; }
        uint8_t getIndex()                                      { return this->index; }
        uint8_t getDestroyCountdown(uint8_t i)                  { return this->destroyCountdown[i]; }

        void setColor(uint8_t i, ExplosionColor val)            { this->rocketColors[i] = val; }
        void setIndexes(uint8_t i, uint8_t val)                 { this->indexes[i] = val; }
        void setIndex(uint8_t val)                              { this->index = val; }
        void setDestroyCountdown(uint8_t i, uint8_t val)        { this->destroyCountdown[i] = val; }


    public:

        uint16_t getScore() {

            return (1 << (this->getSelectedColorsCount() - 1)) * 100;

        }

        void incDestroyCountdown(uint8_t index) {

            this->destroyCountdown[index]++;

        }

        void set(ExplosionColor color, uint8_t index) {

            this->setColor(this->index, color);
            this->setIndexes(this->index, index);

            this->index++;

        }

        ExplosionColor getValidColor() {

            if (this->index == 0) return ExplosionColor::Rainbow;

            ExplosionColor lstColor = ExplosionColor::None;
            
            uint8_t lstColorRun = 0;
            uint8_t lstRainRun = 0;

            for (uint8_t i = 0; i < this->index; i++) {

                if (lstColor != this->rocketColors[i] || this->rocketColors[i] == ExplosionColor::Rainbow) {

                    switch (this->rocketColors[i]) {

                        case ExplosionColor::Red:
                        case ExplosionColor::Green:
                        case ExplosionColor::Blue:

                            lstColorRun = lstRainRun + 1;
                            lstColor = this->rocketColors[i];                          
                            lstRainRun = 0;

                            break;

                        case ExplosionColor::Rainbow:

                            if (lstColor == ExplosionColor::None) lstColor = this->rocketColors[i];
                            lstColorRun++;
                            lstRainRun++;

                            break;

                    }

                }
                else {

                    lstColorRun++;
                    lstColor = this->rocketColors[i];                          
                    lstRainRun = 0;
                    
                }

            }
            
            return lstColorRun >= 3 ? ExplosionColor::Rainbow : lstColor;

        }


        void clearSelections() {

            this->index = 0;

            for (uint8_t i = 0; i < Constants::SelectedColor_Count; i++) {

                this->rocketColors[i] = ExplosionColor::None;
                this->indexes[i] = Constants::Rocket_None;

            }

        }


        uint8_t getSelectedColorsCount() {

            uint8_t selected = 0;

            for (uint8_t i = 0; i < Constants::SelectedColor_Count; i++) {

                if (this->rocketColors[i] != ExplosionColor::None) {

                    selected++;

                }

            }

            return selected;

        }

        bool hasRainbowSelected() {

            uint8_t selected = 0;

            for (uint8_t i = 0; i < this->index; i++) {

                if (this->rocketColors[i] == ExplosionColor::Rainbow) {
                    return true;
                }

            }

            return false;

        }

};

