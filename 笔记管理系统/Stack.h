#include<stddef.h>
#include "serch.h"

typedef struct node seqStackType;

typedef struct seqStack
{
    seqStackType *data;
    size_t size;
    //��ʾdata���ڴ��������ɵ�Ԫ�ظ���
    size_t capacity;
}seqStack;

seqStack stack;

//��ʼ������
void seqStackInit(seqStack *stack);
//���ٺ���
void seqStackDestroy(seqStack *stack);
//��ջ����
void seqStackPush(seqStack *stack,seqStackType value);
//��ջ����
void seqStackPop(seqStack *stack);
//ȡջ��Ԫ�غ���
int seqStackGetTop(seqStack *stack,seqStackType *value);
