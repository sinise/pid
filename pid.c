#include <stdio.h>
#include <time.h>
#include <unistd.h>


int getTemp();
void setCorrection();

int setTemp;
int setTime = 0;
int secPassed = 0;
float powerOut;

int main(void)
{
    time_t startTime = time(NULL);
    unsigned startSec = (unsigned)startTime;

    printf("You started cooking %s", ctime(&startTime));

    while(setTime > secPassed){
        secPassed = (unsigned)time(NULL) +12000 - startSec;
        unsigned ssPassed = secPassed % 60;
        unsigned hhPassed = secPassed / (60*60);
        unsigned mmPassed = (secPassed - hhPassed*60*60) / 60;
        printf("time passed is %u hours :  %u minutes : %u seconds\n", hhPassed, mmPassed,ssPassed);
        printf("curent temperature is %d\n", getTemp());
        sleep(1);
    }
}


int getTemp()
{
    }

    int temp;
    FILE *fp;

    fp = fopen("/sys/bus/w1/devices/28-000005f5dac4/w1_slave", "r");

    if(fp == -1) {
        perror ("Couldn't open the w1 device.");
        return 1;
    }
    int c;
    while((c = getc(fp)) !=EOF){
        putchar(c);
    }
//    rewind(fp);
//    fscanf(fp, " %d ", &temp);
    fclose(fp);
//    return temp;
}
