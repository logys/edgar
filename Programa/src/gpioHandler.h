#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

enum DIRECTION{INPUT, OUTPUT};
enum LEVEL{LOW, HIGH};

short const pinToGpio(short const pin);
void gpio_setDirection(short const pin, DIRECTION);
void gpio_setLevel(short const pin, LEVEL);

#endif// GPIO_HANDLER_H
