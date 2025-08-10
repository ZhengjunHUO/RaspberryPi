#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

# define PIN_BUZZER 0   // [S] connected to GPIO17

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

	pinMode(PIN_BUZZER, OUTPUT);
	signal(SIGINT, intr_handler);

	while(running) {
		digitalWrite(PIN_BUZZER, HIGH);
		printf("HIGH\n");
		delay(3000);
		digitalWrite(PIN_BUZZER, LOW);
		printf("LOW\n");
		delay(3000);
	}

	printf("Bye\n");
	return 0;
}