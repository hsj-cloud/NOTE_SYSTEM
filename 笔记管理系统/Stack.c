#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

//��ʼ������
void seqStackInit(seqStack *stack)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;
    stack->data = (seqStackType*)malloc(stack->capacity * sizeof(seqStackType));
}
//���ٺ���
void seqStackDestroy(seqStack *stack)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    free(stack->data);
    stack->data == NULL;
    stack->size = 0;
    stack->capacity = 0;
}
//ջ�����ݺ���
void seqStackReSize(seqStack *stack)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    //ջ��ʵ�ʴ洢��Ԫ�ظ���С�ڹ涨�������ɵ��������
    if(stack->size < stack->capacity)
    {
        //�������ݣ�ֱ�ӷ���
        return;
    }
    //���ݹ������Լ�����
    stack->capacity = stack->capacity * 2 + 1;
    seqStackType *new_ptr = (seqStackType*)malloc(stack->capacity * sizeof(seqStackType));
    //��ԭ��ջ��Ԫ��һһ���Ƶ������ݵ�ջ��
    size_t i = 0;
    for(;i < stack->size;i++)
    {
        new_ptr[i] = stack->data[i];
    }
    //�ͷŵ���ջ
    free(stack->data);
    //��ջ��������ָ����ջ��������
    stack->data = new_ptr;
    return;
}
//��ջ����
void seqStackPush(seqStack *stack,seqStackType value)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    //ÿ����ջǰ����Ҫ�ж�ջ�Ƿ��пռ乩���ǲ���Ԫ��
    if(stack->size >= stack->capacity)
    {
        //���ջ�ռ�����
        //����Ҫ����
        seqStackReSize(stack);
    }
    //��ջ�����һ��Ԫ������Ϊ��Ҫ��ջ��Ԫ��ֵ
    //����ЧԪ�ظ���+1
    stack->data[stack->size++] = value;
}
//��ջ����
void seqStackPop(seqStack *stack)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    if(stack->size == 0)
    {
        //��ջ�޷��ٽ��г�ջ����
        return;
    }
    //��ջֻ��Ҫ��ջ����ЧԪ�ظ�����1
    --stack->size;
}
//ȡջ��Ԫ�غ���
//ʧ�ܷ���0���ɹ�����1
int seqStackGetTop(seqStack *stack,seqStackType *value)
{
    if(stack == NULL)
    {
        //�Ƿ�����
        return 0;
    }
    if(stack->size == 0)
    {
        //��ջ
        return 0;
    }
    //valueΪһ������Ͳ���
    //ջ��Ԫ��Ϊ���һ����ջ��Ԫ��
    *value = stack->data[stack->size-1];
    return 1;
}
//��ӡ����
void Print(seqStack *stack,const char *msg)
{
    printf("[%s]\n",msg);
    if(stack == NULL)
    {
        //�Ƿ�����
        return;
    }
    if(stack->size == 0)
    {
        //��ջ
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

//���������ò��Ժ���
int main()
{
    return 0;
}
