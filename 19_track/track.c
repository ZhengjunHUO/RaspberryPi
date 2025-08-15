#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

# define PIN_TRACK 0   // connected to GPIO17

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

	pinMode(PIN_TRACK, INPUT);
	signal(SIGINT, intr_handler);

	while(running) {
		if(digitalRead(PIN_TRACK) == LOW) {
			printf("White line detected.\n");
		} else {
			printf("Black line detected.\n");
		}
		delay(500);
	}

	printf("Bye\n");
	return 0;
}