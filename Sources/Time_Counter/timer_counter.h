#define FPWM  400

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			                  */
/* Outpu params:	   n/a 		                      */
/* ************************************************** */
void timer_initTPM1AsPWM(void);

/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_initEngine_2(void);

/* ************************************************ */
/* Method name:        timer_setDutyCicle           */
/* Method description: Set dutycycle between 0, 25  */
/* 						50, 75 e 100				*/
/* Input params:       Number between 0 and 4       */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_changeEngine2(unsigned int uiCycle);

/* ************************************************ */
/* Method name:        timer_changeHeaterPwm        */
/* Method description: change the cooler pwm        */
/* Input params:       pwm desired (percentage)     */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_changeEngine1(unsigned int iPwm);

/* ************************************************ */
/* Method name:        timer_initHeater             */
/* Method description: Initialize the heater device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_initEngine(void);
