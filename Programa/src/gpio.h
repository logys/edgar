//gpio.h
#ifndef GPIO_H
#define GPIO_H

typedef enum {INPUT, OUTPUT} DIRECTION;
typedef enum {LOW, HIGH} LEVEL;

void gpio_setDirection(short const pin, DIRECTION);
void gpio_setLevel(short const pin, LEVEL);

#endif // GPIO_H
