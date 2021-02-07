#include<stddef.h>
#include "serch.h"

typedef struct node seqStackType;

typedef struct seqStack
{
    seqStackType *data;
    size_t size;
    //表示data段内存中能容纳的元素个数
    size_t capacity;
}seqStack;

seqStack stack;

//初始化函数
void seqStackInit(seqStack *stack);
//销毁函数
void seqStackDestroy(seqStack *stack);
//入栈函数
void seqStackPush(seqStack *stack,seqStackType value);
//出栈函数
void seqStackPop(seqStack *stack);
//取栈顶元素函数
int seqStackGetTop(seqStack *stack,seqStackType *value);
