#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

class Rocket {

    private:
    
        float x = 0;
        float deltaX = 0;

        int8_t yIndex = 0;
        uint8_t yOffset = 0;
        uint8_t endPoint = 0;
        bool active = false;
        bool selected = false;

        // uint8_t launchCountdown = 0;
        // uint8_t velocity = 0;

        ExplosionColor color = ExplosionColor::Blue;
        ExplosionShape shape = ExplosionShape::Normal;
        Direction direction = Direction::Up;


    public:

        float getX()                            { return this->x; }
        uint8_t getY()                          { return Constants::RocketTrajectory[yIndex] + yOffset; }
        float getDeltaX()                       { return this->deltaX; }
        bool getActive()                        { return this->active; }
        bool getSelected()                      { return this->selected; }
        uint8_t getEndPoint()                   { return this->endPoint; }

        ExplosionColor getColor()               { return this->color; }
        ExplosionShape getShape()               { return this->shape; }
        Direction getDirection()                { return this->direction; }

        void setX(float val)                    { this->x = val; }
        void setDeltaX(float val)               { this->deltaX = val; }
        void setActive(bool val)                { this->active = val; }
        void setSelected(bool val)              { this->selected = val; }
        void setEndPoint(uint8_t val)           { this->endPoint = val; }

        void setColor(ExplosionColor val)       { this->color = val; }
        void setShape(ExplosionShape val)       { this->shape = val; }
        void setDirection(Direction val)        { this->direction = val; }

        void reset() {

            this->x = 0;
            this->deltaX = 0;
            this->active = false;
            this->selected = false;
            this->yIndex = 0;
            this->direction = Direction::Up;

        }

        bool update() {  // returns whether the rocket was disabled.

            if (!this->active) return false;

            this->x = this->x + this->deltaX;

            switch (this->direction) {
                
                case Direction::Up:

                    this->yIndex++;

                    if (this->yIndex == 119) {
                        this->yIndex = 118;
                        this->direction = Direction::Down;
                    }

                    break;
                
                case Direction::Down:

                    this->yIndex--;

                    if (this->yIndex == this->endPoint) {
                        this->reset();
                        return true;
                    }

                default: break;

            }

            return false;

        }
        
        uint8_t stepsToGo() {

            return this->yIndex - this->endPoint;
            
        }

        void skipSteps(uint8_t i) {

            this->yIndex = i;
            this->yOffset = 88 - Constants::RocketTrajectory[yIndex];

        }

};

