#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPi.h>

#define PIN_CLK 0
#define PIN_DT 1
#define PIN_SW 2

typedef unsigned char uchar;

static volatile int counter = 0;

bool hasRotated;
uchar prevVal;
uchar currVal;

void intr_handler() {
	counter = 0;
}

void detect_rotary() {
	prevVal = digitalRead(PIN_DT);

	while(!digitalRead(PIN_CLK)) {
		currVal = digitalRead(PIN_DT);
		hasRotated = true;
	}

	if (hasRotated) {
		hasRotated = false;
		if ((prevVal == 0) && (currVal == 1)) {
			++counter;
		}
		if ((prevVal == 1) && (currVal == 0)) {
			--counter;
		}
	}
}

int main() {	
	if (wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi.\n");
		exit(1);
	}

	pinMode(PIN_CLK, INPUT);
	pinMode(PIN_DT, INPUT);
	pinMode(PIN_SW, INPUT);

	pullUpDnControl(PIN_SW, PUD_UP);

	if (wiringPiISR(PIN_SW, INT_EDGE_FALLING, &intr_handler) < 0) {
		printf("Error occurred setting up ISR.\n");
		exit(1);
	}
	
	int current = 0;

	while (1) {
		detect_rotary();
		if (current != counter) {
			printf("%d\n", counter);
			current = counter;
		}
	}

	return 0;
}