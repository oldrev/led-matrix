/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>

#include "devices/devices.h"
#include "settings.h"
#include "comm.h"
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
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi2_tx;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

osThreadId defaultTaskHandle;
osThreadId displayTaskHandle;
osMessageQId g_cmdBusHandle;
/* USER CODE BEGIN PV */

Display g_display[1];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void TaskProc_Default(void const * argument);
void TaskProc_Display(void const * argument);

/* USER CODE BEGIN PFP */
static int MsgProc_System_Reset(const Comm_RemoteHeader* header, const void* args);
static int MsgProc_System_Hello(const Comm_RemoteHeader* header, const void* args);
static int MsgProc_Display_Fill(const Comm_RemoteHeader* header, const void* args);
static int MsgProc_Display_SetPixel(const Comm_RemoteHeader* header, const void* args);
static int MsgProc_Display_SetPixelXY(const Comm_RemoteHeader* header, const void* args);
static int MsgProc_Config_DisplaySettings(const Comm_RemoteHeader* header, const void* args);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static int MsgProc_System_Reset(const Comm_RemoteHeader* header, const void* args) {
    HAL_NVIC_SystemReset();
    return 0;
}


static int MsgProc_System_Hello(const Comm_RemoteHeader* header, const void* args) {
    if(Comm_ReplyPackage(header->ID, header->Type, args, header->Size - COMM_REMOTE_PACKAGE_HEADER_SIZE) != 0) {
        return -1;
    }
    return 0;
}

static int MsgProc_Display_Fill(const Comm_RemoteHeader* header, const void* args) {
    const uint8_t* pColorIndex = (const uint8_t*)args;
    if(Display_Fill(&g_display[0], *pColorIndex) != 0) {
        return -1;
    }
    return 0;
}


static int MsgProc_Display_SetPixel(const Comm_RemoteHeader* header, const void* args) {
    const uint8_t* buf = (const uint8_t*)args;
    const uint16_t* pixelIndex = (const uint16_t*)buf;
    const uint8_t* colorIndex = buf + 2;
    if(Display_SetPixel(&g_display[0], *pixelIndex, *colorIndex) != 0) {
        return -1;
    }
    return 0;
}


static int MsgProc_Display_SetPixelXY(const Comm_RemoteHeader* header, const void* args) {
    const uint8_t* buf = (const uint8_t*)args;
    const uint16_t* x = (const uint16_t*)buf;
    const uint16_t* y = (const uint16_t*)(buf + 2);
    const uint8_t* colorIndex = buf + 4;
    if(Display_SetPixelXY(&g_display[0], *x, *y, *colorIndex) != 0) {
        return -1;
    }
    return 0;
}


static int MsgProc_Config_DisplaySettings(const Comm_RemoteHeader* header, const void* args) {
    const uint8_t* buf = (const uint8_t*)args;
    AppSettings settings;
    // 从 Flash 取出现有设置到临时变量
    memcpy(&settings, (const void*)Settings_Get(), sizeof(AppSettings));
    // 执行显示设置修改
    settings.DisplaySettings.LedCount = *((const uint16_t*)buf);
    settings.DisplaySettings.XMax = (*(const uint16_t*)(buf + 2));
    settings.DisplaySettings.YMax = (*(const uint16_t*)(buf + 4));
    settings.DisplaySettings.XSkip = (*(const uint16_t*)(buf + 6));
    settings.DisplaySettings.YSkip = (*(const uint16_t*)(buf + 8));
    // 设置调色板
    uint16_t bytesIndex = 0;
    const uint8_t* paletteBytes = buf + 10;
    for(uint16_t i = 0; i < PALETTE_SIZE; i ++) {
        settings.DisplaySettings.Palette[i].Red = paletteBytes[bytesIndex];
        settings.DisplaySettings.Palette[i].Green = paletteBytes[bytesIndex + 1];
        settings.DisplaySettings.Palette[i].Blue = paletteBytes[bytesIndex + 2];
        bytesIndex += 3;
    }
    // 保存设置
    Settings_Save(&settings);
    // 返回响应
    uint8_t responseArgs = 0;
    if(Comm_ReplyPackage(header->ID, header->Type, &responseArgs, 1) != 0) {
        return -1;
    }
    // 执行重启
    HAL_NVIC_SystemReset();
    return 0;
}

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
    
    // 初始化指示灯
    Indicator_Init();
    Indicator_TurnOn(0);

    //初始化设置
    Settings_Init();
    if(Settings_IsFirstBoot()) {
        Settings_Restore();
    }

    //初始化蓝牙模�????????
    if (JDY08_Init(&huart2, &hdma_usart2_rx) != 0) {
        Error_Handler();
    }

    // 初始化显示模�????????
    if (Display_Init(&g_display[0], &Settings_Get()->DisplaySettings, &hspi1) != 0) {
        Error_Handler();
    }

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of g_cmdBus */
  osMessageQDef(g_cmdBus, 2, 512);
  g_cmdBusHandle = osMessageCreate(osMessageQ(g_cmdBus), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, TaskProc_Default, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of displayTask */
  osThreadDef(displayTask, TaskProc_Display, osPriorityIdle, 0, 128);
  displayTaskHandle = osThreadCreate(osThread(displayTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Enables the Clock Security System 
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BLE_ATCMD_GPIO_Port, BLE_ATCMD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BLE_PWRC_Pin|DBG_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BLE_STAT_Pin */
  GPIO_InitStruct.Pin = BLE_STAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BLE_STAT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BLE_ATCMD_Pin */
  GPIO_InitStruct.Pin = BLE_ATCMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BLE_ATCMD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BLE_PWRC_Pin DBG_LED_Pin */
  GPIO_InitStruct.Pin = BLE_PWRC_Pin|DBG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_TaskProc_Default */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskProc_Default */
void TaskProc_Default(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN 5 */
    // 初始化�?�讯模块
    if(Comm_Init(g_cmdBusHandle) != 0) {
        Error_Handler();
    }

    osEvent event;
    /* Infinite loop */
    for (;;) {
        osThreadYield();
        event = osMessageGet(g_cmdBusHandle, osWaitForever); // wait for message
        if (event.status == osEventMessage) {
            // 解析�??
            Comm_RemoteHeader header = { 0 };
            Comm_ParsePackageHeader(event.value.p, &header);
            const uint8_t* arguments = ((const uint8_t*)event.value.p) + COMM_REMOTE_PACKAGE_HEADER_SIZE;
            switch (header.Type) {
                case MESSAGE_SYSTEM_RESET: MsgProc_System_Reset(&header, arguments); break;
                case MESSAGE_DISPLAY_FILL: MsgProc_Display_Fill(&header, arguments); break;
                case MESSAGE_DISPLAY_SET_PIXEL: MsgProc_Display_SetPixel(&header, arguments); break;
                case MESSAGE_DISPLAY_SET_PIXELXY: MsgProc_Display_SetPixelXY(&header, arguments); break;
                case MESSAGE_CONFIG_DISPLAY: MsgProc_Config_DisplaySettings(&header, arguments); break;
                default: break;
            }
        }
    }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_TaskProc_Display */
/**
 * @brief Function implementing the displayTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TaskProc_Display */
void TaskProc_Display(void const * argument)
{
  /* USER CODE BEGIN TaskProc_Display */
    uint32_t indicatorTimer = 0;
    uint32_t displayTimer = 0;
    /* Infinite loop */
    for (;;) {
        osThreadYield();
        // 刷新显示
        if (HAL_GetTick() - displayTimer >= 20) {
            Display_Update(&g_display[0]);
            displayTimer = HAL_GetTick();
        }

        // 已连接则指示灯每 300ms 闪烁�?????????次，未连接则 1500ms 闪烁�?????????�?????????
        uint32_t indicatorInterval = JDY08_IsConnected() ? 300 :
                    1500;
                    if (HAL_GetTick() - indicatorTimer >= indicatorInterval) {
                        Indicator_TurnOnInPeriod(0, 50);
                        indicatorTimer = HAL_GetTick();
        }

        Indicator_Drive();
    }
  /* USER CODE END TaskProc_Display */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    //打开指示灯常亮，然后卡在这里
    Indicator_TurnOn(0);
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
    /* User can add his own implementation to report the file name and line
       number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
     */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
