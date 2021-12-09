/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
volatile uint32_t LED_col = 0b00010000;
volatile uint32_t LED_row = 0b00010000;
volatile int row_pos;
volatile int col_pos;
volatile uint8_t x_ball =7;
volatile uint8_t y_ball =4;
volatile uint8_t y_bat = 4;
volatile uint8_t x_bat = 0;
volatile uint16_t play2 = 0;
volatile uint16_t maze = 0;
volatile uint8_t mazex;
volatile uint8_t mazey;
extern uint8_t refresh;
char outstr[1000];
uint32_t outlen;
uint16_t startup;
volatile uint32_t tennis;
extern uint32_t ball_speed;
extern uint32_t hit_count;

extern uint32_t left_pressed;
extern uint32_t right_pressed;
extern uint32_t middle_pressed;
extern uint32_t update_screen;
extern uint32_t top_pressed;
extern uint32_t bottom_pressed;
extern uint8_t dir;
extern _Bool maze1;
extern uint8_t visible_ball;
extern uint8_t visible_goal;
extern uint8_t velocity;
extern uint32_t debounce;
extern uint32_t UART_maze;
extern uint32_t UART_tennis;
extern uint32_t player_refresh;
extern uint32_t end_refresh;
uint8_t maze_selected = 0;
_Bool temp_maze[8][8];
uint8_t maze_menu = 0;
uint8_t maze_number = 0;
uint8_t end_posx;
uint8_t end_posy;

int16_t vx;
int16_t vy;
uint8_t i2cdata[10];
int res;
char imu;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
void configure(void);
void menu(void);
void move_col(void);
void print_maze();
void moveball(void);
void move_row_bat(void);
void move_row_ball(void);
void slideball(uint16_t adc);
void move_mazex(void);
void move_mazey(void);
void updown(void);
void leftright(void);
void ten_updown(void);
void ten_leftright(void);
void accel_x(void);
void accel_y(void);
void I2C(void);
void maze_acc_x(void);
void maze_acc_y(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
_Bool maze1main[8][8] = {{0,0,0,0,0,0,1,0},
					     {1,1,0,1,1,0,0,0},
					     {0,0,0,0,0,0,1,0},
					     {0,1,1,1,1,1,0,1},
					     {0,0,0,0,1,0,0,0},
					     {1,1,0,1,1,0,1,0},
					     {0,0,0,1,0,0,1,0},
					     {0,1,0,0,0,1,1,0}};

_Bool maze2main[8][8] = {{0,0,0,0,0,0,0,0},
						 {0,1,0,1,0,1,1,0},
					     {0,0,1,0,1,0,0,0},
					     {0,1,0,0,0,0,1,1},
					     {0,0,1,1,1,1,0,0},
					     {1,0,1,0,0,1,1,0},
					     {0,0,1,0,0,0,1,0},
					     {0,0,0,0,1,0,0,0}};

_Bool maze3main[8][8] = {{0,0,0,1,1,0,0,0},
					     {0,1,0,0,1,0,1,0},
					     {0,0,1,0,1,0,1,0},
					     {1,0,1,0,0,0,1,0},
					     {0,0,1,0,1,1,1,0},
					     {0,1,0,0,1,0,0,0},
					     {0,1,0,1,1,0,1,1},
					     {0,0,0,0,1,0,0,0}};

_Bool maze4main[8][8] = {{0,1,0,1,0,0,0,0},
					     {0,1,0,0,0,1,1,0},
					     {0,1,1,1,1,0,0,0},
					     {0,1,0,0,1,0,1,0},
					     {0,1,0,1,0,0,1,0},
					     {0,0,0,0,0,1,0,0},
					     {1,1,1,1,1,1,0,1},
					     {0,0,0,0,0,0,0,0}};

_Bool temp_maze[8][8];


void slideball(uint16_t adc)
{
	if(adc > 3900)
	{
		row_pos=0;
		mazey=y_bat=0;

	}else if(adc > 3400){
			row_pos=1;
			y_bat=1;
	}else if(adc > 2900){
			row_pos=2;
			y_bat=2;
	}else if(adc > 2400){
			row_pos=3;
			y_bat=3;
	}else if(adc > 1900){
			row_pos=4;
			y_bat=4;
	}else if(adc > 1400){
			row_pos=5;
			y_bat=5;
	}else if(adc > 900){
			row_pos=6;
			y_bat=6;
	}else if(adc > 10){
			row_pos=6;
			y_bat=6;
		}
}

void accel_x(){
	if(vx < -5000)
	{
		imu = 'L';
		  if(x_bat>0)
		{
		  x_bat--;
		  col_pos--;
		 }
	}

	if(vx > 5000)
	{
		imu = 'R';
		 if(x_bat < 7)
		  {
		  x_bat++;
		  col_pos++;
		  }
	}
}
void accel_y(){
	if(vy < -5000)
	{
		imu = 'U';
		  if(y_bat > 0)
		{
		  y_bat--;
		//  col_pos--;
		 }
	}

	if(vy > 5000)
	{
		imu = 'D';
		 if(y_bat < 6)
		  {
		  y_bat++;
	//	  col_pos++;
		  }
	}
}

void ten_updown(){
	  if((top_pressed == 1))
	  {
		  debounce = 0;
		  if(y_bat > 0)
		  {
		  y_bat--;
		  }
		  top_pressed = 0;
	  }else if(top_pressed == 1){
		  debounce = 0;
		  top_pressed = 0;
	  }

	  if(bottom_pressed == 1)
	  {
		  if(y_bat < 7 )
		  {
		  y_bat++;
		  }
		  bottom_pressed = 0;
		  debounce=0;
	  }
}
void ten_leftright(){
	  if(left_pressed == 1)
	  {
		  if(x_bat>0)
	      {
		  x_bat--;
		  col_pos--;
		  }
		  left_pressed = 0;
		  debounce = 0;
	  }

	  if(right_pressed == 1)
	  {
		 if(x_bat < 7)
		  {
		  x_bat++;
		  col_pos++;
		  }
		  right_pressed = 0;
		  debounce=0;
	  }

}


void updown(){
	  if((top_pressed == 1) & ((mazex > 3) | (mazey >= 1)))
	  {
		  debounce = 0;
		  if((mazey > 0) & ((temp_maze[mazey-1][mazex] == 0)))
		  {
		  mazey--;
		  }
		  top_pressed = 0;
	  }else if(top_pressed == 1){
		  debounce = 0;
		  top_pressed = 0;
	  }

	  if(bottom_pressed == 1)
	  {
		  if((mazey < 7 ) & ((temp_maze[mazey+1][mazex] == 0)))
		  {
		  mazey++;
		  }
		  bottom_pressed = 0;
		  debounce=0;
	  }
}

void leftright(){
	  if(left_pressed == 1)
	  {
		  if((mazex>0) & (temp_maze[mazey][mazex-1] == 0))
	      {
		  mazex--;
		  }
		  left_pressed = 0;
		  debounce = 0;
	  }

	  if(right_pressed == 1)
	  {// if(col_pos < 7)
		 if((mazex < 7) & (temp_maze[mazey][mazex+1] == 0))
		  {
		  mazex++;
		  }
		  right_pressed = 0;
		  debounce=0;
	  }

}

void I2C(){

	  i2cdata[0] = 0xA8;
	  HAL_I2C_Master_Transmit(&hi2c1, 0x30, i2cdata, 1, 10);
	  HAL_I2C_Master_Receive(&hi2c1, 0x30, i2cdata, 6, 10);
	//  HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout)
	  vy = *((int16_t*) i2cdata);
	  vx = *((int16_t*) (i2cdata + 2));

}

void maze_acc_x(void){
	  if(vx < -5000)
	  {
		  imu = 'L';
		  if((mazex>0) & (temp_maze[mazey][mazex-1] == 0))
	      {
		  mazex--;
		  }
	  }

	  if(vx > 5000)
	  {
		  imu = 'R';
		 if((mazex < 7) & (temp_maze[mazey][mazex+1] == 0))
		  {
		  mazex++;
		  }
	  }

}

void maze_acc_y(void){
	  if((vy < -5000) & ((mazex > 3) | (mazey >= 1)))
	  {
		  imu = 'U';
		  if((mazey > 0) & ((temp_maze[mazey-1][mazex] == 0)))
		  {
		  mazey--;
		  }
	  }
	  if(vy > 5000)
	  {
		  imu = 'D';
		  if((mazey < 7 ) & ((temp_maze[mazey+1][mazex] == 0)))
		  {
		  mazey++;
		  }
	  }
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
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  startup=1;
  	i2cdata[0] = 0x20;
    i2cdata[1] = 0x47;
    res = HAL_I2C_Master_Transmit(&hi2c1, 0x30, i2cdata, 2, 10);

    if(res == HAL_OK)
    {
    	outlen = sprintf(outstr, "good_____\n");
    	HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
    }else if(res == HAL_ERROR){
    	outlen = sprintf(outstr, "error_____\n");
    	HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
    }else if(res == HAL_BUSY){
    	outlen = sprintf(outstr, "busy_____\n");
    	HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
    }else if(res == HAL_TIMEOUT){
    	outlen = sprintf(outstr, "timeout___\n");
    	HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
    }

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);  //1
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);  //2
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);  //3
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);  //4


  configure();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  //1
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  //2
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  //3
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);  //4

	 // I2C();
	  menu();
	  //outlen = sprintf(outstr, "x = %d, y =%d\n", vx,vy);
	 // HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);

	  if(middle_pressed == 1){
		  x_ball =7;
		  y_ball =4;
		  dir = 0;
		  tennis = 1;
		  middle_pressed = 0;
		  ball_speed = 700;
		  hit_count = 0;
		  velocity = 1;
		  col_pos=0;
		  row_pos=4;
	  }

	  if(left_pressed == 1){

		  play2 = 1;
		  left_pressed = 0;
		  maze_number=1;
	  }

	  		  while(play2 == 1)
	  	{
	  			 while(maze_selected == 0)
	  				  {
	  				 	 switch(maze_number)
	  				 	 {
	  				 	 case 1:
								  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);  //1
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  //2
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  //3
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);  //4
						 break;
	  				 	 case 2:
	  				 	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  //1
	  				 		  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);  //2
	  							  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  //3
	  	     					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);  //4
						 break;
	  				 	 case 3:
								  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  //1
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  //2
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);  //3
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);  //4
	  				     break;
	  				 	 case 4:
								  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  //1
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);  //2
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  //3
								  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);  //4
	  				     break;
	  				 	 }
	  				 	 	 maze_menu = 1;
	  					  	  if((top_pressed == 1) & (maze_number < 4))
	  					  	  {
	  					  		  top_pressed = 0;
	  					  		 maze_number++;
	  					  	  }
	  					  	  if((bottom_pressed == 1) & (maze_number > 1))
	  					  	  {
	  					  		 bottom_pressed = 0;
	  					  		 maze_number--;
	  					  	  }

	  					  	  if(middle_pressed == 1)
	  					  	  {
	  					  		  middle_pressed = 0;
	  					  		  maze_selected = 1;
	  							  player_refresh=0;
	  							  end_refresh=0;
	  							  visible_ball = 1;
	  							  visible_goal = 1;
	  							  mazex=0;
	  							  mazey=0;
	  							  switch(maze_number)
	  							  {
	  							  case 1:
	  							   end_posx = 7;
	  							   end_posy = 7;
								  	  for(int i = 0; i<8; i++)
								  	  {
								  		  for(int j=0;j<8;j++)
								  		  {
	  									  temp_maze[i][j] = maze1main[i][j];
								  		  }
								  	  }
								  	  break;

	  							  case 2:
	  							    end_posx = 3;
	  			  				    end_posy = 3;
	  								  for(int i = 0; i<8; i++)
							  	      {
	  									  for(int j=0;j<8;j++)
							  		      {
	  								      temp_maze[i][j] = maze2main[i][j];
							  		      }
							  	      }
	  								  break;

	  							  case 3:
	  							     end_posx = 7;
	  			  				     end_posy = 7;
	  								  for(int i = 0; i<8; i++)
							  	      {
	  									  for(int j=0;j<8;j++)
							  		      {
	  								      temp_maze[i][j] = maze3main[i][j];
							  		      }
							  	      }
	  								  break;

	  							  case 4:
	  						        end_posx = 2;
	  			  				    end_posy = 0;
	  								  for(int i = 0; i<8; i++)
							  	      {
	  									  for(int j=0;j<8;j++)
							  		      {
	  								      temp_maze[i][j] = maze4main[i][j];
							  		      }
							  	      }
	  								  break;
	  							  }
	  					  	  }
	  				  }


	  		while(maze_selected == 1)
	  		{
	  		    HAL_ADC_Start(&hadc1);
	  		    HAL_ADC_PollForConversion(&hadc1, 10);

	  		    HAL_Delay(10);

	  			updown();
	  			leftright();

	  			if(middle_pressed == 1)
	  			{
	  				play2 = 0;
	  				middle_pressed = 0;
	  				menu();
	  				maze_selected=0;
	  			}
	  			if((mazex == end_posx) & (mazey == end_posy))
	  			{
	  				play2 = 0;
	  				maze_selected = 0;
	  				menu();
	  			}
	  			if(UART_maze == 1)
	  			{
					I2C();
					maze_acc_x();
					maze_acc_y();
						if((vx<5000) & (vx>-5000) & (vy<5000) & (vy > -5000)){
							imu = 'N';
						}
					outlen = sprintf(outstr, "$3%d%d%d%d%c__\n", mazex, mazey, visible_ball, visible_goal, imu);
					HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
					update_screen = 0;
					UART_maze = 0;
	  			}
	  		}
	  	}

	  		  while(tennis == 1)
	  	{

	  			//  I2C();
	  		//	  uint16_t adcval = HAL_ADC_GetValue(&hadc1);
	  			//slideball(adcval);
	  			  ten_updown();

	  			  ten_leftright();

	  			if(middle_pressed == 1)
	  			{
	  				tennis = 0;
	  				middle_pressed = 0;
	  				menu();
	  			}

	  					if(UART_tennis == 1){
	  						I2C();
	  						accel_y();
	  						accel_x();
	  						if((vx<5000) & (vx>-5000) & (vy<5000) & (vy > -5000)){
	  							imu = 'N';
	  						}
	  					outlen = sprintf(outstr, "$2%d%d%d%d%d%d%c\n", x_ball, y_ball, velocity, dir, x_bat, y_bat, imu);
	  				//	outlen = sprintf(outstr, "x = %d,y =%d\n", vx,vy);
	  					HAL_UART_Transmit(&huart2, (uint8_t*)outstr, outlen, 10);
	  					UART_tennis = 0;
	  					}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4 
                          |GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA6 PA7 PA9 
                           PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 PC6 PC7 
                           PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB11 PB12 
                           PB13 PB14 PB15 PB4 
                           PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_4 
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
