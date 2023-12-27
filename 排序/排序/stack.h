#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
typedef int STDataType;

typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
	
}ST;

void StackInit(ST* ps);
void StackDestory(ST* ps); //����
void StackPush(ST* ps, STDataType x); //��ջ
void StackPop(ST* ps); //��ջ
STDataType StackTop(ST* ps);
int StackSize(ST* ps);
bool StackEmpty(ST* ps);

