#include<stdio.h>
#include<stdlib.h>

struct Book{
    char id[20];
    char name[50];
    int price;
};

//顺序表
typedef struct {
    Book *elem;
    int length;
}SqList;
//链表
typedef struct LNode{
    Book data;
    struct LNode *next;
}LNode, *PLNode;

