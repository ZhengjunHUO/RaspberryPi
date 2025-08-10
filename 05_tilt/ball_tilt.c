#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

# define PIN_TILT 0   // [S] connected to GPIO17
# define PIN_LASER 1  // [S] connected to GPIO18

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

	pinMode(PIN_TILT, INPUT);
	pinMode(PIN_LASER, OUTPUT);
	signal(SIGINT, intr_handler);

	while(running) {
		if(digitalRead(PIN_TILT) == 0) {
			printf("Tilt detected.\n");
			digitalWrite(PIN_LASER, HIGH);
		} else {
			printf("Idle\n");
			digitalWrite(PIN_LASER, LOW);
		}
		delay(100);
	}

	printf("Bye\n");
	return 0;
}