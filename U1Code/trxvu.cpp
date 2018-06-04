/*
* trxvu.c
*
*  Created on: 10 ???? 2016
*      Author: Ariel
*/
#include "stdafx.h"
#include "main.h"
#include "EPS.h"
#include "trxvu.h"
unsigned char tc_count;
unsigned char dumpparam[11];
unsigned int dump_completed = 0;
unsigned int dump_created = 0;
unsigned char beacon_count = 0;
unsigned long last_wod = 0;
void update_wod(gom_eps_hk_t EpsTelemetry_hk)
{
	Set_Vbatt(EpsTelemetry_hk.fields.vbatt);
	Set_Cursys(EpsTelemetry_hk.fields.cursys);
	Set_Curout3V3(EpsTelemetry_hk.fields.curout[0]);
	Set_Curout5V(EpsTelemetry_hk.fields.curout[3]);
	Set_tempCOMM(25);
	Set_tempEPS((short)EpsTelemetry_hk.fields.temp[0]);
	Set_tempBatt((short)EpsTelemetry_hk.fields.temp[4]);
}

void vurc_getRxTelemTest(isisRXtlm *converted)
{
	unsigned short telemetryValue;
	float eng_value = 0.0;
	ISIStrxvuRxTelemetry telemetry;

	// Telemetry values are presented as raw values
	//printf("\r\nGet all Telemetry at once in raw values \r\n\r\n");
	IsisTrxvu_rcGetTelemetryAll(0, &telemetry);

	telemetryValue = telemetry.fields.tx_current;
	eng_value = ((float)telemetryValue) * 0.0897;
	converted->tx_current = eng_value;
	//printf("Transmitter current is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.rx_doppler;
	eng_value = ((float)telemetryValue) * 6.837 - 14000;
	converted->rx_doppler = eng_value;
	//printf("Receiver doppler value is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.rx_current;
	eng_value = ((float)telemetryValue) * 0.0305;
	converted->rx_current = eng_value;
	//printf("Receiver current is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.bus_volt;
	eng_value = ((float)telemetryValue) * 0.00488;
	converted->bus_volt = eng_value;
	//printf("Bus voltage is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.board_temp;
	eng_value = ((float)telemetryValue) * -0.0546 + 189.5522;
	converted->board_temp = eng_value;
	//printf("Board temperature = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.pa_temp;
	eng_value = ((float)telemetryValue) * -0.0546 + 189.5522;
	converted->pa_temp = eng_value;
	//printf("Pa temperature = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.rx_rssi;
	eng_value = ((float)telemetryValue * 0.03) + 152;
	converted->rx_rssi = eng_value;
	//printf("Receiver RSSI = %f \r\n", eng_value);


}

void vurc_getTxTelemTest(isisTXtlm *converted)
{
	unsigned short telemetryValue;
	float eng_value = 0.0;
	ISIStrxvuTxTelemetry telemetry;

	/*
	float tx_reflpwr; ///< Tx Telemetry reflected power.
	float pa_temp; ///< Tx Telemetry power amplifier temperature.
	float tx_fwrdpwr; ///< Tx Telemetry forward power.
	float tx_current; ///< Tx Telemetry transmitter current.
	*/
	// Telemetry values are presented as raw values
	//printf("\r\nGet all Telemetry at once in raw values \r\n\r\n");
	IsisTrxvu_tcGetTelemetryAll(0, &telemetry);

	telemetryValue = telemetry.fields.tx_current;
	eng_value = ((float)telemetryValue) * 0.0897;
	converted->tx_current = eng_value;
	//printf("Transmitter current is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.pa_temp;
	eng_value = ((float)telemetryValue) * -0.0546 + 189.5522;
	converted->pa_temp = eng_value;
	//printf("PA temperature is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.tx_reflpwr;
	eng_value = ((float)(telemetryValue * telemetryValue)) * 0.00005887;
	converted->tx_reflpwr = eng_value;
	//printf("RF reflected power is = %f \r\n", eng_value);

	telemetryValue = telemetry.fields.tx_fwrdpwr;
	eng_value = ((float)(telemetryValue * telemetryValue)) * 0.00005887;
	converted->tx_fwrdpwr = eng_value;
	//printf("RF reflected power is = %f \r\n", eng_value);


}

void init_trxvu(void)
{
	int retValInt = 0;

	// Definition of I2C and TRXUV
	ISIStrxvuI2CAddress myTRXVUAddress[1];
	ISIStrxvuFrameLengths myTRXVUBuffers[1];
	ISIStrxvuBitrate myTRXVUBitrates[1];

	//I2C addresses defined
	myTRXVUAddress[0].addressVu_rc = 0x60;
	myTRXVUAddress[0].addressVu_tc = 0x61;

	//Buffer definition
	myTRXVUBuffers[0].maxAX25frameLengthTX = SIZE_TXFRAME;
	myTRXVUBuffers[0].maxAX25frameLengthRX = SIZE_RXFRAME;

	//Bitrate definition
	myTRXVUBitrates[0] = trxvu_bitrate_1200;

	if (retValInt != 0)
	{
		printf("\n\r I2Ctest: I2C_start_Master for TRXUV test: %d! \n\r", retValInt);
	}

	//Initialize the trxvu subsystem
	IsisTrxvu_initialize(myTRXVUAddress, myTRXVUBuffers, myTRXVUBitrates, 1);
}

int TRX_sendFrame(unsigned char* data, unsigned char length)
{
	unsigned char avalFrames = 0;

	IsisTrxvu_tcSendAX25DefClSign(0, data, length, &avalFrames);
	if (avalFrames == 0) return -1;
	availableFrames = avalFrames;
	//printf("\navailable space in queue: %d\n",availableFrames);
	return 0;
}


void end_gs_mode()
{
	printf("exit ground station mode");
	//Exit ground station mode
	states &= ~STATE_GS;
	//initialize Mnlp
	//glb_channels_state.fields.channel3V3_2 = 1;
	//glb_channels_state.fields.channel5V_2 = 1;
	//GomEpsSetOutput(0, glb_channels_state);
}

Boolean check_ants_deployed()// NOT WORKING CAUSE ISIS CODE
{
	int first_activation;
	/*ISISantsSide side = isisants_sideA;
	ISISantsStatus ants_stat;
	side = isisants_sideA;
	IsisAntS_getStatusData(0,side,&ants_stat);
	side = isisants_sideB;
	IsisAntS_getStatusData(0,side,&ants_stat);
	printf("%d,%d,%d,%d\n",ants_stat.fields.ant1Undeployed,ants_stat.fields.ant2Undeployed,ants_stat.fields.ant3Undeployed,ants_stat.fields.ant4Undeployed);
	if(ants_stat.fields.ant1Undeployed || ants_stat.fields.ant2Undeployed || ants_stat.fields.ant3Undeployed || ants_stat.fields.ant4Undeployed)
	{
	printf("deployed\n");
	return TRUE;
	}*/

	// for testing only

	FRAM_read((unsigned char *)&first_activation, FIRST_ACTIVATION_ADDR, 4);
	printf("checking deployed %d\n", first_activation);
	if (first_activation == 0)
	{
		printf("not deployed\n");
		return FALSE;
	}
	else
	{
		printf("deployed\n");
		return TRUE;
	}

}


//void print_wod(short vbat, short vcur_5,short vcur_3,short eps_temp,short com_temp)
void print_wod(short vbat, short vcur_5, short vcur_3, short eps_temp, short com_temp, int bat_temp)
{
	printf("---WOD packet params---\n");
	printf("vbat is %d\n", vbat);
	printf("5v current is %d\n", vcur_5);
	printf("3v current is %d\n", vcur_3);
	printf("eps_temp %d\n", eps_temp);
	printf("com_temp %d\n", com_temp);
	printf("bat_temp %d\n", bat_temp);
}
