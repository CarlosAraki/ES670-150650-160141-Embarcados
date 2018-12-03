/*
 * taco_hal.c
 *
 *  Created on: 14/05/2018
 *      Author: Guilherme e Victor
 */

#include "taco_hal.h"
#include "../KL25Z/es670_peripheral_board.h"

/* ************************************************ */
/* Method name:        taco_init			        */
/* Method description: Initializes TPM0 			*/
/* Input params:       n/a							*/
/* Output params:      n/a                          */
/* ************************************************ */

void taco_init(void){

	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED); //Ungate no clock
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

	TPM0_SC |= TPM_SC_PS(0x00u); 	//Pre scale 1:1
	TPM0_SC |= TPM_SC_CMOD(0x02u); 	//LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock

	SIM_SOPT4 |= SIM_SOPT4_TPM0CLKSEL(0x00u); //TPM0 external clock driven by TPM_CLKIN0 pin.
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10u);	 //OSCERCLK clock

    PORTE_PCR29 |= PORT_PCR_MUX(TACO_ALT);

    /* set pin as digital output */
    GPIOE_PDDR |= GPIO_PDDR_PDD(TACO_DIR);


    SIM_SCGC6 |= SIM_SCGC6_TPM2(CGC_CLOCK_ENABLED); //Ungate no clock
	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

	TPM0_SC |= TPM_SC_PS(0x00u); 	//Pre scale 1:1
	TPM0_SC |= TPM_SC_CMOD(0x02u); 	//LPTPM counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock

	SIM_SOPT4 |= SIM_SOPT4_TPM0CLKSEL(0x00u); //TPM0 external clock driven by TPM_CLKIN0 pin.
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10u);	 //OSCERCLK clock

    PORTE_PCR30 |= PORT_PCR_MUX(TACO_ALT);

    /* set pin as digital output */
    GPIOE_PDDR |= GPIO_PDDR_PDD(TACO_DIR);


}

/* ************************************************ */
/* Method name:        taco_count			        */
/* Method description: Receive TPM0 Counter			*/
/* Input params:       int i						*/
/* Output params:      Returns TPM0 Counter value   */
/* ************************************************ */

int taco_count(int isRight){
	int iCount;
	if (isRight == 1)
	{
		iCount = TPM0_CNT;
		return iCount;
	}
	else{
		iCount = TPM2_CNT;
		return iCount;
	}
}
