/* ********************************************************************/
/* File name:        display_hal.c                                    */
/* File description: File dedicated to the hardware abstraction layer */
/*                   related 7 segments display from the peripheral   */
/*		     board                                            */
/* Author name:      Victor Camardelli & Guilherme Campiani           */
/* Creation date:    28mar2018                                        */
/* Revision date:    05abr2018                                        */
/* ********************************************************************/

#include "display_hal.h"
#include "../KL25Z/es670_peripheral_board.h"



/* *********************************************************** */
/* Method name:        display_init                            */
/* Method description: Initialize the 7-segment display device */
/* Input params:       n/a                                     */
/* Output params:      n/a                                     */
/* *********************************************************** */

void display_init(void){
	/* un-gate port clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

    PORTC_PCR0 = PORT_PCR_MUX(DA_ALT);
    PORTC_PCR1 = PORT_PCR_MUX(DB_ALT);
    PORTC_PCR2 = PORT_PCR_MUX(DC_ALT);
    PORTC_PCR3 = PORT_PCR_MUX(DD_ALT);
    PORTC_PCR4 = PORT_PCR_MUX(DE_ALT);
    PORTC_PCR5 = PORT_PCR_MUX(DF_ALT);
    PORTC_PCR6 = PORT_PCR_MUX(DG_ALT);
    PORTC_PCR7 = PORT_PCR_MUX(DDOT_ALT);

    PORTC_PCR10 = PORT_PCR_MUX(D4_ALT);
    PORTC_PCR11 = PORT_PCR_MUX(D3_ALT);
    PORTC_PCR12 = PORT_PCR_MUX(D2_ALT);
    PORTC_PCR13 = PORT_PCR_MUX(D1_ALT);

    GPIOC_PDDR |= GPIO_PDDR_PDD(D1_DIR | D2_DIR | D3_DIR | D4_DIR | DA_DIR | DB_DIR |
    		DC_DIR | DD_DIR | DE_DIR | DF_DIR | DG_DIR | DDOT_DIR);

}


/* *********************************************************** */
/* Method name:        display_clear                           */
/* Method description: clear the 7-segment display             */
/* Input params:       n/a                                     */
/* Output params:      n/a                                     */
/* *********************************************************** */

void display_clear(void){
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << D1_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << D2_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << D3_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << D4_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DA_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DB_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DC_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DD_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DE_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DF_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DG_PIN) );
	GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << DDOT_PIN) );
}





/* *************************************************************  */
/* Method name:        display_set                                */
/* Method description: Set which of the four 7-segments display   */ 
/*                     will be selected and which segments of the */
/*                     selected display will be turned ON (Based  */
/*                     on the number that will be shown)          */
/* Input params:       dNum = Number of the display to be selected*/                                     
/*                     Word = Number to be shown on the selected  */
/*                      display (Range: 0 to 15)		  */
/*                     dot = Set the dot of the display ON (dot=1)*/
/*			or OFF (dot=0)                            */
/* Output params:      n/a                                        */
/* *************************************************************  */

void display_set(char dNum, char Word, char dot){

	display_clear();

	if (dot == 1)
		GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DDOT_PIN) );


	switch (dNum){
		case 1:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << D1_PIN) );
			break;
		case 2:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << D2_PIN) );
			break;
		case 3:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << D3_PIN) );
			break;
		case 4:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << D4_PIN) );
			break;
		default:
			break;
	}

	switch (Word){
		case 0:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			break;
		case 1:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			break;
		case 2:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 3:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 4:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 5:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 6:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 7:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			break;
		case 8:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 9:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 10:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 11:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 12:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			break;
		case 13:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DB_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DC_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 14:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DD_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		case 15:
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DA_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DE_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DF_PIN) );
			GPIOC_PSOR |= GPIO_PSOR_PTSO( (0x01U << DG_PIN) );
			break;
		default:
			break;
	}

}

