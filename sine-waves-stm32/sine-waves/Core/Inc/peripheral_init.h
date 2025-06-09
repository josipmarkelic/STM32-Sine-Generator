#ifndef __PERIPHERAL_INIT_H
#define __PERIPHERAL_INIT_H

extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_dac1;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart4;

void peripheral_init();

#endif
