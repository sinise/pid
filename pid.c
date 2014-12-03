#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>


int getTemp();
void setCorrection();
int setOut();
void pidcalc();

// pid variables
float e; // error value sp - pv
float ei; // error arkumulated
float kp = 1; //proportional gain
float ki = 1; //integral gain
float kd = 1; // deavirate gain
float pv; // tempereture
float pv_1 = 0; //forige temp
float pv_2 = 0; //forige af forige temp
float co = 0; // controller output
int secPassed = 0;

// cycletime for powerOut
int cycleTime = 2000;


// user setings
float sp = 57.0; // set point
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
        if(pv == 85){
          getTemp();
        }
        pidCalc();
  //      printf("6\n");
        setOut();
    //    printf("7\n");
        printf("e %f\n ei %f\n kp %f\n ki %f\n kd %f\n pv %f\n pv_1 %f\n pv_2 e %f\n co %f\n", e, ei, kp, ki, kd, pv, pv_1, pv_2, co);
    }
}

int pidCalc(){
  e = sp - pv;
  ei += e;
  float p = kp * (pv_1 - pv);
  float i = ki*ei;
  float d = kd * (2.0 * pv_1 - pv - pv_2);
  pv_1 = pv;
  pv_2 = pv_1;
  co = p + i + d;
}

int setOut()
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
    float timeHigh = 1000 - co * 10;
    float timeLow = cycleTime - timeHigh;
    printf("timeHigh = %f  timeLow = %f\n", timeHigh, timeLow);
    if(co > 0 ){
      digitalWrite (0, HIGH) ; delay ((int)timeHigh) ;
      digitalWrite (0, LOW) ; delay ((int)timeLow) ;
    }
    else{
      digitalWrite (0,  LOW) ; delay (2000) ;
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
//      printf("starting loop in getTemp\n" );
      if(strstr(buf, "YES") != NULL){
          fgets(buf, 80, fp);
          strncpy(tmp, strstr(buf, "t=") + 2, 5);
          pv = atoi(tmp) / 1000.0;
          printf("pv = %f \n", pv );
      }
    fclose(fp);
    return 1;
}
