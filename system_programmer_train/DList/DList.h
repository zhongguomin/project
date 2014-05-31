/**
 * DList.h
 */

#ifndef DLIST_H
#define DLIST_H

typedef struct MyNode {
    int data;
    struct MyNode *left;
    struct MyNode *right;
} MyNode, *pmyNode;


pmyNode CreateNode(int data);
pmyNode CreateList(int head);
pmyNode InsertNode(pmyNode node, int data);
pmyNode FindNode(pmyNode node, int data);
pmyNode DelectNode(pmyNode node, int data);
int GetLenght(pmyNode node);
void PrintList(pmyNode node);
int GetMaxData(pmyNode node);
int GetListSum(pmyNode node);
void DelectList(pmyNode node);
void ClearList(pmyNode node);
void printfHowUse();

#endif //DLIST_H
