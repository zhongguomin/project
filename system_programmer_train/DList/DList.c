/****************************************
 *	双向循环链表的实现
 *	DList.c
 *	Gene At 2014-04-21
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include "DList.h"


pmyNode CreateNode(int data) 
{
	pmyNode pnode = (pmyNode)malloc(sizeof(MyNode));
	pnode->data = data;
	pnode->left = pnode->right = pnode;
	return pnode;
}

pmyNode CreateList(int head)
{
	return CreateNode(head);
}

pmyNode InsertNode(pmyNode node, int data)
{
	pmyNode pnode = CreateNode(data);
	pmyNode ptmp = node->left;

	node->left->right = pnode;
	node->left = pnode;
	
	pnode->right = node;
	pnode->left = ptmp;

	return node;
}

pmyNode FindNode(pmyNode node, int data)
{
	pmyNode pnode = node->right;
	while(pnode != node) {
		if(pnode->data == data)	return pnode;
		pnode = pnode->right;
	}

	return NULL;
}

pmyNode DelectNode(pmyNode node, int data)
{
	pmyNode pnode = FindNode(node, data);
	if(NULL == pnode)	return NULL;

	pnode->left->right = pnode->right;
	pnode->right->left = pnode->left;

	return node;
}

int GetLenght(pmyNode node)
{
	int nCount = 0;
	pmyNode pnode = node->right;

	while(pnode != node) {
		nCount++;
		pnode = pnode->right;
	}

	return nCount;
}

void PrintList(pmyNode node)
{
	pmyNode pnode;

	if(NULL == node)	return;

	pnode = node->right;
	while(pnode != node && pnode != NULL) {
		printf("%d	", pnode->data);
		pnode = pnode->right;
	}
	printf("\n");
}

int GetMaxData(pmyNode node)
{
	int max = 0;
	pmyNode pnode = node->right;

	while(pnode != NULL && pnode != node) {
		if(pnode->data > max)	max = pnode->data;
		pnode = pnode->right;
	}

	return max;
}

int GetListSum(pmyNode node)
{
	int sum = 0;
	pmyNode pnode = node->right;

	while(pnode != NULL && pnode != node) {
		sum += pnode->data;
		pnode = pnode->right;
	}

	return sum;
}

void DelectList(pmyNode node)
{
	if(NULL == node)	return;

	pmyNode pnode = node->right;
	pmyNode ptmp;

	while(pnode != node) {
		ptmp = pnode;
		pnode = pnode->right;
		free(ptmp);
	}
	free(node);
}

void ClearList(pmyNode node)
{
	if(NULL == node)	return;

	pmyNode pnode = node->right;
	pmyNode ptmp;

	while(pnode != node) {
		ptmp = pnode;
		pnode = pnode->right;
		free(ptmp);
	}

	node->right = node->left = node;
}

void printfHowUse()
{
	printf("======== Main Menu ========\n");\
    printf("1   InsertNode\n");
    printf("2   DelectNode\n");
    printf("3   FindNode\n");
    printf("4   GetLenght\n");
    printf("5   PrintList\n");
    printf("7   ClearList\n");
    printf("8   GetMaxData\n");
    printf("9   GetListSum\n");
    printf("0   quit\n\n");
    printf("===========================\n");
}

