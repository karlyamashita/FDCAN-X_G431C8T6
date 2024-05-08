/*
 * FDCAN_Buffer_STM32.h
 *
 *  Created on: Oct 7, 2023
 *      Author: karl.yamashita
 */

#ifndef INC_FDCAN_BUFFER_STM32_H_
#define INC_FDCAN_BUFFER_STM32_H_


#define FDCAN_RX_BUF_SIZE 8
#define FDCAN_TX_BUF_SIZE 4


typedef struct
{
	FDCAN_RxHeaderTypeDef *pRxHeader;
	uint8_t data[64];
}FDCAN_Rx;

typedef struct
{
	FDCAN_TxHeaderTypeDef pTxHeader;
	uint8_t data[64];
}FDCAN_Tx;


typedef struct
{
	FDCAN_HandleTypeDef *fdcan;
	struct
	{
		FDCAN_Rx queue[FDCAN_RX_BUF_SIZE];
		uint32_t queueSize;
		FDCAN_Rx *msgToParse;
		RING_BUFF_STRUCT ptr;
	}rx;
	struct
	{
		FDCAN_Tx queue[FDCAN_TX_BUF_SIZE];
		uint32_t queueSize;
		RING_BUFF_STRUCT ptr;
	}tx;
}FDCAN_Buffer;

int FDCAN_MsgReady(FDCAN_Buffer *msg);
void FDCAN_AddToRxBuffer(FDCAN_Buffer *msg, FDCAN_Rx *rxData);

void FDCAN_AddDataToTxBuffer(FDCAN_Buffer *msg, FDCAN_Tx *data);
void FDCAN_Transmit(FDCAN_Buffer *msg);


#endif /* INC_FDCAN_BUFFER_STM32_H_ */
