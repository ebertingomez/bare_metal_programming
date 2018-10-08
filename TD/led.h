#define REG (*(volatile uint32_t *)0xff00ff00)
enum state
{
    LED_OFF = 0,
    LED_YELLOW = 1,
    LED_BLUE = 2
};

void led_init(void);
void led_g_on();
void led_g_off();
void led(state);