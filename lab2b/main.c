#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "string.h"


TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t myTask3Handle = NULL;
QueueHandle_t queue1;

 void task1(void *arg)
{

char txbuff[50];

queue1= xQueueCreate(100, sizeof(txbuff));

 if( queue1 == 0 )
 {
    printf("failed to create queue1= %p \n",queue1); // Failed to create the queue.

 }


//sprintf(txbuff,"0");
//xQueueSend(queue1, (void*)txbuff , (TickType_t)0 );
//
//
//sprintf(txbuff,"1");
//xQueueSend(queue1, (void*)txbuff , (TickType_t)0 );
//
//
//sprintf(txbuff,"2");
//xQueueSendToFront(queue1, (void*)txbuff , (TickType_t)0 );
 for(int i = 0;  i< 100; i ++)
 {
	 int data = i%2;
	 sprintf(txbuff,"%d", data);
	 xQueueSend(queue1, (void*)txbuff , 0 );
 }

 while(1){

//   printf("data waiting to be read : %d  available spaces: %d \n",uxQueueMessagesWaiting(queue1),uxQueueSpacesAvailable(queue1));

   vTaskDelay(pdMS_TO_TICKS(1000)); }
}

 void task2(void *arg)
{
char rxbuff[50];
while(1)

  {
//if(xQueuePeek(queue1, &(rxbuff) , (TickType_t)5 ))
if(xQueueReceive(queue1, &(rxbuff) , (TickType_t)5 ))
{
	if(rxbuff[0] == '1')
	{
		printf("task 2 is running with id:  %s \n",rxbuff); }
	}
	if(rxbuff[0] == '3')
	{
		printf("error id: %s \n", rxbuff);
	}



   vTaskDelay(pdMS_TO_TICKS(1000));
   }
}

 void task3(void *arg)
 {
 char rxbuff[50];
 while(1)

   {
 //if(xQueuePeek(queue1, &(rxbuff) , (TickType_t)5 ))
	 if(xQueueReceive(queue1, &(rxbuff) , (TickType_t)5 ))
	 {
		 if(rxbuff[0] == '0')
		 	{
		 		printf("task 3 is running with id:  %s \n",rxbuff); }
		 	}
	 if(rxbuff[0] == '3')
	 	{
	 		printf("error id: %s \n", rxbuff);
	 	}

	 	 vTaskDelay(pdMS_TO_TICKS(1000));
    	}
 }



void app_main()
{

    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTask2Handle,1);
    xTaskCreatePinnedToCore(task3, "task3", 4096, NULL, 10, &myTask3Handle,1);

}
