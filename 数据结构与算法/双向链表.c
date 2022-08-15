#include <stdio.h>
#include <stdlib.h>
typedef struct ElemType {
    int data;
    char *name;
}ElemType,*PElemType;

typedef struct DuLNode {
    ElemType data;
    struct DuLNode  *prior,*next;
}DuLNode, *DuLinkList;

//双向链表插入
DuLinkList LocateList(DuLinkList L, int i)
{
    DuLNode *p;
     p = L;
     int k;
     while(p &&k < i){
         p = p->next;
         k++;
     }
     if( !p || k > i)
      return NULL;

      return p;

}
int Listlnsert_Dul(DuLinkList L, int i, ElemType e)
{
    //在带头结点的双向循链表L中第i个位置之前插入元素e
     DuLNode *s, *p;
     int err;
    p = LocateList(L, i);
    if(!p)
    return -1;
    s = (DuLinkList)malloc(sizeof(DuLNode));
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return 0;


}
//双链表删除
int Delate_Dul(DuLinkList L, int i, ElemType e)
{
   DuLNode *p;
   int err;
   p = LocateList(L, i);
   if(!p)
    return -1;

    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return 0;


}
