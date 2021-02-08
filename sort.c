
#include<stdio.h> 
#include<string.h>
#include<malloc.h> 
#include<dirent.h>
#include<time.h> 

typedef struct node{           
	int label;         //��ǩ��1�������ļ���0�������ļ��� 
	char name[260];    //�ļ����У����� 
	char path[260];    //�ļ����У�·�� 
	char *tag_1[10];   //������ǩ 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //����޸�ʱ�� 
	node* P_left;      //ָ�����ӵ�ָ�� 
	node* P_right;     //ָ���Һ��ӵ�ָ�� 
	node* P_parents;   //ָ�򸸽���ָ�� 
} node ;

node* POINTER;     //ȫ�ֱ�����ʵʱָ���û��򿪵ĵ�ǰĿ¼ 
node* HEAD;        //����ͷ�ڵ� 

void Sort(void){  //�Ե�ǰĿ¼�µ��ļ����ļ��н���ʱ������ 
	node* p=POINTER->P_left;
	node* s=POINTER->P_left;
	node* head_file=NULL,*p_file;  //
	node* head_folder=NULL,*p_folder;  //
	node* q;
	int flag_file=0,flag_folder=0;
	int n=0,m=0;
	node* t,*tf;
	for(;p!=NULL;p=p->P_right){
		for(s=POINTER->P_left;s!=NULL;s=s->P_right){
			if(s->label==0){    //�ļ��� 
				if(s->time > n){
					t=s;
					n=s->time;
				}
			}
			else {    //�ļ� 
				if(s->time > m){
					tf=s;
					m=s->time;
				}
			}
		}
		
		q=t->P_parents;    //������ 
		if(q!=POINTER) q->P_right=t->P_right;
		else q->P_left = t->P_right;
		if(t->P_right) t->P_right->P_parents = t->P_parents;
		t->P_right=NULL;
		t->P_parents=NULL;
		
		if(!flag_folder){
			head_folder=t;
			p_folder=t;
			flag_folder=1;
		}
		else{
			t->P_parents=p_folder;
			p_folder->P_right=t;
			p_folder=t;
		}
		
		q=tf->P_parents;
		if(q!=POINTER) q->P_right=tf->P_right;
		else q->P_left = tf->P_right;
		if(tf->P_right) tf->P_right->P_parents = tf->P_parents;
		tf->P_right=NULL;
		tf->P_parents=NULL; 
		if(!flag_file){
			head_file=tf;
			p_file=tf;
			flag_file=1;
		}
		else{
			tf->P_parents=p_file;
			p_file->P_right=tf;
			p_file=tf;
		}
	}
	if(head_folder!=NULL){
		if(head_file!=NULL) {
			head_file->P_parents = p_folder;
			p_folder->P_right = head_file;
		}
		head_folder->P_parents=POINTER;
		POINTER->P_left=head_folder;
	}
	else{
		if(head_file!=NULL) {
			head_file->P_parents=POINTER;
		    POINTER->P_left=head_file;
		}
	}	
}

int main(){
	return 0;
}


