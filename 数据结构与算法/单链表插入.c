#include <stdio.h>
#include <stdlib.h>
typedef struct ElemType {
    int data;
    char *name;
}ElemType,*PElemType;

typedef struct Lnode {
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;

void CreateList(LinkList L)
{
    L = (LinkList)malloc(sizeof(Lnode));
    L->next =NULL;
}
//头插法
void HeadInList(LinkList L, ElemType data)
{
    Lnode *p;
    p = (LinkList)malloc(sizeof(Lnode));
    p->data = data;
    p->next = L->next;
    L->next = p;
}
//尾插法
void EndInList(LinkList L, ElemType data)
{
    Lnode *p, *q;
    p = (LinkList)malloc(sizeof(Lnode));
    q = (LinkList)malloc(sizeof(Lnode));
    p = L;
    while(p->next){
        p = p->next;
    }
    q->data = data;
    q->next = NULL;
    p->next = q;

}
//