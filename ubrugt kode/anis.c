void underline(uint8_t on) {
	if(on) printf("%c[%dm", ESC, 4);
	else printf("%c[%dm", ESC, 24);
}

void blink(uint8_t on) {
	if(on) printf("%c[%dm", ESC, 5);
	else printf("%c[%dm", ESC, 25);
}

void inverse(uint8_t on) {
	if(on) printf("%c[%dm", ESC, 7);
	else printf("%c[%dm", ESC, 27);
}


int32_t expand(int32_t i) {
// Converts an 18.14 fixed point number to 16.16
return i << 2;
}

void printFix(int32_t i) {
 // Prints a signed 16.16 fixed point number
 if ((i & 0x80000000) != 0) { // Handle negative numbers
 printf("-");
 i = ~i + 1;
 }
 printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
 // Print a maximum of 4 decimal digits to avoid overflow
 }

int32_t calcsin(int32_t x) {
	int32_t i = x % 512; // Modulus to make sure we dont have values larger than 512
	if (i<0) {
		i = i + 512; // Make sure it is a positive input
	}

	int32_t a = SIN[i]; //call the sin array from LUT.h
	return expand(a);
}

int32_t calccos(int32_t x) {
	int32_t a = calcsin(x + 128);
	return a;
}

int32_t rotateVector(int32_t x, int32_t y, int32_t d) {
	int32_t* px;
	int32_t* py;
	px= &x;
	py= &y;
	int32_t rx = *px * (calccos(d) >> 2) - *py * (calcsin(d) >> 2);
	int32_t ry = *px * (calcsin(d) >> 2) + *py * (calccos(d) >> 2);
	int32_t ex = expand(rx);
	int32_t ey = expand(ry);
	printFix(ex);
	printFix(ey);
}

void clreol() {
	printf("%c[2K", ESC);
}

void color(uint8_t foreground, uint8_t background) {
	// combination of fgcolor() and bgcolor() - uses less bandwidth
	uint8_t type = 22;             // normal text
	if (foreground > 7) {
		type = 1;                // bold text
		foreground -= 8;
	}
	printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
	// gray on black text, no underline, no blink, no reverse
	printf("%c[m", ESC);
}

void bgcolor(uint8_t background) {
	/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
	 */
	printf("%c[%dm", ESC, background+40);
}
