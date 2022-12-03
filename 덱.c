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

element deck[MAX_CARD_SIZE];	//��(����) ����

//---------------------���ð��� �Լ�----------------------------
int is_empty() {
	return (top == -1);
}

int is_full() {
	return (top = MAX_CARD_SIZE);
}

void push(element data) {
	if (is_full()) {
		fprintf(stderr, "���� ��ȭ ����");
		return;
	}
	else {
		deck[++top] = data;
	}
}

element pop() {
	if (is_empty()) {
		fprintf(stderr, "���� ���� ����");
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

void showcard(element card) {	//ī�� ���
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
		fprintf(stderr, "ī�� ����");
	}
}