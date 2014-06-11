/**
 * 链式栈的实现
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


Stack* InitStack()
{
	Stack* ps = (Stack*)malloc(sizeof(Stack));

	if(ps != NULL) {
		ps->top = NULL;
		ps->size = 0;
	}

	return ps;
}

int IsEmpty(Stack* ps)
{
	if(ps->top == NULL && ps->size == 0)	return 1;
	else	return 0;
}

int GetSize(Stack* ps)
{
	return ps->size;
}

PNode Push(Stack* ps, Item item)
{
	PNode pnode = (PNode)malloc(sizeof(Node));

	if(pnode != NULL) {
		pnode->data = item;
		pnode->down = GetTop(ps, NULL);
		ps->size++;
		ps->top = pnode;
	}

	return pnode;
}

PNode GetTop(Stack* ps, Item* pitem)
{
	if(IsEmpty(ps) != 1 && pitem != NULL) {
		*pitem = ps->top->data;
	}

	return ps->top;
}

PNode Pop(Stack* ps, Item* pitem)
{
	PNode p = ps->top;

	if(IsEmpty(ps) != 1 && p != NULL) {
		if(pitem != NULL)	*pitem = p->data;
		ps->size--;
		ps->top = ps->top->down;
		free(p);
	}

	return ps->top;
}

void DestroyStack(Stack* ps)
{
	if(IsEmpty(ps) != 1)	ClearStack(ps);
	free(ps);
}

void ClearStack(Stack* ps)
{
	while(IsEmpty(ps) != 1) {
		Pop(ps, NULL);
	}
}

void StackTraverse(Stack* ps, void (*visit)())
{
	PNode p = ps->top;
	int i = ps->size;

	while(i--) {
		visit(p->data);
		p = p->down;
	}
}


