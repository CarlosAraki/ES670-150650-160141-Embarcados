/* ********************************************************************/
/* File name:        cmdmachine_hal.h                                 */
/* File description: Header file containing the functions/methods     */
/*                   interfaces for handling the command interpreter  */
/*                   and state machine of cmdmachine_hal.c            */
/* Author name:      Victor Camardelli & Guilherme Campiani           */
/* Creation date:    16abr2018                                        */
/* Revision date:    23abr2018                                        */
/* ********************************************************************/

#ifndef SOURCES_CMDMACHINE_HAL_H_
#define SOURCES_CMDMACHINE_HAL_H_
#include "../Controller/controller_hal.h"
/* Definindo os estados */
typedef enum
{
    IDLE,
    L,
	S,
	B,
	LS,
	LC,
	B1,
	B2,
	C,
	C1,
	C2,
	H,
	H1,
	H2,
	P,
	P1,
	P2,
	P3,
	I,
	I1,
	I2,
	I3,
	D,
	D1,
	D2,
	D3
} current_status;

/* ********************************************************************* */
/* Method name:        interpretCmd                                      */
/* Method description: State Machine of communication protocol           */
/* Input params:       iBuzzerTimer = pointer to variable that holds     */
/*                          the amount of time the buzzer will be on     */
/*                     uiReceiveBuff = char on the buffer                */
/*                     currentState = current state of state machine     */
/*                     iLeds = Vector that holds the information of      */
/*                          which LEDs should remain on                  */
/* Output params:     nextState = next state of state machine            */
/* ********************************************************************* */
void interpretCmd(unsigned int uiReceiveBuff, PID_DATA *pid_data, double *dReference_value);

/* *************************************************** */
/* Method name:        cmdmachine_buzzerInterpreter    */
/* Method description: creates a window of activation  */
/*                        for the buzzer               */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void cmdmachine_buzzerInterpreter(int iBuzzerTimer);


/* ************************************************ */
 /* Method name:        print_error                  */
 /* Method description: prints error message (ERR)   */
 /* Input params:       n/a                          */
 /* Output params:      n/a                          */
 /* ************************************************ */
void print_error(void);


/* ************************************************ */
 /* Method name:        print_error                  */
 /* Method description: prints success message (ACK) */
 /* Input params:       n/a                          */
 /* Output params:      n/a                          */
 /* ************************************************ */
void print_success(void);

void print(char* s);

#endif /* SOURCES_CMDMACHINE_HAL_H_ */
