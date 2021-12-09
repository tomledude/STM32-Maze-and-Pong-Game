#include "main.h"
#include <stdio.h>
//extern _Bool maze1;
extern uint16_t col_count;
uint8_t ptr_maze;
extern uint8_t maze_number;
extern uint8_t maze_selected;
void print_maze(){



	_Bool maze1[8][8] =  {{0,0,0,0,0,0,1,0},
						  {1,1,0,1,1,0,0,0},
						  {0,0,0,0,0,0,1,0},
						  {0,1,1,1,1,1,0,1},
						  {0,0,0,0,1,0,0,0},
						  {1,1,0,1,1,0,1,0},
						  {0,0,0,1,0,0,1,0},
						  {0,1,0,0,0,1,1,0}};

	_Bool maze2[8][8] = {{0,0,0,0,0,0,0,0},
						 {0,1,0,1,0,1,1,0},
						 {0,0,1,0,1,0,0,0},
						 {0,1,0,0,0,0,1,1},
						 {0,0,1,1,1,1,0,0},
						 {1,0,1,0,0,1,1,0},
						 {0,0,1,0,0,0,1,0},
						 {0,0,0,0,1,0,0,0}};

	_Bool maze3[8][8] = {{0,0,0,1,1,0,0,0},
						 {0,1,0,0,1,0,1,0},
						 {0,0,1,0,1,0,1,0},
						 {1,0,1,0,0,0,1,0},
						 {0,0,1,0,1,1,1,0},
						 {0,1,0,0,1,0,0,0},
						 {0,1,0,1,1,0,1,1},
						 {0,0,0,0,1,0,0,0}};

	_Bool maze4[8][8] = {{0,1,0,1,0,0,0,0},
						 {0,1,0,0,0,1,1,0},
						 {0,1,1,1,1,0,0,0},
						 {0,1,0,0,1,0,1,0},
						 {0,1,0,1,0,0,1,0},
						 {0,0,0,0,0,1,0,0},
						 {1,1,1,1,1,1,0,1},
						 {0,0,0,0,0,0,0,0}};

 	_Bool one[8][8]  =  {{0,0,0,0,0,0,0,0},
 						 {0,0,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,0,0,0,0,0,0}};

 	_Bool two[8][8] =   {{0,0,0,0,0,0,0,0},
 						 {0,0,0,1,1,0,0,0},
						 {0,0,1,0,0,1,0,0},
						 {0,0,0,0,0,1,0,0},
						 {0,0,0,0,1,0,0,0},
						 {0,0,0,1,0,0,0,0},
						 {0,0,1,1,1,1,1,0},
						 {0,0,0,0,0,0,0,0}};

 	_Bool three[8][8] = {{0,0,0,0,0,0,0,0},
 					     {0,0,1,1,0,0,0,0},
						 {0,0,0,0,1,0,0,0},
						 {0,0,1,1,0,0,0,0},
						 {0,0,0,0,1,0,0,0},
						 {0,0,0,0,1,0,0,0},
 					     {0,0,1,1,0,0,0,0},
						 {0,0,0,0,0,0,0,0}};

 	_Bool four[8][8] =  {{0,0,0,0,0,0,0,0},
 					     {0,0,0,0,0,0,1,0},
						 {0,0,0,0,0,1,0,0},
						 {0,0,0,0,1,0,0,0},
						 {0,0,0,1,0,1,0,0},
						 {0,0,1,1,1,1,1,0},
						 {0,0,0,0,0,1,0,0},
 					     {0,0,0,0,0,0,0,0}};



	//col

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);

	  //row
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);


	switch(col_count)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		break;
	}


	if(maze_selected == 0){
			if(maze_number == 1)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, one[0][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, one[1][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, one[2][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, one[3][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, one[4][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, one[5][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, one[6][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, one[7][col_count]);
			}else if(maze_number == 2)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, two[0][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, two[1][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, two[2][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, two[3][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, two[4][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, two[5][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, two[6][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, two[7][col_count]);
			}else if(maze_number == 3)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, three[0][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, three[1][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, three[2][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, three[3][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, three[4][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, three[5][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, three[6][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, three[7][col_count]);
			}else if(maze_number == 4)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, four[0][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, four[1][col_count]);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, four[2][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, four[3][col_count]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, four[4][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, four[5][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, four[6][col_count]);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, four[7][col_count]);
			}
	}else if(maze_selected == 1){
		if(maze_number == 1)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, maze1[0][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, maze1[1][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, maze1[2][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, maze1[3][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, maze1[4][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, maze1[5][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, maze1[6][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, maze1[7][col_count]);
				}else if(maze_number == 2)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, maze2[0][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, maze2[1][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, maze2[2][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, maze2[3][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, maze2[4][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, maze2[5][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, maze2[6][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, maze2[7][col_count]);
				}else if(maze_number == 3)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, maze3[0][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, maze3[1][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, maze3[2][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, maze3[3][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, maze3[4][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, maze3[5][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, maze3[6][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, maze3[7][col_count]);
				}else if(maze_number == 4)
				{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, maze4[0][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, maze4[1][col_count]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, maze4[2][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, maze4[3][col_count]);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, maze4[4][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, maze4[5][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, maze4[6][col_count]);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, maze4[7][col_count]);
				}
	}



}
