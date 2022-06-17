/*
 * position.h
 *
 *  Created on: 14. jun. 2022
 *      Author: Christian
 */
#define ESC 0x1B
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"
#include "control.h"


#ifndef POSITION_H_
#define POSITION_H_

struct object {
	int8_t x, y, vx, vy;
};

struct spaceship {
	int8_t x, y;
};

struct window {
	int8_t x1, y1, x2, y2;
};

void posSpaceship(struct spaceship *s, int8_t control, struct window *w);
void posBullet(struct object *b1, struct object *a, struct window *w);
void posEnemy(struct object *e1, struct window *w);
void posAsteroid(struct object *a);
void multipleBullets(struct object *b1,struct object *b2,struct object *b3,struct object *a, struct window *w, struct spaceship *s);

#endif /* POSITION_H_ */

