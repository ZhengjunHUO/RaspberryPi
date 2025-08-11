#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>

#define PIN_BUZZER  0

#define  CL1  131
#define  CL2  147
#define  CL3  165
#define  CL4  175
#define  CL5  196
#define  CL6  221
#define  CL7  248

#define  CM1  262
#define  CM2  294
#define  CM3  330
#define  CM4  350
#define  CM5  393
#define  CM6B 415
#define  CM6  441
#define  CM7  495

#define  CH1  525
#define  CH2  589
#define  CH3  661
#define  CH4  700
#define  CH5  786
#define  CH6  882
#define  CH7  990

static volatile bool running = true;

static void intr_handler(int signal) {
    printf("Ctrl-c captured, quit ...\n");
    running = false;
}

//int song[] = {CM1,0,CM1,0,CM5,0,CM5,0,CM6,0,CM6,0,CM5,0,0,CM4,0,CM4,0,CM3,0,CM3,0,CM2,0,CM2,0,CM1,0,0};
//int beat[] = {1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1};

// The Imperial March
int song[] = {CM6,0,CM6,0,CM6,0,CM4,CH1,CM6,0,CM4,CH1,CM6,0,0,CH3,0,CH3,0,CH3,0,CH4,CH1,CM6B,0,CM4,CH1,CM6,0,0};
int beat[] = {2,1,2,1,2,1,3,1,2,1,3,1,2,1,1,2,1,2,1,2,1,3,1,2,1,3,1,2,1,1};

int main() {
    if(wiringPiSetup() == -1) {
        printf("Error occurred setting up wiringPi, quit...\n");
        return -1;
    }

    if(softToneCreate(PIN_BUZZER) == -1){
        printf("Error occurred setting up softTone, quit...\n");
        return -1;
    }

    signal(SIGINT, intr_handler);

    while(running){
        printf("[Music]\n");
        for(int i=0;i<sizeof(song)/4;i++){      // int takes 4 bytes
            softToneWrite(PIN_BUZZER, song[i]);
            delay(beat[i] * 250);
        }
    }

    softToneStop(PIN_BUZZER);
    printf("Bye\n");
    return 0;
}