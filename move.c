
#include<stdio.h> 
#include<string.h>
#include<malloc.h> 
#include<dirent.h>
#include<time.h> 

struct node{           
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
};

node* POINTER;     //ȫ�ֱ�����ʵʱָ���û��򿪵ĵ�ǰĿ¼ 
node* HEAD;        //����ͷ�ڵ� 

void move_file(void);           //�ƶ��ļ�/�ļ��� 
int check(char name[],node* p); //���أ���pָ���Ŀ¼�²����Ƿ�������Ϊname���ļ�/Ŀ¼ 
node* search(char path[],node*p); //���ң��ҵ�����·���ļ����У����ڵĽ��,����ָ��pָ��ý�� 
void rename_file(void);         //�������ļ�/�ļ��� 
void change_path(int len_oldname,char* newname,node* p);  //���������·�� 
int Today(void);  //��ȡ��ǰʱ��
 
int main(){
	return 0;
}

void move_file()    //�ƶ��ļ�/�ļ��� 
{
	char oldpath[260],newpath[260];  //oldname��·����newname��·�� 
	printf("��������Ҫ�ƶ����ļ����ļ��У�"); 
	scanf("%s",oldpath);
	printf("�������ļ����ļ��е�Ŀ��λ��");
	scanf("%s",newpath);
	node * p1;    //��¼���ƶ��ļ�/�ļ��еĽ��λ�� 
	node * p2;    //��¼Ŀ��λ�õ���һ�� 
	if(rename(oldpath,newpath)) {
		perror("rename");
		return ;
	}
	int i,len_newpath;
	len_newpath = strlen(newpath);
	for( i=len_newpath;i>=0;i--){           //�ҵ�Ŀ��λ�õ���һ��Ŀ¼ 
		if(newpath[i]==92) return ;         // '\'��ASCII��Ϊ92     
	}
	int j;
	char newpath_pre[260];    //newpath����һ��·�� 
	for(j=0;j<i;j++){
		newpath_pre[j]=newpath[j];    //���������·����Ҳ�����Ǿ���·�� 
	}
	j=0;
	char newpath_post[260];
	while((j+i+1)<len_newpath){
		newpath_post[j]=newpath[j+i+1];  //newpath��׺ 
	}
	p1=search(oldpath,p1);      //�������ҵ���·���µ��ļ�/�ļ��У�����p1��¼��λ�� 
	p2=search(newpath_pre,p2);  //p2����·������һ�� 
	strcpy(newpath,p2->path);
	strcat(newpath,newpath_post); //�ƶ���ľ���·�� 
	
	p1->time=Today();    //���� ����޸�ʱ�� 
	
	node * p=p1->P_parents;        //������ 
	if(strstr(p1->path,p->path)) p->P_left=p1->P_right; 
	else p->P_right=p1->P_right;
	if(p1->P_right!=NULL) p1->P_right->P_parents = p;
	p1->P_right=NULL; 
	p1->P_parents=NULL;
	
	int len_oldpath=strlen(p1->path);    //��·���ĳ��� 
	strcpy(p1->path,newpath);            //��p1��·��   
	
	//���ӽ�� 
	if(p2->P_left==NULL) {
		p2->P_left=p1;
		p1->P_parents=p2;
	}
	else {
		if(p1->label==0){     //���ƶ������ļ��� ������ͷ�巨 
			p=p2->P_left;
			p2->P_left = p1;
			p->P_parents=p1;
			p1->P_parents = p2;
			p1->P_right = p;
			change_path(len_oldpath,newpath,p->P_left);  //��p1��������·�� 
		}
		else {               //���ƶ������ļ� ��β�巨 
			p=p2->P_left;
			while(p->P_right!=NULL&&p->label==0) p=p->P_right;
			p->P_right=p1;
			p1->P_parents=p;
		}
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

void rename_file(void){  //�������ļ�/�ļ���
	char newname[260];
	printf("������������: ");
	scanf("%s",newname);
	while(strlen(newname)>260){
		printf("���ֹ�����������260�������ڵ������֣�\n");
		scanf("%s",newname);
	} 
	if(check(newname,POINTER->P_parents))  {      //�ڵ�ǰĿ¼�в鿴�Ƿ�������� 
		printf("�ļ��������������������ļ�����");
		return rename_file();
	}
	int len_oldpath=strlen(POINTER->path);
	int len_oldname=strlen(POINTER->name);
	char* path_pre;
	for(int i=0;i<(len_oldpath-len_oldname);i++){
		path_pre[i]=POINTER->path[i];
	} 
	char* newpath=strcat(path_pre,newname);
		if(!rename(POINTER->path,newpath)){ //�Ծ���·������������ 
		    strcpy(POINTER->name,newname);  //ʵ���ļ����У������ֺ����ڵ㴢������ֶ�Ҫ��
			strcpy(POINTER->path,newpath);
			POINTER->time=Today();        //���� ����޸�ʱ�� 
			change_path(len_oldpath,newpath,POINTER);  //��PIONTER������������·�� 
		} 
		else{
			printf("������ʧ�ܣ�\n");
			perror("rename");
		} 
	return ;
}

node* search(char path[],node* p){  //���ң��ҵ�����·���ļ�/�ļ������ڵĽ��,����ָ��pָ��ý�� 
	if(strstr(path,HEAD->path)){     //����·�� 
		p=HEAD;    //�����ĸ���㿪ʼ������ 
	    while(p!=NULL){
			if(!strcmp(path,p->path)) return p;   //�ҵ������ؽ��ָ��p 
	        if(strstr(path,p->path)) p=p->P_left; //p->path��path���Ӵ���˵��p���ָ����ļ����������ļ��ĸ�Ŀ¼������һ���ļ����У� 
	        else p=p->P_right;                    //p->path����path���Ӵ�������һ��ͬ��Ŀ¼ 
		}		
	} 
	else{ //���·�� 
	    p=POINTER; //�ӵ�ǰĿ¼���� 
	    int i=2;
		int len=strlen(path);
	    while(i<len&&path[i]=='/'){   //�м����ͻ��˼���Ŀ¼ 
	    	p=p->P_parents;
			i=i+3;
		}
		char* path_post=(char*)malloc(sizeof(char)*(len-i+2));
		for(int j=0;j<len-i+2;j++){
			path_post[j]==path[j+i-2];   //��ȥ../���·�� 
		}
		char* path_all=strcat(p->path,path_post);   //����·���������Ҫ�ҵ��ļ����У��ľ���·�� 
		    while(p!=NULL){ 
			    if(!strcmp(path_all,p->path)) return p;
    	        if(strstr(path_all,p->path)) p=p->P_left;
	            else p=p->P_right;   
		    }   
	}
	return NULL;    //��ִ����������еķ��أ�˵����·���µ��ļ����У������� 
}

void change_path(int len_oldpath,char* newpath,node* p){  //���������·�� 
	if(p!=NULL) {
		int len_path=strlen(p->path);      //ԭ·������ 
	    int len=len_path - len_oldpath;    
	    char* path_post=(char*)malloc(sizeof(char)*len);  
		for(int i=0;i<len;i++){
		    path_post[i]=p->path[i+len_oldpath];  //·������Ĳ��֣�oldpath��·��Ҫ��Ϊnewname�Ĳ��� 
	    }
	    char* path_new=strcat(newpath,path_post);
	    strcpy(p->path,path_new);     //�������·�� 
		change_path(len_oldpath,newpath,p->P_left);
	    change_path(len_oldpath,newpath,p->P_right);
	} 
	return;
}

int Today(void){   //��ȡ��ǰʱ�� 
	int date; 
	time_t timer;
	time( &timer );
	struct tm * p;
	p=localtime(&timer);
	int year=1900+p->tm_year; 
	int month=1+p->tm_mon; 
    int day=p->tm_mday;
    //printf("%d %d %d \n",year,month,day);
    date=year*10000+month*100+day;
    //printf("%d",today);
	return date;
}
