#include "stdafx.h"
#include "IsisTRXVU.h"
#include "Communication.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define IsisTrxvu_initializetoSendLength 39
/**
*  @brief      Initialize the ISIS TRXVU with the corresponding i2cAddress from the array of TRXVU I2C Address structure.
*  @note       This function can only be called once.
*  @param[in]  address array of TRXVU I2C Address structure.
*  @param[in]  maxFrameLengths array of maximum frame length structures for TRXVU.
*  @param[in]	default_bitrates initial default bitrate.
*  @param[in]  number number of attached TRXVU in the system to be initialized.
*  @return     Error code according to <hal/errors.h>
*/
int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number){
	char * funcName = "IsisTrxvu_initialize&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_initializetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, address, sizeof(ISIStrxvuI2CAddress)); //address
	toSend[funcNameLength + sizeof(ISIStrxvuI2CAddress)] = '&';
	memcpy(toSend + funcNameLength + sizeof(ISIStrxvuI2CAddress) + sizeof(char), maxFrameLengths, sizeof(ISIStrxvuFrameLengths)); //maxFrameLengths
	toSend[funcNameLength + sizeof(ISIStrxvuI2CAddress) + sizeof(char) + sizeof(ISIStrxvuFrameLengths)] = '&';
	memcpy(toSend + funcNameLength + sizeof(ISIStrxvuI2CAddress) + sizeof(char) + sizeof(ISIStrxvuFrameLengths) + sizeof(char), default_bitrates, sizeof(ISIStrxvuBitrate)); //default_bitrates
	toSend[funcNameLength + sizeof(ISIStrxvuI2CAddress) + sizeof(char) + sizeof(ISIStrxvuFrameLengths) + sizeof(char) + sizeof(ISIStrxvuBitrate)] = '&';
	memcpy(toSend + funcNameLength + sizeof(ISIStrxvuI2CAddress) + sizeof(char) + sizeof(ISIStrxvuFrameLengths) + sizeof(char) + sizeof(ISIStrxvuBitrate) + sizeof(char), &number, sizeof(unsigned char)); //number
	char* ans = get_data(toSend, IsisTrxvu_initializetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_componentSoftResettoSendLength 37
/**
*  @brief       Soft Reset the ISIS TRXVU Component.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   component TRXVU component, either VU_TC or VU_RC.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_componentSoftReset(unsigned char index, ISIStrxvuComponent component){
	char * funcName = "IsisTrxvu_componentSoftReset&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_componentSoftResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &component, sizeof(ISIStrxvuComponent)); //component
	char* ans = get_data(toSend, IsisTrxvu_componentSoftResettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_componentHardResettoSendLength 37
/**
*  @brief       Hard Reset the ISIS TRXVU Component.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   component TRXVU component, either VU_TC or VU_RC.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_componentHardReset(unsigned char index, ISIStrxvuComponent component){
	char * funcName = "IsisTrxvu_componentHardReset&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_componentHardResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &component, sizeof(ISIStrxvuComponent)); //component
	char* ans = get_data(toSend, IsisTrxvu_componentHardResettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_softResettoSendLength 22
/**
*  @brief       Soft Reset the ISIS TRXVU VU_RC and VU_TC.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_softReset(unsigned char index){
	char * funcName = "IsisTrxvu_softReset&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_softResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_softResettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_hardResettoSendLength 22
/**
*  @brief       Hard Reset the ISIS TRXVU VU_RC and VU_TC.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_hardReset(unsigned char index){
	char * funcName = "IsisTrxvu_hardReset&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_hardResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_hardResettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSendAX25DefClSigntoSendLength 290
/**
*  @brief       Tell the TRXVU to transmit an AX.25 message with default callsigns and specified content.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
*  @param[in]   length Length of the data to be put in the AX.25 message.
*  @param[out]  avail Number of the available slots in the transmission buffer of the VU_TC after the frame has been added.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSendAX25DefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned char *avail){
	char * funcName = "IsisTrxvu_tcSendAX25DefClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSendAX25DefClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), data, length); //data
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + length] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char), &length, sizeof(unsigned char)); //length
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char) + sizeof(unsigned char)] = '&'; //determine the end of string
	char* ans = get_data(toSend, IsisTrxvu_tcSendAX25DefClSigntoSendLength);
	memcpy(avail, ans + 4, sizeof(unsigned char));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSendAX25OvrClSigntoSendLength 306
/**
*  @brief       Tell the TRXVU to transmit an AX.25 message with override callsigns and specified content.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]	 fromCallsign This variable will define the new 7 characters from callsign.
*  @param[in]	 toCallsign This variable will define the new 7 characters to callsign.
*  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
*  @param[in]   length Length of the data to be put in the AX.25 message.
*  @param[out]  avail Number of the available slots in the transmission buffer of the VU_TC after the frame has been added.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSendAX25OvrClSign(unsigned char index, unsigned char *fromCallsign, unsigned char *toCallsign, unsigned char *data, unsigned char length, unsigned char *avail){
	char * funcName = "IsisTrxvu_tcSendAX25OvrClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSendAX25OvrClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), fromCallsign, 7); //fromCallsign
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char), toCallsign, 7); //toCallsign
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char), data, length); //data
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char), &length, sizeof(unsigned char)); //length
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char) + sizeof(unsigned char)] = '&';//determine the end of string
	char* ans = get_data(toSend, IsisTrxvu_tcSendAX25OvrClSigntoSendLength);
	memcpy(avail, ans + 4, sizeof(unsigned char));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetAx25BeaconDefClSigntoSendLength 293
/**
*  @brief       Tell the TRXVU to set the parameters for the AX25 Beacon with default callsigns.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   data Pointer to the array containing the message to be transmitted.
*  @param[in]   length Length of the message.
*  @param[in]   interval Interval of beacon transmission.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25BeaconDefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned short interval){
	char * funcName = "IsisTrxvu_tcSetAx25BeaconDefClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetAx25BeaconDefClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), data, length); //data
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + length] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char), &length, sizeof(unsigned char)); //length
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char) + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char) + sizeof(unsigned char) + sizeof(char), &interval, sizeof(unsigned short)); //interval
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + length + sizeof(char) + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short)] = '&'; //determine the end of string
	char* ans = get_data(toSend, IsisTrxvu_tcSetAx25BeaconDefClSigntoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetAx25BeaconOvrClSigntoSendLength 314
/**
*  @brief       Tell the TRXVU to set the parameters for the AX25 Beacon with override callsigns.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]	 fromCallsign This variable will define the new 7 characters from callsign.
*  @param[in]	 toCallsign This variable will define the new 7 characters to callsign.
*  @param[in]   data Pointer to the array containing the message to be transmitted.
*  @param[in]   length Length of the message.
*  @param[in]   interval Interval of beacon transmission.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25BeaconOvrClSign(unsigned char index, unsigned char *fromCallsign, unsigned char *toCallsign, unsigned char *data, unsigned char length, unsigned short interval){
	char * funcName = "IsisTrxvu_tcSetAx25BeaconOvrClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetAx25BeaconOvrClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), fromCallsign, 7); //fromCallsign
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char), toCallsign, 7); //toCallsign
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char), data, length); //data
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char), &length, sizeof(unsigned char)); //length
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char) + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char) + sizeof(unsigned char) + sizeof(char), &interval, sizeof(unsigned short)); //interval
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + 7 + sizeof(char) + 7 + sizeof(char) + length + sizeof(char) + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short)] = '&'; //determine the end of string
	char* ans = get_data(toSend, IsisTrxvu_tcSetAx25BeaconOvrClSigntoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcClearBeacontoSendLength 26
/**
*  @brief       Tell the TRXVU to clear the current beacon.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcClearBeacon(unsigned char index){
	char * funcName = "IsisTrxvu_tcClearBeacon&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcClearBeacontoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_tcClearBeacontoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetDefToClSigntoSendLength 37
/**
*  @brief       Tell the TRXVU to set a new default to callsign name.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   toCallsign This variable will define the new 7 characters default to callsign.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetDefToClSign(unsigned char index, unsigned char *toCallsign){
	char * funcName = "IsisTrxvu_tcSetDefToClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetDefToClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), toCallsign, 7); //toCallsign
	char* ans = get_data(toSend, IsisTrxvu_tcSetDefToClSigntoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetDefFromClSigntoSendLength 39
/**
*  @brief       Tell the TRXVU to set a new default from callsign name.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   fromCallsign This variable will define the new 7 characters default from callsign.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetDefFromClSign(unsigned char index, unsigned char *fromCallsign){
	char * funcName = "IsisTrxvu_tcSetDefFromClSign&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetDefFromClSigntoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), fromCallsign, 7); //fromCallsign
	char* ans = get_data(toSend, IsisTrxvu_tcSetDefFromClSigntoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetIdlestatetoSendLength 31
/**
*  @brief       Set the idle state of the TRXVU transmitter, i.e. the state in between transmission.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   state The desired idle state of the TRXVU.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetIdlestate(unsigned char index, ISIStrxvuIdleState state){
	char * funcName = "IsisTrxvu_tcSetIdlestate&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetIdlestatetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &state, sizeof(ISIStrxvuIdleState)); //state
	char* ans = get_data(toSend, IsisTrxvu_tcSetIdlestatetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcSetAx25BitratetoSendLength 33
/**
*  @brief       Set the AX.25 bitrate of the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   bitrate The desired AX.25 bitrate of the TRXVU.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25Bitrate(unsigned char index, ISIStrxvuBitrate bitrate){
	char * funcName = "IsisTrxvu_tcSetAx25Bitrate&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcSetAx25BitratetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &bitrate, sizeof(ISIStrxvuBitrate)); //bitrate
	char* ans = get_data(toSend, IsisTrxvu_tcSetAx25BitratetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcGetUptimetoSendLength 29
/**
*  @brief       Retrieve the current time of operation of the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  uptime This array of 4 characters contains the operation time of the transmitter (Seconds, Minutes, Hours and Days, in that order).
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetUptime(unsigned char index, unsigned char *uptime){
	char * funcName = "IsisTrxvu_tcGetUptime&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcGetUptimetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_tcGetUptimetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(uptime, ans + 4, 4);
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcGetStatetoSendLength 25
/**
*  @brief       Retrieve the current transmitter status.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  currentvutcState Pointer to the union where the current status should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetState(unsigned char index, ISIStrxvuTransmitterState *currentvutcState){
	char * funcName = "IsisTrxvu_tcGetState&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcGetStatetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_tcGetStatetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	currentvutcState->fields.transmitter_idle_state = (ISIStrxvuIdleState)((int*)ans)[1];
	currentvutcState->fields.transmitter_beacon = (ISIStrxvuBeacon)((int*)ans)[2];
	int bitrate = (ISIStrxvuBitrateStatus)((int*)ans)[3];
	if (bitrate == 0){
		currentvutcState->fields.transmitter_bitrate = trxvu_bitratestatus_1200;
	}
	else
	{
		if (bitrate == 1){
			currentvutcState->fields.transmitter_bitrate = trxvu_bitratestatus_2400;
		}
		else
		{
			if (bitrate == 2){
				currentvutcState->fields.transmitter_bitrate = trxvu_bitratestatus_4800;
			}
			else
			{
				currentvutcState->fields.transmitter_bitrate = trxvu_bitratestatus_9600;
			}
		}
	}
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcGetTelemetryAlltoSendLength 32
/**
*  @brief       Retrieve a block of telemetry from the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetTelemetryAll(unsigned char index, ISIStrxvuTxTelemetry *telemetry){
	char * funcName = "IsisTrxvu_tcGetTelemetryAll&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcGetTelemetryAlltoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_tcGetTelemetryAlltoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(telemetry->raw, ans + 4, sizeof(ISIStrxvuTxTelemetry));
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcGetLastTxTelemetrytoSendLength 42
/**
*  @brief       Retrieve a block of telemetry from the TRXVU transmitter sotre on the last transmission.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  last_telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetLastTxTelemetry(unsigned char index, ISIStrxvuTxTelemetry *last_telemetry){
	char * funcName = "IsisTrxvu_tcGetLastTxTelemetry&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcGetLastTxTelemetrytoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_tcGetLastTxTelemetrytoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(last_telemetry, ans + 4, sizeof(ISIStrxvuTxTelemetry));
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_tcEstimateTransmissionTimetoSendLength 41
/**
*  @brief       Calculates the approximate time it will take for a certain transmission to complete.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   length The length of the transmission in bytes.
*  @return      The time estimate in milliseconds.
*/
unsigned short IsisTrxvu_tcEstimateTransmissionTime(unsigned char index, unsigned char length){
	char * funcName = "IsisTrxvu_tcEstimateTransmissionTime&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_tcEstimateTransmissionTimetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &length, sizeof(unsigned char)); //length
	char* ans = get_data(toSend, IsisTrxvu_tcEstimateTransmissionTimetoSendLength);
	unsigned short estTime;
	memcpy(&estTime, ans, sizeof(unsigned short));
	free(ans);
	return estTime;
}

#define IsisTrxvu_rcGetFrameCounttoSendLength 28
/**
*  @brief       Retrieve the number of telecommand frames present in the receive buffer of the TRXVU.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  frameCount The number of telecommand frames in the buffer.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetFrameCount(unsigned char index, unsigned short *frameCount){
	char * funcName = "IsisTrxvu_rcGetFrameCount&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_rcGetFrameCounttoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_rcGetFrameCounttoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(frameCount, ans + 4, sizeof(unsigned short));
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_rcGetCommandFrametoSendLength 30
/**
*  @brief       Retrieve and delete a telecommand frame from the TRXVU.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  rx_frame Pointer to the struct where the telecommand frame should be store.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetCommandFrame(unsigned char index, ISIStrxvuRxFrame *rx_frame){
	char * funcName = "IsisTrxvu_rcGetCommandFrame&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_rcGetCommandFrametoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_rcGetCommandFrametoSendLength);
	int errorToReturn = -((int*)ans)[0];
	rx_frame->rx_length = ((unsigned short*)ans)[2];
	rx_frame->rx_doppler = ((unsigned short*)ans)[3];
	rx_frame->rx_rssi = ((unsigned short*)ans)[4];
	memcpy(rx_frame->rx_framedata, ans + 10, rx_frame->rx_length);
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_rcGetTelemetryAlltoSendLength 30
/**
*  @brief       Retrieve a block of telemetry from the TRXVU receiver.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetTelemetryAll(unsigned char index, ISIStrxvuRxTelemetry *telemetry){
	char * funcName = "IsisTrxvu_rcGetTelemetryAll&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_rcGetTelemetryAlltoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_rcGetTelemetryAlltoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(telemetry->raw, ans + 4, sizeof(ISIStrxvuRxTelemetry));
	free(ans);
	return errorToReturn;
}

#define IsisTrxvu_rcGetUptimetoSendLength 24
/**
*  @brief       Retrieve the current time of operation of the TRXVU receiver.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  uptime This array of 3 characters contains the operation time of the receiver (Minutes, Hours and Days, in that order)..
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetUptime(unsigned char index, unsigned char *uptime){
	char * funcName = "IsisTrxvu_rcGetUptime&";
	int funcNameLength = strlen(funcName);
	char toSend[IsisTrxvu_rcGetUptimetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, IsisTrxvu_rcGetUptimetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(uptime, ans + 4, 3);
	free(ans);
	return errorToReturn;
}
