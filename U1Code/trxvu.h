/*
* trxvu.h
*
*  Created on: 10 ???? 2016
*      Author: Ariel
*/

#ifndef TRXVU_H_
#define TRXVU_H_

#include "IsisTRXVU.h"
#include <stdlib.h>
#include "main.h"
#include "EPS.h"
#define TX_UPBOUND				30
#define TIMEOUT_UPBOUND			10

#define SIZE_RXFRAME	200 // should be 63 but char doesn't go alone
#define SIZE_TXFRAME	235

#define SCRIPT_RAW_ADDR 0x10000
#define BLOCK_SIZE 60

#define ADC_COMM_SIZE 84//TBD
#define ADC_SID 201

#define BACON_TIME 20

typedef struct isisTXtlm
{
	float tx_reflpwr; ///< Tx Telemetry reflected power.
	float pa_temp; ///< Tx Telemetry power amplifier temperature.
	float tx_fwrdpwr; ///< Tx Telemetry forward power.
	float tx_current; ///< Tx Telemetry transmitter current.
} isisTXtlm;
typedef struct isisRXtlm {
	float tx_current; ///< Rx Telemetry transmitter current.
	float rx_doppler; ///< Rx Telemetry receiver doppler.
	float rx_current; ///< Rx Telemetry receiver current.
	float bus_volt; ///< Rx Telemetry bus voltage.
	float board_temp; ///< Rx Telemetry board temperature.
	float pa_temp; ///< Rx Telemetry power amplifier temperature.
	float rx_rssi; ///< Rx Telemetry rssi measurement.
} isisRXtlm;




int availableFrames;

void update_wod(gom_eps_hk_t EpsTelemetry_hk);
void vurc_getRxTelemTest(isisRXtlm *converted);
void vurc_getTxTelemTest(isisTXtlm *converted);
void init_trxvu(void);
int TRX_sendFrame(unsigned char* data, unsigned char length);
void act_upon_comm(unsigned char* in, gom_eps_channelstates_t channels_state);
void end_gs_mode();

extern unsigned char dumpparam[11];
#endif /* TRXVU_H_ */
