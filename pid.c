#include <stdio.h>
#include <time.h>
#include <unistd.h>


int getTemp();
void setCorrection();

int setTemp;
int setTime = 66000;
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
    int temp;
    FILE *fp;

    fp = fopen("tempFile", "r");

    rewind(fp);
    fscanf(fp, " %d ", &temp);
    fclose(fp);
    return temp;
}
