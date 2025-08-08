#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

typedef unsigned int uint;
typedef unsigned char uchar;

# define LED_R 0   // connected to GPIO17
# define LED_G 1   // connected to GPIO18
# define LED_B 2   // connected to GPIO27

static volatile bool running = true;

static void intr_handler(int signal) {
	printf("Ctrl-c captured, quit ...\n");
	running = false;
}

void init_led() {
	softPwmCreate(LED_R, 0, 255);
	softPwmCreate(LED_G, 0, 255);
	softPwmCreate(LED_B, 0, 255);
}

void set_color_hold(uchar val_r, uchar val_g, uchar val_b, uint duration) {
	softPwmWrite(LED_R, val_r);
	softPwmWrite(LED_G, val_g);
	softPwmWrite(LED_B, val_b);
	delay(duration);
}

void stop_led() {
	softPwmStop(LED_R);
	softPwmStop(LED_G);
	softPwmStop(LED_B);
}

int main() {
	if(wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi, quit...\n");
		return -1;
	}

	init_led();

	signal(SIGINT, intr_handler);

	while(running) {
		set_color_hold(0xff, 0x00, 0x00, 500);
		set_color_hold(0xff, 0x80, 0x00, 500);
		set_color_hold(0xff, 0xff, 0x00, 500);
		set_color_hold(0x00, 0xff, 0x00, 500);
		set_color_hold(0x00, 0xff, 0xff, 500);
		set_color_hold(0x00, 0x00, 0xff, 500);
		set_color_hold(0xff, 0x00, 0xff, 500);
	}

	stop_led();
	printf("Bye\n");

	return 0;
}