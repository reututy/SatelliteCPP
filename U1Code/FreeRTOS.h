typedef unsigned int TickType_t;

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	unsigned portLONG
#define portBASE_TYPE	portLONG

/* Defines the prototype to which task functions must conform. */
typedef void(*pdTASK_CODE)(void *);

typedef void * xTaskHandle;

typedef unsigned long portTickType;

typedef struct xMEMORY_REGION
{
	void *pvBaseAddress;
	unsigned long ulLengthInBytes;
	unsigned long ulParameters;
} xMemoryRegion;

typedef struct xTASK_PRPS
{
	pdTASK_CODE pxTaskCode;
	unsigned short usStackDepth;
	void *pvParameters;
}xTasks;

#define TASKS_AMOUNT 50

void vTaskStartScheduler(void);
portTickType xTaskGetTickCount(void);
void vTaskDelete(xTaskHandle xTaskToDelete);