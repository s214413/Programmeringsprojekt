/*
 * graphics.c
 *
 *  Created on: 14. jun. 2022
 *      Author: Christian
 */
#include "graphics.h"
#define ESC 0x1B
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"


void gotoxy(uint8_t x,uint8_t y) {
	printf("%c[%d;%dH", ESC, y, x);
}

void clrscr() {
	printf("%c[2J", ESC);
}

void drawBall(struct ball *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	if(b->x > x1 && b->x < x2 && b->y > y1 && b->y < y2){
	gotoxy(b->x, b->y);
	printf("o");
	}
}

void clrball(struct ball *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	if(b->x > x1 && b->x < x2 && b->y > y1 && b->y < y2){
		gotoxy(b->x, b->y);
		printf(" ");
	}
}

void ballHit(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t *counter) {
	walls(((x1+x2)/2)-5, ((y1+y2)/2)-4, ((x1+x2)/2)+5, ((y1+y2)/2)-2,0);
	printf("%c[H", ESC);
	printf("%c[%dC", ESC, ((x1+x2)/2)-4);
	printf("%c[%dB", ESC, ((y1+y2)/2)-4);
	printf("Hits: %d", *counter);
}

void windowwh(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t style, char header[1000]) {
	uint8_t i;
	uint8_t urc;
	uint8_t ulc;
	uint8_t drc;
	uint8_t dlc;
	uint8_t hl;
	uint8_t vl;
	uint8_t tb;
	uint8_t te;


	if(style == 0) {
		urc = 218;
		ulc = 191;
		drc = 217;
		dlc = 192;
		hl = 196;
		vl = 179;
		tb = 180;
		te = 195;
	}

	if(style == 1) {
		urc = 201;
		ulc = 187;
		drc = 188;
		dlc = 200;
		hl = 205;
		vl = 186;
		tb = 185;
		te = 204;
	}

	gotoxy(x1,y1);
	printf("%c", urc);
	printf("%c",tb);
	for(i = 0; i < strlen(header); i++) {
		printf("%c", header[i]);
	}
	printf("%c",te);
	for(i = 0; i < (x2-x1-strlen(header)-2); i++) {
		printf("%c", hl);
	}

	for(i = 1; i < (y2-y1); i++) {
		gotoxy(x1,y1 + i);
		printf("%c\n", vl);
	}

	gotoxy(x2,y1);
	printf("%c", ulc);
	for(i = 1; i < (y2-y1); i++) {
		gotoxy(x2,y1 + i);
		printf("%c\n", vl);
	}

	gotoxy(x2,y2);
	printf("%c", drc);

	gotoxy(x1,y2);
	printf("%c", dlc);
	for(i = 1; i < (x2-x1-1); i++) {
		printf("%c", hl);
	}
}

void walls(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t style) {
	uint8_t i;
	uint8_t urc;
	uint8_t ulc;
	uint8_t drc;
	uint8_t dlc;
	uint8_t hl;
	uint8_t vl;

	if(style == 0) {
		urc = 218;
		ulc = 191;
		drc = 217;
		dlc = 192;
		hl = 196;
		vl = 179;
	}

	if(style == 1) {
		urc = 201;
		ulc = 187;
		drc = 188;
		dlc = 200;
		hl = 205;
		vl = 186;
	}

	gotoxy(x1,y1);
	printf("%c", urc);
	for(i = 0; i < (x2-x1-1); i++) {
		printf("%c", hl);
	}

	gotoxy(x1,y1 + 1);
	for(i = 1; i < (y2-y1); i++) {
		gotoxy(x1,y1 + i);
		printf("%c\n", vl);
	}

	gotoxy(x2,y1);
	printf("%c", ulc);
	for(i = 1; i < (y2-y1); i++) {
		gotoxy(x2,y1 + i);
		printf("%c\n", vl);
	}

	gotoxy(x1,y2);
	printf("%c", dlc);
	for(i = 0; i < (x2-x1); i++) {
		printf("%c", hl);
	}
	gotoxy(x2,y2);
	printf("%c", drc);


}
