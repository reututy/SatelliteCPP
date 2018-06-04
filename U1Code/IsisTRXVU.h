/**
* @file IsisTRXVU.h
* @brief ISIS VHF up / UHF down transceiver
* @note based on TRXVU Manual 1.1
*/

#ifndef ISISTRXVU_H_
#define ISISTRXVU_H_

#define TRXVU_UPTIME_SIZE				4  ///< Size for the up time buffer.
#define TRXVU_ALL_RXTELEMETRY_SIZE		14  ///< Size of the buffer for the complete telemetry read out from the receiver component.
#define TRXVU_ALL_TXTELEMETRY_SIZE		8  ///< Size of the buffer for the complete telemetry read out from the transmitter component.

/**
* Enumeration list of the Idle states of the TRXVU.
*/
typedef enum _ISIStrxvuIdleState
{
	trxvu_idle_state_off = 0x00,
	trxvu_idle_state_on = 0x01
} ISIStrxvuIdleState;

/**
* Enumeration list of bitrate options for setting the bitrate in the TRXVU.
*/
typedef enum _ISIStrxvuBitrate
{
	trxvu_bitrate_1200 = 0x01, ///< Transmission Bitrate 1200 bps.
	trxvu_bitrate_2400 = 0x02, ///< Transmission Bitrate 2400 bps.
	trxvu_bitrate_4800 = 0x04, ///< Transmission Bitrate 4800 bps.
	trxvu_bitrate_9600 = 0x08 ///< Transmission Bitrate 9600 bps.
} ISIStrxvuBitrate;

/**
* Enumeration list of bitrate options of the TRXVU when reporting the status
*/
typedef enum _ISIStrxvuBitrateStatus
{
	trxvu_bitratestatus_1200 = 0x00, ///< Transmission Bitrate 1200 bps.
	trxvu_bitratestatus_2400 = 0x01, ///< Transmission Bitrate 2400 bps.
	trxvu_bitratestatus_4800 = 0x02, ///< Transmission Bitrate 4800 bps.
	trxvu_bitratestatus_9600 = 0x03 ///< Transmission Bitrate 9600 bps.
} ISIStrxvuBitrateStatus;

/**
* Enumeration list of TRXVU Components.
*/
typedef enum _ISIStrxvuComponent
{
	trxvu_rc = 0x00, ///< TRXVU receiver component.
	trxvu_tc = 0x01 ///< TRXVU transmitter component.
} ISIStrxvuComponent;

/**
* Enumeration list of TRXVU beacon status.
*/
typedef enum _ISIStrxvuBeacon
{
	trxvu_beacon_none = 0x00,
	trxvu_beacon_active = 0x01
} ISIStrxvuBeacon;

/**
*  Struct for defining ISIS TRXVU I2C Address.
*/
typedef struct _ISIStrxvuI2CAddress
{
	unsigned char addressVu_rc; ///< I2C address of the VU_RC.
	unsigned char addressVu_tc; ///< I2C address of the VU_TC.
} ISIStrxvuI2CAddress;

/**
*  Struct for defining ISIS TRXVU buffers length.
*/
typedef struct _ISIStrxvuFrameLengths
{
	unsigned int maxAX25frameLengthTX; ///< AX25 maximum frame size for transmission.
	unsigned int maxAX25frameLengthRX; ///< AX25 maximum frame size for reception.
} ISIStrxvuFrameLengths;

/**
*  Struct for the TRXVU reception frame.
*/
typedef struct _ISIStrxvuRxFrame
{
	unsigned short rx_length; ///< Reception frame length.
	unsigned short rx_doppler; ///< Reception frame doppler measurement.
	unsigned short rx_rssi; ///< Reception frame rssi measurement.
	unsigned char* rx_framedata; ///< Reception frame data.
} ISIStrxvuRxFrame;

/**
*  Struct for the TRXVU Rx telemetry.
*/
typedef union _ISIStrxvuRxTelemetry
{
	/** Raw value array with Rx Telemetry data*/
	unsigned char raw[TRXVU_ALL_RXTELEMETRY_SIZE];
	/** Telemetry values*/
	struct
	{
		unsigned short tx_current; ///< Rx Telemetry transmitter current.
		unsigned short rx_doppler; ///< Rx Telemetry receiver doppler.
		unsigned short rx_current; ///< Rx Telemetry receiver current.
		unsigned short bus_volt; ///< Rx Telemetry bus voltage.
		unsigned short board_temp; ///< Rx Telemetry board temperature.
		unsigned short pa_temp; ///< Rx Telemetry power amplifier temperature.
		unsigned short rx_rssi; ///< Rx Telemetry rssi measurement.
	} fields;
} ISIStrxvuRxTelemetry;

/**
*  Struct for the TRXVU Tx telemetry.
*/
typedef union _ISIStrxvuTxTelemetry
{
	/** Raw value array with Tx Telemetry data*/
	unsigned char raw[TRXVU_ALL_TXTELEMETRY_SIZE];
	/** Telemetry values*/
	struct
	{
		unsigned short tx_reflpwr; ///< Tx Telemetry reflected power.
		unsigned short pa_temp; ///< Tx Telemetry power amplifier temperature.
		unsigned short tx_fwrdpwr; ///< Tx Telemetry forward power.
		unsigned short tx_current; ///< Tx Telemetry transmitter current.
	} fields;
} ISIStrxvuTxTelemetry;

/**
*  Struct for the TRXVU current buffer status.
*/
typedef union _ISIStrxvuTransmitterState
{
	/** Raw value that contains the current transmitter state*/
	unsigned char raw;
	struct
	{
		ISIStrxvuIdleState transmitter_idle_state : 1; ///< Transmitter current idle state.
		ISIStrxvuBeacon transmitter_beacon : 1; ///< Transmitter beacon mode status.
		ISIStrxvuBitrateStatus transmitter_bitrate : 2; ///< Transmitter current bitrate.
	}fields;
} ISIStrxvuTransmitterState;

/**
*  @brief      Initialize the ISIS TRXVU with the corresponding i2cAddress from the array of TRXVU I2C Address structure.
*  @note       This function can only be called once.
*  @param[in]  address array of TRXVU I2C Address structure.
*  @param[in]  maxFrameLengths array of maximum frame length structures for TRXVU.
*  @param[in]	default_bitrates initial default bitrate.
*  @param[in]  number number of attached TRXVU in the system to be initialized.
*  @return     Error code according to <hal/errors.h>
*/
int IsisTrxvu_initialize(ISIStrxvuI2CAddress *address, ISIStrxvuFrameLengths *maxFrameLengths, ISIStrxvuBitrate* default_bitrates, unsigned char number);

/**
*  @brief       Soft Reset the ISIS TRXVU Component.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   component TRXVU component, either VU_TC or VU_RC.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_componentSoftReset(unsigned char index, ISIStrxvuComponent component);

/**
*  @brief       Hard Reset the ISIS TRXVU Component.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   component TRXVU component, either VU_TC or VU_RC.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_componentHardReset(unsigned char index, ISIStrxvuComponent component);

/**
*  @brief       Soft Reset the ISIS TRXVU VU_RC and VU_TC.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_softReset(unsigned char index);

/**
*  @brief       Hard Reset the ISIS TRXVU VU_RC and VU_TC.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_hardReset(unsigned char index);

/**
*  @brief       Tell the TRXVU to transmit an AX.25 message with default callsigns and specified content.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
*  @param[in]   length Length of the data to be put in the AX.25 message.
*  @param[out]  avail Number of the available slots in the transmission buffer of the VU_TC after the frame has been added.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSendAX25DefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned char *avail);

/**
*  @brief       Tell the TRXVU to transmit an AX.25 message with override callsigns and specified content.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]	 fromCallsign This variable will define the new 7 characters from callsign.
*  @param[in]	 toCallsign This variable will define the new 7 characters to callsign.
*  @param[in]   data Pointer to the array containing the data to put in the AX.25 message.
*  @param[in]   length Length of the data to be put in the AX.25 message.
*  @param[out]  avail Number of the available slots in the transmission buffer of the VU_TC after the frame has been added.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSendAX25OvrClSign(unsigned char index, unsigned char *fromCallsign, unsigned char *toCallsign, unsigned char *data, unsigned char length, unsigned char *avail);

/**
*  @brief       Tell the TRXVU to set the parameters for the AX25 Beacon with default callsigns.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   data Pointer to the array containing the message to be transmitted.
*  @param[in]   length Length of the message.
*  @param[in]   interval Interval of beacon transmission.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25BeaconDefClSign(unsigned char index, unsigned char *data, unsigned char length, unsigned short interval);

/**
*  @brief       Tell the TRXVU to set the parameters for the AX25 Beacon with override callsigns.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]	 fromCallsign This variable will define the new 7 characters from callsign.
*  @param[in]	 toCallsign This variable will define the new 7 characters to callsign.
*  @param[in]   data Pointer to the array containing the message to be transmitted.
*  @param[in]   length Length of the message.
*  @param[in]   interval Interval of beacon transmission.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25BeaconOvrClSign(unsigned char index, unsigned char *fromCallsign, unsigned char *toCallsign, unsigned char *data, unsigned char length, unsigned short interval);

/**
*  @brief       Tell the TRXVU to clear the current beacon.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcClearBeacon(unsigned char index);

/**
*  @brief       Tell the TRXVU to set a new default to callsign name.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   toCallsign This variable will define the new 7 characters default to callsign.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetDefToClSign(unsigned char index, unsigned char *toCallsign);

/**
*  @brief       Tell the TRXVU to set a new default from callsign name.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   fromCallsign This variable will define the new 7 characters default from callsign.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetDefFromClSign(unsigned char index, unsigned char *fromCallsign);

/**
*  @brief       Set the idle state of the TRXVU transmitter, i.e. the state in between transmission.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   state The desired idle state of the TRXVU.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetIdlestate(unsigned char index, ISIStrxvuIdleState state);

/**
*  @brief       Set the AX.25 bitrate of the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   bitrate The desired AX.25 bitrate of the TRXVU.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcSetAx25Bitrate(unsigned char index, ISIStrxvuBitrate bitrate);

/**
*  @brief       Retrieve the current time of operation of the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  uptime This array of 4 characters contains the operation time of the transmitter (Seconds, Minutes, Hours and Days, in that order).
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetUptime(unsigned char index, unsigned char *uptime);

/**
*  @brief       Retrieve the current transmitter status.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  currentvutcState Pointer to the union where the current status should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetState(unsigned char index, ISIStrxvuTransmitterState *currentvutcState);

/**
*  @brief       Retrieve a block of telemetry from the TRXVU transmitter.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetTelemetryAll(unsigned char index, ISIStrxvuTxTelemetry *telemetry);

/**
*  @brief       Retrieve a block of telemetry from the TRXVU transmitter sotre on the last transmission.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  last_telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_tcGetLastTxTelemetry(unsigned char index, ISIStrxvuTxTelemetry *last_telemetry);

/**
*  @brief       Calculates the approximate time it will take for a certain transmission to complete.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[in]   length The length of the transmission in bytes.
*  @return      The time estimate in milliseconds.
*/
unsigned short IsisTrxvu_tcEstimateTransmissionTime(unsigned char index, unsigned char length);

/**
*  @brief       Retrieve the number of telecommand frames present in the receive buffer of the TRXVU.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  frameCount The number of telecommand frames in the buffer.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetFrameCount(unsigned char index, unsigned short *frameCount);

/**
*  @brief       Retrieve and delete a telecommand frame from the TRXVU.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  rx_frame Pointer to the struct where the telecommand frame should be store.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetCommandFrame(unsigned char index, ISIStrxvuRxFrame *rx_frame);

/**
*  @brief       Retrieve a block of telemetry from the TRXVU receiver.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  telemetry Pointer to the union where the telemetry should be stored.
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetTelemetryAll(unsigned char index, ISIStrxvuRxTelemetry *telemetry);

/**
*  @brief       Retrieve the current time of operation of the TRXVU receiver.
*  @param[in]   index index of ISIS TRXVU I2C bus address.
*  @param[out]  uptime This array of 3 characters contains the operation time of the receiver (Minutes, Hours and Days, in that order)..
*  @return      Error code according to <hal/errors.h>
*/
int IsisTrxvu_rcGetUptime(unsigned char index, unsigned char *uptime);

#endif /* ISISTRXVU_H_ */
