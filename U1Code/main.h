/*
* maininclude.h
*
*  Created on: 21 באפר 2016
*      Author: USER1
*/

#ifndef MAININCLUDE_H_
#define MAININCLUDE_H_

#include <string.h>
#include <stdio.h>
//

#include "EPS.h"
#include "GomEPS.h"
#include "trxvu.h"
#include "Global.h"
#include "FRAM.h"
#include "IsisTRXVU.h"

// define FRAM addresses

#define THREAD_TIMESTAMP_LEN 5
extern unsigned char frame_count;
extern unsigned char tc_count;
extern unsigned long timestamp[THREAD_TIMESTAMP_LEN];//0=main 1=mnlp 2=mnlplistener 3=adcs 4=reset
extern gom_eps_channelstates_t channels_state;

#endif /* MAININCLUDE_H_ */
