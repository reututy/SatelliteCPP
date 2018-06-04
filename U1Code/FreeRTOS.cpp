#include "stdafx.h"
#include "FreeRTOS.h"

#include <process.h> 

/*
* Generic version of the task creation function which is in turn called by the
* xTaskCreate() and xTaskCreateRestricted() macros.
*/
signed portBASE_TYPE xTaskGenericCreate(pdTASK_CODE pxTaskCode, const signed char * const pcName, unsigned short usStackDepth, void *pvParameters, unsigned portBASE_TYPE uxPriority, xTaskHandle *pxCreatedTask, portSTACK_TYPE *puxStackBuffer, const xMemoryRegion * const xRegions);

void vTaskDelay(const TickType_t xTicksToDelay);
//vTaskDelete
//vTaskStartScheduler
//xTaskGetTickCount