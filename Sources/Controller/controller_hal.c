/* ***************************************************************** */
/* File name:        controller_hal.c                                */
/* File description: File dedicated to initialize a PID digital      */
/*                    controller, and containing its equations       */
/* Author name:      Victor Camardelli & Guilherme Campiani          */
/* Creation date:    25jun2018                                       */
/* Revision date:    25jun2018                                       */
/* ***************************************************************** */

#include "controller_hal.h"



/* ************************************************ */
/* Method name:        controller_PidInit           */
/* Method description: initialize PID controller    */
/* 	                  with its gains as 1 and its   */
/* 	                  errors as 0                   */
/*                                                  */
/* Input params:       *pid_data: struct que contem */
/* 			os valores de ganhos e erros para o PID */
/*													*/
/* 													*/
/*													*/
/* Output params:      n/a                          */
/* ************************************************ */
void controller_PidInit(PID_DATA *pid_data){
	pid_data->dPgain = 1.0;
	pid_data->dDgain = 1.0;
	pid_data->dIgain = 1.0;
	pid_data->dSensor_value_previous = 0.0;
	pid_data->dError_sum = 0.0;
}




/* ************************************************ */
/* Method name:        controller_PidUpdate         */
/* Method description: Calcula os termos do control */
/* 				ador, baseado nas suas equações     */
/*                                                  */
/* Input params:     *pid_data = struct que contem  */
/* 			os valores de ganhos e erros para o PID */
/*			   	   dSensor_Value = valor PWM medido */
/*   				dReference_Value = valor de     */
/*		referencia determinado para o controlador   */
/*					                                */
/* Output params:      n/a                          */
/* ************************************************ */

double controller_PidUpdate(PID_DATA *pid_data, double dSensor_value, double dReference_value){

	double dPterm, dIterm, dDterm;
	double dError, dDifference, dTotal;

	dError = dReference_value - dSensor_value;

	dPterm = pid_data->dPgain * dError;

	pid_data->dError_sum += dError;

	dIterm = pid_data->dIgain * pid_data->dError_sum;

	dDifference = pid_data->dSensor_value_previous - dSensor_value;

	pid_data->dSensor_value_previous = dSensor_value;

	dDterm = pid_data->dDgain * dDifference;

	dTotal = dPterm + dIterm + dDterm;

	if (dTotal > 100) dTotal = 100;
	else if (dTotal < 0) dTotal = 0;

	return (dTotal);
}


