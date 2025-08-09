#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

# define PIN_BUTTON 0   // [S] connected to GPIO17

static volatile bool running = true;

static void intr_handler(int signal) {
	printf("Ctrl-c captured, quit ...\n");
	running = false;
}

int main() {
	if(wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi, quit...\n");
		return -1;
	}

	pinMode(PIN_BUTTON, INPUT);
	signal(SIGINT, intr_handler);

	while(running) {
		if(digitalRead(PIN_BUTTON) == 0) {
			printf("Button pressed.\n");
		} else {
			printf("Idle\n");
		}
		delay(100);
	}

	printf("Bye\n");
	return 0;
}