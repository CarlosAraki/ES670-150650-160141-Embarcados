/*
 * cooler_hal.c
 *
 *  Created on: 14/05/2018
 *      Author: aluno
 */

#include "cooler_hal.h"
#include "../KL25Z/es670_peripheral_board.h"

void cooler_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTA_PCR13 = PORT_PCR_MUX(COOLER_ALT);

    /* set pin as digital output */
    GPIOA_PDDR |= GPIO_PDDR_PDD(COOLER_DIR);

}

void cooler_set(void)
{
    /* set desired led */
    GPIOA_PSOR = GPIO_PSOR_PTSO(0x01U << COOLER_PIN);
}

void cooler_clear(void)
{
    /* clear desired led */
    GPIOA_PCOR = GPIO_PCOR_PTCO(0x01U << COOLER_PIN);
}
