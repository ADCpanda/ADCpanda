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

//循环列表，假设Ta，Tb都是循环列表
LinkList Connect(LinkList Ta, LinkList Tb)
{
    Lnode *p;
    p = Ta->next;
    Ta->next = Tb->next->next;
    free(Tb->next);
    Tb->next = p;
    return Tb;
}