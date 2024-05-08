/*
 * FDCAN_Handler.h
 *
 *  Created on: May 7, 2024
 *      Author: karl.yamashita
 */

#ifndef INC_FDCAN_HANDLER_H_
#define INC_FDCAN_HANDLER_H_

void FDCAN_ConfigFilter(FDCAN_Buffer *fdcanBuffer);
void FDCAN_InitConfigGlobalFilter(FDCAN_Buffer *fdcanBuffer, uint32_t nmf);
void FDCAN_InitActivation(FDCAN_Buffer *fdcanBuffer);

void FDCAN_ConfigTxDelayCompensation(FDCAN_Buffer *msg);
void FDCAN_EnableTxDelayCompensation(FDCAN_Buffer *msg);
void FDCAN_Start(FDCAN_Buffer *msg);


#endif /* INC_FDCAN_HANDLER_H_ */
