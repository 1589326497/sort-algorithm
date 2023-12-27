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
	ps->top = 0;          //topָ��ջ����ǰһ�����ݣ�����ÿ����ջtop++��topָ������
	                      //topָ��ջ��ʱ��ÿ����ջtop++��topָ��ջ������һ���ռ�
}
void StackDestory(ST* ps) //����
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}
void StackPush(ST* ps, STDataType x)//��ջ
{
	assert(ps);
	if (ps->top == ps->capacity)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, ps->capacity * 2 * sizeof(STDataType));  //���ݶ���
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
void StackPop(ST* ps)//��ջ
{
	assert(ps);
	assert(ps->top>0);  //ջ���� ����topֱ�ӱ���
	ps->top--;
}
STDataType StackTop(ST* ps) //����ջ��
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
