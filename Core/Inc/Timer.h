/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Timer.h
  * @brief   This file contains all the function prototypes for
  * the Timer.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
void Timer_Init(void);
void Timer_SetPeriod(uint32_t period_ms);
uint8_t Timer_HasElapsed(void);
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H__ */