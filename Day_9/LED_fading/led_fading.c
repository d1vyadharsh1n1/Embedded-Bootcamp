#include <reg52.h>

sbit LED = P1^1;

void pwm_delay(unsigned int us_count) {
    unsigned int i;
    for(i = 0; i < us_count; i++); 
}


void main(void) {
    unsigned int brightness;
    unsigned int TOTAL_PERIOD = 100;

    while(1) {
        for(brightness = 0; brightness <= TOTAL_PERIOD; brightness++) {
            unsigned int repeat;
            for(repeat = 0; repeat < 10; repeat++) {
                if(brightness > 0) {
                    LED = 1;                  
                    pwm_delay(brightness);    
                }
                if(brightness < TOTAL_PERIOD) {
                    LED = 0;                  
                    pwm_delay(TOTAL_PERIOD - brightness); 
                }
            }
        }

        for(brightness = TOTAL_PERIOD; brightness > 0; brightness--) {
            unsigned int repeat;
            for(repeat = 0; repeat < 10; repeat++) {
                if(brightness > 0) {
                    LED = 1;
                    pwm_delay(brightness);
                }
                if(brightness < TOTAL_PERIOD) {
                    LED = 0;
                    pwm_delay(TOTAL_PERIOD - brightness);
                }
            }
        }
    }
}
