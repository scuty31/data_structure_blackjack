#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>

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
	int stop;
	int result;
	int character;
	hand_cards hand;
}player;	//player

typedef struct dealer {
	int hand_count;
	int stop;
	int result;
	int character;
	hand_cards hand;
}deal;	//dealer

void init_stack();
int is_empty();
int is_full();
void push(element card);
element pop();

void init(hand_cards* head);
void insert(hand_cards* before, element data);
void delete(hand_cards* head, hand_cards* removed);
void print_hand(hand_cards* head);

int start();		//시작 준비
void make_player(int player_num);	//플레이어 준비 함수
void make_dealer();				//딜러 준비 함수
void play(int player_num);		//블랙잭 플레이 함수

int betting(int u_coin, int player_num);	//배팅하는 함수
void getCard(int num);	//카드를 받는 함수
void player_play(int num);	//플레이어 플레이 함수

void getCard_dealer();	//딜러가 카드를 받는 함수
void dealer_play();		//딜러 플레이 함수

void print_all(int player_num);	//모든 player 카드 출력
void showcard(int num);	//카드 출력 함수
void shakedeak();	//카드 섞는수함수
int player_character();		//player 성격
int dealer_character();		//dealer 성격
void change(char* hit);

deck card_deck;
char shape[4][3] = { "♠", "◆", "♥", "♣" };	//카드 문양
player player_arr[4];	//최대 플레이어 4명
deal dealer;

int main(void) {

	int player_num = start();
	char select;

	init_stack();
	shakedeak();
	
	while (player_arr[0].coin > 0) {
		play(player_num);
		
		for (int i = 1; i < player_num; i++) {	//돈 다 떨어진 player 삭제
			if (player_arr[i].coin == 0) {
				for (int j = i; j < player_num - 1; j++) {
					player_arr[j] = player_arr[j + 1];
				}
				player_num--;
			}
		}

		system("cls");
		printf("             게임이 종료되었습니다.\n");
		printf("            게임을 계속하시겠습니까?         \n");
		printf("                    [Y/N]                   \n ");
		printf("command : ");
		scanf("%c", &select);
	}
	
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
		printf("┌─────┐\t");
	}
	printf("┌─────┐\n");

	for (p = head->Rlist; p->Rlist != head; p = p->Rlist) {
		printf("│%s    │\t", p->data.pattern);
	}
	printf("│%s    │\n", p->data.pattern);

	for (p = head->Rlist; p->Rlist != head; p = p->Rlist) {
		showcard(p->data.num);
	}
	showcard(p->data.num);
	printf("\n");

	for (p = head->Rlist; p->Rlist != head; p = p->Rlist) {
		printf("│    %s│\t", p->data.pattern);
	}
	printf("│    %s│\n", p->data.pattern);

	for (p = head->Rlist; p->Rlist != head; p = p->Rlist) {
		printf("└─────┘\t");
	}
	printf("└─────┘\n");
}
//--------------------------------------------------

// 초기 시작 화면 몇 명의 CPU와 게임을 할 것인지 정함
int start() {
	int player_num;
	char choice1;
	printf("     블랙잭 게임에 오신 것을 환영합니다!     \n");
	printf("            게임을 시작하시겠습니까?         \n");
	printf("                    [Y/N]                   \n ");

	

	while (1) {
		printf("\ncommand = ");
		scanf("%c", &choice1);
		if (choice1 == 'Y' || choice1 == 'y') {
			system("cls");
			printf("\n       PLAYER를 몇 명으로 하시겠습니까?  (최대 4명)\n");
			printf("\ncommand = ");
			scanf("%d", &player_num);	//본인 포함 플레이어의 수
			if (player_num < 1 || player_num > 4) {
				printf("입력이 잘못되었습니다. 다시 입력해주세요.");
			}
			else {
				system("cls");
				printf("\n");
				make_player(player_num);
				make_dealer();
				break;
			}
		}
		else if (choice1 == 'N' || choice1 == 'n') {
			system("cls");
			printf("\n");
			printf("          게임을 종료하겠습니다.             \n");
			exit(0);
		}
		else {
			system("cls");
			printf("\n");
			printf("입력이 잘못되었습니다. 다시 입력해주세요.\n");
		}
	}
	
	return player_num;
}


void showcard(int num) {	//카드 출력
	if (num == 1) {
		printf("│  A  │\t");
	}
	else if (num < 11) {
		printf("│  %d  │\t", num);
	}
	else if (num == 11) {
		printf("│  J  │\t");
	}
	else if (num == 12) {
		printf("│  Q  │\t");
	}
	else if (num == 13) {
		printf("│  K  │\t");
	}
	else {
		fprintf(stderr, "카드 에러");
	}
}

void shakedeak() {
	element cards[52];	//카드 덱
	element card;		//카드

	for (int i = 0; i < 52; i++) {
		strcpy(card.pattern, shape[i / 13]);
		card.num = (i % 13) + 1;
		cards[i] = card;
	}	// set cards

	for (int i = 0; i < 300; i++) {	//카드 섞기
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

	for (int i = 0; i < 52; i++) {	//카드를 덱에 집어넣기
		push(cards[i]);
	}
}

void make_player(int player_num) {
	for (int i = 0; i < player_num; i++) {
		player_arr[i].coin = cash;
		player_arr[i].hand_count = 0;
		player_arr[i].stop = 0;
		player_arr[i].result = 0;
		player_arr[i].character = player_character();
		init(&player_arr[i].hand);
	}
}

void make_dealer() {
	dealer.hand_count = 0;
	dealer.result = 0;
	dealer.stop = 0;
	dealer.character = dealer_character();
	init(&dealer.hand);
}

void play(int player_num) {
	int betting_cash = 0;	//이기면 받음
	betting_cash = betting(player_arr[0].coin, player_num);
	int is_stop = 0;
	char hit[5];
	for (int i = 0; i < player_num; i++) {
		getCard(i);
	}
	getCard_dealer();


	
	while (1)
	{
		is_stop = 0;

		system("cls");
		printf("your cash = $%d\n", player_arr[0].coin);
		print_all(player_num);
		printf("\n");
		system("pause");

		if (player_arr[0].stop == 0) {
			printf("           HIT OR STAY \n\n");
			printf("     ┏━━━━━┓         ┏━━━━━━┓\n");
			printf("     ┃ HIT ┃         ┃ STAY ┃\n");
			printf("     ┗━━━━━┛         ┗━━━━━━┛\n");
			printf("commend : ");
			scanf("%s", hit);

			change(&hit);

			if (strcmp(hit, "stay") == 0) {
				player_arr[0].stop = 1;
				is_stop++;
			}


			//hit 하거나 stay

		}
		else {	//stay를 했으면
			is_stop++;
		}

		for (int i = 1; i < player_num; i++) {
			if (player_arr[i].stop == 0) {	//hit
				player_play(i);
			}
			else {		//stay를 한 이후
				is_stop++;
			}
		}

		if (dealer.stop == 0) {
			dealer_play();
		}
		else {		//stay를 한 이후
			is_stop++;
		}

		if (is_stop == player_num + 1)	//만약 모든 이들이 stay를 했다면
			break;
	}
}

int betting(int u_coin, int player_num) {
	int bet;
	system("cls");
	printf("your cash = $%d\n", u_coin);
	printf("얼마나 베팅할 것인가요?\n");
	printf("$ ");
	scanf("%d", &bet);
	printf("\n");
	printf("--------------------------------------\n");
	printf("                c o i n      \n");
	printf("--------------------------------------\n");

	for (int i = 0; i < player_num; i++) {
		if (player_arr[i].coin <= bet) {
			printf("             player %d : ALL-IN\n", i+1);
			player_arr[i].coin = 0;
		}
		else {
			player_arr[i].coin = player_arr[i].coin - bet;
			printf("             player %d : $%d\n", i+1, player_arr[i].coin);
		}
	}
	printf("--------------------------------------\n");
	system("pause");
	return bet;
}

void getCard(int num) {		//player가 카드를 받는 함수
	if (player_arr[num].stop == 1) {
		return;
	}

	element data = pop();
	insert(&player_arr[num].hand, data);
	player_arr[num].hand_count++;		//카드를 받으면 손패 1장 추가
	
	/*
		if (player_arr[num].hand_count == 1 && data.num > 10) {
		player_arr[num].result += 10;
	}
	else {
		player_arr[num].result += data.num;
	}
	*/

	if (data.num > 10) {
		player_arr[num].result += 10;
	}
	else if (num == 0 && data.num == 1) {	//사용자에게 a 카드가 나온다면
		int a = 0;
		printf("A를 1로 사용하겠습니까? 아니면 13으로 사용하겠습니까?\n");
		printf("command : ");
		scanf("%d", a);
		player_arr[0].result += a;
	}
	else if (num != 0 && data.num == 1) {		//cpu에게 a 카드가 나온다면
		if (player_arr[num].result + 13 > 21)
			player_arr[num].result += 1;
		else
			player_arr[num].result += 13;
	}
	else {		//일반 카드 더하기
		player_arr[num].result += data.num;
	}
}

void getCard_dealer() {		//딜러가 카드를 받는 함수
	if (dealer.stop == 1)
		return;

	element data = pop();
	insert(&dealer.hand, data);
	dealer.hand_count++;

	if (dealer.hand_count == 1 && data.num > 10) {
		dealer.result += 10;
	}
	else if (data.num == 1) {
		if (dealer.result + 13 > 21)
			dealer.result += 1;
		else
			dealer.result += 13;
	}
	else if (data.num > 10) {
		dealer.result += 10;
	}
	else {
		dealer.result += data.num;
	}

}

void print_all(int player_num) {	//카드 출력
	printf("--------------------------------------\n");
	printf("               YOUR CARD\n");
	printf("--------------------------------------\n");
	print_hand(&player_arr[0].hand);
	printf("--------------------------------------\n");
	printf("your result = % d\n", player_arr[0].result);

	for (int i = 1; i < player_num; i++) {
		printf("--------------------------------------\n");
		printf("           PLAYER %d CARD\n", i + 1);
		printf("--------------------------------------\n");
		print_hand(&player_arr[i].hand);
		printf("--------------------------------------\n");
		printf("player %d result = %d\n", i+1, player_arr[i].result);
	}

	printf("--------------------------------------\n");
	printf("             DEALER CARD\n");
	printf("--------------------------------------\n");
	print_hand(&dealer.hand);
	printf("--------------------------------------\n");
	printf("dealer result = %d\n", dealer.result);
	printf("--------------------------------------\n");
}

int player_character() {		//캐릭터 난수
	int x = rand() % 17;
	int y = rand() % 13;
	int z = rand() % 7;
	int character = (x * y * z) % 50;

	return character;
}

int dealer_character() {		//캐릭터 난수
	int x = rand() % 5;
	int y = rand() % 13;
	int z = rand() % 7;
	int character = (x * y * z) % 30;

	return character;
}

void player_play(int num) {
	int n;
	if (player_arr[num].result < 17)		//손패가 17 미만이면 hit
		getCard(num);
	else if (player_arr[num].result >= 17 && player_arr[num].result < 19) {	// 현재 손패가 17, 18이면
		n = rand() % 100;					//100 난수
		if (n < player_arr[num].character)		//만약 캐릭터 변수보다 낮게 나오면
			getCard(num);					//hit
		else								//아니면
			player_arr[num].stop = 1;		//stay
	}
	else									//현재 손패가 19 이상이면
		player_arr[num].stop = 1;			//stay
}

void dealer_play() {
	int n;
	if (dealer.result < 17)		//손패가 17 미만이면 hit
		getCard_dealer();
	else if (dealer.result >= 17 && dealer.result < 19) {	// 현재 손패가 17, 18이면
		n = rand() % 100;					//100 난수
		if (n < dealer.character)		//만약 캐릭터 변수보다 낮게 나오면
			getCard_dealer();					//hit
		else								//아니면
			dealer.stop = 1;		//stay
	}
	else									//현재 손패가 19 이상이면
		dealer.stop = 1;			//stay
}

void change(char* hit) {	//대문자를 소문자로 변경
	for (int i = 0; i < 5; i++) {
		{
			if ((hit[i] >= 'A') && (hit[i] <= 'Z'))
			{
				hit[i] = hit[i] - 'A' + 'a';
			}
		}
	}
}