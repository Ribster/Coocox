#include "main.h"

GPIO_InitTypeDef GPIO_InitStruct;

static void SystemClock_Config(void);
void Error_Handler(void);

USBD_HandleTypeDef  USBD_Device;

int main(void)
{
	 /* This sample code shows how to use STM32F4xx GPIO HAL API to toggle PG6, PG7,
	    PG10, and PG12 IOs (connected to LED1, LED2, LED3 and LED4 on STM324x9I-EVAL board)
	    in an infinite loop.
	    To proceed, 3 steps are required: */

	  /* STM32F4xx HAL library initialization:
	       - Configure the Flash prefetch, instruction and Data caches
	       - Configure the Systick to generate an interrupt each 1 msec
	       - Set NVIC Group Priority to 4
	       - Global MSP (MCU Support Package) initialization
	     */
	  HAL_Init();

	  /* Configure the system clock to 180 MHz */
	  SystemClock_Config();

	  /* -1- Enable GPIOG Clock (to be able to program the configuration registers) */
	  __GPIOD_CLK_ENABLE();


	  /* -2- Configure PG.6, PG.7, PG10 and PG.12 IOs in output push-pull mode to
	         drive external LEDs */
	  GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);


	  /* Init Device Library */
	  USBD_Init(&USBD_Device, &VCP_Desc, 0);

	  /* Add Supported Class */
	  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);

	  /* Add CDC Interface Class */
	  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);

	  /* Start Device Process */
	  USBD_Start(&USBD_Device);

	  char sendString[] = "I'm sending this string, yay!\r\n";

	  /* -3- Toggle PG.6, PG.7, PG10 and PG.12 IOs in an infinite loop */
	  while (1)
	  {
	    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
	    /* Insert delay 100 ms */
	    HAL_Delay(100);
	    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	    /* Insert delay 100 ms */
	    HAL_Delay(100);
	    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	    /* Insert delay 100 ms */
	    HAL_Delay(100);
	    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	    /* Insert delay 100 ms */
	    HAL_Delay(100);
	    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	    /* Insert delay 100 ms */
	    HAL_Delay(100);

	    CDC_Itf_Send(sendString, strlen(sendString));
	  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

void Error_Handler(void){

}
