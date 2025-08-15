#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

# define WAITING 85
# define PIN_DHT 0   // connected to GPIO17

int dht11_array[5] = {0, 0, 0, 0, 0};

static volatile bool running = true;

static void intr_handler(int signal) {
	printf("Ctrl-c captured, quit ...\n");
	running = false;
}

void read_from_dht11() {
	uint8_t prev = HIGH;
	uint8_t counter = 0;
	uint8_t i;
	uint8_t j = 0;
	float temp;

	// memset(dht11_array, 0, 5 * sizeof(int));
	memset(dht11_array, 0, sizeof(dht11_array));

	pinMode(PIN_DHT, OUTPUT);
	digitalWrite(PIN_DHT, LOW);
	delay(18);
	digitalWrite(PIN_DHT, HIGH);
	delayMicroseconds(40);

	pinMode(PIN_DHT, INPUT);
	printf("[DEBUG] Entering for loop ...\n");
	for (i = 0; i < WAITING; i++) {
		counter = 0;
		while (digitalRead(PIN_DHT) == prev) {
			++counter;
			delayMicroseconds(1);
			if (counter == 255) break;
		}

		prev = digitalRead(PIN_DHT);
		if (counter == 255) break;
		// printf("[DEBUG] Counter: %d\n", counter);

		if ((i > 3) && (i % 2 == 0)) {
				dht11_array[j/8] <<= 1;
				if (counter > 16)
					dht11_array[j/8] |= 1;
				++j;
		}
	}

	printf("[DEBUG] j: %d\n", j);
	for(int loop = 0; loop < 5; loop++)
      printf("[DEBUG] dht11_array[%d]: %d\n", loop, dht11_array[loop]);

	if ((j >= 40) && (dht11_array[4] == ((dht11_array[0] + dht11_array[1] + dht11_array[2] + dht11_array[3]) & 0xFF))) {
		temp = dht11_array[2] * 9. / 5. + 32;
		printf("Temperature: [%d.%d]C (%.1f F)  Humidity: [%d.%d]\n", dht11_array[2], dht11_array[3], temp, dht11_array[0], dht11_array[1]);
	}
}

int main() {
	if(wiringPiSetup() == -1) {
		printf("Error occurred setting up wiringPi, quit...\n");
		return -1;
	}

	signal(SIGINT, intr_handler);

	while(running) {
		read_from_dht11();
		delay(1000);
	}

	printf("Bye\n");
	return 0;
}