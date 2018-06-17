#include "stdafx.h"
#include "FreeRTOS.h"

#include <process.h> 
#include <stdlib.h>
#include <stdio.h>
#include "Windows.h"

xTasks tasks[TASKS_AMOUNT];
int currTaskToAdd = 0;
char schedulerStarted = 0;

/*
* Generic version of the task creation function which is in turn called by the
* xTaskCreate() and xTaskCreateRestricted() macros.
*/
signed portBASE_TYPE xTaskCreate(pdTASK_CODE pxTaskCode, const signed char * const pcName, unsigned short usStackDepth, void *pvParameters, unsigned portBASE_TYPE uxPriority, xTaskHandle *pxCreatedTask){
	if (schedulerStarted == 0){
		tasks[currTaskToAdd].pxTaskCode = pxTaskCode;
		tasks[currTaskToAdd].usStackDepth = usStackDepth;
		tasks[currTaskToAdd].pvParameters = pvParameters;
		currTaskToAdd++;
	}
	else{
		_beginthread(pxTaskCode, usStackDepth, pvParameters);
	}
}

void vTaskDelay(const TickType_t xTicksToDelay){
	Sleep(xTicksToDelay);
}

void vTaskStartScheduler(void){
	schedulerStarted = 1;
	int i;
	for (i = 0; i < currTaskToAdd; i++){
		_beginthread(tasks[i].pxTaskCode, tasks[i].usStackDepth, tasks[i].pvParameters);
	}
	currTaskToAdd = 0;
}

portTickType xTaskGetTickCount(void){
	return GetTickCount();
}

void vTaskDelete(xTaskHandle xTaskToDelete){

}