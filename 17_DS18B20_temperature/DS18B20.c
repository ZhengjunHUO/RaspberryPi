#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <wiringPi.h>

static volatile bool running = true;
static volatile int fd = -1;

static void intr_handler(int signal) {
	printf("Ctrl-c captured, quit ...\n");
	running = false;
	if (fd != -1) {
		close(fd);
	}
}

int main() {
	char pathToW1[] = "/sys/bus/w1/devices";
	char dev[16];
	char pathToDev[128];
	char buf[256];
	char temperature[6];
	bool found = false;
	ssize_t read_size;

	struct dirent *ent;
	DIR *dir;

	dir = opendir(pathToW1);
	if (dir == NULL) {
		printf("Unable to open dir %s, quit.\n", pathToW1);
		exit(1);
	}

	while ((ent = readdir(dir))) {
		if (ent->d_type == DT_LNK && strstr(ent->d_name, "28-") != NULL) {
			found = true;
			strcpy(dev, ent->d_name);
			printf("Found device: %s\n", dev);
			break;
		}			
	}

	closedir(dir);

	if (!found) {
		printf("Unable to locate DS18B20 device, quit.\n");
		exit(1);
	}
	
	sprintf(pathToDev, "%s/%s/w1_slave", pathToW1, dev);

	signal(SIGINT, intr_handler);

	int fd = open(pathToDev, O_RDONLY);
	if (fd == -1) {
		printf("Unable to open DS18B20 device, quit.\n");
		exit(1);		
	}

	while(running) {
		while ((read_size = read(fd, buf, 256)) > 0) {
			strncpy(temperature, strstr(buf, "t=") + 2, 5);
			float temp = strtof(temperature, NULL)/1000;
			printf("Current temperature: %.3f C\n", temp);

			if (lseek(fd, 0, SEEK_SET) == -1) {
				printf("Unable to rewind on %s, quit.\n", pathToDev);
				close(fd);
				exit(1);
			}
		}
		delay(1000);
	}

	printf("Bye\n");
	return 0;
}