void getinputmin(char input[], int min, int max, int type);
void getinput(char input[], int max, int type);
void getpass(char input[], int max);
void getteksnum(char input[], int max);
void getletter(char input[], int max);

void getinputmin(char input[], int min, int max, int type)
{
	char current;
	int i,n;
	n = 0;
	do
	{
		current = getch();

		if(current == '\b' && n != 0) 		//backspace
		{
			printf("\b \b");
			n--;
			input[n]='\0';
		}
		//else if(current >= 32 && current <= 122){
		else if(isprint(current)){ //karakter yang bisa di print
			if(n == max) {
				continue;
			}
			else{
				if(type == 3){ //isdigit = angka doang
					if(isdigit(current)) {
						printf("%c", current);
						input[n]=current;
						n++;
					}
					else printf("\a");
				}
				else if(type == 2){ //isalpha = alpabet dan spasi co : nama
					if(isalpha(current) || current == ' ') {
						printf("%c", current);
						input[n]=current;
						n++;
					}
					else printf("\a");
				}
				else { // password //0= bebas
					if(type == 1) printf("*");
					else printf("%c", current);
					input[n]=current;
					n++;
				}
			}
		}
		else if(current == 13)
		{
			if(n < min) {
				printf("\a");
				current = 0;
			}
			else input[n]='\0';
		}
		//else if(current == 27) end();
	}
	while(current != 13);
}

void getinput(char input[], int max, int type)
{
	getinputmin(input, 1, max, type);
}

void getpass(char input[], int max)					//teks sebagai password jadi ada bintangnya
{
	getinput(input, max, 1);
}

void getteksnum(char input[], int max)				//tidak bisa input huruf
{
	getinput(input, max, 3);
}

void getletter(char input[], int max)				//tidak bisa input angka
{
	getinput(input, max, 2);
}

