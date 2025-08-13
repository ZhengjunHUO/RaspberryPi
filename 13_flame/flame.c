#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <adc0832.h>

#define PIN_DATA_IN 0	// DO(6) -> CPIO17
#define PIN_DATA_OUT 1	// DI(5) -> CPIO18
#define PIN_CLK 14		// CLK(7) -> SCLK
#define PIN_CS 15		// CS(1)-> TXD
						// CH0(2) -> [S]
#define PIN_FLAME 2		// CPIO27

int main() {
	uchar val;
	uint digit_val;
	uint current_val = 0;
	
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup failed!\n");
		exit(1);
	}

	adc0832_setup(
		PIN_DATA_IN,
		PIN_DATA_OUT,
		PIN_CS,
		PIN_CLK
	);

	pinMode(PIN_FLAME, INPUT);
	
	while (1) {
		val = adc0832_read(
			PIN_DATA_IN,
			PIN_DATA_OUT,
			PIN_CS,
			PIN_CLK,
			adc0832_mode_single_ended,
			adc0832_channel0
		);
		printf("Analog value: %d\n", val);

		digit_val = digitalRead(PIN_FLAME);
		if (digit_val != current_val) {
			printf("flame value changed: %d -> %d\n", current_val, digit_val);
			current_val = digit_val;
		}

		delay(300);
	}
	return 0;
}