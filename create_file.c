#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct node{           
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
}node ;

node* POINTER;     //全局变量，实时指向用户打开的当前目录 
node* HEAD;        //树的头节点 

int Today(void) //获取当前时间
{}

void create(char* name){  //创建txt文件 
	if(check(name,POINTER)){  //先检查文件是否重名 
		printf("文件重名！\n");
		return;
	}
	FILE* fp=fopen(name,"r");  //创建文件 
	if(fp==0){
		printf("创建失败！\n");
		return ;
	}
	fclose(fp);  
	node* pNew=(node*)malloc(sizeof(node));
	pNew->label = 1;
	strcpy(pNew->name,name);
	pNew->P_left=NULL;
	pNew->time = Today();
	strcpy(pNew->path,POINTER->path);
	strcat(pNew->path,"\\");
	strcat(pNew->path,name);
	//连接结点 
	if(POINTER->P_left==NULL){   //当前目录为空文件夹时，直接连接即可 
		pNew->P_parents=POINTER;
		POINTER->P_left=pNew;
		pNew->P_right=NULL;
	}
	else{
		node* p=POINTER->P_left;
        while(p->P_right!=NULL&&p->label==0){ //将结点插在文件夹之后，原有文件之前 
        	p=p->P_right;
		}
		pNew->P_parents=p;
		pNew->P_right=p->P_right;
		if(p->P_right != NULL) p->P_right->P_parents = pNew;  
		p->P_right=pNew;
		
	}
}


int check(char name[],node* p){  //查重：在p指向的目录下查找是否有名字为name的文件/目录
	if(p->P_left=NULL) 
		return 0;     //当前目录下无文件或文件夹 
	p=p->P_left;   
	while(p!=NULL){
		if(!strcmp(p->name,name))  return 1;  //找到重名文件/文件夹 
		else p=p->P_right;
	}
	return 0;    //未找到重名文件/文件夹 
}


int main(){
	return 0;
}
