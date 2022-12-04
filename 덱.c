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

void push(deck* d, element card) {	//근데 여기와서는 d의 주소가 바뀜
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

void shakedeak(deck *d);

int main(void) {
	deck card_deck;

	init_stack(&card_deck);

	shakedeak(&card_deck);
	int i=0, n;

	printf("카드 몇장 뽑음?\n");
	scanf("%d", &n);

	while (i < n) {
		showcard(pop(&card_deck));
		printf("\n");
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

void shakedeak(deck *d) {
	element cards[52];
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

	for (int i = 0; i < 52; i++) {
		push(&d, cards[i]);	//여기에서는 d의 주소가 정상적으로 출력이 
	}
}
