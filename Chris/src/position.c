/*
 * position.c
 *
 *  Created on: 14. jun. 2022
 *      Author: Christian
 */
#include "position.h"
#define ESC 0x1B
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"

void posShip(struct ship *s) {
	s->x += s->vx;
}




void posBall(struct ball *b) {
	b->x += b->vx;
	b->y += b->vy;
}

void bounce(struct ball *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t *counter) {
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









