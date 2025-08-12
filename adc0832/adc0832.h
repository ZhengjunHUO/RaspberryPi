typedef unsigned char uchar;
typedef unsigned int uint;

#define adc0832_period_usec 2
#define adc0832_mode_differential 0
#define adc0832_mode_single_ended 1
#define adc0832_channel0 0
#define adc0832_channel1 1

void adc0832_setup(
	uint data_in_pin, 
	uint data_out_pin, 
	uint cs_pin,
	uint clk_pin
);

uchar adc0832_read(
	uint data_in_pin, 
	uint data_out_pin, 
	uint cs_pin,
	uint clk_pin,
	uchar mux_mode,
	uchar channel
);
