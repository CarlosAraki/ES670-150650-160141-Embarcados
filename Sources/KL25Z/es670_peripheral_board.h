/* ***************************************************************** */
/* File name:        es670_peripheral_board.h                        */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/*-----General uC definitions-----*/

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U


/*-----END OF General uC definitions-----*/


/*-----BUZZER Definitions-----*/
#define BUZZER_PORT_BASE_PNT        PORTD                                   /* peripheral port base pointer */
#define BUZZER_GPIO_BASE_PNT        PTD                                     /* peripheral gpio base pointer */

#define BUZZER_PIN                  1U                                      /* buzzer pin */
#define BUZZER_DIR                  kGpioDigitalOutput
#define BUZZER_ALT                  0x01u
/*-----END OF BUZZER definitions-----*/


/*-----LED and SWITCH Definitions-----*/
#define LS_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define LS_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

/* THIS PIN CONFLICTS WITH PTA1 USED AS UART0_RX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS1_PIN                     1U                                      /* led/switch #1 pin */
#define LS1_DIR_OUTPUT              (GPIO_OUTPUT << LS1_PIN)
#define LS1_DIR_INPUT               (GPIO_OUTPUT << LS1_PIN)
#define LS1_ALT                     0x01u                                   /* GPIO alternative */

/* THIS PIN CONFLICTS WITH PTA2 USED AS UART0_TX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS2_PIN                     2U                                      /* led/switch #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_DIR_INPUT               (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     LS1_ALT

#define LS3_PIN                     4U                                      /* led/switch #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_DIR_INPUT               (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     LS1_ALT

#define LS4_PIN                     5U                                      /* led/switch #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_DIR_INPUT               (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     LS1_ALT

/*-----END OF LED and SWITCH definitions-----*/

/* Display */
#define DISPLAY_ALT					0x01u

#define DISPLAY_PORT_BASE_PNT     	PORTC                                   /* peripheral port base pointer */
#define DISPLAY_GPIO_BASE_PNT       PTC                                     /* peripheral gpio base pointer */

/* segments definition */
#define DA_PIN                     	0U
#define DA_DIR	            	   	(GPIO_OUTPUT << DA_PIN)
#define DA_ALT                     	DISPLAY_ALT

#define DB_PIN                     	1U
#define DB_DIR			         	(GPIO_OUTPUT << DB_PIN)
#define DB_ALT                    	DISPLAY_ALT

#define DC_PIN                     2U
#define DC_DIR		     	       (GPIO_OUTPUT << DC_PIN)
#define DC_ALT                     DISPLAY_ALT

#define DD_PIN                     3U
#define DD_DIR		               (GPIO_OUTPUT << DD_PIN)
#define DD_ALT                     DISPLAY_ALT

#define DE_PIN                     4U
#define DE_DIR		               (GPIO_OUTPUT << DE_PIN)
#define DE_ALT                     DISPLAY_ALT

#define DF_PIN                     5U
#define DF_DIR		               (GPIO_OUTPUT << DF_PIN)
#define DF_ALT                     DISPLAY_ALT

#define DG_PIN                     6U
#define DG_DIR		               (GPIO_OUTPUT << DG_PIN)
#define DG_ALT                     DISPLAY_ALT

#define DDOT_PIN                   7U
#define DDOT_DIR	 	           (GPIO_OUTPUT << DDOT_PIN)
#define DDOT_ALT                   DISPLAY_ALT

/* display definitions */
#define D1_PIN                     13U
#define D1_DIR		               (GPIO_OUTPUT << D1_PIN)
#define D1_ALT                     DISPLAY_ALT

#define D2_PIN                     12U
#define D2_DIR	 		           (GPIO_OUTPUT << D2_PIN)
#define D2_ALT                     DISPLAY_ALT

#define D3_PIN                     11U
#define D3_DIR		              (GPIO_OUTPUT << D3_PIN)
#define D3_ALT                     DISPLAY_ALT

#define D4_PIN                     10U
#define D4_DIR		               (GPIO_OUTPUT << D4_PIN)
#define D4_ALT                     DISPLAY_ALT

/* Fim Display */

/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  (GPIO_OUTPUT << LCD_RS_PIN)
#define LCD_RS_ALT                  0x01u

#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              (GPIO_OUTPUT << LCD_ENABLE_PIN)
#define LCD_ENABLE_ALT              0x01u

#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U

#define LCD_DATA_DIR                kGpioDigitalOutput                      /* LCD data pins */
#define LCD_DATA_ALT                0x01u

#define LCD_DATA_DB0_PIN            0U
#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB7_PIN            7U

#define LCD_DATA_DB0_DIR            (GPIO_OUTPUT << LCD_DATA_DB0_PIN)
#define LCD_DATA_DB1_DIR            (GPIO_OUTPUT << LCD_DATA_DB1_PIN)
#define LCD_DATA_DB2_DIR            (GPIO_OUTPUT << LCD_DATA_DB2_PIN)
#define LCD_DATA_DB3_DIR            (GPIO_OUTPUT << LCD_DATA_DB3_PIN)
#define LCD_DATA_DB4_DIR            (GPIO_OUTPUT << LCD_DATA_DB4_PIN)
#define LCD_DATA_DB5_DIR            (GPIO_OUTPUT << LCD_DATA_DB5_PIN)
#define LCD_DATA_DB6_DIR            (GPIO_OUTPUT << LCD_DATA_DB6_PIN)
#define LCD_DATA_DB7_DIR            (GPIO_OUTPUT << LCD_DATA_DB7_PIN)

/*                 END OF LCD definitions                 */

/* Cooler Definitions */
#define COOLER_PORT_BASE_PNT        PORTA                                   /* peripheral port base pointer */
#define COOLER_GPIO_BASE_PNT        PTA                                     /* peripheral gpio base pointer */

#define COOLER_PIN                  13U                                      /* cooler pin */
#define COOLER_DIR                  (GPIO_OUTPUT << COOLER_PIN)
#define COOLER_ALT                  0x01u
#define COOLER_ALT_PWM				0x03u

#define HEATER_PIN                  12U
#define HEATER_ALT_PWM				0x03u
/* End Cooler def */

/* Tacometer Definitions */

#define TACO_PORT_BASE_PNT        PORTE                                   /* peripheral port base pointer */
#define TACO_GPIO_BASE_PNT        PTE                                     /* peripheral gpio base pointer */

#define TACO_PIN                  29U                                      /* taco pin */
#define TACO_DIR                  (GPIO_OUTPUT << TACO_PIN)
#define TACO_ALT                  0x04u

/* End */


/* Led RGB Definitions */
#define LEDRGB_PORT_BASE_PNT        PORTA                                   /* peripheral port base pointer */
#define LEDRGB_GPIO_BASE_PNT        PTA                                     /* peripheral gpio base pointer */

#define LEDRGB_PIN                  1U                                      /* LedRGB pin */
#define LEDRGB_DIR                  (GPIO_OUTPUT << LEDRGB_PIN)
#define LEDRGB_ALT                  0x01u
/* End */

/* Sensores de chão */

#define FLOOR_PORT_BASE_PNT        PORTB
#define FLOOR_GPIO_BASE_PNT        PTB

#define FLOOR1_PIN                  0U
#define FLOOR1_DIR                  (GPIO_OUTPUT << FLOOR1_PIN)
#define FLOOR1_ALT                  0x00u

#define FLOOR2_PIN                  1U
#define FLOOR2_DIR                  (GPIO_OUTPUT << FLOOR2_PIN)
#define FLOOR2_ALT                  0x00u

#define FLOOR3_PIN                  2U
#define FLOOR3_DIR                  (GPIO_OUTPUT << FLOOR3_PIN)
#define FLOOR3_ALT                  0x00u

#define FLOOR4_PIN                  3U
#define FLOOR4_DIR                  (GPIO_OUTPUT << FLOOR4_PIN)
#define FLOOR4_ALT                  0x00u

#define FLOOR5_PORT_BASE_PNT        PORTC
#define FLOOR5_GPIO_BASE_PNT        PTC

#define FLOOR5_PIN                  1U
#define FLOOR5_DIR                  (GPIO_OUTPUT << FLOOR5_PIN)
#define FLOOR5_ALT                  0x00u




#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */
