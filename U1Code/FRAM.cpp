#include "stdafx.h"
# include "FRAM.h"

int FRAM_start(){
	return 0;
}

void FRAM_stop(){
	return;
}

int FRAM_write(unsigned char *data, unsigned int address, unsigned int size){
	return 0;
}

int FRAM_read(unsigned char *data, unsigned int address, unsigned int size){
	return 0;
}


int FRAM_writeAndVerify(unsigned char *data, unsigned int address, unsigned int size){
	return 0;
}

int FRAM_protectBlocks(FRAMblockProtect blocks){
	return 0;
}

int FRAM_getDeviceID(unsigned char *deviceID){
	return 0;
}
