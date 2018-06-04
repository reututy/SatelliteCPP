#include "stdafx.h"
#include "FRAM.h"
#include "Communication.h"

#define FRAM_starttoSendLength 12

/*!
* Initializes the FRAM driver and the SPI driver if its not already initialized.
* @return -2 if initializing the SPI driver fails,
* -1 If creating semaphores to control access to the FRAM fails.
* 0 on success.
*/
int FRAM_start(void){
	char * funcName = "FRAM_start&";
	int funcNameLength = strlen(funcName);
	char toSend[FRAM_starttoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	char* ans = get_data(toSend, FRAM_starttoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define FRAM_writetoSendLength 300
/*!
* Writes data to the FRAM.
* @param data Address where data to be written is stored.
* @param address Location in the FRAM where data should be written.
* @param size Number of bytes to write.
* @return -2 if the specified address and size are out of range,
* -1 if obtaining lock for FRAM access fails,
* 0 on success.
*/
int FRAM_write(unsigned char *data, unsigned int address, unsigned int size){
	char snum[5];
	itoa(address, snum, 10);
	char * funcName = "FRAM_write&";
	int funcNameLength = strlen(funcName);
	char toSend[FRAM_writetoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, data, size); //data
	toSend[funcNameLength + size] = '&';
	memcpy(toSend + funcNameLength + size + sizeof(char), &snum, 5); //address
	toSend[funcNameLength + size + sizeof(char) + sizeof(unsigned int)] = '&';
	memcpy(toSend + funcNameLength + size + sizeof(char) + sizeof(unsigned int) + sizeof(char), &size, sizeof(unsigned int)); //size
	toSend[funcNameLength + size + sizeof(char) + sizeof(unsigned int) + sizeof(char) + sizeof(unsigned int)] = '&'; //determine end of message
	char* ans = get_data(toSend, FRAM_writetoSendLength);
	int errorToReturn = -((int*)ans)[0];
	free(ans);
	return errorToReturn;
}

#define FRAM_readtoSendLength 40
/*!
* Reads data from the FRAM.
* @param data Address where read data will be stored, this location must be able to accommodate size bytes.
* @param address Location in the FRAM from which the data should be read.
* @param size Number of bytes to read.
* @return -2 if the specified address and size are out of range of the FRAM space.
* -1 if obtaining lock for FRAM access fails,
* 0 on success.
*/
int FRAM_read(unsigned char *data, unsigned int address, unsigned int size){
	char snum[5];
	itoa(address, snum, 10);
	char * funcName = "FRAM_read&";
	int funcNameLength = strlen(funcName);
	char toSend[FRAM_readtoSendLength];
	memcpy(toSend, funcName, funcNameLength); //function name
	memcpy(toSend + funcNameLength, &snum, 5); //address
	toSend[funcNameLength + sizeof(unsigned int)] = '&';
	memcpy(toSend + funcNameLength + sizeof(unsigned int) + sizeof(char), &size, sizeof(unsigned int)); //size
	toSend[funcNameLength + sizeof(unsigned int) + sizeof(char) + sizeof(unsigned int)] = '&'; //determine end of message
	char* ans = get_data(toSend, FRAM_readtoSendLength);
	int errorToReturn = -((int*)ans)[0];
	memcpy(data, ans + 4, size);
	free(ans);
	return errorToReturn;
}
