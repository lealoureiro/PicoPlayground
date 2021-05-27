
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "tusb.h"


static char event_str[128];

void gpio_event_string(char *buf, uint32_t events);

void gpio_callback(uint gpio, uint32_t events) {

    // Put the GPIO event(s) that just happened into event_str
    // so we can print it
    gpio_event_string(event_str, events);
    printf("GPIO %d %s\n", gpio, event_str);

}


void set_callback() {

    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

}

int main() {

    stdio_init_all();

    while(!tud_cdc_connected()) {
        sleep_ms(100);
    }

    printf("Hello GPIO IRQ\n");

    // output pin
    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);

    // input pin
    gpio_init(2);
    gpio_set_dir(2, GPIO_IN);
    gpio_pull_down(2);

    multicore_launch_core1(set_callback);

    while (1) {

        int16_t led = getchar_timeout_us(1);

        if (led == 'o') {
            gpio_put(0, true);
        } else if (led == 'f') {
            gpio_put(0, false);
        } else if (led == PICO_ERROR_TIMEOUT) {
            // do nothing
        } else {
            printf("Unknown command!\n");
        }
        
    }

    return 0;
    
}

static const char *gpio_irq_str[] = {
        "LEVEL_LOW",  // 0x1
        "LEVEL_HIGH", // 0x2
        "EDGE_FALL",  // 0x4
        "EDGE_RISE"   // 0x8
};

void gpio_event_string(char *buf, uint32_t events) {

    for (uint i = 0; i < 4; i++) {
        uint mask = (1 << i);
        if (events & mask) {
            // Copy this event string into the user string
            const char *event_str = gpio_irq_str[i];
            while (*event_str != '\0') {
                *buf++ = *event_str++;
            }
            events &= ~mask;

            // If more events add ", "
            if (events) {
                *buf++ = ',';
                *buf++ = ' ';
            }
        }
    }
    
    *buf++ = '\0';
    
}