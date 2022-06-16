/*
 * position.c
 *
 *  Created on: 14. jun. 2022
 *      Author: Christian
 */
#include "position.h"
#include "math.h"
#define ESC 0x1B
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

void posSpaceship(struct spaceship *s, int8_t control, struct window *w) {
	if (control == 0){
		int16_t x2 = set2Axis(2); //set
		if (x2 > 2000){
			s->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (x2 < 1800){
			s->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
	if (control == 1){
		if (readJoystick() == 8){
			s->x += 1;//update the x-position by adding the velocity in x-direction
		}
		else if (readJoystick() == 4){
			s->x -= 1; //update the y-position by adding the velocity in y-direction
		}
	}
	if (s->x < w->x1 + 2) {
		s->x = w->x2 - 2;
	}
	if (s->x > w->x2 - 2) {
		s->x = w->x1 + 2;
	}
}

void posBall(struct object *b) {
	b->x += b->vx;
	b->y += b->vy;
}

void posAsteroid(struct object *a) {
	gotoxy(a->x,a->y);
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

	if (b1->x <= w->x1 || b1->x >= w->x2-1 || b1->y <= w->y1+1){
		b1->vx = 0;
		b1->vy = 0;
	}
}

void posEnemy(struct object *e1, struct window *w) {
	e1->x += e1->vx;
	e1->y += e1->vy;
	if (e1->y >= w->y2) {
		e1->vx = 0;
		e1->vy = 0;
	}
}

void bounce(struct object *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t *counter) {
	if(b->y <= y1+1 || b->y >= y2-1) {
		*counter += 1;
		b->vy =- b->vy;
	}
	if(b->x <= x1+1 || b->x >= x2-1) {
		*counter += 1;
		b->vx =- b->vx;
	}
	else
		printf("%c[j", ESC);
}











