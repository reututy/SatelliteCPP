#include "stdafx.h"
#include "GomEPS.h"
#include "Global.h"
#include "IsisTRXVU.h"
#include "FreeRTOS.h"
#include <stdlib.h>
#include "main.h"

gom_eps_channelstates_t channels_state;

#define TASK_FREQUENCY_MS		5000
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 70 )
#define BVATT_TASK_PRIORITY 10

void initialize_subsystems(gom_eps_hk_t* EpsTelemetry_hk, gom_eps_channelstates_t *channels_state, unsigned short* vbatt_previous)
{
	Boolean deployed = FALSE;

	//initialize FRAM
	FRAM_start();

	//check if first activation
	FRAM_read((unsigned char *)&not_first_activation, FIRST_ACTIVATION_ADDR, 4);
	deployed = not_first_activation;

	if (!deployed)
	{
		//initialize EPS voltages and states to default values
		unsigned char voltages[6] = { 65, 71, 73, 74, 72, 66 }; //
		FRAM_write(voltages, EPS_VOLTAGE_ADDR, EPS_VOLTAGE_SIZE);

		states = STATE_MNLP_ON_GROUND;
	}
	else
	{
		// read states values
		FRAM_read(&states, STATES_ADDR, 1);

		//makes sure that we know payload is off at startup
		states &= ~STATE_MNLP_ON;
	}

	EPS_Init(EpsTelemetry_hk, channels_state, vbatt_previous);

	//initialize trxvu
	init_trxvu();
	IsisTrxvu_tcSetAx25Bitrate(0, trxvu_bitrate_2400);
}


int main(){

	unsigned short vbatt_previous;

	gom_eps_hk_t EpsTelemetry_hk;
	ISIStrxvuRxTelemetry rx_tlm;
	ISIStrxvuTxTelemetry tx_tlm;
	unsigned long pt;
	unsigned char time_array[TIME_SIZE];
	Boolean redeployed = 0;

	Boolean deployed;

	// Initialize subsystems
	initialize_subsystems(&EpsTelemetry_hk, &channels_state, &vbatt_previous);

	// check if first activation
	FRAM_read((unsigned char *)&not_first_activation, FIRST_ACTIVATION_ADDR, 4);
	deployed = not_first_activation;

	// read start time
	FRAM_read(time_array, TIME_ADDR, TIME_SIZE);
	pt = convert_epoctime(time_array);

	if (deployed) redeployed = TRUE;

	while (!deployed)
	{
		unsigned long rt;

		// get House keeping power conditioning
		GomEpsGetHkData_general(0, &EpsTelemetry_hk);
		EPS_Power_Conditioning(&EpsTelemetry_hk, &vbatt_previous, &channels_state);
		deployed = TRUE;
	}

	unsigned long pt_beacon = pt;
	unsigned long pt_hk = pt;
	unsigned long first_deploy = pt;

	printf("love was given\n");

	while (1)
	{
		// 1. get telemetry trxvu
		IsisTrxvu_rcGetTelemetryAll(0, &rx_tlm);

		IsisTrxvu_tcGetTelemetryAll(0, &tx_tlm);

		// 2. get telemetry EPS
		GomEpsGetHkData_general(0, &EpsTelemetry_hk);

		EPS_Power_Conditioning(&EpsTelemetry_hk, &vbatt_previous, &channels_state);

	}
}