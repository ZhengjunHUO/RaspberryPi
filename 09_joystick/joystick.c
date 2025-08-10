#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <adc0832.h>

#define sampling_interval_ms 500

int main()
{
	uchar val_x;
	uchar val_y;
	
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup failed!\n");
		exit(1);
	}

	uint adc_data_in_pin = 0;		// DO(6) -> CPIO17
	uint adc_data_out_pin = 1;		// DI(5) -> CPIO18
	uint adc_clk_pin = 14;			// CLK(7) -> SCLK
	uint adc_cs_pin = 15;			// CS(1)-> TXD
									// CH0(2) -> VRx
									// CH1(3) -> VRy
	
	adc0832_setup(
		adc_data_in_pin,
		adc_data_out_pin,
		adc_cs_pin,
		adc_clk_pin
	);
	
	while (1) {
		val_x = adc0832_read(
			adc_data_in_pin,
			adc_data_out_pin,
			adc_cs_pin,
			adc_clk_pin,
			adc0832_mode_single_ended,
			adc0832_channel0
		);
		printf("adc channel0: %d\n", val_x);

		val_y = adc0832_read(
			adc_data_in_pin,
			adc_data_out_pin,
			adc_cs_pin,
			adc_clk_pin,
			adc0832_mode_single_ended,
			adc0832_channel1
		);
		printf("adc channel1: %d\n", val_y);

		delay(sampling_interval_ms);
	}

	return 0;
}