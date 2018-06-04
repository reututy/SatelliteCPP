/*
* GomEPS.c
*
*  Created on: 8 בינו׳ 2018
*      Author: User
*/
#include "stdafx.h"
#include "GomEPS.h"
#include "Communication.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GomEpsInitializetoSendLenght 20
/**
* 	Initialize the GOMSpace EPS with the corresponding i2cAddress. This function can only be called once.
*
* 	@param[in] i2c_address array of GOMSpace EPS I2C bus address
* 	@param[in] number number of attached EPS in the system to be initialized
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsInitialize(unsigned char* i2c_address, unsigned char number) {
	char* funcName = "GomEpsInitialize&";
	int funcNameLenght = strlen(funcName);
	const int toSendLenght = GomEpsInitializetoSendLenght;
	char toSend[GomEpsInitializetoSendLenght];
	memcpy(toSend, funcName, funcNameLenght); //function name
	memcpy(toSend + funcNameLenght, i2c_address, sizeof(i2c_address[0])); //i2c_address
	toSend[funcNameLenght + sizeof(i2c_address[0])] = '&';
	memcpy(toSend + funcNameLenght + sizeof(i2c_address[0]) + sizeof(char),
		&number, sizeof(number)); //number
	char* ans = get_data(toSend, toSendLenght);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsPingtoSendLength 14
/**
*	Send a ping to the GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] ping_byte a byte used to ping the GOMSpace EPS
*	@param[out] ping_byte_out byte returned from GOMSpace EPS as a response
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsPing(unsigned char index, unsigned char ping_byte,
	unsigned char* ping_byte_out) {
	char* funcName = "GomEpsPing&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsPingtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(char) + sizeof(char), &ping_byte,
		sizeof(unsigned char)); //ping_byte
	char* ans = get_data(toSend, GomEpsPingtoSendLength);
	int outputLength = sizeof(unsigned char);
	ping_byte_out[0] = ans[4];
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsSoftResettoSendLength 18
/**
* 	Software Reset on the GOMSpace EPS based on the index.
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSoftReset(unsigned char index) {
	char* funcName = "GomEpsSoftReset&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSoftResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsSoftResettoSendLength);
	int errorToReturn = ((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsHardResettoSendLength 18
/**
* 	Hardware Reset on the GOMSpace EPS based on the index.
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsHardReset(unsigned char index) {
	char* funcName = "GomEpsHardReset&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsHardResettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsHardResettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsGetHkData_paramtoSendLength 24
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_param(unsigned char index, gom_eps_hkparam_t* data_out) {
	char* funcName = "GomEpsGetHkData_param&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_paramtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_paramtoSendLength);
	memcpy(data_out, ans + 1, sizeof(gom_eps_hkparam_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsGetHkData_generaltoSendLength 26
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. p31u-8 format.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_general(unsigned char index, gom_eps_hk_t* data_out) {
	char* funcName = "GomEpsGetHkData_general&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_generaltoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_generaltoSendLength);
	memcpy(data_out->raw, ans + 4, sizeof(gom_eps_hk_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define GomEpsGetHkData_vitoSendLength 21
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS.Voltage and Current subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_vi(unsigned char index, gom_eps_hk_vi_t* data_out) {
	char* funcName = "GomEpsGetHkData_vi&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_vitoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_vitoSendLength);
	memcpy(data_out->raw, ans + 4, sizeof(gom_eps_hk_vi_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsGetHkData_outtoSendLength 22
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. Output switch data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_out(unsigned char index, gom_eps_hk_out_t* data_out) {
	char* funcName = "GomEpsGetHkData_out&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_outtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_outtoSendLength);
	memcpy(data_out->raw, ans + 4, sizeof(gom_eps_hk_out_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsGetHkData_wdttoSendLength 22
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. WDT data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_wdt(unsigned char index, gom_eps_hk_wdt_t* data_out) {
	char* funcName = "GomEpsGetHkData_wdt&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_wdttoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_wdttoSendLength);
	memcpy(data_out->raw, ans + 4, sizeof(gom_eps_hk_wdt_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsGetHkData_basictoSendLength 24
/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. Basic data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_basic(unsigned char index, gom_eps_hk_basic_t* data_out) {
	char* funcName = "GomEpsGetHkData_basic&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsGetHkData_basictoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsGetHkData_basictoSendLength);
	memcpy(data_out->raw, ans + 4, sizeof(gom_eps_hk_basic_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsSetOutputtoSendLength 20
/**
*	Set the GOMSpace EPS Output channel
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] output output channel mask selection, 1 = on, 0 = off
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetOutput(unsigned char index, gom_eps_channelstates_t output) {
	char* funcName = "GomEpsSetOutput&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSetOutputtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		&output, sizeof(gom_eps_channelstates_t)); //channels output byte
	char* ans = get_data(toSend, GomEpsSetOutputtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsSetSingleOutputtoSendLength 31
/**
* 	Command the GOMSpace EPS to turn on / off a single switched channel after a delay
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] channel_id channel number to be turned on / off
*	@param[in] out value of the output channel defined in the output channel mask selection
*	@param[in] delay scheduled delay in seconds before the output is executed
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetSingleOutput(unsigned char index, gom_eps_channelid_t channel_id,
	gom_eps_output_status_t out, unsigned short delay) {
	char* funcName = "GomEpsSetSingleOutput&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSetSingleOutputtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &channel_id, sizeof(gom_eps_channelid_t)); //channel_id channel number to be turned on / off
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(gom_eps_channelid_t)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(gom_eps_channelid_t) + sizeof(char),
		&out, sizeof(gom_eps_output_status_t)); //out value of the output channel
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(gom_eps_channelid_t) + sizeof(char) + sizeof(gom_eps_output_status_t)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(gom_eps_channelid_t) + sizeof(char) + sizeof(gom_eps_output_status_t) + sizeof(char),
		&delay, sizeof(unsigned short)); //out value of the output channel
	char* ans = get_data(toSend, GomEpsSetSingleOutputtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsSetPhotovoltaicInputstoSendLength 39
/**
*	Set the GOMSpace EPS photovoltaic input voltage into a specific value
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] voltage1 photovoltaic1 voltage
*	@param[in] voltage2 photovoltaic2 voltage
*	@param[in] voltage3 photovoltaic3 voltage
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetPhotovoltaicInputs(unsigned char index, unsigned short voltage1,
	unsigned short voltage2, unsigned short voltage3) {
	char* funcName = "GomEpsSetPhotovoltaicInputs&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSetPhotovoltaicInputstoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &voltage1, sizeof(unsigned short)); // voltage1
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short) + sizeof(char),
		&voltage2, sizeof(unsigned short)); // voltage2
	toSend[funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short) + sizeof(char) + sizeof(unsigned short)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char) + sizeof(unsigned short) + sizeof(char) + sizeof(unsigned short) + sizeof(char),
		&voltage3, sizeof(unsigned short)); // voltage3
	char* ans = get_data(toSend, GomEpsSetPhotovoltaicInputstoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsSetPptModetoSendLength 21
/**
*	Set the GOMSpace EPS power point mode
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] mode power point mode of the eps
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetPptMode(unsigned char index, gom_eps_power_point_mode_t mode) {
	char* funcName = "GomEpsSetPptMode&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSetPptModetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		&mode, sizeof(gom_eps_power_point_mode_t)); //mode
	char* ans = get_data(toSend, GomEpsSetPptModetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsSetHeaterAutoModetoSendLength 28
/**
*	Set the GOMSpace EPS Heater Auto Mode
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] auto_mode desired heater auto mode to the GOMSpace EPS
*	@param[out] auto_mode_return current heater auto mode
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetHeaterAutoMode(unsigned char index,
	gom_eps_heater_auto_t auto_mode,
	gom_eps_heater_auto_t* auto_mode_return) {
	char* funcName = "GomEpsSetHeaterAutoMode&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsSetHeaterAutoModetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char), &auto_mode,
		sizeof(gom_eps_heater_auto_t)); //auto_mode
	char* ans = get_data(toSend, GomEpsSetHeaterAutoModetoSendLength);
	int outputLength = sizeof(gom_eps_heater_auto_t);
	memcpy(auto_mode_return, ans + 4, outputLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsResetCounterstoSendLength 22
/**
*	Reset the GOMSpace EPS counters
*
*	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsResetCounters(unsigned char index) {
	char* funcName = "GomEpsResetCounters&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsResetCounterstoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsResetCounterstoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsResetWDTtoSendLength 17
/**
*	Reset WDT in the GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsResetWDT(unsigned char index) {
	char* funcName = "GomEpsResetWDT&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsResetWDTtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsResetWDTtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfigCMDtoSendLength 20
/**
*	Configuration command for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] cmd configuration control command.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigCMD(unsigned char index, unsigned char cmd) {
	char* funcName = "GomEpsConfigCMD&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfigCMDtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		&cmd, sizeof(unsigned char)); //cmd
	char* ans = get_data(toSend, GomEpsConfigCMDtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfigGettoSendLength 18
/**
*	Get configuration data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigGet(unsigned char index, eps_config_t* config_data) {
	char* funcName = "GomEpsConfigGet&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfigGettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsConfigGettoSendLength);
	memcpy(config_data->raw, ans + 4, sizeof(eps_config_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfigSettoSendLength 79
/**
*	Set configuration data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigSet(unsigned char index, eps_config_t* config_data) {
	char* funcName = "GomEpsConfigSet&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfigSettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		config_data, sizeof(eps_config_t)); //config_data
	char* ans = get_data(toSend, GomEpsConfigSettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfig2CMDtoSendLength 21
/**
*	Configuration 2 command for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] cmd configuration control command.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2CMD(unsigned char index, unsigned char cmd) {
	char* funcName = "GomEpsConfig2CMD&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfig2CMDtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		&cmd, sizeof(unsigned char)); //cmd
	char* ans = get_data(toSend, GomEpsConfig2CMDtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfig2GettoSendLength 19
/**
*	Get configuration 2 data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2Get(unsigned char index, eps_config2_t* config_data) {
	char* funcName = "GomEpsConfig2Get&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfig2GettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	char* ans = get_data(toSend, GomEpsConfig2GettoSendLength);
	memcpy(config_data->raw, ans + 4, sizeof(eps_config2_t));
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define  GomEpsConfig2SettoSendLength 42
/**
*	Set configuration 2 data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2Set(unsigned char index, eps_config2_t* config_data) {
	char* funcName = "GomEpsConfig2Set&";
	int funcNameLength = strlen(funcName);
	char toSend[GomEpsConfig2SettoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &index, sizeof(unsigned char)); //index
	toSend[funcNameLength + sizeof(unsigned char)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned char) + sizeof(char),
		config_data, sizeof(eps_config2_t)); //config_data
	char* ans = get_data(toSend, GomEpsConfig2SettoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}
