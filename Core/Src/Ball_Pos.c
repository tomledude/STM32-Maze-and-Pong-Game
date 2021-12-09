/*
 * Ball_Pos.c
 *
 *  Created on: 18 May 2021
 *      Author: 99tho
 */

#include "main.h"
#include <stdio.h>
uint8_t dir = 0;
extern uint8_t x_ball;
extern uint8_t y_ball;
extern uint8_t y_bat;
extern uint8_t x_bat;
extern uint32_t tennis;
extern menu();
volatile uint32_t hit_count;

void update_ball_pos(void){
	if(x_ball == 0){
		tennis = 0;
		menu();
	}


	if(dir == 0){
		if((x_ball == x_bat+1) & (y_ball == y_bat)){
			dir=4;
			hit_count++;
		}else if((x_ball == x_bat+1) & (y_ball == (y_bat+1))){
			dir=2;
			hit_count++;
		}else
		{
		x_ball--;
		}
	}
	if(dir == 1){
		if(x_ball == 7){
			dir=0;
		}
		x_ball++;
	}
	if(dir == 2){
		if(y_ball == 7){
			dir = 4;
		}else if(x_ball == 7){
			dir = 5;
		}else{
		x_ball++;
		y_ball++;
		}
	}
	if(dir ==3 ){
		if(y_ball == 0){
			dir = 5;
		}else if((x_ball == x_bat + 1) & ((y_ball == y_bat) | (y_ball == y_bat+1))){
			dir = 4;
			hit_count++;
		}else if((x_ball == x_bat + 1) & ((y_ball == y_bat+2))){
			dir = 2;
			hit_count++;
			x_ball++;
			y_ball++;
		}else{
		x_ball--;
		y_ball--;
		}
	}
	if(dir == 4){
		if((x_ball == 7) & (y_ball == 0)){
			dir = 5;
		}else if(y_ball == 0){
			dir = 2;
			x_ball++;
			y_ball++;
		}else if(x_ball == 7){
			dir=3;
			x_ball--;
				y_ball--;
		}else{
		x_ball++;
		y_ball--;
		}
	}
	if(dir == 5){
		if((x_ball == x_bat +1) & (y_ball == y_bat-1)){
			dir = 4;
			hit_count++;
			x_ball++;
			y_ball--;
		}else if(y_ball == 7){
			dir = 3;
			x_ball--;
			y_ball--;
		}else if((x_ball == x_bat +1) & ((y_ball == y_bat) | (y_ball == y_bat+1))){
			dir = 2;
			hit_count++;
			x_ball++;
			y_ball++;
		}else{
		x_ball--;
		y_ball++;
		}
	}
}
