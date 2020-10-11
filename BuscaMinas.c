/*
	Jesús Alfredo Navarro Guzmán
	4513902
	IDS
	05/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define maxtamx 35
#define maxtamy 14	

void rellMinas(int);
void ponerNumeros(void);
void mostrar(int , int);
void quitarCeros(void);
void marco(void);
int tabla[maxtamx+2][maxtamy+2][2]={0};

int tamx=35, tamy=14;

int main(void){
	int i, j, numMinas = 50, x=1, y=1, tabla2[maxtamx][maxtamy];
	int ant = 0, bandera = 1, contadorBom=0, contador=0;
	randomize();
	system("color 0f");
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	printf("Ingrese el numero de columnas (col<%i)\n", maxtamx);
	scanf("%i", &tamx);
	printf("Ingrese el numero de filas (fil<%i)\n", maxtamy);
	scanf("%i", &tamy);
	printf("Ingrese el numero de minas (minas<%i)\n", tamx*tamy-10);
	scanf("%i", &numMinas);
	rellMinas(numMinas);
	ponerNumeros();
	quitarCeros();
	clrscr();
	marco();
	gotoxy(tamx*2+5, 4);
	cprintf("Teclas de movimieto: a, w, s, d");
	gotoxy(tamx*2+5, 5);
	cprintf("Mostar celda: \"Espacio\"");
	gotoxy(tamx*2+5, 6);
	cprintf("Marcar mina: \"Enter\"");
	gotoxy(tamx*2+5, 7);
	cprintf("Salir: p");
	while(contador+numMinas < tamx*tamy){
		textbackground(0);
		for(i=1; i<=tamx; i++){
			for(j=1; j<=tamy; j++){
				if(tabla[i][j][1] != tabla2[i-1][j-1] || bandera){
					gotoxy(i*2, j*2);
					if(tabla[i][j][1]==1){
						if(tabla[i][j][0] == -1){
							textcolor(15);
							textbackground(RED);
							cprintf("*");
							textbackground(WHITE);
							goto fin;
						}else{
							textcolor(tabla[i][j][0]+2);
							cprintf("%i", tabla[i][j][0]);
						}
					}else if(tabla[i][j][1] == 0){
						textcolor(WHITE);
						cprintf("%c", 219);
					}else if (tabla[i][j][1] == 2){
						textcolor(RED);
						cprintf("%c", 219);
					}else if(tabla[i][j][1] == 3){
						textbackground(WHITE);
						textcolor(RED);
						cprintf("%c", 244);
						textbackground(BLACK);
					}
				}
			}
		}
		gotoxy(tamx*2+5, 2);
		textcolor(WHITE);
		cprintf("Minas restantes:    ");
		gotoxy(tamx*2+5, 2);
		cprintf("Minas restantes: %i", numMinas-contadorBom);
		bandera=0;
		contador=0;
		for(i=1; i<=tamx; i++){
			for(j=1; j<=tamy; j++){
				tabla2[i-1][j-1] = tabla[i][j][1];
				if(tabla[i][j][1] == 1){
					contador++;
				}
			}
		}
		tabla[x][y][1] = ant;
		switch(getch()){
			case 'a':
				x--;
				if(x==0)
					x=tamx;
				ant = tabla[x][y][1];
				tabla[x][y][1] = 2;
			break;
			case 'w':
				y--;
				if(y==0)
					y=tamy;
				ant = tabla[x][y][1];
				tabla[x][y][1] = 2;
			break;
			case 'd':
				x++;
				if(x==tamx+1)
					x=1;
				ant = tabla[x][y][1];
				tabla[x][y][1] = 2;
			break;
			case 's':
				y++;
				if(y==tamy+1)
					y=1;
				ant = tabla[x][y][1];
				tabla[x][y][1] = 2;
			break;
			case 'p':
				return 0;
			case 32:
				if(tabla[x][y][1] == 3)
					contadorBom--;
				tabla[x][y][1] = 1;
				if(tabla[x][y][0] == 0){
					mostrar(x, y);
				}
				ant = 1;
			break;
			case 13:
				if(tabla[x][y][1] != 3){
					tabla[x][y][1]=3;
					ant = tabla[x][y][1];
					contadorBom++;
				}else{
					tabla[x][y][1]=0;
					ant = tabla[x][y][1];
					contadorBom--;
				}
			break;
		}
	}
	gotoxy(tamx*2+5, 9);
	textcolor(BLUE);
	textbackground(WHITE);
	cprintf(" Ganaste ");
	gotoxy(1, tamy*2+1);
	return 0;
	
fin:gotoxy(tamx*2+5, 9);
	textcolor(RED);
	textbackground(WHITE);
	cprintf(" Perdiste ");
	gotoxy(1, tamy*2+1);
	return 0;
}

void rellMinas(int num){
	int i, x, y;
	for(i=0; i<num; i++){
		x = rand()%tamx + 1;
		y = rand()%tamy + 1;
		if(tabla[x][y][0] != -1)
			tabla[x][y][0] = -1;
		else{
			i--;
		}
	}
}

void ponerNumeros(void){
	int i, j, x, y;
	for(i=1; i<=tamx; i++){
		for(j=1; j<=tamy; j++){
			if(tabla[i][j][0] != -1){
				for(x=-1; x<=1; x++){
					for(y=-1; y<=1; y++){
						if(tabla[i+x][j+y][0] == -1)
							tabla[i][j][0]++;
					}
				}
			}
		}
	}
}

void mostrar(int x, int y){
	int i, j;
	for(i=-1; i<=1; i++){
		for(j=-1; j<=1; j++){
			if(!(i==0 && j==0)){
				if(tabla[x+i][y+j][1] == 0){
					tabla[x+i][y+j][1] = 1;
					if(tabla[x+i][y+j][0] == 0)
					mostrar(x+i, y+j);
				}
			}
		}
	}
}

void quitarCeros(void){
	int i;
	for(i=0; i<tamx+2; i++){
		tabla[i][0][0] = 10;
		tabla[i][0][1] = 1;
		tabla[i][tamy+1][0] = 10;
		tabla[i][tamy+1][1] = 1;
	}
	for(i=0; i<tamy+2; i++){
		tabla[0][i][0] = 10;
		tabla[0][i][1] = 1;
		tabla[tamx+1][i][0] = 10;
		tabla[tamx+1][i][1] = 1;
	}
}

void marco(void){
	int i;
	textcolor(WHITE);
	for(i=1; i<(tamx+1)*2; i++){
		gotoxy(i, 1);
		cprintf("%c", 196);
		gotoxy(i, tamy*2+1);
		cprintf("%c", 196);
	}
	for(i=1; i<(tamy+1)*2; i++){
		gotoxy(1, i);
		cprintf("%c", 179);
		gotoxy(tamx*2+1, i);
		cprintf("%c", 179);
	}
	gotoxy(1, 1);
	cprintf("%c", 218);
	gotoxy(tamx*2+1, 1);
	cprintf("%c", 191);
	gotoxy(1, tamy*2+1);
	cprintf("%c", 192);
	gotoxy(tamx*2+1, tamy*2+1);
	cprintf("%c", 217);
}