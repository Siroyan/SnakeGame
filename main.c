#include <stdio.h>
#include <stdlib.h>

struct snake {
	int x;
	int y;
	struct snake *next;
};

int main(void){
	int field[20][20];
	/* new := pointer of extension amount */
	/* head := pointer of snake head */
	/* tgt := pointer of target */
	struct snake *new, *tail, *tgt;

	/* init field */
	for(int i=0; i<20; i++){
		for(int j=0; j<20; j++){
			field[i][j] = 1;
		}
	}

	/* init head */
	tail = (struct snake *)malloc(sizeof(struct snake));
	tail -> x = 5;
	tail -> y = 10;
	tail -> next = NULL;

	/* init body */
	for(int i=0; i<4; i++){
		new = (struct snake *)malloc(sizeof(struct snake));
		new -> x = (tail -> x) + 1;
		new -> y = tail -> y;
		new -> next = tail;
		tail = new;
	}

	/* set snake to field */
	tgt = tail;
	while(tgt != NULL){
		field[tgt->y][tgt->x] = 2;
		tgt = tgt -> next;
	}

	/* show field */
	for(int y=0; y<20; y++){
		for(int x=0; x<20; x++){
			if(field[y][x] == 2) printf(" # ");
			if(field[y][x] == 1) printf("[ ]");
			if(field[y][x] == 0) printf("   ");
		}
		printf("\n");
	}
}
