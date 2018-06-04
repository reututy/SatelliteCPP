/**
*	@file GomEPS.h
* 	@brief	GOMspace Electrical Power System
*/

#ifndef GOMEPS_H_
#define GOMEPS_H_

#include "simulatorEPSFormat.h"

/**
*	This is the list of power point modes in the GOMSpace EPS
*/
typedef enum _gom_eps_power_point_mode_t
{
	gomeps_ppt_hardware = 0x00,
	gomeps_ppt_maximum = 0x01,
	gomeps_ppt_software = 0x02
} gom_eps_power_point_mode_t;

/**
*	Union consisting of bitflags used in the GOMSpace EPS Channel Status
*/
typedef union _gom_eps_channelstates_t
{
	unsigned char raw; //!< Unformatted GOM EPS channel status
	struct
	{
		unsigned char channel5V_1 : 1,
		channel5V_2 : 1,
				  channel5V_3 : 1,
							channel3V3_1 : 1,
									   channel3V3_2 : 1,
												  channel3V3_3 : 1,
															 quadbatSwitch : 1,
																		 quadbatHeater : 1;
	}fields; //!< Struct with individual fields of GOM EPS channel status
} gom_eps_channelstates_t;

/**
* List of EPS channel IDs
*/
typedef enum _gom_eps_channelid_t
{
	gomeps_channel_0 = 0,
	gomeps_channel_1 = 1,
	gomeps_channel_2 = 2,
	gomeps_channel_3 = 3,
	gomeps_channel_4 = 4,
	gomeps_channel_5 = 5,
	gomeps_channel_quadbat_heater = 6,
	gomeps_channel_quadbat_switch = 7
} gom_eps_channelid_t;

/**
*	Output status of a channel
*/
typedef enum _gom_eps_output_status_t
{
	gomeps_channel_off = 0x00,
	gomeps_channel_on = 0x01
} gom_eps_output_status_t;

/**
* Union for storing the block of telemetry values coming from the EPS. HK version 1.
*/
typedef union _gom_eps_hkparam_t
{
	unsigned char raw[45]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned short photoVoltaic3; //!< Voltage value at photovoltaic 3 [mV]
		unsigned short photoVoltaic2; //!< Voltage value at photovoltaic 2 [mV]
		unsigned short photoVoltaic1; //!< Voltage value at photovoltaic 1 [mV]
		unsigned short pc; //!< Total photo current [mA]
		unsigned short bv; //!< Battery voltage [mV]
		unsigned short sc; //!< Total system current [mA]
		short tempConverter1; //!< Temperature of boost converter 1 [degC]
		short tempConverter2; //!< Temperature of boost converter 2 [degC]
		short tempConverter3; //!< Temperature of boost converter 3 [degC]
		short tempBattery; //!< Temperature of EPS battery [degC]
		short batteryBoardTemp[2]; //!< External board battery temperatures [degC]; (will always be zero, board not present)
		unsigned short latchUp3v3Channel3; //!< Latchup Count at 3v3 Channel 3
		unsigned short latchUp3v3Channel2; //!< Latchup Count at 3v3 Channel 2
		unsigned short latchUp3v3Channel1; //!< Latchup Count at 3v3 Channel 1
		unsigned short latchUp5vChannel3; //!< Latchup Count at 5v Channel 3
		unsigned short latchUp5vChannel2; //!< Latchup Count at 5v Channel 2
		unsigned short latchUp5vChannel1; //!< Latchup Count at 5v Channel 1
		unsigned char reset; //!< Cause of last EPS reset
		unsigned short bootCount; //!< Number of EPS reboots
		unsigned short swErrors; //!< Number of errors in the eps software
		unsigned char pptMode; //!< 0 = Hardware, 1 = MPPT, 2 = Fixed SW PPT.
		gom_eps_channelstates_t channelStatus; //!< Output channel status, 1 = on, 0 = off
	} fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 1.
} gom_eps_hkparam_t;

/**
* Status of the EPS battery heater
*/
typedef enum _gom_eps_heater_auto_t
{
	mode_off = 0x00,
	mode_on = 0x01
} gom_eps_heater_auto_t;

/**
* 	Initialize the GOMSpace EPS with the corresponding i2cAddress. This function can only be called once.
*
* 	@param[in] i2c_address array of GOMSpace EPS I2C bus address
* 	@param[in] number number of attached EPS in the system to be initialized
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsInitialize(unsigned char* i2c_address, unsigned char number);

/**
*	Send a ping to the GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] ping_byte a byte used to ping the GOMSpace EPS
*	@param[out] ping_byte_out byte returned from GOMSpace EPS as a response
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsPing(unsigned char index, unsigned char ping_byte, unsigned char* ping_byte_out);

/**
* 	Software Reset on the GOMSpace EPS based on the index.
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSoftReset(unsigned char index);

/**
* 	Hardware Reset on the GOMSpace EPS based on the index.
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsHardReset(unsigned char index);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_param(unsigned char index, gom_eps_hkparam_t* data_out);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. p31u-8 format.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_general(unsigned char index, gom_eps_hk_t* data_out);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS.Voltage and Current subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_vi(unsigned char index, gom_eps_hk_vi_t* data_out);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. Output switch data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_out(unsigned char index, gom_eps_hk_out_t* data_out);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. WDT data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_wdt(unsigned char index, gom_eps_hk_wdt_t* data_out);

/**
*	Read back the current housekeeping data from GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] data_out housekeeping output of GOMSpace EPS. Basic data subset.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsGetHkData_basic(unsigned char index, gom_eps_hk_basic_t* data_out);

/**
*	Set the GOMSpace EPS Output channel
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] output output channel mask selection, 1 = on, 0 = off
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetOutput(unsigned char index, gom_eps_channelstates_t output);

/**
* 	Command the GOMSpace EPS to turn on / off a single switched channel after a delay
*
* 	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] channel_id channel number to be turned on / off
*	@param[in] out value of the output channel defined in the output channel mask selection
*	@param[in] delay scheduled delay in seconds before the output is executed
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetSingleOutput(unsigned char index, gom_eps_channelid_t channel_id, gom_eps_output_status_t out, unsigned short delay);

/**
*	Set the GOMSpace EPS photovoltaic input voltage into a specific value
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] voltage1 photovoltaic1 voltage
*	@param[in] voltage2 photovoltaic2 voltage
*	@param[in] voltage3 photovoltaic3 voltage
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetPhotovoltaicInputs(unsigned char index, unsigned short voltage1, unsigned short voltage2, unsigned short voltage3);

/**
*	Set the GOMSpace EPS power point mode
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] mode power point mode of the eps
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetPptMode(unsigned char index, gom_eps_power_point_mode_t mode);

/**
*	Set the GOMSpace EPS Heater Auto Mode
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] auto_mode desired heater auto mode to the GOMSpace EPS
*	@param[out] auto_mode_return current heater auto mode
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsSetHeaterAutoMode(unsigned char index, gom_eps_heater_auto_t auto_mode, gom_eps_heater_auto_t* auto_mode_return);

/**
*	Reset the GOMSpace EPS counters
*
*	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsResetCounters(unsigned char index);

/**
*	Reset WDT in the GOMSpace EPS
*
*	@param[in] index index of GOMSpace EPS I2C bus address
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsResetWDT(unsigned char index);

/**
*	Configuration command for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] cmd configuration control command.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigCMD(unsigned char index, unsigned char cmd);

/**
*	Get configuration data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigGet(unsigned char index, eps_config_t* config_data);

/**
*	Set configuration data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfigSet(unsigned char index, eps_config_t* config_data);

/**
*	Configuration 2 command for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] cmd configuration control command.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2CMD(unsigned char index, unsigned char cmd);

/**
*	Get configuration 2 data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[out] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2Get(unsigned char index, eps_config2_t* config_data);

/**
*	Set configuration 2 data for the GOMSpace EPS version
*
*	@param[in] index index of GOMSpace EPS I2C bus address
*	@param[in] config_data configuration 1 data.
* 	@return Error code according to <hal/errors.h>
*/
int GomEpsConfig2Set(unsigned char index, eps_config2_t* config_data);

int GomEpsDistractor();

/*For testing and threads*/
struct p31u_eps* get_eps_table(void);

int get_N_EPS(void);



#endif /* GOMEPS_H_ */
