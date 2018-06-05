#include "stdafx.h"
#include "main.h"
#include "IsisTRXVU.h"

unsigned char states;


void EPS_Power_Conditioning(gom_eps_hk_t* EPS_Cur_TLM, unsigned short* Vbatt_Previous, gom_eps_channelstates_t* channels_state)
{
	unsigned char voltages[EPS_VOLTAGE_SIZE];
	FRAM_read(voltages, EPS_VOLTAGE_ADDR, EPS_VOLTAGE_SIZE);
	if (EPS_Cur_TLM->fields.vbatt < *Vbatt_Previous) // in case of battery discharge
	{
		if (EPS_Cur_TLM->fields.vbatt < (int)voltages[0] * 100 && channels_state->fields.channel3V3_1 == 1)
		{
			Safe(channels_state);
			states &= ~STATE_ADCS_ON_EPS;
			GomEpsSetOutput(0, *channels_state); // Shuts down the ADCS actuators as well
		}
		else if (EPS_Cur_TLM->fields.vbatt < (int)voltages[1] * 100)
		{
			Cruse(channels_state);
			states |= STATE_MUTE_EPS;
			GomEpsSetOutput(0, *channels_state); // Shuts down the transmitter as well

		}
		else if (EPS_Cur_TLM->fields.vbatt < (int)voltages[2] * 100)
		{
			Cruse(channels_state);
			states &= ~STATE_MNLP_ON_EPS;
			GomEpsSetOutput(0, *channels_state); // Shuts down the payload
		}
	}
	else if (EPS_Cur_TLM->fields.vbatt > *Vbatt_Previous)
	{
		if (EPS_Cur_TLM->fields.vbatt > (int)voltages[3] * 100)
		{
			Cruse(channels_state);
			states |= STATE_MNLP_ON_EPS;
			GomEpsSetOutput(0, *channels_state); // Activates the payload as well
		}
		else if (EPS_Cur_TLM->fields.vbatt > (int)voltages[4] * 100)
		{
			Cruse(channels_state);
			states &= ~STATE_MUTE_EPS;
			GomEpsSetOutput(0, *channels_state); // Activates the tranciever as well
		}
		else if (EPS_Cur_TLM->fields.vbatt > (int)voltages[5] * 100 && channels_state->fields.channel3V3_1 == 0)
		{
			Cruse(channels_state);
			states |= STATE_ADCS_ON_EPS;
			GomEpsSetOutput(0, *channels_state); // Activates the ADCS actuators
		}
	}
	*Vbatt_Previous = EPS_Cur_TLM->fields.vbatt;
	FRAM_write(&states, STATES_ADDR, 1);
}



void EPS_Init(gom_eps_hk_t* EPS_Cur_TLM, gom_eps_channelstates_t *channels_state, unsigned short* vbatt_previous)
{
	unsigned char EPS_addr = EPS_address;
	GomEpsGetHkData_general(0, EPS_Cur_TLM);
	unsigned char voltages[EPS_VOLTAGE_SIZE];
	FRAM_read(voltages, EPS_VOLTAGE_ADDR, EPS_VOLTAGE_SIZE);

	if (EPS_Cur_TLM->fields.vbatt < voltages[0] * 100)
	{
		Safe(channels_state);
		GomEpsSetOutput(0, *channels_state); // Shuts down the ADCS actuators as well
		states &= ~(STATE_ADCS_ON_EPS + STATE_MNLP_ON_EPS);
		states |= STATE_MUTE_EPS;
	}
	else if (EPS_Cur_TLM->fields.vbatt < voltages[1] * 100)
	{
		printf("ADCS ON\n");
		Cruse(channels_state);
		GomEpsSetOutput(0, *channels_state); // Shuts down the transmitter as well
		states &= ~(STATE_MNLP_ON_EPS);
		states |= STATE_ADCS_ON_EPS + STATE_MUTE_EPS;
	}
	else if (EPS_Cur_TLM->fields.vbatt < voltages[2] * 100)
	{
		printf("ADCS ON\n");
		Cruse(channels_state);
		GomEpsSetOutput(0, *channels_state); // Shuts down the payload
		states &= ~STATE_MNLP_ON_EPS;
		states |= STATE_ADCS_ON_EPS;
		states &= ~STATE_MUTE_EPS;
	}
	else
	{
		printf("ADCS ON\n");
		Cruse(channels_state);
		GomEpsSetOutput(0, *channels_state); // everything is on
		states |= STATE_ADCS_ON_EPS + STATE_MNLP_ON_EPS;
		states &= ~STATE_MUTE_EPS;
	}

	*vbatt_previous = EPS_Cur_TLM->fields.vbatt;
	FRAM_write(&states, STATES_ADDR, 1);
}

void print_config(eps_config_t config_data)
{
	printf(" battery low is %d and high is %d\n", (int)config_data.fields.battheater_low, (int)config_data.fields.battheater_high);
	printf(" heater mode %d\n", (int)config_data.fields.battheater_mode);
	printf("vboost PPT %d,%d,%d\n ", config_data.fields.vboost[0], config_data.fields.vboost[1], config_data.fields.vboost[2]);
}

void set_heater_values(char heater_params[2])
{
	eps_config_t config_data;
	GomEpsConfigGet(0, &config_data);
	print_array((unsigned char *)heater_params, 2);
	printf("before:\n");
	print_config(config_data);
	config_data.fields.battheater_low = heater_params[0];
	config_data.fields.battheater_high = heater_params[1];
	GomEpsConfigSet(0, &config_data);

	GomEpsConfigGet(0, &config_data);
	printf("after:\n");
	print_config(config_data);
}

void Cruse(gom_eps_channelstates_t* channels_state)
{
	channels_state->fields.quadbatSwitch = 0;
	channels_state->fields.quadbatHeater = 0;
	channels_state->fields.channel3V3_1 = 1;
	channels_state->fields.channel3V3_2 = 0;
	channels_state->fields.channel3V3_3 = 0;
	channels_state->fields.channel5V_1 = 1;
	channels_state->fields.channel5V_2 = 0;
	channels_state->fields.channel5V_3 = 0;
}

void Safe(gom_eps_channelstates_t* channels_state)
{
	channels_state->fields.quadbatSwitch = 0;
	channels_state->fields.quadbatHeater = 0;
	channels_state->fields.channel3V3_1 = 0;
	channels_state->fields.channel3V3_2 = 0;
	channels_state->fields.channel3V3_3 = 0;
	channels_state->fields.channel5V_1 = 0;
	channels_state->fields.channel5V_2 = 0;
	channels_state->fields.channel5V_3 = 0;
}
