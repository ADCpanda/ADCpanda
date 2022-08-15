#include <stdio.h>
#include <stdlib.h>

typedef struct ElemType {
    int data;

}ElemType,*PElemType;
//链表
typedef struct Lnode {
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;
//顺序表
typedef struct SqList {
   PElemType data;
   int Length;
}SqList,*PSqList;

int ListLength(LinkList L)
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
int GetElem_L(LinkList L, int i, ElemType e)
{
    Lnode *p;
    p = L->next;
    int j = 1;
    while(p && j < i){
      p = p->next;
    }
    if(!p || j > i){
        return -1;
    }
    e = p->data;
    return 0;
}
LinkList LocateElem(LinkList L,  ElemType e)
{
    Lnode *p;
    p = L->next;
    while(p && p->data.data!=e.data){
        p = p->next;
    }
    return p;
}
int ListInsert(LinkList L, int i, ElemType e)
{
    Lnode *p, *q;
    p = L;
    int j;
    while(p && j < i - 1){
        p = p->next;
        ++j;
    }
    if( !p || j > i-1)
        return -1;
    q = (LinkList)malloc(sizeof(Lnode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 0;
}
LinkList union_List(LinkList La, LinkList Lb)
{
    int La_len, Lb_len;
    La_len = ListLength(La);
    Lb_len = ListLength(Lb);
    int i;

    for(i = 0; i < Lb_len; i++){
        GetElem_L(Lb, i, Lb->data);
        if(!LocateElem(La, Lb->data)){
            ListInsert(La, ++La_len, Lb->data);
        }
    }
    return La;
}
//有序表合并--用顺序表实现
LinkList Selete_List(PSqList La, PSqList Lb)
{
  PElemType Pa, Pb, Pc, Pa_last, Pb_last;
  PSqList Lc;
  Lc->data = (PElemType)malloc(sizeof(ElemType));
  Lc->Length = La->Length + Lb->Length;
  Pc = Lc->data;
  Pa_last = &La->data[La->Length-1];
  Pb_last = &Lb->data[Lb->Length-1];
  int i=0;
  while(Pa <= Pa_last && Pb <= Pb_last){
    if(Pa->data <= Pb->data){
        Pc = &Lc->data[i];
        Pa = &La->data[i];
        Pc->data= Pa->data;
        i++;

      }else{
        Pc = &Lc->data[i];
        Pb= &Lb->data[i];
        Pc->data= Pb->data;
        i++;
        }

  }
  while(Pa <= Pa_last){
        Pc = &Lc->data[i];
        Pa = &La->data[i];
        Pc->data= Pa->data;
        i++;

  }
  while(Pb <= Pb_last){
        Pc = &Lc->data[i];
        Pb= &Lb->data[i];
        Pc->data= Pb->data;
        i++;
  }


}

//有序表合并--用链表实现
void MergeList(LinkList La, LinkList Lb, LinkList Lc)
{
    Lnode *pa, *pb, *pc;
    pa = La->next; pb = Lb->next;
    pc = Lc = La;
    while(pa && pb){
        if(pa->data.data <= pb->data.data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }else{
         pc->next = pb;
         pc = pb;
         pb = pb->next;
        }
        pc->next = pa ?pa:pb;
        free(Lb);
    }
}

