#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARD_SIZE 52
#define cash 500

typedef struct cards {
	char pattern[3];
	int num;
}element;

typedef struct decks {	//덱 
	element data[MAX_CARD_SIZE];
	int top;
}deck;

typedef struct DlistNode {
	element data;
	struct DlistNode* Llist;
	struct DlistNode* Rlist;
}hand_cards;

typedef struct player {
	int coin;
	int hand_count;
	hand_cards hand;
}player;	//player

typedef struct dealer {
	int hand_count;
	hand_cards hand;
}deal;

void init_stack();
int is_empty();
int is_full();
void push(element card);
element pop();

void init(hand_cards* head);
void insert(hand_cards* before, element data);
void delete(hand_cards* head, hand_cards* removed);
void print_hand(hand_cards* head);

void start();
void make_player();
void play();

int betting(player* user);

void showcard(element card);	//카드 출력 함수
void shakedeak();	//카드 섞는수함수


deck card_deck;
char shape[4][3] = { "♠", "◆", "♥", "♣" };	//카드 문양
int player_num;
player player_arr[4];	//최대 플레이어 4명
deal dealer;

int main(void) {
	start();

	init_stack();
	shakedeak();

	
	play();
}

//---------------------스택관련 함수----------------------------
void init_stack() {
	card_deck.top = -1;
}

int is_empty() {
	return (card_deck.top == -1);
}

int is_full() {
	return (card_deck.top == MAX_CARD_SIZE - 1);
}

void push(element card) {
	if (is_full(card_deck)) {
		fprintf(stderr, "스택 포화 에러");
		return;
	}
	else {
		card_deck.data[++(card_deck.top)] = card;
	}
}

element pop() {
	if (is_empty(card_deck)) {
		fprintf(stderr, "스택 공백 에러");
		return;
	}
	else {
		return card_deck.data[(card_deck.top)--];
	}
}
//--------------------------------------------------

//---------------------리스트관련 함수----------------------------
void init(hand_cards* head) {
	head->Llist = head;
	head->Rlist = head;
}

void insert(hand_cards* before, element data) {
	hand_cards* node = (hand_cards*)malloc(sizeof(hand_cards));
	node->data = data;

	node->Rlist = before->Rlist;
	before->Rlist->Llist = node;
	node->Llist = before;
	before->Rlist = node;
}

void delete(hand_cards* haed, hand_cards* removed) {
	if (haed == NULL)	return;
	removed->Rlist->Llist = removed->Llist;
	removed->Llist->Rlist = removed->Rlist;

	free(removed);
}

void print_hand(hand_cards* head) {
	hand_cards* p;
	for (p = head->Rlist; p->Rlist != head; p = p->Rlist) {
		showcard(p->data);
	}
}
//--------------------------------------------------

// 초기 시작 화면 몇 명의 CPU와 게임을 할 것인지 리턴
void start() {
	int i = 0;
	char choice1;
	printf("     블랙잭 게임에 오신 것을 환영합니다!     \n");
	printf("            게임을 시작하시겠습니까?         \n");
	printf("                    [Y/N]                      ");

	scanf("%c", &choice1);

	// Y나 N을 누르지 않을경우
	while ((choice1 != 'Y') && (choice1 != 'y') && (choice1 != 'N') && (choice1 != 'n'))
	{
		printf("\n");
		printf("입력이 잘못되었습니다. 다시 입력해주세요 [Y/N].\n");
		scanf("%c", &choice1);
	}

	// Y나 N을 누를 경우
	if (choice1 == 'Y' || choice1 == 'y') {
		printf("\n       PLAYER를 몇 명으로 하시겠습니까?  (최대 4명)      ");
		scanf("%d", &player_num);	//본인 포함 플레이어의 수
	}
	else if (choice1 == 'N' || choice1 == 'n') {
		printf("             게임을 종료하겠습니다.             \n");
		exit(0);
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

void shakedeak() {
	element cards[52];
	element card;

	for (int i = 0; i < 52; i++) {
		strcpy(card.pattern, shape[i / 13]);
		card.num = (i % 13) + 1;
		cards[i] = card;
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
		push(cards[i]);
	}
}

void make_player() {
	for (int i = 0; i < player_num; i++) {
		
		player_arr[i].coin == cash;
		//init(player_arr[i].hand);
	}
}

void play() {

}

int betting(player* user) {

}
