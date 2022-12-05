#include<iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>                //Used for srand((unsigned) time(NULL)) command
#include <process.h>             //Used for system("cls") command

#define spade 06                 //Used to print spade symbol
#define club 05                  //Used to print club symbol
#define diamond 04               //Used to print diamond symbol
#define heart 03                 //Used to print heart symbol
#define RESULTS "Blackjack.txt"  //File name is Blackjack
//Global Variables
int k;
int l;
int d;
int won;
int loss;
int cash = 500;
int bet;
int random_card;
int player_total = 0;
int dealer_total;

//Function Prototypes
int clubcard();      //Displays Club Card Image
int diamondcard();   //Displays Diamond Card Image
int heartcard();     //Displays Heart Card Image
int spadecard();     //Displays Spade Card Image
int randcard();      //Generates random card

struct Node {
    int data;
    Node* next, * prev;
    Node() {
        next = prev = NULL;
        data = 0;
    }
    Node(int i, Node* ptr)//ptr 뒤에 추가한다.
    {
        data = i;
        prev = ptr;
        next = ptr->next;
        next->prev = prev->next = this;
    }
    void selvDelete() {
        prev->next = next;
        next->prev = prev;
        delete this;
    }
};

struct DLinkedList {
    Node* head;
    Node* tail;
    int count;
    DLinkedList() { //생성자
        count = 0;
        head = new Node(); //더미를 선언해서 가지고 있게한다.
        tail = new Node(); //더미를 선언해서 가지고 있게한다.
        head->next = tail; //서로연결한다.
        tail->prev = head;
    }
    ~DLinkedList() {
        while (head->next != tail)
            head->next->selvDelete();
        delete head;
        delete tail;
    }
    void clubcard(int i) { //head 다음에 추가한다.
        new Node(i, head);
    }
    void diamondcard(int i) { //tail 앞에 추가한다.
        new Node(i, tail->prev);
    }
    void heartcard(int i) { //tail 앞에 추가한다.
        new Node(i, tail->prev);
    }
    void spadecard(int i) { //tail 앞에 추가한다.
        new Node(i, tail->prev);
    }

    void firstDelete() { //head 다음 노드 삭제한다.
        if (head->next == tail)    return;
        head->next->selvDelete();
    }
    void endDelete() { //tail 앞에 제거한다.
        if (tail->prev == head) return;
        tail->prev->selvDelete();
    }
    void printAll() {
        Node* tmp = head;
        while (tmp->next != tail) {
            printf("%d\n", tmp->next->data);
            tmp = tmp->next;
        }
    }
};

int main() {
    DLinkedList* list = new DLinkedList();
    list->clubcard(1); //1을 삽입한다.(가장앞)
    list->clubcard(3); //3을 삽입한다.(1앞에)
    list->clubcard(5); //5을 삽입한다.(3앞에)
    list->heartcard(1); //1을 삽입한다.(가장앞)
    list->heartcard(3); //3을 삽입한다.(1앞에)
    list->heartcard(5); //5을 삽입한다.(3앞에)
    list->spadecard(1); //1을 삽입한다.(가장앞)
    list->spadecard(3); //3을 삽입한다.(1앞에)
    list->spadecard(5); //5을 삽입한다.(3앞에)
    list->firstDelete(); //5를 삭제한다
    list->diamondcard(100); //100을 삽입한다.(가장뒤에)
    list->diamondcard(200); //200을 삽입한다.(100뒤에)
    list->diamondcard(300); //300을 삽입한다.(200뒤에)
    list->endDelete(); //300을 삭제한다.
    list->printAll();
    delete list;
}