#include "../KL25Z/es670_peripheral_board.h"
#include "fsl_tpm_hal.h"
#include "timer_counter.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM        */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 		              */
/* ************************************************** */
void timer_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

	TPM1_SC |= TPM_SC_CPWMS(0x00u);  //up counting mode
	TPM1_SC |= TPM_SC_CMOD(0x01u);  //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= TPM_SC_PS(0x00u);   //Prescale 1:1

	/* Channel 0 Config - Heater */
	TPM1_C0SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSB(0b1) | TPM_CnSC_ELSA(0b0));

	TPM1_C0V = 0x00; //PWM 00%


	//ELSnB:ELSnA = 1:0
	//MSnB:MSnA = 1:0
	TPM1_C1SC |= TPM_CnSC_MSB(0x01u) | TPM_CnSC_MSA(0x00u) | TPM_CnSC_ELSB(0x01u) | TPM_CnSC_ELSA(0x00u);

	TPM1_CNT = TPM_CNT_COUNT(0x00u);
	TPM1_MOD = TPM_MOD_MOD((8000000*(1/1))/FPWM);

	TPM1_C1V = 0x00;
//	TPM1_C1V = TPM_CnV_VAL(TPM1_MOD); //PWM 100%
//	TPM1_C1V = TPM_CnV_VAL(0.75*TPM1_MOD); //PWM 75%
//	TPM1_C1V = TPM_CnV_VAL(0.5*TPM1_MOD); //PWM 50%
//	TPM1_C1V = TPM_CnV_VAL(0.25*TPM1_MOD); //PWM 25%
//	TPM1_C1V = TPM_CnV_VAL(0U); //PWM 0%
}


/* ************************************************ */
/* Method name:        timer_setDutyCicle           */
/* Method description: Set dutycycle between 0, 25  */
/* 						50, 75 e 100				*/
/* Input params:       Number between 0 and 4       */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_changeEngine2(unsigned int uiCycle)
{
	TPM1_C1V = (uiCycle*TPM1_MOD)/100;
}

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_initEngine_2(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as PWM */
    PORTA_PCR13 |= PORT_PCR_MUX(0x03);
}

/* ************************************************ */
/* Method name:        timer_change Engine1         */
/* Method description: change the engine pwm        */
/* Input params:       pwm desired (percentage)     */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_changeEngine1(unsigned int iPwm)
{
	iPwm = (iPwm*TPM1_MOD)/100;
	TPM1_C0V = iPwm;
}

/* ************************************************ */
/* Method name:        timer_initHeater             */
/* Method description: Initialize the heater device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_initEngine(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as PWM */
    PORTA_PCR12 |= PORT_PCR_MUX(0x03);
}

