/*
 * FDCAN_Handler.c
 *
 *  Created on: May 7, 2024
 *      Author: karl.yamashita
 */

#include "main.h"

extern FDCAN_Buffer fdcan1Msg;


void FDCAN_ConfigFilter(FDCAN_Buffer *fdcanBuffer)
{
	FDCAN_FilterTypeDef sFilterConfig;

	sFilterConfig.IdType = FDCAN_STANDARD_ID;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_DISABLE;
	sFilterConfig.FilterID1 = 0x101;
	sFilterConfig.FilterID2 = 0x7FF;

	if(HAL_FDCAN_ConfigFilter(fdcan1Msg.fdcan, &sFilterConfig) != HAL_OK)
	{
		Error_Handler(); // we should never get here
	}
}

/*
 * Description: This should be called twice, one for FIFO0 and another for FIFO1
 * Input: FDCAN_Buffer and Non-Matching Frame type.
 * 			NMF can be FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO1 or FDCAN_REJECT
 *
 */
void FDCAN_InitConfigGlobalFilter(FDCAN_Buffer *msg, uint32_t nmf)
{
	/* Configure global filter on both FDCAN instances:
	     Filter all remote frames with STD and EXT ID
	     Reject non matching frames with STD ID and EXT ID */
	if(HAL_FDCAN_ConfigGlobalFilter(msg->fdcan, nmf, nmf, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
	{
		Error_Handler(); // we should never get here
	}
}

/*
 * Description: Initialize FDCAN buffer.
 * 				Assign FDCAN instance to buffer instance. Set queueSize.
 */
void FDCAN_InitActivation(FDCAN_Buffer *msg)
{
	/* Activate Rx FIFO 0/1 new message notification*/
	if (HAL_FDCAN_ActivateNotification(msg->fdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler(); // we should never get here
	}
}

void FDCAN_ConfigTxDelayCompensation(FDCAN_Buffer *msg)
{
	HAL_FDCAN_ConfigTxDelayCompensation(msg->fdcan, 5, 0);
}

void FDCAN_EnableTxDelayCompensation(FDCAN_Buffer *msg)
{
	HAL_FDCAN_EnableTxDelayCompensation(msg->fdcan);
}

void FDCAN_Start(FDCAN_Buffer *msg)
{
	HAL_FDCAN_Start(msg->fdcan);
}

/*
 * Description: FIFO0 callback
 *
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	FDCAN_Rx *ptr = &fdcan1Msg.rx.queue[fdcan1Msg.rx.ptr.index_IN];

	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
	{
		if(HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, ptr->pRxHeader, ptr->data) == HAL_OK)
		{
			RingBuff_Ptr_Input(&fdcan1Msg.rx.ptr, fdcan1Msg.rx.queueSize);
		}
	}
}

/*
 * Description: FIFO1 callback
 *
 */
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
	FDCAN_Rx *ptr = &fdcan1Msg.rx.queue[fdcan1Msg.rx.ptr.index_IN];

	if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != 0)
	{
		if(HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, ptr->pRxHeader, ptr->data) == HAL_OK)
		{
			RingBuff_Ptr_Input(&fdcan1Msg.rx.ptr, fdcan1Msg.rx.queueSize);
		}
	}
}

