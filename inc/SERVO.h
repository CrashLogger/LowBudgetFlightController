
#include "pico/stdlib.h"

#ifndef __SERVO_H_
#define __SERVO_H_

class SERVO{

    private:
        //VARS
        uint8_t pin;
        uint16_t min;
        uint16_t max;

        uint slice;
        uint channel;

        //FUNCS
        uint16_t convertAngle(uint8_t receivedPos, uint16_t min, uint16_t max);
        void config();

    public:
        //VARS

        //FUNCS
        void moveServo(uint8_t pos);

    public:
    SERVO(uint8_t pin, uint16_t min, uint16_t max);
    SERVO(uint8_t pin);
    ~SERVO();

};



#endif