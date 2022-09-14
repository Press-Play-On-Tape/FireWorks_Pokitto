#pragma once

#include "Point.h"
#include "../utils/Enums.h"

struct FloatingScore {

    private:
    
        uint8_t x = 0;
        uint8_t y = 0;
        uint32_t score = 0;
        uint8_t age = 0;

    public:

        uint8_t getX()                          { return this->x; }
        uint8_t getY()                          { return this->y; }
        uint32_t getScore()                     { return this->score; }
        uint8_t getAge()                        { return this->age; }

        void setX(uint8_t val)                  { this->x = val; }
        void setY(uint8_t val)                  { this->y = val; }
        void setScore(uint32_t val)             { this->score = val; }
        void setAge(uint8_t val)                { this->age = val; }

        void decAge() {

            this->age--;

        }

        void reset() {

            this->x = 0;
            this->y = 0;
            this->score = 0;
            this->age = 0;

        }

        uint8_t getLength() {

            switch (this->getScore()) {

                case 0 ... 9:           return 4;
                case 10 ... 19:         return 8;
                case 20 ... 99:         return 9;
                case 100 ... 199:       return 13;
                case 200 ... 999:       return 14;
                case 1000 ... 1999:     return 18;
                case 2000 ... 9999:     return 19;
                case 10000 ... 19999:   return 23;
                case 20000 ... 99999:   return 24;
                default:                return 29;

            }

        }

        uint8_t getChars() {

            switch (this->getScore()) {

                case 0 ... 9:           return 1;
                case 10 ... 99:         return 2;
                case 100 ... 999:       return 3;
                case 1000 ... 9999:     return 4;
                case 10000 ... 99999:   return 5;
                default:                return 6;

            }

        }

};

