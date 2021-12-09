/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
  volatile uint32_t debounce = 0;
  volatile uint32_t mid_bounce = 0;
  volatile uint32_t bottom_bounce = 0;
 volatile uint32_t refresh = 0;
 volatile uint32_t update_screen;
 volatile uint32_t middle_pressed=0;
 volatile uint32_t left_pressed = 0;
 volatile uint32_t right_pressed = 0;
 volatile uint32_t top_pressed = 0;
 volatile uint32_t bottom_pressed = 0;
 extern uint16_t startup;
 volatile uint32_t ball_speed;
volatile uint16_t col_count = 0;
extern uint8_t x_ball;
extern uint8_t y_ball;
extern uint8_t y_bat;
extern uint8_t x_bat;
extern int col_pos;
extern void move_col();
extern void move_row_bat();
extern void move_row_ball();
extern void update_ball_pos();
extern void print_maze();
extern void move_mazex();
extern void move_mazey();
extern void maze_end();
extern uint8_t mazex;
extern uint8_t mazey;
extern uint32_t tennis;
uint32_t player_refresh=0;
uint32_t end_refresh=0;
uint32_t ball_count = 0;
extern uint16_t play2;
uint32_t test_count=0;
uint8_t visible_ball;
uint8_t visible_goal;
uint8_t velocity;
uint32_t UART_maze;
uint32_t UART_tennis;
uint32_t tennis_refresh=0;
extern uint8_t maze_selected;

extern uint32_t hit_count;
extern uint8_t maze_menu;


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	col_count++;

	test_count++;
	if(startup==0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);

	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);

	debounce++;
	refresh++;

	if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 0) & ((debounce > 99))){
			left_pressed = 1;
			debounce = 0;
	}

	if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0) & ((debounce > 99))){
			right_pressed = 1;
			debounce = 0;
	}

	if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0) & ((debounce > 99))){
			top_pressed = 1;
			debounce = 0;
	}

	if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0) & ((debounce > 99))){
			bottom_pressed = 1;
			debounce = 0;
	}
	}


	if(col_count == 8){
		col_count = 0;
	}

	if(startup == 0)
	{

	if(tennis == 1)
	{
		player_refresh++;
		tennis_refresh++;
		if((tennis_refresh==100)){
			UART_tennis = 1;
			tennis_refresh = 0;
		}
		if(hit_count == 3){
			ball_speed = ball_speed - 50;
			velocity++;
			hit_count = 0;
		}
		for(int  i=0; i<8; i++)
		{
			if(col_count == i)
			{
				if(x_ball == i)
				{
					col_pos = i;
					move_col();
					move_row_ball();
				}
				if(x_bat == i)
				{
					col_pos = i;
					move_col();
					move_row_bat();
				}
			}
		}
		if(ball_count > ball_speed)
		{
		update_ball_pos();
		ball_count=0;
		}
		ball_count++;
	}



	if(play2 == 1)
	{
		//print_maze();
		if(maze_selected == 1)
		{
			player_refresh++;
			end_refresh++;
			if((player_refresh==300) | (player_refresh == 600)){
				UART_maze = 1;
			}

			if(end_refresh >= 100)
			{
				maze_end();
				if(end_refresh >= 200)
				{
					end_refresh=0;
				}
			}

			print_maze();
			for(int  i=0; i<8; i++)
			{
				if(col_count == i)
				{
					if((mazex == i) & (player_refresh >= 300))
					{
						col_pos = i;
						if(player_refresh >= 600)
						{
						player_refresh = 0;
						}

						move_mazex();
					    move_mazey();
					}
				}
			}

			if(player_refresh >= 300)
			{
				visible_ball = 1;
			}else{
				visible_ball = 0;
			}

			if(end_refresh <= 100)
			{
				visible_goal = 0;
			}else{
				visible_goal = 1;
			}

		}else{
			print_maze();
		}

		}
	}











  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
	mid_bounce++;
	if((debounce>100) & (startup == 0)){
	middle_pressed = 1;
	debounce=0;
	mid_bounce = 0;
	}
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
