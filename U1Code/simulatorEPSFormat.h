/* * simulatorEPSFormat.h
*
*  Created on: 28 áãöî× 2017
*      Author: User
*/

#ifndef SRC_SIMULATOREPSFORMAT_H_
#define SRC_SIMULATOREPSFORMAT_H_

#include <stdint.h>

typedef struct hkparam_t{
	uint16_t pv[3]; //Photo-voltaic input voltage [mV]
	uint16_t pc; //Total photo current [mA]
	uint16_t bv; //Battery voltage [mV]
	uint16_t sc; //Total system current [mA]
	int16_t temp[4]; //Temp. of boost converters (1,2,3) and onboard battery [degC]
	int16_t batt_temp[2]; //External board battery temperatures [degC];
	uint16_t latchup[6]; //Number of latch-ups on each output 5V and +3V3 channel
	//Order[5V1 5V2 5V3 3.3V1 3.3V2 3.3V3]
	//Transmit as 5V1 first and 3.3V3 last
	uint8_t reset; //Cause of last EPS reset
	uint16_t bootcount; //Number of EPS reboots
	uint16_t sw_errors; //Number of errors in the eps software
	uint8_t ppt_mode; //0 = Hardware, 1 = MPPT, 2 = Fixed SW PPT.
	uint8_t channel_status; //Mask of output channel status, 1=on, 0=off
	//MSB - [QH QS 3.3V3 3.3V2 3.3V1 5V3 5V2 5V1] - LSB
	// QH = Quadbat heater, QS = Quadbat switch
};

/**
* Union for storing the block of telemetry values coming from the EPS. HK version 2.

The order of the struct is important (because of the typdef union rount by int part), do not change order of fields.
*/
typedef union _gom_eps_hk_t
{
	unsigned char raw[133]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned short vboost[3]; //!< Voltage of boost converters [mV] [PV1, PV2, PV3]
		unsigned short vbatt; //!< Voltage of battery [mV]
		unsigned short curin[3]; //!< Current in [mA]
		unsigned short cursun; //!< Current from boost converters
		unsigned short cursys; //!< Current out of battery
		unsigned short reserved1; //!< Reserved for future use
		unsigned short curout[6]; //!< Current out [mA]
		unsigned char output[8]; //!< Status of outputs
		unsigned short output_on_delta[8]; //!< Time till power on for each channel
		unsigned short output_off_delta[8]; //!< Time till power off for each channel
		unsigned short latchup[6]; //!< Number of latch-ups for each channel
		unsigned int wdt_i2c_time_left; //!< Time left on I2C wdt
		unsigned int wdt_gnd_time_left; //!< Time left on I2C wdt
		unsigned char wdt_csp_pings_left[2]; //!< Pings left on CSP wdt
		unsigned int counter_wdt_i2c; //!< Number of WDT I2C reboots
		unsigned int counter_wdt_gnd; //!< Number of WDT GND reboots
		unsigned int counter_wdt_csp[2]; //!< Number of WDT CSP reboots
		unsigned int counter_boot; //!< Number of EPS reboots
		short temp[6]; //!< Temperature sensors [0 = TEMP1, TEMP2, TEMP3, TEMP4, BATT0, BATT1]
		unsigned char bootcause; //!< Cause of last EPS reset
		unsigned char battmode; //!< Mode for battery [0 = normal, 1 = undervoltage, 2 = overvoltage]
		unsigned char pptmode; //!< Mode of PPT tracker
		unsigned short reserved2;
	} fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 2. 92*/
} gom_eps_hk_t;


/**
* Union for storing the block of telemetry values coming from the EPS. HK version 3.
*/
typedef union _gom_eps_hk_vi_t
{
	unsigned char raw[22]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned short vboost[3]; //!< Voltage of boost converters [mV] [PV1, PV2, PV3]
		unsigned short vbatt; //!< Voltage of battery [mV]
		unsigned short curin[3]; //!< Current in [mA]
		unsigned short cursun; //!< Current from boost converters
		unsigned short cursys; //!< Current out of battery
		unsigned short reserved1; //!< Reserved for future use
	} fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 3.
} gom_eps_hk_vi_t;

/**
* Union for storing the block of telemetry values coming from the EPS. HK version 4.
*/
typedef union _gom_eps_hk_out_t
{
	unsigned char raw[66]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned short curout[6]; //!< Current out [mA]
		unsigned char output[8]; //!< Status of outputs
		unsigned short output_on_delta[8]; //!< Time till power on
		unsigned short output_off_delta[8]; //!< Time till power off
		unsigned short latchup[6]; //!< Number of latch-ups
	} fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 4.
} gom_eps_hk_out_t;

/**
* Union for storing the block of telemetry values coming from the EPS. HK version 5.
*/
typedef union _gom_eps_hk_wdt_t
{
	unsigned char raw[28]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned int wdt_i2c_time_left; //!< Time left on I2C wdt
		unsigned int wdt_gnd_time_left; //!< Time left on I2C wdt
		unsigned char wdt_csp_pings_left[2]; //!< Pings left on CSP wdt
		unsigned int counter_wdt_i2c; //!< Number of WDT I2C reboots
		unsigned int counter_wdt_gnd; //!< Number of WDT GND reboots
		unsigned int counter_wdt_csp[2]; //!< Number of WDT CSP reboots
	}fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 5.*/
} gom_eps_hk_wdt_t;

/**
* Union for storing the block of telemetry values coming from the EPS. HK version 6.
*/
typedef union _gom_eps_hk_basic_t
{
	unsigned char raw[23]; //!< Unformatted GOM EPS telemetry
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned int counter_boot; //!< Number of EPS reboots
		short temp[6]; //!< Temperature sensors [0 = TEMP1, TEMP2, TEMP3, TEMP4, BATT0, BATT1]
		unsigned char bootcause; //!< Cause of last EPS reset
		unsigned char battmode; //!< Mode for battery [0 = normal, 1 = undervoltage, 2 = overvoltage]
		unsigned char pptmode; //!< Mode of PPT tracker
		unsigned short reserved2;
	}fields; //!< Struct with individual fields of GOM EPS telemetry. HK version 6.*/
} gom_eps_hk_basic_t;

/**
* Union for storing the block of configuration values coming from the EPS.
*/
typedef union _eps_config_t
{
	unsigned char raw[60]; //!< Unformatted GOM EPS configuration values
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned char ppt_mode; //!< Mode for PPT [1 = AUTO, 2 = FIXED]
		unsigned char battheater_mode; //!< Mode for battheater [0 = Manual, 1 = Auto]
		char battheater_low; //!< Turn heater on at [degC]
		char battheater_high; //!< Turn heater off at [degC]
		unsigned char output_normal_value[8]; //!< Nominal mode output value
		unsigned char output_safe_value[8]; //!< Safe mode output value
		unsigned short output_initial_on_delay[8]; //!< Output switches: init with these on delays [s]
		unsigned short output_initial_off_delay[8];//!< Output switches: init with these off delays [s]
		unsigned short vboost[3]; //!< Fixed PPT point for boost converters [mV]
	}fields; //!< Struct with individual fields of GOM EPS configuration values.*/
} eps_config_t;

/**
* Union for storing the block of configuration values 2 coming from the EPS.
*/
typedef union _eps_config2_t
{
	unsigned char raw[22]; //!< Unformatted GOM EPS configuration values 2
	struct
	{
		unsigned short commandReply; //!< reply of the last command
		unsigned short batt_maxvoltage; //!< Maximum battery voltage
		unsigned short batt_safevoltage; //!< Battery voltage for safe mode
		unsigned short batt_criticalvoltage; //!< Battery voltage for critical mode
		unsigned short batt_normalvoltage; //!< Battery voltage for normal mode
		unsigned int reserved1[2];
		unsigned char reserved2[4];
	}fields; //!< Struct with individual fields of GOM EPS configuration values 2.
} eps_config2_t;

/* battery software level set points */
#define MAX_VBAT 		8300
#define NORMAL_VBAT 	7400
#define SAFE_VBAT 		7200
#define CRITICAL_VBAT 	6500

/* battery protection states */
enum batt_state { INITIAL, CRITICAL, SAFE, NORMAL, FULL };

/*MSB - [QH QS 3.3V3 3.3V2 3.3V1 5V3 5V2 5V1] - LSB*/
/*channel types*/
enum channel_type{ T_5V1, T_5V2, T_5V3, T_3_3V1, T_3_3V2, T_3_3V3, T_QS, T_QH };

/*wdt types*/
enum wdt_type{ I2C, GND, CSP0, CSP1 };

/* ppt mode */
#define HARDWARE 0
#define MPPT 1
#define FIXEDSWPPT 2

/* channels status */
#define ON 1
#define OFF 0

/* battery type */
#define ONBOARD_BATT 0
#define EXTERNAL_BATT 1

/* battery heater mode */
#define MANUAL 0
#define AUTO 1

/* heater type */
#define BP4_HEATER		0
#define ONBOARD_HEATER	1
#define BOTH_HEATER		2

/* causes of reset */
#define UNKNOWN_RESET_R 		0
#define DEDICATED_WDT_RESET_R 	1
#define I2C_WDT_RESET_R 		2
#define HARD_RESET_R 			3
#define SOFT_RESET_R 			4
#define STACK_OVERFLOW_RESET_R 	5
#define TIMER_OVERFLOW_RESET_R 	6
#define BROWNOUT_RESET_R 		7
#define INTERNAL_WDT_RESET_R 	8


#define SOFTWARE_PPT_DEFAULT_V	4000

#define SWITCH_OFF_V	6000
#define SWITCH_ON_V		6400

/*config default values*/
#define DEFAULT_CONFIG_PPT_MODE			FIXEDSWPPT
#define DEFAULT_CONFIG_BATTHEAT_MODE	AUTO
#define DEFAULT_CONFIG_BATTHEAT_LOW		0 		//need to be changed
#define DEFAULT_CONFIG_BATTHEAT_HIGH	100 	//need to be changed
#define DEFAULT_CONFIG_OUTPUT_NORMAL	0 		//need to be changed
#define DEFAULT_CONFIG_OUTPUT_SAFE		0 		//need to be changed
#define DEFAULT_CONFIG_OUTPUT_ON_DELAY	1 		//need to be changed
#define DEFAULT_CONFIG_OUTPUT_OFF_DELAY	1 		//need to be changed
#define DEFAULT_CONFIG_VBOOST 			SOFTWARE_PPT_DEFAULT_V

/*parameters - min, max and typ values*/

/*battery*/
#define BAT_CONNECT_V_MIN					6000
#define BAT_CONNECT_V_TYP					7400
#define BAT_CONNECT_V_MAX					8400
#define BAT_CONNECT_I_CHARGE_MAX			6000
#define BAT_CONNECT_I_DISCHARGE_THRESHOLD	6800

/*pv inputs*/
#define PV_IN_V_MIN			0
#define PV_IN_V_TYP			4200
#define PV_IN_V_MAX			8500
#define PV_IN_I_CHARGE_MIN	0
#define PV_IN_I_CHARGE_MAX	2000

/*5v in*/
#define IN_5V_V_MIN		4100
#define IN_5V_V_TYP		5000
#define IN_5V_V_MAX		5000
#define IN_5V_I_MIN		0
#define IN_5V_I_TYP		900
#define IN_5V_I_MAX		1100

/*out 1-6 latchup protected*/
#define OUT_LATCHUP_PROTEC_5V_TYP		4980
#define OUT_LATCHUP_PROTEC_3_3V_TYP		3300
#define OUT_LATCHUP_PROTEC_I_MIN		500
#define OUT_LATCHUP_PROTEC_I_MAX		3000

/*+5v*/
#define REG_OUT_5V_V_MIN	4890
#define REG_OUT_5V_V_TYP	4980
#define REG_OUT_5V_V_MAX	5050
#define REG_OUT_5V_I_MIN	5
#define REG_OUT_5V_I_MAX	4000

/*+3.3v*/
#define REG_OUT_3V_V_MIN	3290
#define REG_OUT_3V_V_TYP	3340
#define REG_OUT_3V_V_MAX	3390
#define REG_OUT_3V_I_MIN	0
#define REG_OUT_3V_I_MAX	5000

/*v_bat raw battery*/
#define V_BAT_V_MIN			6000
#define V_BAT_V_MAX			8400
#define V_BAT_I_OUT_TYP		12000

/*power cosumption mW*/
#define POWER_CONSUMPTION_TYP	115

/*Current consumed with separation switch OFF uA - micro???*/
#define SEPARATION_SWITCH_OFF_I_TYP	35
#define SEPARATION_SWITCH_OFF_I_MAX	60

#define SHELF_LIFE_MIN	700
#define SHELF_LIFE_TYP	1400


/*batteries*/
#define EOCV	4150 //end of charge voltage
#define DOD 	20 // Depth-Of-Discharge % -OURS


/*OURS defualt values*/
#define DEFAULT_TEMP	1


/*CMD*/
#define RESTORE_DEFAULT_CONFIG	1


/*WDT*/
/*I2C reset mode*/
#define I2C_WDT_RESET_0		0
#define I2C_WDT_RESET_1		1

#define WDT_I2C_INIT_TIME	10 //sec
#define WDT_GND_INIT_TIME	480 //sec - should be configurable to  48 hours in the real system
#define WDT_GND_HOUR		10 //sec - should be 1 hour
#define WDT_CSP_INIT_PING	5 //num of pings
/**
* Structs of p31u_eps.
*/
typedef struct battery_struct
{
	uint8_t onboard_external; //whether the battery is onboard or external
	uint16_t vbat;
	uint16_t current_in;
	uint16_t current_out;
	int16_t temp;
	enum batt_state state;
};

typedef struct channel_struct
{
	uint8_t status;
	enum channel_type type;
	uint16_t volt;
	uint16_t latchup;
};

typedef struct boost_convertor_struct
{
	int16_t temp;
	uint16_t volt;
	uint16_t current_in;
};

typedef struct battery_heater
{
	uint8_t mode; //0 = Manual, 1 = Auto]
	uint8_t type; //0 = BP4, 1= Onboard
	uint8_t status; //0 = OFF 1 = ON
	int8_t battheater_low;   //! Turn heater on at [degC]
	int8_t battheater_high;  //! Turn heater off at [degC]
};

typedef struct wdt
{
	enum wdt_type type;
	uint32_t reboot_counter;
	uint32_t time_ping_left;
	uint32_t data; //I2C- type of reset, GND- last hour, CSP- channel connected
};

typedef struct p31u_eps
{
	struct channel_struct channels[8];
	struct boost_convertor_struct boost_convertors[3];
	struct battery_struct onboard_battery;
	struct battery_heater battery_heaters[2];
	uint16_t photo_current; //Total photo current [mA]
	uint16_t system_current; //Total system current [mA]
	uint16_t reboot_count; //Number of EPS reboots
	uint16_t sw_errors; //Number of errors in the eps software
	uint8_t last_reset_cause; //Cause of last EPS reset
	struct wdt wdts[4];
	eps_config_t config;
	eps_config2_t config2;
	uint16_t curout[6]; //! Current out (switchable outputs) [mA]
	uint8_t kill_switch; //ON or OFF
	uint8_t charging; //ON or OFF

}; //!< Struct with individual fields of GOM EPS telemetry. HK version 1.


#endif /* SRC_SIMULATOREPSFORMAT_H_ */
