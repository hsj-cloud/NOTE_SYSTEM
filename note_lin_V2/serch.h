#ifndef __SERCH_H__
#define __SERCH_H__

struct node{           
 int label;         //标签：1：代表文件；0：代表文件夹 
 char name[260];    //文件（夹）名字 
 char path[260];    //文件（夹）路径 
 char *tag_1[10];   //三个标签 
 char *tag_2[10];
 char *tag_3[10];
 int time;          //最近修改时间 
 struct node* P_left;      //指向左孩子的指针 
 struct node* P_right;     //指向右孩子的指针 
 struct node* P_parents;   //指向父结点的指针 
};

#endif
