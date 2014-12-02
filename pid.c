#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>


int getTemp();
void setCorrection();
int setOut();
float error;
float temp;
float setTemp = 63.0;
int setTime = 60000;
int secPassed = 0;
float powerOut;
int pwm;


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
        setOut();
        printf("curent temperature is %f\n", temp);
        sleep(1);
    }
}



int setOut ()
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  int i = 0;
  if(temp - setTemp < 0 ){
    digitalWrite (0, HIGH) ; delay (1000) ;
  }
  else{
    digitalWrite (0,  LOW) ; delay (1000) ;
  }
  return 0 ;
}


/*
int setOut() {
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;

  pinMode (0, OUTPUT) ;         // aka BCM_GPIO pin 17

  if(temp - setTemp < 0) {
        printf("set high");
    digitalWrite (0, HIGH) ; delay (500) ;
    delay (1000) ;
  }
  else{
    digitalWrite (0,  LOW) ; delay (500) ;
    delay (1000) ;
  }
  return 0 ;

}
*/






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
        temp = atoi(tmp) / 1000.0;
    }
    fclose(fp);
    return temp;
}
