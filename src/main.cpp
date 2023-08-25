#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>
#include <string.h>
#include "NRF24.h"
#include "SERVO.h"

#define packetSize 2;

int main(){

    stdio_init_all();
    printf("Begin\n");
    
    NRF24 nrf(spi1, 9, 8);

    SERVO esc(14);

    nrf.config();
    nrf.modeRX();

    gpio_init(25);
    gpio_init(15);
    gpio_init(16);

    gpio_set_dir(25, 1);
    gpio_set_dir(15, 0);
    gpio_set_dir(16, 0);

    char bufferOut[32] {0};
    char bufferIn[32] {0};

    while(1){

        if(!gpio_get(15)){
            
            nrf.modeTX();
            //sprintf(bufferOut, "A");
            bufferOut[1] = 0b11111111;
            bufferOut[0] = 0b00000000;
            nrf.sendMessage(bufferOut);
            nrf.modeRX();
        }

        else if(!gpio_get(16)){
            nrf.modeTX();
            bufferOut[0] = 0b11111111;
            bufferOut[1] = 0b00000000;
            // sprintf(bufferOut, "B");
            nrf.sendMessage(bufferOut);
            nrf.modeRX();
        }

        if (nrf.newMessage() == 1){

            nrf.receiveMessage(bufferIn);
            if(bufferIn[1] == 0b00000000){
                gpio_put(25, 0);
            }
            else if(bufferIn[1] == 0b11111111){ 
                gpio_put(25, 1);
            }
        }
        esc.moveServo(bufferIn[0]);
    }
    return 0;
}