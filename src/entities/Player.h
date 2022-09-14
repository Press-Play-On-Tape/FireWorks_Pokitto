#pragma once

class Player {

    private:

        uint8_t x = 0;
        uint8_t y = 0;
        int8_t ang = 0;

    
    public:

        uint8_t getX()                          { return this->x; }
        uint8_t getY()                          { return this->y; }
        int8_t getAng()                         { return this->ang; }

        void setX(uint8_t val)                  { this->x = val; }
        void setY(uint8_t val)                  { this->y = val; }
        void setAng(int8_t val)                 { this->ang = val; }


        void reset() {

            this->x = 55;
            this->y = 44;
            this->ang = 0;

        }

        void incAng(uint8_t val) {

            this->ang = this->ang + val;
            if (this->ang >= 90) this->ang = this->ang - 90;

        }
        
        void decAng(uint8_t val) {

            this->ang = this->ang - val;
            if (this->ang < 0) this->ang = this->ang + 90;

        }


};
