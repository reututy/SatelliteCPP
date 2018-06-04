#include "stdafx.h"
#include "Global.h"
#include "main.h"

global_param glb;
unsigned char states;
gom_eps_channelstates_t glb_channels_state;
int not_first_activation;


double Min(double a, double b)
{
	if (b>a) return a;
	return b;
}

double Max(double a, double b)
{
	if (a>b) return a;
	return b;
}



void Set_Mute(Boolean bool)
{
	if (bool == TRUE)
	{
		states = states | STATE_MUTE;
	}
	else
	{
		states &= ~STATE_MUTE;
	}
	FRAM_write(&states, STATES_ADDR, 1);
}
void Set_Mnlp_State(Boolean state)
{
	glb.Mnlp_State = state;
}

void Set_Vbatt(unsigned short Vbatt)//in mV
{
	glb.vbatt = (unsigned char)Max(0, Min(255, ((double)20 * Vbatt) / 1000 - 60));
}

void Set_Cursys(unsigned short cursys)//in mA
{
	glb.cursys = (unsigned char)Max(0, Min(255, ((double)127 * cursys) / 1000 + 127));
}

void Set_Curout3V3(unsigned short curout)//in mA
{
	glb.curout3V3 = (unsigned char)Max(0, Min(255, (double)40 * curout / 1000));
}

void Set_Curout5V(unsigned short curout)//in mA
{
	glb.curout5V = (unsigned char)Max(0, Min(255, (double)40 * curout / 1000));
}

void Set_tempCOMM(short temp)
{
	glb.tempCOMM = (unsigned char)Max(0, Min(255, (double)4 * temp + 60));
}

void Set_tempEPS(short temp)
{
	glb.tempEPS = (unsigned char)Max(0, Min(255, (double)4 * temp + 60));
}

void Set_tempBatt(short temp)
{
	glb.tempBatt = (unsigned char)Max(0, Min(255, (double)4 * temp + 60));
}


Boolean Get_Mute()
{
	if ((states & STATE_MUTE) || (states& STATE_MUTE_EPS))
	{
		return TRUE;
	}
	return FALSE;
}

unsigned long convert_epoctime(unsigned char packet[])
{
	//get the epoctime signature from the packet sent
	unsigned long tl = 0;
	tl += packet[0] << 24;
	tl += packet[1] << 16;
	tl += packet[2] << 8;
	tl += packet[3];
	//printf("final answer is %lu\n",tl);
	return tl;
}

void convert_time_array(unsigned long t_l, unsigned char time[5])
{
	time[0] = t_l >> 24;
	time[1] = t_l >> 16;
	time[2] = t_l >> 8;
	time[3] = t_l;
	time[4] = 0;
}

void print_array(unsigned char *arr, int length)
{
	int i;
	for (i = 0; i<length; i++)
	{
		printf("%x ", arr[i]);
	}
	printf("END\n");
}


void switch_endian(unsigned char *in, int len)
{
	int temp;
	int i = 0;
	for (; i<len; i += 2)
	{
		temp = in[i];
		//in[i] = in[len - 1 - i];
		//in[len - 1 - i] = temp;
		in[i] = in[i + 1];
		in[i + 1] = temp;
	}
}

void double_little_endian(unsigned char* d)
{
	int i = 0;
	char temp;
	for (i = 0; i<4; i++)
	{
		temp = d[i];
		d[i] = d[7 - i];
		d[7 - i] = temp;
	}
}
