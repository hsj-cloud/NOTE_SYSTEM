
#include<stdio.h> 
#include<string.h>
#include<malloc.h> 
#include<dirent.h>


struct node{           
	int label;         //标签：1：代表文件；0：代表文件夹 
	char name[260];    //文件（夹）名字 
	char path[260];    //文件（夹）路径 
	char *tag_1[10];   //三个标签 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //最近修改时间 
	node* P_left;      //指向左孩子的指针 
	node* P_right;     //指向右孩子的指针 
	node* P_parents;   //指向父结点的指针 
};

node* POINTER;     //全局变量，实时指向用户打开的当前目录 
node* HEAD;        //树的头节点 

void move_file(void);           //移动文件/文件夹 
int check(char name[],node* p); //查重：在p指向的目录下查找是否有名字为name的文件/目录 
node* search(char path[],node*p); //查找，找到给定路径文件（夹）所在的结点,并让指针p指向该结点 
void rename_file(void);         //重命名文件/文件夹 
void change_path(int len_oldname,char* newname,node* p);  //先序遍历改路径 

int main(){
	return 0;
}

void move_file()    //移动文件/文件夹 
{
	char oldpath[260],newpath[260];  //oldname旧路径，newname新路径 
	printf("请输入您要移动的文件或文件夹："); 
	scanf("%s",oldpath);
	printf("请输入文件或文件夹的目标位置");
	scanf("%s",newpath);
	node * p1;    //记录被移动文件/文件夹的结点位置 
	node * p2;    //记录目标位置的上一级 
	if(rename(oldpath,newpath)) {
		perror("rename");
		return ;
	}
	int i,len_newpath;
	len_newpath=strlen(newpath);
	for( i=len_newpath;i>=0;i--){           //找到newpath的上一级目录的位置 
		if(newpath[i]==92) return ; // '\'的ASCII码为92 
	}
	int j;
	char newpath_pre[260];    //newpath的上一级路径 
	for(j=0;j<i;j++){
		newpath_pre[j]=newpath[j];    //可能是相对路径，也可能是绝对路径 
	}
	j=0;
	char newpath_post[260];
	while((j+i+1)<len_newpath){
		newpath_post[j]=newpath[j+i+1];  //newpath后缀 
	}
	p1=search(oldpath,p1);      //在树中找到旧路径下的文件/文件夹，并用p1记录其位置 
	p2=search(newpath_pre,p2);  //p2：新路径的上一级 
	strcpy(newpath,p2->path);
	strcat(newpath,newpath_post); //移动后的绝对路径 
	
	node * p=p1->P_parents;        //分离结点 
	p->P_right=p1->P_right;
	p1->P_right=NULL; 
	
	int len_oldpath=strlen(p1->path);    //旧路径的长度 
	strcpy(p1->path,newpath);   //改p1的路径   //////newname绝对路径//////////////////////// 
	
	//连接结点 
	if(p2->P_left==NULL) {
		p2->P_left=p1;
		p1->P_parents=p2;
	}
	else {
		if(p1->label==0){     //被移动的是文件夹 ，头插法 
			p=p2->P_left;
			p1->P_parents=p2;
			p1->P_right=p->P_right;
			p->P_right=p1;
			change_path(len_oldpath,newpath,p->P_left);  //改p1左子树的路径 
		}
		else {               //被移动的是文件 ，尾插法 
			p=p2->P_left;
			while(p->P_right!=NULL) p=p->P_right;
			p->P_right=p1;
			p1->P_parents=p2;
		}
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

void rename_file(void){  //重命名文件/文件夹
	char newname[260];
	printf("请输入新名字: ");
	scanf("%s",newname);
	while(strlen(newname)>260){
		printf("名字过长，请输入260个字以内的新名字：\n");
		scanf("%s",newname);
	} 
	if(check(newname,POINTER->P_parents))  {      //在当前目录中查看是否出现重名 
		printf("文件重名！请重新输入新文件名！");
		return rename_file();
	}
	int len_oldpath=strlen(POINTER->path);
	int len_oldname=strlen(POINTER->name);
	char* path_pre;
	for(int i=0;i<(len_oldpath-len_oldname);i++){
		path_pre[i]=POINTER->path[i];
	} 
	char* newpath=strcat(path_pre,newname);
		if(!rename(POINTER->path,newpath)){ //以绝对路径进行重命名 
		    strcpy(POINTER->name,newname);  //实际文件（夹）的名字和树节点储存的名字都要改
			strcpy(POINTER->path,newpath);
			change_path(len_oldpath,newpath,POINTER);  //改PIONTER及其左子树的路径 
		} 
		else{
			printf("重命名失败！\n");
			perror("rename");
		} 
	return ;
}

node* search(char path[],node* p){  //查找，找到给定路径文件/文件夹所在的结点,并让指针p指向该结点 
	if(strstr(path,HEAD->path)){     //绝对路径 
		p=HEAD;    //从树的根结点开始往下找 
	    while(p!=NULL){
			if(!strcmp(path,p->path)) return p;   //找到，返回结点指针p 
	        if(strstr(path,p->path)) p=p->P_left; //p->path是path的子串，说明p结点指向的文件夹是所找文件的父目录，找下一级文件（夹） 
	        else p=p->P_right;                    //p->path不是path的子串，找下一个同级目录 
		}		
	} 
	else{ //相对路径 
	    p=POINTER; //从当前目录入手 
	    int i=2;
		int len=strlen(path);
	    while(i<len&&path[i]=='/'){   //有几个就回退几个目录 
	    	p=p->P_parents;
			i=i+3;
		}
		char* path_post=(char*)malloc(sizeof(char)*(len-i+2));
		for(int j=0;j<len-i+2;j++){
			path_post[j]==path[j+i-2];   //除去../后的路径 
		}
		char* path_all=strcat(p->path,path_post);   //完整路径，即求出要找的文件（夹）的绝对路径 
		    while(p!=NULL){ 
			    if(!strcmp(path_all,p->path)) return p;
    	        if(strstr(path_all,p->path)) p=p->P_left;
	            else p=p->P_right;   
		    }   
	}
	return NULL;    //不执行上面语句中的返回，说明该路径下的文件（夹）不存在 
}

void change_path(int len_oldpath,char* newpath,node* p){  //先序遍历改路径 
	if(p!=NULL) {
		int len_path=strlen(p->path);      //原路径长度 
	    int len=len_path - len_oldpath;    
	    char* path_post=(char*)malloc(sizeof(char)*len);  
		for(int i=0;i<len;i++){
		    path_post[i]=p->path[i+len_oldpath];  //路径不变的部分；oldpath：路径要变为newname的部分 
	    }
	    char* path_new=strcat(newpath,path_post);
	    strcpy(p->path,path_new);     //求出绝对路径 
		change_path(len_oldpath,newpath,p->P_left);
	    change_path(len_oldpath,newpath,p->P_right);
	} 
	return;
}

