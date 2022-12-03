#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cards {
	char pattern;
	int num;
}element;

#define MAX_CARD_SIZE 52
#define spade 06
#define club 05
#define diamond 04
#define heart 03

int top = -1;

element deck[MAX_CARD_SIZE];	//덱(스택) 생성

//---------------------스택관련 함수----------------------------
int is_empty() {
	return (top == -1);
}

int is_full() {
	return (top = MAX_CARD_SIZE);
}

void push(element data) {
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러");
		return;
	}
	else {
		deck[++top] = data;
	}
}

element pop() {
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러");
		return;
	}
	else {
		return deck[top--];
	}
}
//--------------------------------------------------

void showcard(element card);

void shakedeak();

int main(void) {

}

void showcard(element card) {	//카드 출력
	if (card.num == 1) {
		printf("-------\n");
		printf("|%c    |\n", card.pattern);
		printf("|  A  |\n");
		printf("|    %c|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num < 11) {
		printf("-------\n");
		printf("|%c    |\n", card.pattern);
		printf("|  %d  |\n", card.num);
		printf("|    %c|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 11) {
		printf("-------\n");
		printf("|%c    |\n", card.pattern);
		printf("|  J  |\n");
		printf("|    %c|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 12) {
		printf("-------\n");
		printf("|%c    |\n", card.pattern);
		printf("|  Q  |\n");
		printf("|    %c|\n", card.pattern);
		printf("-------\n");
	}
	else if (card.num == 13) {
		printf("-------\n");
		printf("|%c    |\n", card.pattern);
		printf("|  K  |\n");
		printf("|    %c|\n", card.pattern);
		printf("-------\n");
	}
	else {
		fprintf(stderr, "카드 에러");
	}
}