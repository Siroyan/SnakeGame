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

struct snake {
	int x;
	int y;
	struct snake *next;
};
struct snake *new, *tail, *tgt;
int field[20][20];

int main(void){
	/* new := pointer of extension amount */
	/* head := pointer of snake head */
	/* tgt := pointer of target */
	char dir = 'd';
	char prevdir = 'd';
	int buf;
	int cnt = 0;
	init();
	while(1){
		clearView();
		
		/* set snake to field */
		tgt = tail;
		while(tgt != NULL){
			field[tgt->y][tgt->x] = 2;
			tgt = tgt -> next;
		}

		/* show field */
		for(int x=0; x<XSIZE; x++){
			for(int y=0; y<YSIZE; y++){
				if(field[x][y] == ESA) printf("◆ ");
				if(field[x][y] == SNAKE) printf("● ");
				if(field[x][y] == AREA) printf("□ ");
				if(field[x][y] == EMPTY) printf("  ");
			}
			printf("\n");
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
	for(int i=0; i<YSIZE; i++){
		for(int j=0; j<XSIZE; j++){
			if(i==0||j==0||i==YSIZE-1||j==XSIZE-1) field[i][j] = WALL;
			else field[i][j] = AREA;
		}
	}
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
			tgt -> y = tgt -> y - 1;
			break;
		case 'a':
			printf("Left\n");
			tgt -> x = tgt -> x - 1;
			break;
		case 's':
			printf("Down\n");
			tgt -> y = tgt -> y + 1;
			break;
		case 'd':
			printf("Right\n");
			tgt -> x = tgt -> x + 1;
			break;
		default:
			printf("Error\n");
			break;
	}
}