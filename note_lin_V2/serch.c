#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "serch.h"
#include <string.h>

int top = -1;
/*********************��ջ*********************************/
void push(struct node **a,struct node * elem){
    a[++top]=elem;
}
//��ջ����
void pop( ){
    if (top==-1) {
        return ;
    }
    top--;
}

//�õ�ջ��Ԫ��
struct node *getTop(struct node **a){
    return a[top];
}
/**********************************************************/ 

/******************************�������ڲ�����*************************************/ 
int sign = 0;
/**
* �ݹ�ɾ��Ŀ¼(ɾ����Ŀ¼�Լ���Ŀ¼�������ļ���Ŀ¼)
* @dir:Ҫɾ����Ŀ¼����·��
*/
int remove_mulu(const char *dir)
{
	char cur_dir[] = ".";
	char up_dir[] = "..";
	char dir_name[128];
	DIR *dirp;
	struct dirent *dp;
	struct stat dir_stat;
	// �������ݽ�����Ŀ¼�����ڣ�ֱ�ӷ���
	if ( 0 != access(dir, F_OK) ) 
	{
		return 0;
	}
	// ��ȡĿ¼����ʧ�ܣ����ش���
	if ( 0 > stat(dir, &dir_stat) ) 
	{
		printf("��ȡĿ¼����ʧ�ܣ�\n");
		return -1;
	}
	if ( S_ISREG(dir_stat.st_mode) ) 
	{	// ��ͨ�ļ�ֱ��ɾ��
		remove(dir);
	} 
	else if ( S_ISDIR(dir_stat.st_mode) ) 
	{	// Ŀ¼�ļ����ݹ�ɾ��Ŀ¼������
		dirp = opendir(dir);
		while ( (dp=readdir(dirp)) != NULL ) 
		{
			// ���� . �� ..
			if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) )
			{
				continue;
			}			
			sprintf(dir_name, "%s/%s", dir, dp->d_name);
			remove_mulu(dir_name);   // �ݹ����
		}
		closedir(dirp);
		rmdir(dir);		// ɾ����Ŀ¼
	} 
	else 
	{
		printf("ɾ��ʧ��!\n");
		return 0;	
	}
	return 3;
}

struct node *right_travel(struct node *T)		//�������������ҵ���һ��Ϊ�յ�ָ�벢���� 
{
	struct node *str = NULL;
	if(T->P_right == NULL)
	{
		return T;
	}
	str = right_travel(T->P_right);
	if( str != NULL)
	{
		return str ;
	}
	else
	{
		return NULL;	
	}	 
}

char *get_path()							//��ȡ��ǰĿ¼ 
{
	char *strpwd = NULL;
	strpwd = (char *)malloc(sizeof(char[MAX_PATH]));	
	getcwd(strpwd,MAX_PATH);
	return strpwd;
}

void free_all(struct node *T)									//�ͷſռ� 
{
	if(T == NULL )
	{
		return;
	}
	free_all(T->P_left);
	free_all(T->P_right);										//��������free��� 
	free(T);
}	 

void del_NodeTree(struct node *Node_Tree)							//ɾ���ʼǵĽ�� 
{																	//�ʼǽ�������� 
	Node_Tree->P_parents = Node_Tree->P_right; 						//�����ָ��ʼǽ����Һ��� 
	free(Node_Tree); 												//�ͷŸý��Ŀռ� 
}

struct node *createfather()							//�������ĸ���� 
{
	struct node *father_Tree = (struct node *)malloc( sizeof(struct node) );
	char *i = get_path();
	father_Tree->label = 0;
	sprintf(father_Tree->path,i);
	strcat(father_Tree->path,"\\��ʼ");				//�����·��Ϊϵͳ����Ŀ¼
	sprintf(father_Tree->name,"��ʼ");				//��ʼĿ¼��������Ϊ ����ʼ��		 
	father_Tree->P_left = NULL;
	father_Tree->P_parents = NULL;
	father_Tree->P_right = NULL;
	father_Tree->time = 0;
	chdir(father_Tree->path);						//������ָ���л�������ʼ��Ŀ¼ 
	return father_Tree;
}

struct node *createtree_label(struct node *father,const char *name)			//����Ŀ¼ 
{		//fatherָ���Ǹ�Ŀ¼�ĸ�Ŀ¼�Ľ��(��һ������һ�����) 		//name�Ǹ�Ŀ¼������ 
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	struct node *str = NULL;
	Node_Tree->label = 0;											//���ļ�����ΪĿ¼ 
	Node_Tree->P_left = NULL;	
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	sprintf(Node_Tree->name,name);
	strcpy(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\"); 
	strcat(Node_Tree->path,name);
	//�ڸ�����·�������ӡ�\\name�����������ӽ���·�� 
   	/*	"D:\C����\�ļ��ĵݹ����\��ʼ\1"  ���������  */
	/*"D:\C����\�ļ��ĵݹ����\��ʼ\1\�½��ı��ĵ�.txt" */
	if(father->P_left != NULL)					//�ø�Ŀ¼������ 
	{		
		str = right_travel(father->P_left);
		str->P_right = Node_Tree;
		Node_Tree->P_parents = str;
	}
	else										//�ø�Ŀ¼������ 
	{	
		father->P_left = Node_Tree;
		Node_Tree->P_parents = father;
	}
	chdir(Node_Tree->path);						//������ָ��ָ����Ŀ¼ 
	return Node_Tree;
}

struct node *create_left_txt(struct node *father,const char *name)	//�����ӽ��_�ʼ��ļ� 
{	//fatherָ����Ŀ¼�ĸ�Ŀ¼�Ľ��(��һ������һ�����)
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	struct node *str = NULL;
	Node_Tree->label = 1;
	sprintf(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\");	//�ڸ�����·�������ӡ�\\name�����������ӽ���·�� 
/*	"D:\C����\�ļ��ĵݹ����\��ʼ\1"  ��������� 
	"D:\C����\�ļ��ĵݹ����\��ʼ\1\�½��ı��ĵ�.txt"*/
	strcat(Node_Tree->path,name);
	strcat(Node_Tree->path,".txt");
	sprintf(Node_Tree->name,name);
	strcat(Node_Tree->name,".txt");
	Node_Tree->P_left = NULL;
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	if(father->P_left != NULL)
	{
		str = right_travel(father->P_left);
		str->P_right = Node_Tree;
		Node_Tree->P_parents = str;
	}
	else
	{
		father->P_left = Node_Tree;
		Node_Tree->P_parents = father;
	}
	
	return Node_Tree;							//������ָ����ļ���ָ�� 
}

struct node *Travsal_name(struct node *T,char *name)			//ǰ�����,�鿴����Ƿ�����ͬ���� 
{																//�еĻ���Ҫ����ָ��ý���ָ�� 
	char *str = NULL;
	int top = -1;
	if(T == NULL)
	{
		return;
	}
	char *pat = NULL;
	pat = (char *)malloc( sizeof(T->name) );
	/**********************************************************************************/
	struct node *Stack[260];
	struct node *p = NULL;
	p =(struct node *)malloc( sizeof(struct node) );
	Stack[++top] = T;
	while(top != -1)
	{
		p = Stack[top--];
		sprintf(pat,p->name);								//��p->name���Ƶ�pat����ȥ
		if( strcmp(name,pat) == 0 )			//�ҵ����ֲ��Ҹ��ļ��ǱʼǶ�����Ŀ¼ 
		{
			return p;	
		} 
		if(p->P_right != NULL)
		{
			Stack[++top] = p->P_right;
		}
		if(p->P_left != NULL)
		{
			Stack[++top] = p->P_left;
		}
	}
	free(pat);
	free(p);
	return NULL;
}	

void PreOrderTravsal(struct node *T,const char *path)		//ǰ�����,�鿴�Ƿ�����ͬ·�� 
{
	char *str = NULL;
	if(T == NULL)
	{
		return;
	}
	char *pat = NULL;
	pat = (char *)malloc( sizeof(T->path) );
	sprintf(pat,T->path);									//��T.path���Ƶ�pat����ȥ 
	if( strcmp(path,pat) == 0 )
	{
		sign = 1;									//�ҵ��˱���1,sign��ֵΪ0 
		return;
	}
	else
	{
		str = strstr(pat,path);						//����û�����������·�� 
		if( str != NULL )							//������Ǿ���·������·������ָ�벻Ϊ�� 
		{
			sign = 1;
			return;
		}
	}
	free(pat);					
	PreOrderTravsal(T->P_left,path);
	PreOrderTravsal(T->P_right,path);
}

struct node *OrderTravsal(struct node *T,const char *path)		//ǰ�����,�鿴����Ƿ�����ͬ·�� 
{																//�еĻ���Ҫ����ָ��ý���ָ�� 
	char *str = NULL;
	int top = -1;
	if(T == NULL)
	{
		return;
	}
	char *pat = NULL;
	pat = (char *)malloc( sizeof(T->path) );
	sprintf(pat,T->path);
	if( strcmp(path,pat) == 0 || strstr(pat,path) != NULL )
	{
		return T;	
	}
	/**********************************************************************************/
	struct node *Stack[260];
	struct node *p = NULL;
	p =(struct node *)malloc( sizeof(struct node) );
	Stack[++top] = T;
	while(top != -1)
	{
		p = Stack[top--];
		sprintf(pat,p->path);									//��p->path���Ƶ�pat����ȥ
		if( strcmp(path,pat) == 0 || strstr(pat,path) != NULL )
		{
			return p;	
		} 
		if(p->P_right != NULL)
		{
			Stack[++top] = p->P_right;
		}
		if(p->P_left != NULL)
		{
			Stack[++top] = p->P_left;
		}
	}
	return NULL;
	free(pat);
	free(p);
}

struct node *find_first(struct node *father_Tree,struct node *Node_Tree,const char *path)
{			//����·���ҵ����ĵ�һ�������
	char path_buffer[_MAX_PATH];
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   char path_n[] = {};
   struct node *ppp = NULL;
   
   sprintf(path_buffer,path);
   _splitpath( path_buffer, drive, dir, fname, ext );
	strcpy(path_n,drive);
	strcat(path_n,dir);
	/************��path_n�����һ����\��ɾ��*******************/ 
	path_n[strlen(path_n)-1]='\0';
    /**********************************************************/
    ppp = OrderTravsal(father_Tree,path_n);	 
    if(ppp != NULL)
    {
    	return ppp;
	}
	else
	{		
		return NULL;
	}
}

struct node *OrderTravsal_parent(struct node *T,const char *path)//ǰ�����,�鿴���ĺ����Ƿ�����ͬ·�� 
{																//�еĻ���Ҫ���ظý�㸸Ŀ¼��ָ�� 
	char *str = NULL;
	struct node *p = NULL;
	struct node *a = NULL;
	int top_1 = -1;
	char *pat = NULL;
	pat = (char *)malloc( sizeof(T->path) );
	sprintf(pat,T->path);
	if( strcmp(path,pat) == 0 )
	{
		return T;	
	}
	/**********************************************************************************/
	struct node *Stack[260];
	p =(struct node *)malloc( sizeof(struct node) );
	Stack[++top_1] = T;
	while(top_1 != -1)
	{
		p = Stack[top_1--];
/********************************************************/			
		memset(pat,0,sizeof(pat));								//��� 
		sprintf(pat,p->path);									//��p->path���Ƶ�pat����ȥ
		if( strcmp(path,pat) == 0 )
		{				
			if( p->P_parents == NULL || p->P_parents->P_right != p)		//��仹�е�����  
			{
				return p;
			}
			else
			{
				a = find_first(T,p,path);		//�ҵ���Ŀ¼�Ľ�� 
				if(a != NULL)
				{
					return a;
				}
				else
				{
					return NULL;
				}
			}				
		}		
 	
/*********************************************************/	                	
		if(p->P_right != NULL)
		{
			Stack[++top_1] = p->P_right;
		}
		if(p->P_left != NULL)
		{
			Stack[++top_1] = p->P_left;
		}
	}	
	free(pat);
	free(p);
	return NULL;
}

void perorder(struct node *T)				//��ӡ�� 
{
	if(T == NULL)
	{
		return;
	}
	printf("�ļ�����:%s\t�ļ�·��:%s\n",T->name,T->path);
	perorder(T->P_left);
	perorder(T->P_right);
}

char *divide_filename(const char *path)
{
	char path_buffer[_MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    char *path_n = NULL;
	path_n = (char *)malloc( sizeof(char[260]) ); 
   sprintf(path_buffer,path);
   _splitpath( path_buffer, drive, dir, fname, ext );
	strcpy(path_n,drive);
	strcat(path_n,dir);
	path_n[strlen(path_n)-1]='\0';
	return path_n;
}
/*******************************************************************************/


/******************************ֱ�ӵ��õĺ���***********************************/
void cd_pre(struct node *T)    			//�ƶ����ϼ�Ŀ¼ 
{
	char *i = get_path();						//��ȡ��ǰ·�� 
	char *p = NULL;
	struct node *str = OrderTravsal(T,i);	//������Ѱ�Ҹ�·���Ľ�㣬������ָ������ָ�� 
	if( str->P_parents == NULL )				//��������Ϊ�գ����ý��Ϊ���ڵ� 
	{
		printf("�л�ʧ�ܣ���鿴�Ƿ�Ϊ��Ŀ¼��\n");
	}
	else
	{
		if( chdir(str->P_parents->path) == 0 )	//�л���������·��
		{
			printf("�л��ɹ���\n");
			p = get_path();
			printf("��ǰ����Ŀ¼Ϊ��%s\n",p);
		}
		else
		{
			printf("�л�ʧ�ܣ�����δ֪����\n");
		}
	}		
}

struct node *cd(struct node *T)			//�л�����Ŀ¼��ָ��Ŀ¼,������ָ���Ŀ¼��ָ�� 
{											
	char *path= NULL;
	char *str = NULL;			
	path = (char *)malloc( sizeof(char[260]) );
	printf("����������������Ҫ�л������ļ��еľ���·��!��������\n");
	printf("��������ע��·���е� '\\' Ҫ�ɶԳ��֡�������\n");
	printf("��������Ҳ�����������룺 Ŀ¼\\Ŀ¼\\�ļ�('��ʼ'��������)��������\n"); 
	printf("�����룺");
	scanf("%s",path);
	if( strcmp(path,"��ʼ")==0 || strcmp(path,"��ʼ\\")==0 || strcmp(path,"\\��ʼ")==0 || strcmp(path,"\\��ʼ\\")==0)
	{										//����û���Ҫ�ص�����ʼ���˵� 
		chdir(T->path); 					//ֱ���л������ڵ� 
		printf("�л��ɹ�!\n");
		str = get_path();
		printf("��ǰ����Ŀ¼Ϊ��%s\n",str);
		return T;							// ������ָ�������ָ�� 
	} 
	struct node *p = OrderTravsal(T,path);					//�ҵ����ָ��Ū����
	if( p != NULL)									
	{
		chdir(T->path);						//�л�����ָ�뵽��ʼĿ¼ 
		if(chdir(path) == 0)
		{
			printf("�л��ɹ���\n");
			str = get_path();
			printf("��ǰ����Ŀ¼Ϊ��%s\n",str);
			system("pause");
			return p;										//�л��󣬻Ὣ��λ�õ�ָ�뷵�� 
		}
		else
		{
			printf("�л�ʧ�ܣ�\n");
			system("pause");
		}
	}
	else
	{
		printf("�޴�Ŀ¼��\n");
	}	
	free(path);
}


void md(struct node *T)  			//����Ŀ¼(�ڵ�ǰ����ָ�봦������Ŀ¼)
{											//��Ҫ����ָ��������ָ�� 
	char *mulu = NULL;						//������ɺ󣬻᷵��ָ�����Ŀ¼��ָ��,��������ָ���Ƶ����� 
	char *i = get_path();					//��ȡ��ǰ·�� 
	struct node *p = NULL;					//�����ǰĿ¼������Ŀ¼���ᴴ������Ŀ¼�������������� 
	struct node *str = NULL;
	mulu = (char *)malloc( sizeof(char [260]) );
	printf("��ǰ����Ŀ¼:%s\n",i);
	printf("������Ŀ¼����(ע�⣺�Ǵ�����Ŀ¼�µ���Ŀ¼)��");
	scanf("%s",mulu);						//Ŀ¼������ 
	p = OrderTravsal_parent(T,i);			//���ҵ���ǰ·������Ŀ¼�ĸ�Ŀ¼�Ľ��ʱ��ֹͣ	
	/*��Ҫ�����ø�Ŀ¼�����û��������������������û��������*/ 
	if(mkdir(mulu) == 0)
	{
		if( p != NULL) 
		{
			createtree_label(p,mulu);				//Ϊ��Ŀ¼����һ�����Ľ��
			printf("���� %s Ŀ¼�ɹ�!\n",mulu);
			system("pause");			
		}
		else
		{
			printf("ϵͳ�ļ����ֹ��ϣ���鿴�Ƿ��޸�!\n");
			system("pause"); 
		}								
	}
	else
	{
		printf("����ʧ�ܣ�\n");
		system("pause");
	}
} 

void rm_r(struct node *T)  							/*ɾ��Ŀ¼������ɾ��Ŀ¼��ͬʱ */
{												/*���ý�㼰�������������еĽ��ɾ�� */
	char *mulu = NULL;			 
	mulu = (char *)malloc(sizeof(T->name));
	printf("��������Ҫɾ����Ŀ¼���ƣ�");
	scanf("%s",mulu);
	struct node *str = Travsal_name(T,mulu);
	if(str != NULL )
	{	
		if(str->label == 0)
		{
			if(remove_mulu(str->path) == 3)
			{
				printf("ɾ����.....\n");
				//ɾ��str�ý�㣬Ȼ����ҽڵ��ϵĽ��� 
				free_all(str->P_left);
				str->P_left = NULL; 
				str->P_parents->P_right = str->P_right;
				str->P_parents->P_right->P_parents = str->P_parents;
				str->P_right = NULL; 
				str = NULL;			
				free(str);							
				printf("ɾ��Ŀ¼ %s �ɹ�!\n",mulu);
			}
			else
			{
				printf("ɾ��Ŀ¼ʧ�ܣ�\n");
			}
		}
		else
		{
			printf("δ�ҵ������Ƶ��ļ���\n");
		}
	}
	else
	{
		printf("δ�ҵ������Ƶ��ļ���\n");
	} 
	free(mulu);	
} 
 
void rm(struct node *T)												//�Աʼ��ļ�����ɾ�� 
{		
	char *name = NULL;
	name = (char *)malloc( sizeof(T->name) );
	sign = 0;
	printf("������Ҫɾ���ʼǵ�����:");
	scanf("%s",name);
	strcat(name,".txt");
	struct node *str = Travsal_name(T,name);						//�����鿴�Ƿ��и����ֵĽ��
	if( str != NULL )												//���ȷʵ�� 
	{
		if(str->label == 1)
		{
			if( remove(str->path) == 0 )								//ɾ�����ļ� 
			{
				del_NodeTree(str);										//ɾ���ý�� 
				printf("ɾ���ɹ���\n");
			}	
			else
			{
				printf("ɾ��ʧ��!\n");
			} 
		}
		else
		{
			printf("�޴����Ƶ��ļ���ɾ��ʧ�ܣ�\n");
		}
	}
	else
	{
		printf("�޴����Ƶ��ļ���ɾ��ʧ�ܣ�\n");
	}
} 
/*******************************************************************************/

/*********************�ļ����������**********************/

void full_filename(struct node *Node_Tree)  //��ȫ·��������װ	
{					//����ָ��������ָ��
	char *p = get_path();					//��ȡC�ļ��Ĺ���·�����Ȼ�������ȫ���·�� 
	if(Node_Tree->path == NULL)
	{
		strcat(p,"\\��ʼ");					//��ʼĿ¼���ȥ�����·����NULL 
		sprintf(Node_Tree->path,p);			//��p��������·��
	}
	else
	{
		strcat(p,Node_Tree->path);			//�����·��������p�ĺ��棬����p������������
		sprintf(Node_Tree->path,p);			//��p��������·�� 
	} 
	
} 

char *cut_filename(struct node *Node_Tree)	//�ֽ����·��������װ 
{											//path����"D:\C����\�ļ��ĵݹ����\��ʼ\2" 
	char *delim = "\\��ʼ\\";				//�ԡ�\��Ϊ�ָ��ķ��� 
	char *p = NULL ;
	char str[260];
	sprintf(str,Node_Tree->path);			//�ָ�����ַ�  \��ʼ\2
	p = strstr(str,delim);
	return p;
}

void writefile_preorder(const char *filename,struct node *T)		//ǰ��д���ļ� 
{
	struct node *Stack[260];
	struct node *p = NULL;
	char *address = NULL;
	FILE *fp = fopen(filename,"w");		
	Stack[++top] = T;
	while(top != -1)
	{
		p = Stack[top--];			//����������Ľ�� 
		address = cut_filename(p);
		fprintf(fp,"%-2d%-50s%-120s%-20s%-20s%-20s%-10d\n",p->label,p->name,address,p->tag_1,p->tag_2,p->tag_3,p->time);
		if(p->P_right != NULL)
		{							//���������Ƚ�ȥ 
			Stack[++top] = p->P_right;
		}
		if(p->P_left != NULL)
		{							//�������ķ����� 
			Stack[++top] = p->P_left;
		}
	}
	fclose(fp);
}

//��������ǵݹ��㷨
void writefile_inorder(const char *filename,struct node *T){
    struct node *a[20];//����һ��˳��ջ
    struct node *p;//��ʱָ��
    char *address = NULL;
    FILE *fp = fopen(filename,"w");
    push(a, T);//������ջ
    while (top!=-1) {//top!=-1˵��ջ�ڲ�Ϊ�գ������������
        while ( (p=getTop(a)) &&p){//ȡջ��Ԫ�أ��Ҳ���ΪNULL
            push(a, p->P_left);//���ý������ӽ�ջ�����û�����ӣ�NULL��ջ
        }
        pop();//����ѭ����ջ��Ԫ�ؿ϶�ΪNULL����NULL��ջ
        if (top!=-1) {
            p=getTop(a);//ȡջ��Ԫ��
            pop();//ջ��Ԫ�ص�ջ
            address = cut_filename(p);
            fprintf(fp,"%-2d%-50s%-120s%-20s%-20s%-20s%-10d\n",p->label,p->name,address,p->tag_1,p->tag_2,p->tag_3,p->time);
            push(a, p->P_right);//��pָ��Ľ����Һ��ӽ�ջ
        }
    }
    fclose(fp);
}

/**********************************************************/ 

int main()
{	
	//��ʼ������ �������� 
	struct node *father_Tree = createfather();	
	createtree_label(father_Tree,"1");
	createtree_label(father_Tree->P_left,"1.1");
	create_left_txt(father_Tree->P_left->P_left,"1.1.1");
	createtree_label(father_Tree,"2");
	create_left_txt(father_Tree->P_left->P_right,"2.1");
	createtree_label(father_Tree,"3");	
//	char *p = NULL;
/***********************����*******************************/	
//	perorder(father_Tree);
//	printf("��������������������������������\n");
//	cd(father_Tree);
//	md(father_Tree);	
//	printf("��������������������������������\n");
	perorder(father_Tree);
/****************���ݱ���**********************************/
	char *address = divide_filename(father_Tree->path);
	chdir(address);
	writefile_preorder("preorder_tree.txt",father_Tree);
	writefile_inorder("Inorder_tree.txt",father_Tree);	
/**********************************************************/
	//�������� 
	printf("�ر�ϵͳ��.........");	
	free_all(father_Tree);	
	return 0;
}
