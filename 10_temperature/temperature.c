#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <adc0832.h>
#include <math.h>

#define PIN_DATA_IN 0	// DO(6) -> CPIO17
#define PIN_DATA_OUT 1	// DI(5) -> CPIO18
#define PIN_CLK 14		// CLK(7) -> SCLK
#define PIN_CS 15		// CS(1)-> TXD
						// CH0(2) -> [S]

#define VCC_VAL 5       	// 5V
#define RESIST_VAL 10000 	// 10k [103]

int main() {
	uchar val;
	
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
	
	while (1) {
		val = adc0832_read(
			PIN_DATA_IN,
			PIN_DATA_OUT,
			PIN_CS,
			PIN_CLK,
			adc0832_mode_single_ended,
			adc0832_channel0
		);
		printf("analog value: %d\n", val);
		uint8_t val_u8 = (uint8_t)val;

		double vr = VCC_VAL * (double)(val_u8) / 255;  // adc0832 - 8-bit
		double rt = RESIST_VAL * (double)(vr) / (VCC_VAL - (double)(vr));
		double temp = 1 / (((log(rt / RESIST_VAL)) / 3950) + (1 / (273.15+25)));
		double cel = temp - 273.15;
		printf("temperature: %lf\n", cel);

		delay(100);
	}

	return 0;
}