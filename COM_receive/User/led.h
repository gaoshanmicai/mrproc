#ifndef _LED_H
#define _LED_H

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<1)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<2)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<2)
//#define LED3_ON  LPC_GPIO1->DATA &= ~(1<<6)
//#define LED3_OFF LPC_GPIO1->DATA |= (1<<6)
//#define LED4_ON  LPC_GPIO1->DATA &= ~(1<<7)
//#define LED4_OFF LPC_GPIO1->DATA |= (1<<7)

void LED_ON(uint8_t val);
void led_init(void);
void delay(void);

#endif


