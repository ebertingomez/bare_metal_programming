#include "matrix.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"
/* This file provides a set of function to initialize and control all the 
LEDs from a matrix. To test it, please call the function test_pixels() */

/* This type represents a pixel using its color decomposition in RGB format */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

#define COLUMN_NUMBER 8
#define ROW_NUMBER 8
extern uint8_t _binary_image_raw_start;

/* Initializes all the values of the bank0 to 1 in order to use bank1 */
static void init_bank0(void);

/* Resets all the rows of the current BANK */
static void deactivate_rows();

/* Makes a simulates a pause in the execution.
Steps: Number of operations executed during that "pause" */
static void delay(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        asm volatile("nop");
    }
}

/* Initializes all the registers of the board to the right value */
static void matrix_init()
{

    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE2_Msk, GPIO_MODER_MODE2_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE3_Msk, GPIO_MODER_MODE3_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE4_Msk, GPIO_MODER_MODE4_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE5_Msk, GPIO_MODER_MODE5_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE6_Msk, GPIO_MODER_MODE6_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE7_0);
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE15_Msk, GPIO_MODER_MODE15_0);

    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0_Msk, GPIO_MODER_MODE0_0);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE1_Msk, GPIO_MODER_MODE1_0);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE2_Msk, GPIO_MODER_MODE2_0);

    MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE3_Msk, GPIO_MODER_MODE3_0);
    MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE4_Msk, GPIO_MODER_MODE4_0);
    MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE5_Msk, GPIO_MODER_MODE5_0);

    //Reset
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);
    //Lat
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS4);
    //SB
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS5);
    //SCK SDA
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1);
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
    //PC0-7
    deactivate_rows();

    delay(10000);
    //Set
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3);
    delay(3);
    init_bank0();
}

#define RST(BIT) ((BIT) ? (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3)) : (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3)))
#define SB(BIT) ((BIT) ? (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS5)) : (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR5)))
#define LAT(BIT) ((BIT) ? (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS4)) : (SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR4)))
#define SCK(BIT) ((BIT) ? (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1)) : (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1)))
#define SDA(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS4)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4)))
#define ROW0(BIT) ((BIT) ? (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS2)) : (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR2)))
#define ROW1(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS15)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR15)))
#define ROW2(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS2)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR2)))
#define ROW3(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS7)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR7)))
#define ROW4(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS6)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR6)))
#define ROW5(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5)))
#define ROW6(BIT) ((BIT) ? (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0)) : (SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0)))
#define ROW7(BIT) ((BIT) ? (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS3)) : (SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR3)))

/* Generates a positive pulse SCK (OFF-ON-OFF) */
static void pulse_SCK()
{
    SCK(0);
    delay(1);
    SCK(1);
    delay(1);
    SCK(0);
    delay(1);
}

/* Generates a negative pulse LAT (ON-OFF-ON) in order to transfer the bits to BANK1*/
static void pulse_LAT()
{
    LAT(1);
    delay(1);
    LAT(0);
    delay(1);
    LAT(1);
    delay(1);
}

/* Resets all the rows of the current BANK */
static void deactivate_rows()
{
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

/* Sets the value of a specific row */
static void activate_row(int row)
{
    switch (row)
    {
    case 0:
        ROW0(1);
        break;
    case 1:
        ROW1(1);
        break;
    case 2:
        ROW2(1);
        break;
    case 3:
        ROW3(1);
        break;
    case 4:
        ROW4(1);
        break;
    case 5:
        ROW5(1);
        break;
    case 6:
        ROW6(1);
        break;
    case 7:
        ROW7(1);
        break;

    default:
        break;
    }
}

/* Send a 8bit word starting from the most the most significant bit to a specific BANK */
static void send_byte(uint8_t val, int bank)
{
    switch (bank)
    {
    case 0:
        SB(0);
        break;
    case 1:
        SB(1);
        break;
    default:
        break;
    }

    for (int i = 0; i < 8; i++)
    {
        SDA(val >> 7);
        pulse_SCK();
        val = val << 1;
    }
}

/* Set the colors of the RGB leds of a row according to an array of rgb_colors */
static void mat_set_row(int row, const rgb_color *val)
{
    deactivate_rows();
    for (size_t i = 0; i < COLUMN_NUMBER; i++)
    {
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }
    activate_row(row);
    pulse_LAT();
}

/* Initialize all the values of the bank0 to 1 in order to use bank1 */
static void init_bank0()
{
    for (size_t i = 0; i < 8; i++)
    {
        send_byte(0xFF, 0);
        send_byte(0xFF, 0);
        send_byte(0xFF, 0);
    }
    pulse_LAT();
}

/* Test if the configuration is correct. It shows a sequence of red rows, then a red sequence
and a blue sequence of rows  */
void test_pixels()
{
    rgb_color a[ROW_NUMBER];
    rgb_color b[ROW_NUMBER];
    rgb_color c[ROW_NUMBER];

    for (int i = 0; i < ROW_NUMBER; i++)
    {
        a[i].r = 255 - i * 36;
        a[i].b = 0;
        a[i].g = 0;
    }

    for (int i = 0; i < ROW_NUMBER; i++)
    {
        b[i].r = 0;
        b[i].b = 255 - i * 36;
        b[i].g = 0;
    }

    for (int i = 0; i < ROW_NUMBER; i++)
    {
        c[i].r = 0;
        c[i].b = 0;
        c[i].g = 255 - i * 36;
    }

    matrix_init();
    for (int i = 0; i < ROW_NUMBER; i++)
    {
        mat_set_row(i, a);
        delay(300000);
    }
    delay(300000);
    deactivate_rows();
    for (int i = 0; i < ROW_NUMBER; i++)
    {
        mat_set_row(i, b);
        delay(300000);
    }
    delay(300000);
    deactivate_rows();
    for (int i = 0; i < ROW_NUMBER; i++)
    {
        mat_set_row(i, c);
        delay(300000);
    }
    delay(300000);
    deactivate_rows();
}

void test_image()
{

    rgb_color row[8];
    uint8_t *p = &_binary_image_raw_start;
    matrix_init();
    while (1)
    {
        p = &_binary_image_raw_start;
        for (int i = 0; i < ROW_NUMBER; i++)
        {
            for (int j = 0; j < COLUMN_NUMBER; j++)
            {
                row[j].r = *p;
                p++;
                row[j].g = *p;
                p++;
                row[j].b = *p;
                p++;
            }
            mat_set_row(i, row);
        }
    }
}