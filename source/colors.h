void SetColorBlock(unsigned short color);

void gotoPrint(int x, int y, char text[255]) {
	gotoxy(x, y);
	printf(text);
}

void gotoPrintChar(int x, int y, int ascii) {
	gotoxy(x, y);
	printf("%c", ascii);
}

void underline(int x, int y, char text[255]) {
	int i;
	
	gotoxy(x, y);
	printf("%s", text);
	for(i = 0; i < strlen(text); i++) {
		gotoxy(x+i, y+1);
		printf("%c", 196);
	}
}

void topBottomLine(int x, int y, char text[255]) {
	int i;
	
	gotoxy(x, y);
	printf("%s", text);
	for(i = 0; i < strlen(text); i++) {
		gotoxy(x+i, y+1);
		printf("%c", 196);
		gotoxy(x+i, y-1);
		printf("%c", 196);
	}
}

void textBox1(int x, int y, int width, int height) {
	int i, j;
	
	/* first Line */
	gotoxy(x, y);
	printf("%c", 218);
	for(i = 1; i <= width; i++) {
		printf("%c", 196);
	}
	printf("%c", 191);
	
	/* looping for height */
	for(i = 1; i <= height; i++) {
		gotoxy(x, y + i);
		printf("%c", 179);
		
		gotoxy(x + width + 1, y + i);
		printf("%c", 179);
	}
	
	/* last line */
	printf("\n");
	gotoxy(x, y + height);
	printf("%c", 192);
	for(i = 1; i <= width; i++) {
		printf("%c", 196);
	}
	printf("%c", 217);
}

void textBox2(int x, int y, int width, int height) {
	int i, j;
	
	/* first Line */
	gotoxy(x, y);
	printf("%c", 201);
	for(i = 1; i <= width; i++) {
		printf("%c", 205);
	}
	printf("%c", 187);
	
	/* looping for height */
	for(i = 1; i <= height; i++) {
		gotoxy(x, y + i);
		printf("%c", 186);
		for(j = 1; j <= width; j++) {
			printf(" ");
		}
		gotoxy(x + width + 1, y + i);
		printf("%c", 186);
	}
	
	/* last line */
	printf("\n");
	gotoxy(x, y + height);
	printf("%c", 200);
	for(i = 1; i <= width; i++) {
		printf("%c", 205);
	}
	printf("%c", 188);
}

void Box(int x, int y, int width, int height, int color) {
	int i, j;
	
	/* first Line */
	SetColorBlock(color);
	gotoxy(x, y);
	printf("%c", 219);
	for(i = 1; i <= width; i++) {
		printf("%c", 223);
	}
	printf("%c", 219);
	
	/* looping for height */
	for(i = 1; i <= height; i++) {
		gotoxy(x, y + i);
		printf("%c", 219);
		
		gotoxy(x + width + 1, y + i);
		printf("%c", 219);
	}
	
	/* last line */	
	gotoxy(x, y + height);
	printf("%c", 219);
	for(i = 1; i <= width; i++) {
		printf("%c", 220);
	}
	printf("%c", 219);
	SetColorBlock(0);
}

void BoxBlock(int x, int y, int width, int height, int color) {
	int i, j;
	
	/* first Line */
	SetColorBlock(color);
	for(i = 0; i <= height; i++) {
		for(j = 0; j < width; j++) {
			gotoxy(x + j, y + i);
			printf("%c", 219);
		}
	}
}

void chooseBox(int x, int y, int width, int height) { //[]
	int i, j;
	
	/* first Line */
	gotoxy(x, y);
	printf("%c", 201);
	for(i = 1; i <= width; i++) {
		printf("%c", 205);
	}
	printf("%c", 187);
	
	/* last line */
	printf("\n");
	gotoxy(x, y + height);
	printf("%c", 200);
	for(i = 1; i <= width; i++) {
		printf("%c", 205);
	}
	printf("%c", 188);
}

void SetColor(int ForgC)
{
 	WORD wColor;

  	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	CONSOLE_SCREEN_BUFFER_INFO csbi;
    //We use csbi for the wAttributes word.
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
    	//Mask out all but the background attribute, and add in the forgournd color
      	wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      	SetConsoleTextAttribute(hStdOut, wColor);
 	}
}

void SetColorBlock(unsigned short color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}
