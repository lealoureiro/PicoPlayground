
#include "pico/stdlib.h"
#include <stdio.h>

void print_led_state(int16_t led, bool state);

int main() {

    stdio_init_all();

    uint LEDS[] = {18, 19, 20};
    bool leds_state[] = {0, 0, 0};

    gpio_init(LEDS[0]);
    gpio_init(LEDS[1]);
    gpio_init(LEDS[2]);
    gpio_set_dir(LEDS[0], GPIO_OUT);
    gpio_set_dir(LEDS[1], GPIO_OUT);
    gpio_set_dir(LEDS[2], GPIO_OUT);

    while (true) {
        
        int16_t led = getchar_timeout_us(1);

        if (led >= 0 || led < 3) {

            leds_state[led] = ! leds_state[led];
            gpio_put(LEDS[led], leds_state[led]);
            print_led_state(led, leds_state[led]);

        } else {
            printf("Uknown LED!\n");
        }

    }
    
    return 0;

}

void print_led_state(int16_t led, bool state) {
    if (state) {
        printf("LED %d ON\n", led);
    } else {
        printf("LED %d OFF\n", led);
    }
}