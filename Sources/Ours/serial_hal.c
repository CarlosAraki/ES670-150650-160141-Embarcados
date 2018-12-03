/* *********************************************************************/
/* File name:        serial_hal.c                                      */
/* File description: File dedicated to the initialization of serial    */
/*                   communication, as well as to recieve and transmit */
/*                   data to the buffer                                */
/*                                                                     */
/* Author name:      Victor Camardelli & Guilherme Campiani            */
/* Creation date:    16abr2018                                         */
/* Revision date:    23abr2018                                         */
/* *********************************************************************/

#include "serial_hal.h"
#include "../KL25Z/es670_peripheral_board.h"
#include "../Util/debugUart.h"
#include "fsl_debug_console.h"


 
 /* *************************************************** */
 /* Method name:        serial_setConfig                */
 /* Method description: initializes the peripherals on  */
 /*                     given order                     */
 /* Input params:       n/a                             */
 /* Output params:      n/a                             */
 /* *************************************************** */
void serial_setConfig(void){
	debugUart_init();
}


/* *************************************************** */
/* Method name:        serial_sendBuffer               */
/* Method description: Sends a character to the buffer */
/* Input params:       uiSend = character to be sent   */
/* Output params:      n/a                             */
/* *************************************************** */

void serial_sendBuffer(unsigned int uiSend){
	PUTCHAR(uiSend);
}


/* ********************************************************** */
/* Method name:        serial_recieveBuffer                   */
/* Method description: recieves a character from the buffer   */
/* Input params:       n/a                                    */
/* Output params:      uiRecieveBuffer = Character recieved   */
/* ********************************************************** */

unsigned int serial_receiveBuffer(void){
	unsigned int uiReceiveBuffer;
	uiReceiveBuffer = GETCHAR();
	return uiReceiveBuffer;
}


