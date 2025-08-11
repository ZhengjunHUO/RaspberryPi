gcc -g -Wall -c adc0832.c -lwiringPi -o adc0832.o
ar rcs libadc0832.a adc0832.o
sudo cp adc0832.h /usr/include/
sudo cp adc0832.o libadc0832.a /usr/lib

gcc -o joystick joystick.c -l wiringPi -l adc0832
./joystick
