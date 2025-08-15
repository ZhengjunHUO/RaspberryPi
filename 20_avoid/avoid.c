#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

# define PIN_AVOID 0   // connected to GPIO17

static volatile bool running = true;

static void intr_handler(int signal) {
	printf("Ctrl-c captured, quit ...\n");
	running = false;
}

void isr_handler() {
	printf("obstacle detected !\n");
	delay(1000);
}

int main() {
	if(wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi, quit...\n");
		return -1;
	}

	if(wiringPiISR(PIN_AVOID, INT_EDGE_FALLING, &isr_handler) < 0) {
		printf("Error occurred setting up wiringPiISR, quit...\n");
		return -1;		
	}

	signal(SIGINT, intr_handler);

	while(running) {
		;
	}

	printf("Bye\n");
	return 0;
}