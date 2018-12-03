/* ***************************************************************** */
/* File name:        controller_hal.h                                */
/* File description: Header file  containing the function/methods    */
/*                   prototypes of controller_hal.c                  */
/* Author name:      Victor Camardelli & Guilherme Campiani          */
/* Creation date:    25jun2018                                       */
/* Revision date:    25jun2018                                       */
/* ***************************************************************** */


#ifndef SOURCES_CONTROLLER_CONTROLLER_HAL_H_
#define SOURCES_CONTROLLER_CONTROLLER_HAL_H_

typedef struct PID_DATA {
	double dPgain, dDgain, dIgain;
	double dSensor_value_previous;
	double dError_sum;
}PID_DATA;


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
void controller_PidInit(PID_DATA *pid_data);





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

double controller_PidUpdate(PID_DATA *pid_data, double dSensor_value, double dReference_value);

#endif /* SOURCES_CONTROLLER_CONTROLLER_HAL_H_ */
