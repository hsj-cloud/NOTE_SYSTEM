#ifndef __SERCH_H__
#define __SERCH_H__

struct node{           
 int label;         //��ǩ��1�������ļ���0�������ļ��� 
 char name[260];    //�ļ����У����� 
 char path[260];    //�ļ����У�·�� 
 char *tag_1[10];   //������ǩ 
 char *tag_2[10];
 char *tag_3[10];
 int time;          //����޸�ʱ�� 
 struct node* P_left;      //ָ�����ӵ�ָ�� 
 struct node* P_right;     //ָ���Һ��ӵ�ָ�� 
 struct node* P_parents;   //ָ�򸸽���ָ�� 
};

#endif
