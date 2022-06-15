#include "stdint.h"
#include "stdio.h"
#include "charset.h"
#include "display.h"


void lcd_write_string(uint8_t *graphbuffer, char s[], int8_t column, int8_t row){
	for (int i = 0; i < strlen(s); i++){
		for(int j = 0; j < 5; j++){
			graphbuffer[5*i+j+column+row*128] = character_data[s[i]-0x20][j];
		}
	}
}


void lcd_update(uint8_t *graphbuffer,int8_t interruptflag){
	if (interruptflag=1){
		lcd_push_buffer(graphbuffer);
		interruptflag = 0;
	}
}

void lcd_scroll(uint8_t *graphbuffer) {
	uint16_t i, pos1 = graphbuffer[1], pos2 = graphbuffer[128], pos3 = graphbuffer[256], pos4 = graphbuffer[384];
	for(i = 0; i < 127; i++) {
		graphbuffer[i] = graphbuffer[i+1];
		graphbuffer[128 + i] = graphbuffer[128+i+1];
		graphbuffer[256 + i] = graphbuffer[256+i+1];
		graphbuffer[384 + i] = graphbuffer[384+i+1];
	}

	graphbuffer[0] = pos1;
	graphbuffer[127] = pos2;
	graphbuffer[255] = pos3;
	graphbuffer[383] = pos4;

}
