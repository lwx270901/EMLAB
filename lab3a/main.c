#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/timers.h"

int counter_1 = 0;
int counter_2 = 0;

void ATimerCallback ( TimerHandle_t xTimer ){
    unsigned long index;
    index = (unsigned long) pvTimerGetTimerID(xTimer);
    if(index == 1){
        counter_1++;
        printf("%d: ahihi\n",counter_1);
        if(counter_1 == 10) xTimerStop(xTimer, 0);
    }
    else if(index == 2){
        counter_2++;
        printf("%d: ihaha\n",counter_2);
        if(counter_2 == 5)  xTimerStop(xTimer, 0);
    }
}

void app_main(void)
{
    printf("START!\n");
    TimerHandle_t xTimer_1 = NULL;
    TimerHandle_t xTimer_2 = NULL;
    xTimer_1 = xTimerCreate ( "Timer1" , 2000 , pdTRUE , 1 ,  ATimerCallback);
    xTimer_2 = xTimerCreate ( "Timer2" , 3000 , pdTRUE , 2 ,  ATimerCallback);
    if(xTimer_1 != NULL){
        xTimerStart(xTimer_1, 0);
    }
    if(xTimer_2 != NULL){
        xTimerStart(xTimer_2, 0);
    }
}
