/* ***************************************************************** */
/* File name:        es670.c                                         */
/* File description: File dedicated to the ES670 prototype projects  */
/*                   involving the FRDM-KL25Z board together with is */
/*                   daughter board containing more peripherals      */
/*                                                                   */
/*                   Processor MKL25Z128VLK4 characteristics         */
/*                   48 MHz ARM Cortex-M0+ core                      */
/*                   128 KB program flash memory                     */
/*                   16 KB SRAM                                      */
/*                   Voltage range: 1.71 to 3.6 V                    */
/*                                                                   */
/* Author name:     Carlos Araki & Guilherme Campiani          */
/* Creation date:    23abr2018                                       */
/* Revision date:    30nov2018                                       */
/* ***************************************************************** */


/* our includes */
#include "stdio.h"
#include "ADC/adc.h"
#include "Ours/ADC_StateMachine.h"
#include "Display7seg/display_hal.h"
#include "Ledswi/ledswi_hal.h"
#include "Buzzer/buzzer_hal.h"
#include "Lcd/lcd_hal.h"
#include "Cooler/cooler_hal.h"
#include "Ours/serial_hal.h"
#include "Util/util.h"
#include "Util/mcg_hal.h"
#include "Util/debugUart.h"
#include "Util/tc_hal.h"
#include "Ours/cmdmachine_hal.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "Taco/taco_hal.h"
#include "Time_Counter/timer_counter.h"
#include "Controller/controller_hal.h"

/* system includes */
#include "fsl_debug_console.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         10000 /* 1000*1000 micro seconds */


/* globals */
volatile unsigned int uiFlagNextPeriod = 0;			/* cyclic executive flag */


/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}


/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
	/* initializations*/
	mcg_clockInit();
	serial_setConfig();
	taco_init();
	adc_initADCModule();
	timer_initTPM1AsPWM();

	//Init pwm
	timer_initEngine_2();
	timer_initEngine();

    /* configure cyclic executive interruption */
    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    /* configure PID controller*/
	PID_DATA pid_data1;
	PID_DATA pid_data2;
	controller_PidInit(&pid_data1);
	controller_PidInit(&pid_data2);
    /* Em ordem dos sensores 8, 9, 12, 13, 11 -- tacometros nao vi a ordem ainda*/
    int sensores[7] = {0, 0, 0, 0, 0, 0, 0};
    int control = 0;
    int cont = 0;
    char str[100];
    /* cooperative cyclic executive main loop */
    while(1U)
    {
    	sensores[0] = adc_read(8);
		sensores[1] = adc_read(9);
		sensores[2] = adc_read(12);
		sensores[3] = adc_read(11);
		sensores[4] = adc_read(13);

		if (sensores[0] > 130)
			control = control + 2;
		if (sensores[1] > 130)
			control = control + 1;
		if (sensores[3] > 130)
			control = control - 1;
		if (sensores[4] > 130)
			control = control - 2;

		if(cont < 50){
			if (control > 0){
				if (control < 3){
					timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),10);
					timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),60);
				}
				else{
					timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),0);
					timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),60);
				}
				sprintf(str, "S1: %d S2: %d S3: %d S4: %d S5: %d Esquerda \r\nZ", sensores[0], sensores[1], sensores[2], sensores[3], sensores[4]);
			}
			else if (control < 0){
				if (control > -3){
					timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),60);
					timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),0);
				}
				else{
					timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),60);
					timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),10);
				}
				sprintf(str, "S1: %d S2: %d S3: %d S4: %d S5: %d Direita \r\nZ", sensores[0], sensores[1], sensores[2], sensores[3], sensores[4]);
			}
			else if (sensores[2] > 130){
				timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),60);
				timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),60);
				
				sprintf(str, "S1: %d S2: %d S3: %d S4: %d S5: %d Reto \r\nZ", sensores[0], sensores[1], sensores[2], sensores[3], sensores[4]);
			}
			else{
				timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),0);
				timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),0);
				
				sprintf(str, "S1: %d S2: %d S3: %d S4: %d S5: %d Parado \r\nZ", sensores[0], sensores[1], sensores[2], sensores[3], sensores[4]);
			}

			if (sensores[0] > 100 && sensores[1] > 100 && sensores[2] > 100 && sensores[3] > 100 && sensores[4] > 100){
				while(!(sensores[0] > 100 && sensores[1] > 100 && sensores[2] > 100 && sensores[3] > 100 && sensores[4] > 100)){
				cont++;
				}
			}
    	}

    	else{
    		timer_changeEngine1(controller_PidUpdate(&pid_data1,taco_count(1),0);
			timer_changeEngine2(controller_PidUpdate(&pid_data2,taco_count(2),0);
    		
    	}
		print(str);
		control = 0;
    	while(!uiFlagNextPeriod);
    	uiFlagNextPeriod = 0;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
