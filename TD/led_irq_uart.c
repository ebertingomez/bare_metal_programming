#include "led_irq_uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"
/* This file provides a set of functions to trigger interruptions when receiving an HEX from the serial
port and handle it */

/* This array will store all the bytes received by the serial port*/
static uint8_t array[192];
static int counter = 0;
/* Boolean variable to test if 0xFF was received */ 
static int frame_beginning = 0;
static uint8_t byte;
/* Pointer to the  beginning of the array which will contain all the bytes received */
uint8_t * frame = array;

/* Initialization of the serial port as an interruption trigger */
void serial_init()
{
    frame = array;
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM7);
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT7);
    MODIFY_REG(SYSCFG->EXTICR[1], SYSCFG_EXTICR2_EXTI7_Msk, SYSCFG_EXTICR2_EXTI7_PB);
    NVIC_EnableIRQ(23);
}

/* Function which will handle the interruption triggered by the serial port and store the byte received
at the right location */
void EXTI9_5_IRQHandler()
{
    byte = uart_getchar();
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF7);
    if (byte == (uint8_t)0xFF || counter == 192)
    {
        frame_beginning = (byte == 0xFF) ? 1 : 0; 
        counter=0;
    }
    else
    {
        if (frame_beginning){
            array[counter] = byte;
            counter++;
        }
    }
}