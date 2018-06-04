/*!
* @file	FRAM.h
* @brief	Driver for reading and writing data from/to the FRAM.
* @note	Please don't call any of those functions from an interrupt context
*/

#ifndef FRAM_H_
#define FRAM_H_

#define FRAM_MAX_ADDRESS	0x0003FFFF //!< Highest memory address available in FRAM memory

/*!
* Used by the FRAM_protectBlocks function to protect certain blocks of the FRAM from write operations.
* blockProtect Values: 0 = None,
* 						1 = upper 1/4 protected (0x30000 to 0x3FFFF),
* 						2 = upper 1/2 protected (0x20000 to 0x3FFFF),
* 						3 = Entire FRAM protected (0x00000 to 0x3FFFF)
*/
typedef union _FRAMblockProtect{
	unsigned char rawValue;
	struct {
		unsigned char	reserved1 : 2,
		blockProtect : 2,
				   reserved2 : 4;
	} fields;
} FRAMblockProtect;

/*!
* Initializes the FRAM driver and the SPI driver if its not already initialized.
* @return -2 if initializing the SPI driver fails,
* -1 If creating semaphores to control access to the FRAM fails.
* 0 on success.
*/
int FRAM_start(void);

/*!
* Writes data to the FRAM.
* @param data Address where data to be written is stored.
* @param address Location in the FRAM where data should be written.
* @param size Number of bytes to write.
* @return -2 if the specified address and size are out of range,
* -1 if obtaining lock for FRAM access fails,
* 0 on success.
*/
int FRAM_write(unsigned char *data, unsigned int address, unsigned int size);

/*!
* Reads data from the FRAM.
* @param data Address where read data will be stored, this location must be able to accommodate size bytes.
* @param address Location in the FRAM from which the data should be read.
* @param size Number of bytes to read.
* @return -2 if the specified address and size are out of range of the FRAM space.
* -1 if obtaining lock for FRAM access fails,
* 0 on success.
*/
int FRAM_read(unsigned char *data, unsigned int address, unsigned int size);

#endif /* FRAM_H_ */
