#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <string.h>
#include "Touchpad.h"
#include "Timer.h"

static void Configure_GPIO_Pins(GPIO_InitTypeDef* GPIO_InitStruct, GPIO_TypeDef* pinType, uint32_t pinNumber, int IO);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
