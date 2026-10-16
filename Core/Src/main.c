/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Timer.h"
#include "UART.h"
#include "LED.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
typedef enum {
    MODO_ENCENDIDO = 0,
    MODO_APAGADO,
    MODO_PARPADEO_500MS,
    MODO_PARPADEO_200MS,
    MODO_PARPADEO_100MS
} SystemMode_t;

static SystemMode_t modo_actual = MODO_ENCENDIDO;
static uint32_t tiempo_ultimo_cambio = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void AplicarModo(SystemMode_t modo);
static void EnviarEstado(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  LED_Init();
  Timer_Init();
  UART_Init();

  AplicarModo(modo_actual);
  EnviarEstado();
  tiempo_ultimo_cambio = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if ((modo_actual >= MODO_PARPADEO_500MS) && Timer_HasElapsed())
    {
        LED_Toggle();
        EnviarEstado();
    }

    if ((HAL_GetTick() - tiempo_ultimo_cambio) >= 5000U)
    {
        tiempo_ultimo_cambio = HAL_GetTick();

        switch (modo_actual)
        {
            case MODO_ENCENDIDO:
                modo_actual = MODO_APAGADO;
                break;
            case MODO_APAGADO:
                modo_actual = MODO_PARPADEO_500MS;
                break;
            case MODO_PARPADEO_500MS:
                modo_actual = MODO_PARPADEO_200MS;
                break;
            case MODO_PARPADEO_200MS:
                modo_actual = MODO_PARPADEO_100MS;
                break;
            case MODO_PARPADEO_100MS:
            default:
                modo_actual = MODO_ENCENDIDO;
                break;
        }
        AplicarModo(modo_actual);
        EnviarEstado();
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void AplicarModo(SystemMode_t modo)
{
    switch (modo)
    {
        case MODO_ENCENDIDO:
            LED_On();
            break;
        case MODO_APAGADO:
            LED_Off();
            break;
        case MODO_PARPADEO_500MS:
            LED_Off();
            Timer_SetPeriod(500);
            break;
        case MODO_PARPADEO_200MS:
            LED_Off();
            Timer_SetPeriod(200);
            break;
        case MODO_PARPADEO_100MS:
            LED_Off();
            Timer_SetPeriod(100);
            break;
        default:
            LED_Off();
            break;
    }
}

static void EnviarEstado(void)
{
    switch (modo_actual)
    {
        case MODO_ENCENDIDO:
            UART_SendString("Estado: LED ENCENDIDO\r\n");
            break;
        case MODO_APAGADO:
            UART_SendString("Estado: LED APAGADO\r\n");
            break;
        case MODO_PARPADEO_500MS:
            UART_SendString("Estado: LED PARPADEANDO, periodo 500 ms\r\n");
            break;
        case MODO_PARPADEO_200MS:
            UART_SendString("Estado: LED PARPADEANDO, periodo 200 ms\r\n");
            break;
        case MODO_PARPADEO_100MS:
            UART_SendString("Estado: LED PARPADEANDO, periodo 100 ms\r\n");
            break;
        default:
            UART_SendString("Estado: modo desconocido\r\n");
            break;
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
