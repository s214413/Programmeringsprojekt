#include "position.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"
#include "control.h"


void positionBall(struct ball *b1) {
	b1->x += b1->vx; //update the x-position by adding the velocity in x-direction
	b1->y += b1->vy; //update the y-position by adding the velocity in y-direction
	if (b1->x <= 0 || b1->x >= 100 || b1->y <= 1){
		b1->vx = 0;
		b1->vy = 0;
	}
}

void bounce(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, struct ball *b1, int8_t *counter){

	if (b1->x <= x1+1 || b1->x >= x2-1){ //
		*counter+=1;
		b1->vx = -b1->vx;

	}
	else if (b1->y <= y1+1 || b1->y >= y2-1){
		*counter+=1;
		b1->vy = -b1->vy;
	}
}

void positionSpaceship(struct spaceship *s1, int8_t control) {
	if (control == 0){
		int16_t x2 = set2Axis(2); //set
		if (x2 > 2000){
			s1->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (x2 < 1800){
			s1->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
	if (control == 1){
		if (readJoystick() == 8){
			s1->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (readJoystick() == 4){
			s1->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
}

void positionEnemy(struct enemy *e1) {
	e1->x += e1->vx; //update the x-position by adding the velocity in x-direction
	e1->y += e1->vy; //update the y-position by adding the velocity in y-direction
	if (e1->y >= 45){
		e1->vx = 0;
		e1->vy = 0;
		//lives -= 1
	}
}
