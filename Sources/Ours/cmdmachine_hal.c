/* ********************************************************************/
/* File name:        cmdmachine_hal.c                                 */
/* File description: File dedicated to the command interpretation and */
/*                   state machine of the communication protocol      */
/* Author name:      Victor Camardelli & Guilherme Campiani           */
/* Creation date:    16abr2018                                        */
/* Revision date:    23abr2018                                        */
/* ********************************************************************/

#include "cmdmachine_hal.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "../Buzzer/buzzer_hal.h"
#include "../LedSwi/ledswi_hal.h"
#include "../Time_counter/timer_counter.h"
#include "../Ours/ADC_StateMachine.h"
#include "../Util/util.h"

/* ********************************************************************* */
/* Method name:        interpretCmd                                      */
/* Method description: State Machine of communication protocol           */
/* Input params:       iCount = pointer to variable that holds     */
/*                          the amount of time the buzzer will be on     */
/*                     uiReceiveBuff = char on the buffer                */
/*                     currentState = current state of state machine     */
/*                     iLeds = Vector that holds the information of      */
/*                          which LEDs should remain on                  */
/* Output params:     currentState = next state of state machine            */
/* ********************************************************************* */

 void interpretCmd(unsigned int uiReceiveBuff, PID_DATA *pid_data, double *dReference_value){

	 static current_status currentState = IDLE;
	 static int iLeds[4] = {0, 0, 0, 0};
	 static int iCount = 0;
	 static double dCount = 0;
	 switch_status_type_e switchStatus;

	 /*Tratamento da maquina de estados*/
	 
	 switch(currentState){
	 /*Estado Inicial (IDLE). Compara-se o dado recebido do buffer com o dado correspondente que leva a maquina aos estados seguintes possíveis*/
	 /*Os próximos estados validos são listados. Em caso de erro, imprime-se a mensagem de erro e a maquina volta ao estado inicial*/
	 	 case IDLE:
			 if ('L' == uiReceiveBuff)
				 currentState = L;
			 else if('S' == uiReceiveBuff)
				 currentState = S;
			 else if('B' == uiReceiveBuff)
				 currentState = B;
			 else if('C' == uiReceiveBuff)
			 	currentState = C;
			 else if('H' == uiReceiveBuff)
				 currentState = H;
			 else if('P' == uiReceiveBuff)
				 currentState = P;
			 else if('I' == uiReceiveBuff)
				 currentState = I;
			 else if('D' == uiReceiveBuff)
				 currentState = D;
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
			 
		/*Estado Leds (L). Novamente compara-se o dado recebido*/
		/* Os proximos estados possíveis são Clear(C) e Set(S). Em caso de erro, novamente se imprime a mensagem de erro*/
		 case L:
			 if ('S' == uiReceiveBuff)
				 currentState = LS;
			 else if('C' == uiReceiveBuff)
				 currentState = LC;
			 else
				 currentState = IDLE;
			 break;
			 
		/*Estado Switch (C). Novamente compara-se o dado recebido, desta vez tendo o cuidado de avaliar o range em que um dado válido pode chegar*/
		/*Não há próximo estado para o caso do switch, então caso o dado seja válido a maquina de estado realiza a operação proposta*/
		 case S:
			 if ('0' < uiReceiveBuff && '5' > uiReceiveBuff){
				 print_success();
				 ledswi_initLedSwitch(0, 4);
				 /*Determina o estado do switch*/
				 switchStatus = ledswi_getSwitchStatus(uiReceiveBuff-48);
				 ledswi_initLedSwitch(4, 0);
				 
				 /*Cuidado para avaliar quais LEDs estavam ligados no momento da avaliação do Switch e religa-los após a operação*/
				 if(1 == iLeds[1])
					 ledswi_setLed(1);
				 if(1 == iLeds[2])
					 ledswi_setLed(2);
				 if(1 == iLeds[3])
					 ledswi_setLed(3);
				 if(1 == iLeds[4])
					 ledswi_setLed(4);
				 
				 /*Imprime a resposta adequada a depender do modo do Switch*/
				 if (SWITCH_ON == switchStatus)
					 PUTCHAR('C');
				 else
					 PUTCHAR('O');
			 }
			 else
				 print_error();
			 currentState = IDLE;
			 break;
			 
		/*Estado Buzzer (B). Mais uma vez verifica-se o dado recebido e se ele está no range de validade*/
		/*Caso o dado seja válido, faz a conversão do dado recebido para um número inteiro que será a contagem de tempo do bufffer*/
		 case B:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*100;   /*casa decimal da centena*/
				 currentState = B1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case B1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*10;  /*casa decimal da dezena*/
				 currentState = B2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case B2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*1;  /*casa decimal da unidade*/
				 cmdmachine_buzzerInterpreter(iCount);
				 iCount = 0;
				 currentState = IDLE;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			break;

		 case H:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*100;   /*casa decimal da centena*/
				 currentState = H1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case H1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*10;  /*casa decimal da dezena*/
				 currentState = H2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case H2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 iCount = iCount + (uiReceiveBuff-48)*1;  /*casa decimal da unidade*/
				 timer_changeHeaterPwm(iCount);
				 print_success();
				 iCount = 0;
				 currentState = IDLE;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
				 break;

		/*Estado SetLed (LS). Verifica se o dado está no range adequado*/
		/* faz a operação de setar o Led apropriado*/
		 case LS:
			 if ('0' < uiReceiveBuff && '5' > uiReceiveBuff){
				 print_success();
				 ledswi_initLedSwitch(4, 0);
				 ledswi_setLed(uiReceiveBuff-48);
				 iLeds[uiReceiveBuff-48] = 1;
			 }
			 else
				 print_error();
			 currentState = IDLE;
			 break;
			 
		/*Estado ClearLed (LC). Verifica se o dado está no range adequado*/
		/* faz a operação de limpar o Led apropriado*/
		 case LC:
			 if ('0' < uiReceiveBuff && '5' > uiReceiveBuff){
				 print_success();
				 ledswi_initLedSwitch(4, 0);
				 ledswi_clearLed(uiReceiveBuff-48);
				 iLeds[uiReceiveBuff-48] = 0;
			 }
			 else
				 print_error();
			 currentState = IDLE;
			 break;

		 case C:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = (uiReceiveBuff-48)*100;   /*casa decimal da centena*/
				 currentState = C1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case C1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)*10;  /*casa decimal da dezena*/
				 currentState = C2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case C2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)*1;  /*casa decimal da unidade*/
				 *dReference_value = dCount;
				 print_success();
				 currentState = IDLE;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
				 break;


	/*Proporcional*/
		 case P:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = (uiReceiveBuff-48);   /*casa decimal da centena*/
				 currentState = P1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case P1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/10;  /*casa decimal da dezena*/
				 currentState = P2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case P2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/100;  /*casa decimal da unidade*/
				 currentState = P3;

			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
				 break;
		 case P3:
				 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
					 dCount = dCount + (uiReceiveBuff-48)/1000;  /*casa decimal da unidade*/
					 pid_data->dPgain = dCount;
					 print_success();
					 currentState = IDLE;
				 }
				 else{
					 print_error();
					 currentState = IDLE;
				 }
					 break;


	/*Integrativo*/
		 case I:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = (uiReceiveBuff-48);   /*casa decimal da centena*/
				 currentState = I1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case I1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/10;  /*casa decimal da dezena*/
				 currentState = I2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case I2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/100;  /*casa decimal da unidade*/
				 currentState = I3;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
				 break;
		 case I3:
				 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
					 dCount = dCount + (uiReceiveBuff-48)/1000;  /*casa decimal da unidade*/
					 pid_data->dIgain = dCount;
					 print_success();
					 currentState = IDLE;
				 }
				 else{
					 print_error();
					 currentState = IDLE;
				 }
					 break;

	/*Derivativo*/
		 case D:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = (uiReceiveBuff-48);   /*casa decimal da centena*/
				 currentState = D1;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case D1:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/10;  /*casa decimal da dezena*/
				 currentState = D2;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
			 break;
		 case D2:
			 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
				 dCount = dCount + (uiReceiveBuff-48)/100;  /*casa decimal da unidade*/
				 currentState = D3;
			 }
			 else{
				 print_error();
				 currentState = IDLE;
			 }
				 break;
		 case D3:
				 if ('0' <= uiReceiveBuff && '9' >= uiReceiveBuff){
					dCount = dCount + (uiReceiveBuff-48)/1000;  /*casa decimal da unidade*/
					pid_data->dDgain = dCount;
					print_success();
					currentState = IDLE;
				 }
				 else{
					 print_error();
					 currentState = IDLE;
				 }
					 break;


		 default:
			 //print_error();
			 currentState = IDLE;
			 break;
 		}
 }

 
 /* *************************************************** */
 /* Method name:        cmdmachine_buzzerInterpreter    */
 /* Method description: creates a window of activation  */
 /*                        for the buzzer               */
 /* Input params:       n/a                             */
 /* Output params:      n/a                             */
 /* *************************************************** */
 
 void cmdmachine_buzzerInterpreter(int iCount){
	for (int i = 0; i < iCount/2;i++){
		 buzzer_setBuzz();
		 util_genDelay1ms();
		 buzzer_clearBuzz();
		 util_genDelay1ms();
	}
	print_success();
}

 /* ************************************************ */
 /* Method name:        print_error                  */
 /* Method description: prints error message (ERR)   */
 /* Input params:       n/a                          */
 /* Output params:      n/a                          */
 /* ************************************************ */
 void print_error(void)
 {
 	PUTCHAR('E');
 	PUTCHAR('R');
 	PUTCHAR('R');
 }

 /* ************************************************ */
 /* Method name:        print_error                  */
 /* Method description: prints success message (ACK) */
 /* Input params:       n/a                          */
 /* Output params:      n/a                          */
 /* ************************************************ */
 void print_success(void)
 {
	util_genDelay1ms();
 	PUTCHAR('A');
 	PUTCHAR('C');
 	PUTCHAR('K');
 }

 //IMPRIME COISAS
void print(char* s)
{
	int i = 0;
	while (s[i] != 'Z'){
		PUTCHAR(s[i]);
		i++;
	}
}
