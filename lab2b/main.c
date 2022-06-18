#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>

void sendTask1(void *pvParam)
{
	QueueHandle_t QHandle = (QueueHandle_t) pvParam;
	BaseType_t xStatus;
	char *pcStrToSend;
	const int strMaxLen = 50;

	int i  = 1;
	while(1)
	{
		pcStrToSend = (char *) malloc(strMaxLen);
		snprintf(pcStrToSend, strMaxLen, "String number = %d", i);

		xStatus = xQueueSendToBack(QHandle, &i, 0);
		if(xStatus != pdPASS)
		{
			printf("task 1 can't send! \n");

		}
		else
		{
			printf("task 1 send done! \n");
		}
		vTaskDelay(1000/ portTICK_PERIOD_MS);
	}
}


void sendTask2(void *pvParam)
{
	QueueHandle_t QHandle = (QueueHandle_t) pvParam;
	BaseType_t xStatus;
	char *pcStrToSend;
	const int strMaxLen = 50;

	int i  = 2;
	while(1)
	{
		pcStrToSend = (char *) malloc(strMaxLen);
		snprintf(pcStrToSend, strMaxLen, "String number = %d", i);

		xStatus = xQueueSendToBack(QHandle, &i, 0);
		if(xStatus != pdPASS)
		{
			printf("task 2 can't send! \n");

		}
		else
		{
			printf("task 2 send done! \n");
		}
		vTaskDelay(1000/ portTICK_PERIOD_MS);
	}
}
void sendTask3(void *pvParam)
{
	QueueHandle_t QHandle = (QueueHandle_t) pvParam;
	BaseType_t xStatus;
	char *pcStrToSend;
	const int strMaxLen = 50;

	int i  = 3;
	while(1)
	{
		pcStrToSend = (char *) malloc(strMaxLen);
		snprintf(pcStrToSend, strMaxLen, "String number = %d", i);

		xStatus = xQueueSendToBack(QHandle, &i, 0);
		if(xStatus != pdPASS)
		{
			printf("task 3 can't send! \n");

		}
		else
		{
			printf("task error send done! \n");
		}
		vTaskDelay(1000/ portTICK_PERIOD_MS);
	}
}

void recTask(void * pvParam)
{
	QueueHandle_t  QHandle = (QueueHandle_t) pvParam;
	BaseType_t xStatus;
	int j = 0;
	while(1)
	{
		xStatus = xQueueReceive(QHandle, &j, portMAX_DELAY);
		if(xStatus != pdPASS)
			printf("rec fail!\n");
		else
		{
			if( j == 3) printf("raise error task, can't find task %d\n", j);
			else printf("task %d will run!\n", j);
		}
//		vTaskDelay(1000/ portTICK_PERIOD_MS);
	}
}


//-------------------------------------------------------------------------
void app_main(void)
{
	QueueHandle_t QHandle = xQueueCreate(5, sizeof(int));

	if(QHandle != NULL)
	{
		printf("The queue successfully! \n");
		xTaskCreate(sendTask1, "sendTask1", 1024*5, (void*)QHandle, 1, NULL);
		xTaskCreate(sendTask2, "sendTask2", 1024*5, (void*)QHandle, 1, NULL);
		xTaskCreate(sendTask3, "sendTask3", 1024*5, (void*)QHandle, 1, NULL);
		xTaskCreate(recTask, "recTask", 1024*5, (void*)QHandle, 2, NULL);
	}
	else
	{
		printf("The queue can't be created! \n");
	}
}
