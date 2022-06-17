
#include "graphics.h"
#define ESC 0x1B
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "LUT.h"
#include "ansi.h"
#include "control.h"
#include "position.h"


void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[1000], uint8_t style) {
	uint8_t i;
	//lines for style 0
	uint8_t hl0=205;
	uint8_t vl0=186;
	uint8_t tlc0=201;
	uint8_t trc0=187;
	uint8_t dlc0=200;
	uint8_t drc0=188;
	uint8_t tb0=185;
	uint8_t te0=204;

	//lines for style 1
	uint8_t hl1=196;
	uint8_t vl1=179;
	uint8_t tlc1=218;
	uint8_t trc1=191;
	uint8_t dlc1=192;
	uint8_t drc1=217;
	uint8_t tb1=180;
	uint8_t te1=195;

	if(style==0) {

		gotoxy(x1,y1);
		printf("%c", tlc0);
		printf("%c", tb0);
		for (i = 0; i < strlen(title); i++) {
			printf("%c", title[i]);
		}
		printf("%c", te0);

		for(i = 0; i < (x2-x1-strlen(title)-3); i++){ //horisontal top
			printf("%c", hl0);
		}
		gotoxy(x1,y1+1);
		for(i = 1; i < (y2-y1); i++){ //vertical left
			gotoxy(x1,y1+i);
			printf("%c\n",vl0);
		}
		gotoxy(x2,y1);
		printf("%c", trc0);
		for(i = 1; i < (y2-y1); i++){ //vertical right
			gotoxy(x2,y1+i);
			printf("%c",vl0);
		}
		gotoxy(x1,y2);
		printf("%c", dlc0);
		for(i = 0; i < (x2-x1); i++){ //horisontal bottom
			printf("%c",hl0);
		}
		gotoxy(x2,y2);
		printf("%c", drc0);


	}

	if(style==1) {
		gotoxy(x1,y1);
		printf("%c", tlc1);
		printf("%c", tb1);
		for (i = 0; i < strlen(title); i++) {
			printf("%c", title[i]);
		}
		printf("%c", te1);

		for(i = 0; i < (x2-x1-strlen(title)-3); i++){ //horisontal top
			printf("%c", hl1);
		}
		gotoxy(x1,y1+1);
		for(i = 1; i < (y2-y1); i++){ //vertical left
			gotoxy(x1,y1+i);
			printf("%c\n",vl1);
		}
		gotoxy(x2,y1);
		printf("%c", trc1);
		for(i = 1; i < (y2-y1); i++){ //vertical right
			gotoxy(x2,y1+i);
			printf("%c",vl1);
		}
		gotoxy(x1,y2);
		printf("%c", dlc1);
		for(i = 0; i < (x2-x1); i++){ //horisontal bottom
			printf("%c",hl1);
		}
		gotoxy(x2,y2);
		printf("%c", drc1);
	}
}

void wall(struct window *w, uint8_t style) {
	uint8_t i;
	//lines for style 0
	uint8_t hl0=205;
	uint8_t vl0=186;
	uint8_t tlc0=201;
	uint8_t trc0=187;
	uint8_t dlc0=200;
	uint8_t drc0=188;

	//lines for style 1
	uint8_t hl1=196;
	uint8_t vl1=179;
	uint8_t tlc1=218;
	uint8_t trc1=191;
	uint8_t dlc1=192;
	uint8_t drc1=217;


	if(style==0) {

		gotoxy(w->x1,w->y1);
		printf("%c", tlc0);

		for(i = 0; i < ((w->x2)-(w->x1)-1); i++){ //horisontal top
			printf("%c", hl0);
		}
		gotoxy(w->x1,w->y1+1);
		for(i = 1; i < (w->y2-w->y1); i++){ //vertical left
			gotoxy(w->x1,w->y1+i);
			printf("%c\n",vl0);
		}
		gotoxy(w->x2,w->y1);
		printf("%c", trc0);
		for(i = 1; i < (w->y2-w->y1); i++){ //vertical right
			gotoxy(w->x2,w->y1+i);
			printf("%c",vl0);
		}
		gotoxy(w->x1,w->y2);
		printf("%c", dlc0);
		for(i = 0; i < ((w->x2)-(w->x1)); i++){ //horisontal bottom
			printf("%c",hl0);
		}
		gotoxy(w->x2,w->y2);
		printf("%c", drc0);


	}

	if(style==1) {
		gotoxy(w->x1,w->y1);
		printf("%c", tlc1);

		for(i = 0; i < (w->x2-w->x1-1); i++){ //horisontal top
			printf("%c", hl1);
		}
		gotoxy(w->x1,w->y1+1);
		for(i = 1; i < (w->y2-w->y1); i++){ //vertical left
			gotoxy(w->x1,w->y1+i);
			printf("%c\n",vl1);
		}
		gotoxy(w->x2,w->y1);
		printf("%c", trc1);
		for(i = 1; i < (w->y2-w->y1); i++){ //vertical right
			gotoxy(w->x2,w->y1+i);
			printf("%c",vl1);
		}
		gotoxy(w->x1,w->y2);
		printf("%c", dlc1);
		for(i = 0; i < (w->x2-w->x1); i++){ //horisontal bottom
			printf("%c",hl1);
		}
		gotoxy(w->x2,w->y2);
		printf("%c", drc1);
	}
}



void drawBall(struct window *w, struct ball *b1){
	if (b1->x > w->x1 && b1->x < w->x2 && b1->y > w->y1 && b1->y < w->y2){
		gotoxy(b1->x, b1->y); //Go to the updated position
		printf("o"); //print: o
	}
}

void clrBall(struct window *w, struct ball *b1){
	if (b1->x > w->x1 && b1->x < w->x2 && b1->y > w->y1 && b1->y < w->y2){
		gotoxy(b1->x, b1->y); //Go to the updated position
		printf(" "); //print:
	}
}

void drawBullet(struct window *w, struct bullet *b1){
	if (b1->x > w->x1 && b1->x < w->x2 && b1->y > w->y1 && b1->y < w->y2){
		gotoxy(b1->x, b1->y); //Go to the updated position
		printf("o"); //print: o
	}
}

void clrBullet(struct window *w, struct bullet *b1){
	if (b1->x > w->x1 && b1->x < w->x2 && b1->y > w->y1 && b1->y < w->y2){
		gotoxy(b1->x, b1->y); //Go to the updated position
		printf(" "); //print:
	}
}

/*void hit(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t *counter){
	wall(((x1+x2)/2)-4, ((y1+y2)/2)-1, ((x1+x2)/2)+5, ((y1+y2)/2)+1,1);
	gotoxy(((x1+x2)/2)-3,(y1+y2)/2);
	printf("Hits:%d", *counter);
}*/

void drawSpaceship(struct spaceship *s1){
	gotoxy(s1->x, s1->y); //Go to the updated position
	printf("@"); //print: @
	//printf( "%c%c%c[%dm%c%c[%dm%c%c \v\b\b\b\b\b%c%c%c%c%c" , 187 , 196 , ESC, 33 , 219 , ESC, 37 , 196 , 201 , 204 , 205 , 206 , 205 , 185 );
}

void clrSpaceship(struct spaceship *s1){
	gotoxy(s1->x, s1->y); //Go to the updated position
	printf(" "); //print: blank
}

void drawEnemy(struct window *w, struct enemy *e1){
	if (e1->x > w->x1 && e1->x < w->x2 && e1->y > w->y1 && e1->y < w->y2){
		gotoxy(e1->x-1, e1->y); //Go to the updated position
		printf("%c%c%c", 201,220,187); //print: o
		gotoxy(e1->x-1, e1->y+1);
		printf("%c%c%c", 200,223,188);
	}
}

void clrEnemy(struct window *w, struct enemy *e1){
	if (e1->x > w->x1 && e1->x < w->x2 && e1->y > w->y1 && e1->y < w->y2){
		gotoxy(e1->x-1, e1->y); //Go to the updated position
		printf("   ");
		gotoxy(e1->x-1, e1->y+1);
		printf("   ");
	}
}

/*void shootBullet(struct window *w, struct bullet *b1, struct spaceship *s){
	if (setButton() == 10 || readJoystick() == 16){
		clrBullet(&w,&b1);
		b1->x = s->x;
		b1->y = s->y-1;
		b1->vy = -4;

	}
	/*clrBullet(&w,&b1);
	posBullet(&w,&b1);
	drawBullet(&w,&b1);
}*/


void explode(struct enemy *e1, struct bullet *b1){
	if (hit(&e1, &b1)==1){
		gotoxy(e1->x, e1->y);
		printf("BAANG");
	}
}
