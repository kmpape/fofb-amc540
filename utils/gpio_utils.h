#ifndef GPIO_UTILS_H_
#define GPIO_UTILS_H_

#define GPIO_OUT_1  12 // used for READY
#define GPIO_OUT_2  13
#define GPIO_IN_1   14 // used for VALID
#define GPIO_IN_2   15

void config_GPIO(void);

void set_GPIO_out_to_1(int gpio_num);

void set_GPIO_out_to_0(int gpio_num);

int read_GPIO_in(int gpio_num);

int read_GPIO_out(int gpio_num);

#endif /* GPIO_UTILS_H_ */
