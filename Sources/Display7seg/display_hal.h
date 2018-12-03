/* ********************************************************************/
/* File name:        display_hal.c                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of dipslay_hal                       */
/* Author name:      Victor Camardelli & Guilherme Campiani           */
/* Creation date:    28mar2018                                        */
/* Revision date:    05abr2018                                        */
/* ********************************************************************/

#ifndef SOURCES_DISPLAY_HAL_H_
#define SOURCES_DISPLAY_HAL_H_


/* *********************************************************** */
/* Method name:        display_init                            */
/* Method description: Initialize the 7-segment display device */
/* Input params:       n/a                                     */
/* Output params:      n/a                                     */
/* *********************************************************** */

void display_init(void);


/* *********************************************************** */
/* Method name:        display_clear                           */
/* Method description: clear the 7-segment display             */
/* Input params:       n/a                                     */
/* Output params:      n/a                                     */
/* *********************************************************** */

void display_clear(void);

/* *************************************************************  */
/* Method name:        display_set                                */
/* Method description: Set which of the four 7-segments display   */ 
/*                     will be selected and which segments of the */
/*                     selected display will be turned ON (Based  */
/*                       on the number that will be shown)        */
/* Input params:       dNum = Number of the display to be selected*/                                     
/*                     Word = Number to be shown on the selected  */
/*                     display (Range: 0 to 15)		          */
/*                     dot = Set the dot of the display ON (dot=1)*/
/*			or OFF (dot=0)                            */
/* Output params:      n/a                                        */
/* *************************************************************  */
void display_set(char dNum, char Word, char dot);

#endif /* SOURCES_DISPLAY_HAL_H_ */
