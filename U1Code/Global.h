#ifndef __GLOBAL__
#define __GLOBAL__

#include "GomEPS.h"
//#include "main.h"

typedef unsigned int  Boolean;
typedef unsigned char Boolean8bit;

#define TRUE		0xFFFFFFFF
#define FALSE		0

#define TRUE_8BIT	0xFF
#define FALSE_8BIT	0

#define STATE_MUTE 0x01
#define STATE_GS 0x02
#define STATE_MNLP_ON 0x04
#define STATE_MUTE_EPS 0x08
#define STATE_MNLP_ON_EPS 0x10
#define STATE_ADCS_ON_EPS 0x20
#define STATE_MNLP_ON_GROUND 0x40

// times
#define BEACON_TIME 20
#define SAVE_TELEMETRY_TIME 60
#define MAIN_ITERATION_TIME 1000
#define RESET_TIMEOUT 43200   	//second until reset
#define DEPLOY_TIME	  2700		// seconds until deployment
//#define DEPLOY_TIME	  10		// seconds until deployment
#define BOOM_DEPLOY_TIME 4     //CHANGE THIS TO 5 BEFORE LAUNCH!!
#define REDEPLOY_TIME	  2700		// seconds until deployment
//#define REDEPLOY_TIME 120
#define AUTO_DEPLOYMENT_TIME 10


// FRAM addresses
#define EPS_VOLTAGE_ADDR 0x1000
#define EPS_VOLTAGE_SIZE 6
#define TC_COUNT_ADDR 0x100A     // one byte
#define FRAME_COUNT_ADDR 0x100B // one byte
#define SSC_ADDR 0X100C 		// 17*4
#define FIRST_ACTIVATION_ADDR 0x10A0 // 4 bytes
#define STATES_ADDR    0x10B0	// one byte
#define TIME_ADDR 0x10BB
#define TIME_SIZE 5
#define ADCS_STAGE_ADDR 0x10D0
#define ADCS_STAGE_SIZE 4
#define ARM_DEPLOY_ADDR 0x10E0
#define ARM_SECOND_DEPLOY_ADDR 0x10F0


#define FIRST_ACTIVATION_SIZE 4

#define GS_TIME 420
#define THREAD_TIMEOUT 60
#define THREAD_LISTENER_TIMEOUT 500


#define MAIN_THREAD 0//0=main 1=mnlp 2=mnlplistener 3=adcs 4=reset
#define MNLP_THREAD 1
#define MNLPLISTENER_THREAD 2
#define ADCS_THREAD 3
#define RESET_THREAD 4

#define UNIX_EPOCH_TIME_DIFF (30*365*24*3600+7*24*3600)

extern unsigned char states;
extern gom_eps_channelstates_t glb_channels_state;

typedef struct global_param{
	Boolean Mnlp_State;
	unsigned char vbatt;
	unsigned char cursys;
	unsigned char curout3V3;
	unsigned char curout5V;
	unsigned char tempCOMM;
	unsigned char tempEPS;
	unsigned char tempBatt;
} global_param;

extern global_param glb;
extern int not_first_activation;

void Set_Mute(Boolean bool);// 0 is mute off ,1 is mute on 2 is mute_eps on 3 is both mutes on
void Set_Mnlp_State(Boolean state);
void Set_Vbatt(unsigned short Vbatt);
void Set_Cursys(unsigned short cursys);
void Set_Curout3V3(unsigned short curout);
void Set_Curout5V(unsigned short curout);
void Set_tempCOMM(short temp);
void Set_tempEPS(short temp);
void Set_tempBatt(short temp);
unsigned long convert_epoctime(unsigned char packet[]);
void convert_time_array(unsigned long t_l, unsigned char time[5]);
void print_array(unsigned char *arr, int length);
void switch_endian(unsigned char *in, int len);
void double_little_endian(unsigned char* d);
void zero_initial_activation();
void reset_subsystems(unsigned int reset_idx, gom_eps_channelstates_t channels_state);
Boolean Get_Mute();

void deploy_ants(gom_eps_channelstates_t channels_state);
void redeploy_ants(gom_eps_channelstates_t channels_state);

double Min(double a, double b);
double Max(double a, double b);
#endif
