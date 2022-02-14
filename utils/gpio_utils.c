#include <stdint.h>

#include "gpio_utils.h"



void config_GPIO(void)
{
    volatile uint32_t *gpio_direction = (volatile uint32_t *)0x02320010;
    *gpio_direction = 0xFFFCFFF; // = 1111 1111 1111 1100 1111 1111 1111, sets 12=GPIO_OUT_1 and 13=GPIO_OUT_2 as output pins
}

#if 0
void set_GPIO_out_to_1(int gpio_num)
{
    uint32_t *gpio_out_data = (uint32_t *)0x02320014;
    *gpio_out_data = 1 << gpio_num;
}

void set_GPIO_out_to_0(int gpio_num)
{
    uint32_t *gpio_out_data = (uint32_t *)0x02320014;
    *gpio_out_data = 0 << gpio_num;
}

int read_GPIO_in(int gpio_num)
{
    uint32_t *gpio_in_data = (uint32_t *)0x02320020;
    return (uint32_t)((*gpio_in_data >> gpio_num) & 3UL);
}

int read_GPIO_out(int gpio_num)
{
    uint32_t *gpio_out_data = (uint32_t *)0x02320014;
    return (uint32_t)((*gpio_out_data >> gpio_num) & 3UL);
}
#else
void set_GPIO_out_to_1(int gpio_num)
{
    volatile uint32_t *gpio_out_data = (volatile uint32_t *)0x02320014;
    *gpio_out_data |= 1UL << gpio_num;
}

void set_GPIO_out_to_0(int gpio_num)
{
    volatile uint32_t *gpio_out_data = (volatile uint32_t *)0x02320014;
    *gpio_out_data &= ~(1UL << gpio_num);
}

int read_GPIO_in(int gpio_num)
{
    volatile uint32_t *gpio_in_data = (volatile uint32_t *)0x02320020;
    return (uint32_t)((*gpio_in_data >> gpio_num) & 1);
}

int read_GPIO_out(int gpio_num)
{
    volatile uint32_t *gpio_out_data = (volatile uint32_t *)0x02320014;
    return (uint32_t)((*gpio_out_data >> gpio_num) & 1);
}
#endif


#if 1
void loopback_GPIO_2(void)
{
    config_GPIO();

    set_GPIO_out_to_0(GPIO_OUT_1);
    set_GPIO_out_to_0(GPIO_OUT_2);
    while (1) {
        int printed_statemachine_msg = 0;
        while (read_GPIO_in(GPIO_IN_1) != 1)
        {
            if (printed_statemachine_msg == 0) {
                printed_statemachine_msg = 1;
                //PCIE_logPrintf ("Waiting for GPIO_in %d==1 (=%d).\n", GPIO_IN_1, read_GPIO_in(GPIO_IN_1));
            }
        }
        set_GPIO_out_to_1(GPIO_OUT_1);

        if (read_GPIO_in(GPIO_IN_2) == 1) {
            set_GPIO_out_to_1(GPIO_OUT_2);
        } else {
            set_GPIO_out_to_0(GPIO_OUT_2);
        }
        //PCIE_logPrintf ("GPIO_in %d=%d.\n", GPIO_IN_2, read_GPIO_in(GPIO_IN_2));

        set_GPIO_out_to_0(GPIO_OUT_1);
    }
}
#else
void loopback_GPIO_2(void)
{
    config_GPIO();

    set_GPIO_out_to_0(GPIO_OUT_1);
    set_GPIO_out_to_0(GPIO_OUT_2);
    while (1) {
        if (read_GPIO_in(GPIO_IN_1) == 1) {
            set_GPIO_out_to_1(GPIO_OUT_1);
        } else {
            set_GPIO_out_to_0(GPIO_OUT_1);
        }
        PCIE_logPrintf ("GPIO_in %d=%d, GPIO_out %d=%d.\n",
                        GPIO_IN_1, read_GPIO_in(GPIO_IN_1),
                        GPIO_OUT_1, read_GPIO_out(GPIO_OUT_1));

        if (read_GPIO_in(GPIO_IN_2) == 1) {
            set_GPIO_out_to_1(GPIO_OUT_2);
        } else {
            set_GPIO_out_to_0(GPIO_OUT_2);
        }
        PCIE_logPrintf ("GPIO_in %d=%d, GPIO_out %d=%d.\n",
                        GPIO_IN_2, read_GPIO_in(GPIO_IN_2),
                        GPIO_OUT_2, read_GPIO_out(GPIO_OUT_2));
    }
}
#endif
