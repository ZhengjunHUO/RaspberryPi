#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char uchar;

# define LED_R 0   // connected to GPIO17
# define LED_G 1   // [S] connected to GPIO18

void init_led() {
	softPwmCreate(LED_R, 0, 255);
	softPwmCreate(LED_G, 0, 255);
}

void set_color_hold(uchar val_r, uchar val_g, uint duration) {
	softPwmWrite(LED_R, val_r);
	softPwmWrite(LED_G, val_g);
	delay(duration);
}

int main() {
	if(wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi, quit");
		return -1;
	}

	init_led();

	while(1) {
		set_color_hold(0xff, 0x00, 500);
		set_color_hold(0x00, 0xff, 500);
		set_color_hold(0xff, 0xff, 500);
		set_color_hold(0x00, 0x00, 500);
	}
	return 0;
}