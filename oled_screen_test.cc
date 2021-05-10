#include "pico/stdlib.h"
#include "oled.h"

int main() {

	int h = 32;
	init_display(h);

	int color = 1;

	while(true) {
		for (int i = 0; i < 128; i++) {
			for (int j = 0; j<32; j++) {
				draw_pixel(i, j, color);
				show_scr();
			}
		}

		if (color ==0) {
			color = 1;
		} else {
			color = 0;
		}

	}

	return 0;
    
}