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
    Node(int i, Node* ptr)//ptr �ڿ� �߰��Ѵ�.
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
    DLinkedList() { //������
        count = 0;
        head = new Node(); //���̸� �����ؼ� ������ �ְ��Ѵ�.
        tail = new Node(); //���̸� �����ؼ� ������ �ְ��Ѵ�.
        head->next = tail; //���ο����Ѵ�.
        tail->prev = head;
    }
    ~DLinkedList() {
        while (head->next != tail)
            head->next->selvDelete();
        delete head;
        delete tail;
    }
    void clubcard(int i) { //head ������ �߰��Ѵ�.
        new Node(i, head);
    }
    void diamondcard(int i) { //tail �տ� �߰��Ѵ�.
        new Node(i, tail->prev);
    }
    void heartcard(int i) { //tail �տ� �߰��Ѵ�.
        new Node(i, tail->prev);
    }
    void spadecard(int i) { //tail �տ� �߰��Ѵ�.
        new Node(i, tail->prev);
    }

    void firstDelete() { //head ���� ��� �����Ѵ�.
        if (head->next == tail)    return;
        head->next->selvDelete();
    }
    void endDelete() { //tail �տ� �����Ѵ�.
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
    list->clubcard(1); //1�� �����Ѵ�.(�����)
    list->clubcard(3); //3�� �����Ѵ�.(1�տ�)
    list->clubcard(5); //5�� �����Ѵ�.(3�տ�)
    list->heartcard(1); //1�� �����Ѵ�.(�����)
    list->heartcard(3); //3�� �����Ѵ�.(1�տ�)
    list->heartcard(5); //5�� �����Ѵ�.(3�տ�)
    list->spadecard(1); //1�� �����Ѵ�.(�����)
    list->spadecard(3); //3�� �����Ѵ�.(1�տ�)
    list->spadecard(5); //5�� �����Ѵ�.(3�տ�)
    list->firstDelete(); //5�� �����Ѵ�
    list->diamondcard(100); //100�� �����Ѵ�.(����ڿ�)
    list->diamondcard(200); //200�� �����Ѵ�.(100�ڿ�)
    list->diamondcard(300); //300�� �����Ѵ�.(200�ڿ�)
    list->endDelete(); //300�� �����Ѵ�.
    list->printAll();
    delete list;
}