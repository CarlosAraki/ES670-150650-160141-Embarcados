/* *********************************************************************/
/* File name:        serial_hal.h                                      */
/* File description: Header file containing the functions/methods      */
/*                   interfaces for handling serial communication      */
/* Author name:      Victor Camardelli & Guilherme Campiani            */
/* Creation date:    16abr2018                                         */
/* Revision date:    23abr2018                                         */
/* *********************************************************************/

#ifndef SOURCES_SERIAL_HAL_H_
#define SOURCES_SERIAL_HAL_H_


 /* *************************************************** */
 /* Method name:        serial_setConfig                */
 /* Method description: initializes the peripherals on  */
 /*                     given order                     */
 /* Input params:       n/a                             */
 /* Output params:      n/a                             */
 /* *************************************************** */
void serial_setConfig(void);



/* *************************************************** */
/* Method name:        serial_sendBuffer               */
/* Method description: Sends a character to the buffer */
/* Input params:       uiSend = character to be sent   */
/* Output params:      n/a                             */
/* *************************************************** */
void serial_sendBuffer(unsigned int uiSend);



/* ********************************************************** */
/* Method name:        serial_recieveBuffer                   */
/* Method description: recieves a character from the buffer   */
/* Input params:       n/a                                    */
/* Output params:      uiRecieveBuffer = Character recieved   */
/* ********************************************************** */

unsigned int serial_receiveBuffer(void);

#endif /* SOURCES_SERIAL_HAL_H_ */
