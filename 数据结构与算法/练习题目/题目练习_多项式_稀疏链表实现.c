#include <stdio.h>
#include <stdlib.h>
//题目 A（x）= 7 + 3x + 9x^8 +5x^17
//     B (x) = 8x + 22x^7 -9x^8;
typedef struct Nnode{
    float codf;//系数
    int  expn ; //ָ指数
    struct Nnode *next;

}Nnode, *PNode;

PNode CreateList(void)
{
    PNode headNode = (PNode)malloc(sizeof(Nnode));
    headNode->codf = 0;
    headNode->expn = 0;
    headNode->next = NULL;
    return headNode;
}
PNode CreateNewNode(float codf, int expn)
{
     PNode newNode = (PNode)malloc(sizeof(Nnode));
     newNode->codf = codf;
     newNode->expn = expn;
     newNode->next = NULL;
     return newNode;
}
void insertNodeByEnd(PNode headNode,float codf, int expn)
{
    PNode newNode = CreateNewNode(codf, expn);
    PNode p;
    p = headNode;
    while(p->next){
        p = p->next;
    }
    p->next = newNode;

}
void printList(PNode headNode)
{
    PNode pMove = headNode->next;
    while(pMove){
        printf(" %f^%d",pMove->codf, pMove->expn);
        pMove = pMove->next;
    }
    printf("\n");
}

int main()
{
    Nnode *LA, *LB,*LC, *pa, *pb, *pc;
    LA = CreateList();
    LB = CreateList();
    LC = CreateList();
    insertNodeByEnd(LA, 7, 0);
    insertNodeByEnd(LA, 3, 1);
    insertNodeByEnd(LA, 9, 8);
    insertNodeByEnd(LA, 5, 17);

    insertNodeByEnd(LB, 8, 1);
    insertNodeByEnd(LB, 22, 7);
    insertNodeByEnd(LB, -9, 8);

   pa = LA;
   pb = LB;
   pc = LC;

    while(pa && pb){
        if(pa->expn > pb->expn){
            pc->next = pb;
            pb = pb->next;
            pc = pc->next;
        }else if(pa->expn < pb->expn){
            pc->next = pa;
            pa = pa->next;
            pc = pc->next;
        }else{
         Nnode *b;
         if((pa->codf)+(pb->codf) !=0){
         b =  CreateNewNode((pa->codf)+(pb->codf),pa->expn);
         pc->next = b;
         pc = pc->next;
         }
         pa = pa->next;
         pb = pb->next;


        }
      pc->next = pa ? pa:pb;
    }
    printList(LA);
    return 0;
}
