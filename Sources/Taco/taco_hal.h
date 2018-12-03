/*
 * taco_hal.h
 *
 *  Created on: 14/05/2018
 *      Author: Guilherme e Victor
 */

#ifndef SOURCES_TACO_TACO_HAL_H_
#define SOURCES_TACO_TACO_HAL_H_

/* ************************************************ */
/* Method name:        taco_init			        */
/* Method description: Initializes TPM0 			*/
/* Input params:       n/a							*/
/* Output params:      n/a                          */
/* ************************************************ */


void taco_init(void);

/* ************************************************ */
/* Method name:        taco_count			        */
/* Method description: Receive TPM0 Counter			*/
/* Input params:       n/a							*/
/* Output params:      Returns TPM0 Counter value   */
/* ************************************************ */

int taco_count(void);

#endif /* SOURCES_TACO_TACO_HAL_H_ */
