#include "stack.h"

void StackInit(ST* ps)
{
	assert(ps);
	ps->a = (STDataType*)malloc(sizeof(STDataType)*4);
	if (ps->a == NULL)
	{
		printf("rrealloc fail\n");
		exit(-1);
	}
	ps->capacity = 4;
	ps->top = 0;          //top指向栈顶的前一个数据，这样每次入栈top++，top指向数据
	                      //top指向栈顶时，每次入栈top++，top指向栈顶的下一个空间
}
void StackDestory(ST* ps) //销毁
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}
void StackPush(ST* ps, STDataType x)//入栈
{
	assert(ps);
	if (ps->top == ps->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, ps->capacity * 2 * sizeof(STDataType));  //扩容二倍
		if (tmp == NULL)
		{
			printf("rrealloc fail\n");
			exit(-1);
		}
		else
		{
			ps->a = tmp;
			ps->capacity *= 2;
		}
	}
	ps->a[ps->top] = x;
	ps->top++;
}
void StackPop(ST* ps)//出栈
{
	assert(ps);
	assert(ps->top>0);  //栈空了 调用top直接报错
	ps->top--;
}
STDataType StackTop(ST* ps) //返回栈顶
{
	assert(ps);
	assert(ps->top > 0);
	return ps->a[ps->top - 1];
}
int StackSize(ST* ps)
{
	return ps->top;
}
bool StackEmpty(ST* ps)
{
	assert(ps);
	return ps->top == 0;
}
