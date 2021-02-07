#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

//初始化函数
void seqStackInit(seqStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (seqStackType*)malloc(stack->capacity * sizeof(seqStackType));
}
//销毁函数
void seqStackDestroy(seqStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    free(stack->data);
    stack->data == NULL;
    stack->size = 0;
    stack->capacity = 0;
}
//栈的扩容函数
void seqStackReSize(seqStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    //栈的实际存储的元素个数小于规定的能容纳的最大数量
    if(stack->size < stack->capacity)
    {
        //无需扩容，直接返回
        return;
    }
    //扩容规则由自己决定
    stack->capacity = stack->capacity * 2 + 1;
    seqStackType *new_ptr = (seqStackType*)malloc(stack->capacity * sizeof(seqStackType));
    //将原来栈的元素一一复制到新扩容的栈中
    size_t i = 0;
    for(;i < stack->size;i++)
    {
        new_ptr[i] = stack->data[i];
    }
    //释放掉旧栈
    free(stack->data);
    //将栈的数据域指向新栈的数据域
    stack->data = new_ptr;
    return;
}
//入栈函数
void seqStackPush(seqStack *stack,seqStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    //每次入栈前都需要判断栈是否含有空间供我们插入元素
    if(stack->size >= stack->capacity)
    {
        //如果栈空间满了
        //则需要扩容
        seqStackReSize(stack);
    }
    //将栈的最后一个元素设置为需要入栈的元素值
    //将有效元素个数+1
    stack->data[stack->size++] = value;
}
//出栈函数
void seqStackPop(seqStack *stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空栈无法再进行出栈操作
        return;
    }
    //出栈只需要将栈的有效元素个数减1
    --stack->size;
}
//取栈顶元素函数
//失败返回0，成功返回1
int seqStackGetTop(seqStack *stack,seqStackType *value)
{
    if(stack == NULL)
    {
        //非法输入
        return 0;
    }
    if(stack->size == 0)
    {
        //空栈
        return 0;
    }
    //value为一个输出型参数
    //栈顶元素为最后一个入栈的元素
    *value = stack->data[stack->size-1];
    return 1;
}
//打印函数
void Print(seqStack *stack,const char *msg)
{
    printf("[%s]\n",msg);
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空栈
        printf("\n");
        return;
    }
    size_t i = 0;
    for(;i < stack->size;i++)
    {
        printf("%c ",stack->data[i]);
    }
    printf("\n\n");
}

//主函数调用测试函数
int main()
{
    return 0;
}
