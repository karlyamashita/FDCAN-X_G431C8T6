/*
 * PollingRoutine.c
 *
 *  Created on: Oct 24, 2023
 *      Author: karl.yamashita
 *
 *
 *      Template for projects.
 *
 *
 *      LED's are active low. Initialize LED's high so they are in Off state.
 *
 *
 */


#include "main.h"

extern FDCAN_HandleTypeDef hfdcan1;
extern TimerCallbackStruct timerCallback;


FDCAN_Buffer fdcan1Msg =
{
	.fdcan = &hfdcan1,
	.rx.queueSize = FDCAN_RX_BUF_SIZE,
	.tx.queueSize = FDCAN_TX_BUF_SIZE
};

void PollingInit(void)
{
	FDCAN_ConfigFilter(&fdcan1Msg);
	FDCAN_InitConfigGlobalFilter(&fdcan1Msg, FDCAN_ACCEPT_IN_RX_FIFO0);
	FDCAN_InitConfigGlobalFilter(&fdcan1Msg, FDCAN_ACCEPT_IN_RX_FIFO1);
	FDCAN_InitActivation(&fdcan1Msg);
	FDCAN_Start(&fdcan1Msg);

	TimerCallbackRegisterOnly(&timerCallback, LED_GreenBlink);
	TimerCallbackTimerStart(&timerCallback, LED_GreenBlink, 500, TIMER_REPEAT); // continuously blink
	TimerCallbackRegisterOnly(&timerCallback, LED_BlueBlink);
	TimerCallbackRepetitionStart(&timerCallback, LED_BlueBlink, 500, 6); // blink blue led 3 times
}

void PollingRoutine(void)
{
	TimerCallbackCheck(&timerCallback);

	FDCAN_Parse(&fdcan1Msg);
}


void FDCAN_Parse(FDCAN_Buffer *msg)
{
	FDCAN_RxHeaderTypeDef *ptr;

	if(FDCAN_MsgReady(msg))
	{
		ptr = msg->rx.msgToParse->pRxHeader;
		if(ptr->IdType == FDCAN_STANDARD_ID)
		{
			if(ptr->Identifier == 0x101) // Tech2
			{
				ParseTech2(msg->rx.msgToParse);
			}
		}
		else if(ptr->IdType == FDCAN_EXTENDED_ID)
		{
			if(ptr->Identifier == 0x10010840)
			{
				ParsePowerMode(msg->rx.msgToParse);
			}
		}
	}
}

int ParseTech2(FDCAN_Rx *msg)
{

	return 0;
}

int ParsePowerMode(FDCAN_Rx *msg)
{

	return 0;
}



