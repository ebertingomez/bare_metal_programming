#include "matrix.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

static void init_bank0(void);

static void deactivate_rows();

static void delay(int time)
{
    for (int i = 0; i < time; i++)
    {
        asm volatile("nop");
    }
}

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

static void pulse_SCK()
{
    SCK(0);
    delay(3);
    SCK(1);
    delay(3);
    SCK(0);
    delay(3);
}

static void pulse_LAT()
{
    LAT(1);
    delay(3);
    LAT(0);
    delay(3);
    LAT(1);
    delay(3);
}

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

static void mat_set_row(int row, const rgb_color *val)
{

    for (size_t i = 0; i < 8; i++)
    {
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }
    activate_row(row);
    pulse_LAT();
}

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

void test_pixels()
{
    rgb_color a[8];
    rgb_color b[8];
    rgb_color c[8];

    for (int i = 0; i < 8; i++)
    {
        a[i].r = 255 - i * 36;
        a[i].b = 0;
        a[i].g = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        b[i].r = 0;
        b[i].b = 255 - i * 36;
        b[i].g = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        c[i].r = 0;
        c[i].b = 0;
        c[i].g = 255 - i * 36;
    }

    matrix_init();
    for (int i = 0; i < 8; i++)
    {
        mat_set_row(i, a);
        delay(300000);
    }
    delay(200000);
    deactivate_rows();
    for (int i = 0; i < 8; i++)
    {
        mat_set_row(i, b);
        delay(300000);
    }
    delay(200000);
    deactivate_rows();
    for (int i = 0; i < 8; i++)
    {
        mat_set_row(i, c);
        delay(300000);
    }
    delay(200000);
    deactivate_rows();
}