#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARD_SIZE 52

typedef struct cards {
	char pattern[3];
	int num;
}element;

typedef struct decks{
	element data[MAX_CARD_SIZE];
	int top;
}deck;

char shape[4][3] = { "♠", "◆", "♥", "♣" };

//---------------------스택관련 함수----------------------------
void init_stack(deck* d) {
	d->top = -1;
}

int is_empty(deck *d) {
	return (d->top == -1);
}

int is_full(deck *d) {
	return (d->top == MAX_CARD_SIZE - 1);
}

void push(deck* d, element card) {
	if (is_full(d)) {
		fprintf(stderr, "스택 포화 에러");
		return;
	}
	else {
		d->data[++(d->top)] = card;
	}
}

element pop(deck* d) {
	if (is_empty(d)) {
		fprintf(stderr, "스택 공백 에러");
		return;
	}
	else {
		return d->data[(d->top)--];
	}
}
//--------------------------------------------------

void showcard(element card);

void shakedeak(element cards[]);

int main(void) {
	deck card_deck;
	element cards[52];
	element card;
	int i = 0, n;

	init_stack(&card_deck);

	shakedeak(cards);

	for (i = 0; i < MAX_CARD_SIZE; i++) {
		push(&card_deck, cards[i]);
	}

	printf("카드 몇장 뽑음?\n");
	scanf("%d", &n);
	
	i = 0;
	while (i < n) {
		card = pop(&card_deck);
		showcard(card);
		printf("\n");
		i++;
	}
}

void showcard(element card) {	//카드 출력
	if (card.num == 1) {
		printf("-------\n");
		printf("|%s    |\n", card.pattern);
		printf("|  A  |\n");
		printf("|    %s|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num < 11) {
		printf("-------\n");
		printf("|%s    |\n", card.pattern);
		printf("|  %d  |\n", card.num);
		printf("|    %s|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 11) {
		printf("-------\n");
		printf("|%s    |\n", card.pattern);
		printf("|  J  |\n");
		printf("|    %s|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 12) {
		printf("-------\n");
		printf("|%s    |\n", card.pattern);
		printf("|  Q  |\n");
		printf("|    %s|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 13) {
		printf("-------\n");
		printf("|%s    |\n", card.pattern);
		printf("|  K  |\n");
		printf("|    %s|\n", card.pattern);
		printf("-------\n");
	}
	else {
		fprintf(stderr, "카드 에러");
	}
}

void shakedeak(element* cards) {
	element card;
	int k[52];

	for (int i = 0; i < 52; i++) {
		strcpy(card.pattern, shape[i/13]);
		card.num = (i%13) + 1;
		cards[i] = card;
		k[i] = i;
	}	// set cards

	for (int i = 0; i < 300; i++) {
		int x = rand() % 52;
		int y = rand() % 52;
		element tmp;

		if (x != y) {
			tmp.num = cards[x].num;
			strcpy(tmp.pattern, cards[x].pattern);
			cards[x].num = cards[y].num;
			strcpy(cards[x].pattern, cards[y].pattern);
			cards[y].num = tmp.num;
			strcpy(cards[y].pattern, tmp.pattern);
		}
	}
}
