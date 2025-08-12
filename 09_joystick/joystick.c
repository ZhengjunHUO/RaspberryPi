#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wiringPi.h>
#include <adc0832.h>

#define PIN_DATA_IN 0		// DO(6) -> CPIO17
#define PIN_DATA_OUT 1		// DI(5) -> CPIO18
#define PIN_CLK 14		// CLK(7) -> SCLK
#define PIN_CS 15		// CS(1)-> TXD
				// CH0(2) -> joystick[VRx]
				// CH1(3) -> joystick[VRy]
// #define PIN_SW 2		// joystick[SW] -> CPIO27

void detect_direction(uint8_t val_x, uint8_t val_y) {
	char x[6];
	char y[5];

	switch (val_x) {
		case 0 ... 25:
			strcpy(x, "LEFT");
			break;
		case 230 ... 255:
			strcpy(x, "RIGHT");
			break;
		default:
			strcpy(x, "---");
	}

	switch (val_y) {
		case 0 ... 25:
			strcpy(y, "UP");
			break;
		case 230 ... 255:
			strcpy(y, "DOWN");
			break;
		default:
			strcpy(y, "---");
	}

	printf("%s %s\n", x, y);
}

int main()
{
	uchar val_x;
	uchar val_y;
	
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup failed!\n");
		exit(1);
	}


	// pinMode(PIN_SW, INPUT);
	
	adc0832_setup(
		PIN_DATA_IN,
		PIN_DATA_OUT,
		PIN_CS,
		PIN_CLK
	);
	
	while (1) {
		// if(digitalRead(PIN_SW) == 0) {
		// 	printf("Button pressed.\n");
		// }

		val_x = adc0832_read(
			PIN_DATA_IN,
			PIN_DATA_OUT,
			PIN_CS,
			PIN_CLK,
			adc0832_mode_single_ended,
			adc0832_channel0
		);
		printf("adc channel0: %d\n", val_x);

		val_y = adc0832_read(
			PIN_DATA_IN,
			PIN_DATA_OUT,
			PIN_CS,
			PIN_CLK,
			adc0832_mode_single_ended,
			adc0832_channel1
		);
		printf("adc channel1: %d\n", val_y);

		detect_direction((uint8_t)val_x, (uint8_t)val_y);

		delay(500);
	}

	return 0;
}