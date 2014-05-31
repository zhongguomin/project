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

int main(void)
{
	int choose;
	int data;
	int flag = 1;
	pmyNode pnode;
	pmyNode list = CreateList(0);

	while(flag) {
		printfHowUse();
		scanf("%d", &choose);

		switch(choose) {
			case 1:
				printf("Input the data to insert: ");
				scanf("%d", &data);
				list = InsertNode(list, data);
				break;
			case 2:
				printf("Input the data to delete: ");
				scanf("%d", &data);
				DelectNode(list, data);
				break;
			case 3:
				printf("Input the data to find: ");
				scanf("%d", &data);
				pnode = FindNode(list, data);
				if(NULL != pnode)	printf("Find succeed..!!\n");
				else                printf("Find failed..!!\n");
				break;
			case 4:
				printf("The list's length is %d", GetLenght(list));
				break;
			case 5:
				PrintList(list);
				break;
			case 7:
				ClearList(list);
				break;
			case 8:
				printf("The list's max is %d", GetMaxData(list));
				break;
			case 9:
				printf("The list's sum is %d", GetListSum(list));
				break;
			case 0:
				DelectList(list);
				flag = 0;
				break;
			default:
				printf("Please select 0-7 numbers..!!\n");
				break;
		}
		printf("\n\n\n");
	}

	return 0;
}








