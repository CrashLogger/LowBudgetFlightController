#include <Servo.h>
#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"
#include "hardware/irq.h"

SERVO::SERVO(uint8_t pin)
{
    this -> pin = pin;
    this -> min = 200;
    this -> max = 1200;

    config();
}

SERVO::SERVO(uint8_t pin, uint16_t min, uint16_t max)
{    
    this -> pin = pin;
    this -> min = min;
    this -> max = max;

    config();
}

void SERVO::config(){
    gpio_init(this -> pin);
    gpio_set_function(pin,  GPIO_FUNC_PWM);

    this-> slice = pwm_gpio_to_slice_num(this -> pin);
    this-> channel = pwm_gpio_to_channel(this -> pin);

    pwm_set_clkdiv(slice, 256.0f);
    pwm_set_wrap(slice, 9804);
    pwm_set_enabled(slice, true);
}

//Literally the map function in arduino
uint16_t SERVO::convertAngle(uint8_t receivedPos, uint16_t min, uint16_t max){

    //receivedPos   : The input value we want to convert
    //in_min        : Lower limit of all possible inputs
    //in_max        : Upper limit of all possible inputs
    //this->min       : Lower limit of the desired outputs
    //this->max       : Upper limit of the desired outputs

    uint8_t in_min = 0;
    uint8_t in_max = 255;

    return( (receivedPos - in_min) * (max - min) / (in_max - in_min) + min);
}

SERVO::~SERVO(){
}

void SERVO::moveServo(uint8_t pos){
    uint16_t correctedVal = convertAngle(pos, (this->min), (this->max));
    printf("Servo pos: %d \n", correctedVal);
    pwm_set_chan_level(this->slice, this->channel, correctedVal);
}