#include <stdio.h>
#include <stdlib.h>

typedef struct ElemType {
    int data;
}ElemType,*PElemType;

typedef struct Lnode {
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;

int InitList_L(LinkList L)
{
    L = (LinkList)malloc(sizeof(Lnode));
    L->next = NULL;
    return 0;
}

//判断一个链表是否为空
int ListEmpty(LinkList L)
{
    if(L->next)
      return 0;
    else
      return 1;
}
//单链表的销毁
int DestroyList(LinkList L)
{
    Lnode *p;
    while(L){
        p = L;
        L = L->next;
        free(p);
    }
}

//清空一个单链表
int ClearList(LinkList L)
{
    Lnode *p, *q;
     p = L->next;
     while(p){
        q = p->next;
        free(p);
        p = q;
     }
     L->next = NULL;
     return 0;

}
//求链表的表长
int ListLength_L(LinkList L)
{
    int i = 0;
    Lnode *p;
    p = L->next;
   while(p){
     i++;
     p = p->next;
   }
  return i;
}

//取单链表中第i个元素的内容
int SearchList(LinkList L,int num)
{
    Lnode *p;
    p = L->next;
    int i = 0;
    for(i = 0; i < num; i++){
        p = p->next;
        if(!p){
            return -1;
        }
    }
    return p->data.data;
}

int GetElem_L(LinkList L, int i, ElemType e)
{
    Lnode *p;
    p = L->next;
    int j = 1;
    while(p && j < i){
        p = p->next; ++j;
    }
    if(!p || j > i)
        return -1;
    e = p->data;
    return 0;
}
//按值查找，给出位置
LinkList LocateElem(LinkList L,  ElemType e)
{
    Lnode *p;
    p = L->next;
    while(p && p->data!=e){
        p = p->next;
    }
    return p;
}

//在第i个节点前，插入值为e的新节点
int ListInsert(LinkList L,  ElemType e, int i)
{
    Lnode *p, *q;
    p = L;
    int j;
    while(p &&j <i-1){
        p = p->next;
        ++j;

    }
    if(!p || j > i-1)
        return -1;
    q = (LinkList)malloc(sizeof(Lnode));
    q->data = e;
    q->next = p->next;
    p->next = q;

    return 0;
}
// 删除第i个节点

int Delete(LinkList L, int i, ElemType e)
{
     Lnode *p, *q;
     p = L;
     int j = 0;
     while(p->next && j < i-1){
          p = p->next;
           ++j;
     }
     if(!(p->next) || j > i-1)
        return -1;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return 0;
}
int main()
{
    return 0;
}
