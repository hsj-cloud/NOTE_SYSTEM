#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct node{           
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
}node ;

node* POINTER;     //ȫ�ֱ�����ʵʱָ���û��򿪵ĵ�ǰĿ¼ 
node* HEAD;        //����ͷ�ڵ� 

int Today(void) //��ȡ��ǰʱ��
{}

void create(char* name){  //����txt�ļ� 
	if(check(name,POINTER)){  //�ȼ���ļ��Ƿ����� 
		printf("�ļ�������\n");
		return;
	}
	FILE* fp=fopen(name,"r");  //�����ļ� 
	if(fp==0){
		printf("����ʧ�ܣ�\n");
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
	//���ӽ�� 
	if(POINTER->P_left==NULL){   //��ǰĿ¼Ϊ���ļ���ʱ��ֱ�����Ӽ��� 
		pNew->P_parents=POINTER;
		POINTER->P_left=pNew;
		pNew->P_right=NULL;
	}
	else{
		node* p=POINTER->P_left;
        while(p->P_right!=NULL&&p->label==0){ //���������ļ���֮��ԭ���ļ�֮ǰ 
        	p=p->P_right;
		}
		pNew->P_parents=p;
		pNew->P_right=p->P_right;
		if(p->P_right != NULL) p->P_right->P_parents = pNew;  
		p->P_right=pNew;
		
	}
}


int check(char name[],node* p){  //���أ���pָ���Ŀ¼�²����Ƿ�������Ϊname���ļ�/Ŀ¼
	if(p->P_left=NULL) 
		return 0;     //��ǰĿ¼�����ļ����ļ��� 
	p=p->P_left;   
	while(p!=NULL){
		if(!strcmp(p->name,name))  return 1;  //�ҵ������ļ�/�ļ��� 
		else p=p->P_right;
	}
	return 0;    //δ�ҵ������ļ�/�ļ��� 
}


int main(){
	return 0;
}
