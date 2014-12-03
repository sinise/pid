#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>


int getTemp();
void setCorrection();
int setOut();

// pid variables
float e; // error value sp - pv
float ei; // error arkumulated
float kp = 1; //proportional gain
float ki = 1; //integral gain
float kd = 1; // deavirate gain
float pv; // tempereture
float pv_1 = 0; //forige temp
float pv_2 = 0; //forige af forige temp

int secPassed = 0;

// cycletime for powerOut
int cycleTime = 2000;


// user setings
float sp = 63.0; // set point
int setTime = 60000;

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
        getTemp();
        pidCalc();
        setOut();
        printf("curent temperature is %f\n", pv);
        sleep(1);
    }
}

int pidCalc(){
  e = sp - pv;
  ei += e:
  float p = kp * (pv_1 - pv);
  float i = ki*ei;
  float d = dk * (2.0 * pv_1 - pv - pv_2);
}

int setOut()
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  while(true){
    int timeHigh = pv;
    int timeLow = cycleTime - timeHigh;
    if(poweOut > 0 ){
      digitalWrite (0, HIGH) ; delay (timeHigh) ;
      digitalWrite (0, LOW) ; delay (timeLow) ;
    }
    else{
      digitalWrite (0,  LOW) ; delay (2000) ;
    }
  }
    return 0 ;
}


int getTemp() {
    char tmp[5];
    FILE *fp;
    fp = fopen("/sys/bus/w1/devices/28-000005f5dac4/w1_slave", "r");

//    fp = fopen("w1_slave", "r");
    char buf[80];

    if(fp == 0) {
        perror ("Couldn't open the w1 device.");
        return 1;
    }
    fgets(buf, 80, fp);
    if(strstr(buf, "YES") != NULL){
        fgets(buf, 80, fp);
        strncpy(tmp, strstr(buf, "t=") + 2, 5);
        pv = atoi(tmp) / 1000.0;
    }
    fclose(fp);
    return temp;
}
