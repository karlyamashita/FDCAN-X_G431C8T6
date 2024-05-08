/*
 * FDCAN_BuFfer_STM32.c
 *
 *  Created on: Oct 7, 2023
 *      Author: karl.yamashita
 */

#include "main.h"



/*
 * Description: Check for new message and point msgToParse to buffer index to be parsed
 * return: True if message ready, else return false
 *
 */
int FDCAN_MsgReady(FDCAN_Buffer *msg)
{
	if(msg->rx.ptr.cnt_Handle)
	{
		msg->rx.msgToParse = &msg->rx.queue[msg->rx.ptr.index_OUT];
		RingBuff_Ptr_Output(&msg->rx.ptr, msg->rx.queueSize);
		return true;
	}

	return false;
}

/*
 * Description: copy data to tx buffer and increment buffer pointer.
 *
 */
void FDCAN_AddDataToTxBuffer(FDCAN_Buffer *msg, FDCAN_Tx *data)
{
	FDCAN_Tx *ptr = &msg->tx.queue[msg->tx.ptr.index_IN];

	memcpy(&ptr->pTxHeader, &data->pTxHeader, sizeof(data->pTxHeader));
	memcpy(&ptr->data, &data->data, sizeof(data->data));

	RingBuff_Ptr_Input(&msg->tx.ptr, msg->tx.queueSize);
}

/*
 * Description: Call from polling routine
 * Input: The FDCAN_buffer
 *
 */
void FDCAN_Transmit(FDCAN_Buffer *msg)
{
	FDCAN_Tx *ptr = &msg->tx.queue[msg->tx.ptr.index_OUT];

	if(msg->tx.ptr.cnt_Handle)
	{
		if(HAL_FDCAN_AddMessageToTxFifoQ(msg->fdcan, &ptr->pTxHeader, ptr->data) == HAL_OK)
		{
			RingBuff_Ptr_Output(&msg->tx.ptr, msg->tx.queueSize);
		}
	}
}

