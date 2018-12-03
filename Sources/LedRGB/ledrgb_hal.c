/*
 * ledrgb_hal.c
 *
 *  Created on: 14/05/2018
 *      Author: aluno
 */

#include "ledrgb_hal.h"
#include "../KL25Z/es670_peripheral_board.h"

/* ************************************************ */
/* Method name:        ledrgb_init                  */
/* Method description: Initialize the ledrgb device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */

void ledrgb_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTA_PCR0 = PORT_PCR_MUX(LEDRGB_ALT);

    /* set pin as digital output */
    GPIOA_PDDR |= GPIO_PDDR_PDD(LEDRGB_PIN);
}

/* ************************************************ */
/* Method name:        ledrgb_set	                */
/* Method description: Set the ledrgb               */
/* Input params:       n/a                          */
/* Output params:      n/a                         */
/* ************************************************ */

void ledrgb_set(void)
{
	 GPIOA_PSOR = GPIO_PSOR_PTSO(0x01 << LEDRGB_PIN);
}

/* ************************************************ */
/* Method name:        ledrgb_clear		            */
/* Method description: Clear the ledrgb             */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */

void ledrgb_clear(void)
{
	GPIOA_PCOR = GPIO_PCOR_PTCO(0x01 << LEDRGB_PIN);
}
