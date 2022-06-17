#include "position.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"
#include "control.h"



void posBall(struct window *w, struct ball *b1) {
	b1->x += b1->vx; //update the x-position by adding the velocity in x-direction
	b1->y += b1->vy; //update the y-position by adding the velocity in y-direction
	if (b1->x <= w->x1+1 || b1->x >= w->x2-1 || b1->y <= w->y1+1){
		b1->vx = 0;
		b1->vy = 0;
	}
}

void posBullet(struct object *b1, struct object *a, struct window *w) {
	uint32_t dx = abs(b1->x - a->x) << 14;
	uint32_t dy = abs(b1->y - a->y) << 14;
	uint32_t d = sqrt(pow(dx,2) + pow(dy,2));
	uint32_t f = 2*(FIX14_DIV((15 << 14), d));

	f = f >> 14;
	b1->x += b1->vx;
	b1->y += b1->vy;

	/*if(b1->y < a->y + 2 && b1->y > a->y && b1->x < a->x + 8 && b1->x > a->x - 6) {
		b1->vy = 0;
	}*/

	if(b1->x > a->x && b1->x < a->x + 10 && abs(b1->vx) < 2 && b1->y < a->y) {
		b1->vx = b1->vx - (f/1+abs(b1->vx));
	}

	if(b1->x < a->x && b1->x > a->x - 10 && abs(b1->vx) < 2 && b1->y < a->y) {
		b1->vx = b1->vx + (f/1+abs(b1->vx));
	}

	if (b1->x <= w->x1 || b1->x >= w->x2 || b1->y <= w->y1){
		b1->vx = 0;
		b1->vy = 0;
	}
}

void posBullet(struct window *w, struct bullet *b1) {
	b1->x += b1->vx; //update the x-position by adding the velocity in x-direction
	b1->y += b1->vy; //update the y-position by adding the velocity in y-direction
	if (b1->x <= w->x1 || b1->x >= w->x2 || b1->y <= w->y1){
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

void posSpaceship(struct window *w, struct spaceship *s, int8_t control) {
	if (control == 0){
		int16_t x2 = set2Axis(2); //set
		if (x2 > 2000){
			s->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (x2 < 1800){
			s->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
	else if (control == 1){
		if (readJoystick() == 8){
			s->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (readJoystick() == 4){
			s->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
	if (s->x > w->x2-1){
		s->x = w->x1+1;
	}
	else if (s->x < w->x1+1){
		s->x = w->x2-1;
	}
}

void posEnemy(struct window *w, struct enemy *e1, int8_t *lives) {
	e1->x += e1->vx; //update the x-position by adding the velocity in x-direction
	e1->y += e1->vy; //update the y-position by adding the velocity in y-direction
	if (e1->y >= w->y2){
		e1->d = 1;
		*lives -= 1;
	}
}

int8_t hit(struct enemy *e1, struct bullet *b1){
	if ((e1->x - 1) <= b1->x && b1->x<= (e1->x + 1) && e1->y <= b1->y && b1->y <= (e1->y+1)){
		return 1;
	}
	else {
		return 0;
	}
}

