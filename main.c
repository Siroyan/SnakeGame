#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "key.h"

#define EMPTY 0
#define AREA 1
#define SNAKE 2
#define ESA 3
#define WALL 4
#define XSIZE 20
#define YSIZE 20

void init(void);
void moveSnake(char);
void clearView(void);
void genEsaPosition(void);

struct snake {
	int x;
	int y;
	struct snake *next;
};
struct snake *new, *tail, *tgt;
int field[XSIZE][YSIZE];
int esaX;
int esaY;

int main(void){
	/* new := pointer of extension amount */
	/* head := pointer of snake head */
	/* tgt := pointer of target */
	char dir = 'd';
	char prevdir = 'd';
	int buf;
	int cnt = 0;
	int isEat = 1;
	int isFailed = 0;
	init();
	while(isFailed == 0){
		clearView();
		
		/* set snake to field and check*/
		tgt = tail;
		while(tgt != NULL){
			if(field[tgt->x][tgt->y] != WALL && field[tgt->x][tgt->y] != SNAKE){
				field[tgt->x][tgt->y] = SNAKE;
				tgt = tgt -> next;
			}else{
				isFailed = 1;
				break;
			}
		}

		/* set esa */
		if(isEat == 1){
			genEsaPosition();
			isEat = 0;
		}
		field[esaX][esaY] = ESA;
		/* show field */
		for(int y=0; y<YSIZE; y++){
			for(int x=0; x<XSIZE; x++){
				if(field[y][x] == ESA) printf("◆ ");
				if(field[y][x] == SNAKE) printf("● ");
				if(field[y][x] == AREA) printf("□ ");
				if(field[y][x] == WALL) printf("■ ");
				if(field[y][x] == EMPTY) printf("  ");
			}
			printf("\n");
		}

		tgt = tail;
		while(tgt -> next != NULL){
			tgt = tgt -> next;
		}
		if((esaX == tgt -> x) && (esaY == tgt -> y)){
			new = (struct snake *)malloc(sizeof(struct snake));
			new -> x = (tail -> x) - 1;
			new -> y = tail -> y;
			new -> next = tail;
			tail = new;
			isEat = 1;
		}

		dir = kbhit();
		if(dir == 0){
			moveSnake(prevdir);
		}else{
			moveSnake(dir);
			usleep(1000);
			prevdir = dir;
		}
		usleep(1000 * 100 * 1);
	}
	if (isFailed == 1) {
		printf("GameOver");
	}else{
		printf("GameClear");
	}
	
}

void init(){
	/* init tail */
	tail = (struct snake *)malloc(sizeof(struct snake));
	tail -> x = 10;
	tail -> y = 10;
	tail -> next = NULL;

	/* init body */
	for(int i=0; i<4; i++){
		new = (struct snake *)malloc(sizeof(struct snake));
		new -> x = (tail -> x) - 1;
		new -> y = tail -> y;
		new -> next = tail;
		tail = new;
	}
}

void clearView(void){
	system("clear");
	/* init field */
	for(int y=0; y<YSIZE; y++){
		for(int x=0; x<XSIZE; x++){
			if(y==0||x==0||y==YSIZE-1||x==XSIZE-1) field[y][x] = WALL;
			else field[y][x] = AREA;
		}
	}
}

void genEsaPosition(void){
	do{
		esaX = rand() % XSIZE - 1;
		esaY = rand() % YSIZE - 1;
	}while(field[esaX][esaY] != AREA);
}

void moveSnake(char dir){
	tgt = tail;
	while(tgt -> next != NULL){
		tgt -> x = tgt -> next -> x;
		tgt -> y = tgt -> next -> y;
		tgt = tgt -> next;
	}
	switch(dir){
		case 'w':
			printf("Up\n");
			tgt -> x = tgt -> x - 1;
			break;
		case 'a':
			printf("Left\n");
			tgt -> y = tgt -> y - 1;
			break;
		case 's':
			printf("Down\n");
			tgt -> x = tgt -> x + 1;
			break;
		case 'd':
			printf("Right\n");
			tgt -> y = tgt -> y + 1;
			break;
		default:
			printf("Error\n");
			break;
	}
}