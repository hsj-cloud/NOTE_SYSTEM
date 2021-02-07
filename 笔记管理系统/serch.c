#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "serch.h"

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

struct node *createtree_label(struct node *father,const char *name)			//������Ŀ¼ 
{
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	Node_Tree->label = 0;
	strcpy(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\");      //�ڸ�����·�������ӡ�\\name�����������ӽ���·�� 
/*	"D:\C����\�ļ��ĵݹ����\��ʼ\1"  ��������� 
	"D:\C����\�ļ��ĵݹ����\��ʼ\1\�½��ı��ĵ�.txt"*/
	strcat(Node_Tree->path,name);
	sprintf(Node_Tree->name,name);	
	Node_Tree->P_left = NULL;
	Node_Tree->P_parents = father;
	father->P_left = Node_Tree;
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	chdir(Node_Tree->path);						//������ָ��ָ����Ŀ¼
	return Node_Tree;
}

struct node *create_right_label(struct node *father,const char *name)			//����ͬ��Ŀ¼ 
{																	//fatherָ���Ǹ�Ŀ¼�ĸ�Ŀ¼ 		//name�Ǹ�Ŀ¼������ 
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
	if(father->P_left != NULL)
	{
		str = right_travel(father->P_left);
	}
	str->P_right = Node_Tree;
	Node_Tree->P_parents = str->P_right;
	chdir(Node_Tree->path);						//������ָ��ָ����Ŀ¼ 
	return Node_Tree;
}

struct node *create_left_txt(struct node *father,const char *name)	//�����ӽ��Ϊ�ʼ��ļ� 
{
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
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
	Node_Tree->P_parents = father;
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	father->P_left = Node_Tree;
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
	free(pat);
	free(p);
}

struct node *OrderTravsal_parent(struct node *T,const char *path)//ǰ�����,�鿴���ĺ����Ƿ�����ͬ·�� 
{																//�еĻ���Ҫ����ָ��ý���ָ�� 
	char *str = NULL;
	struct node *p = NULL;
	int top = -1;
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
	Stack[++top] = T;
	while(top != -1)
	{
		p = Stack[top--];
		memset(pat,0,sizeof(pat));
		sprintf(pat,p->path);									//��p->path���Ƶ�pat����ȥ
		if( strcmp(path,pat) == 0 )
		{
			return p->P_parents;	
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
}

void perorder(struct node *T)
{
	if(T == NULL)
	{
		return;
	}
	printf("�ļ�����:%s\t�ļ�·��:%s\n",T->name,T->path);
	perorder(T->P_left);
	perorder(T->P_right);
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
	printf("��������Ҫ�л������ļ��о���·��!\t");
	printf("ע��·���е� '\\' Ҫ�ɶԳ���\n");
	printf("Ҳ�����������룺 Ŀ¼\\Ŀ¼\\�ļ�"); 
	scanf("%s",path);
	if( strcmp(path,"��ʼ")==0 || strcmp(path,"��ʼ\\")==0 || strcmp(path,"\\��ʼ")==0 || strcmp(path,"\\��ʼ\\")==0)
	{										//����û���Ҫ�ص�����ʼ���˵� 
		chdir(T->path); 					//ֱ���л������ڵ� 
		printf("�л��ɹ�!\n");
		str = get_path();
		printf("��ǰ����Ŀ¼Ϊ��%s\n",str);
		return T;							// ������ָ�������ָ�� 
	} 
	sign = 0;												//������0 
	PreOrderTravsal(T,path);								//��Ҫ����ָ��������ָ�� 
	struct node *p = OrderTravsal(T,path);					//�ҵ����ָ��Ū����
	if(sign == 1 && p != NULL)									
	{
		chdir(T->path);
		if(chdir(path) == 0)
		{
			printf("�л��ɹ���\n");
			str = get_path();
			printf("��ǰ����Ŀ¼Ϊ��%s\n",str);
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


struct node *md(struct node *T)  			//����Ŀ¼(�ڵ�ǰ����ָ�봦������Ŀ¼)
{											//��Ҫ����ָ��������ָ�� 
	char *mulu = NULL;						//������ɺ󣬻᷵��ָ�����Ŀ¼��ָ��,��������ָ���Ƶ����� 
	char *i = get_path();					//��ȡ��ǰ·�� 
	struct node *p = NULL;
	mulu = (char *)malloc( sizeof(char [260]) );
	printf("��ǰ����Ŀ¼:%s\n",i);
	printf("������Ŀ¼����(ע�⣺�Ǵ�����Ŀ¼�µ���Ŀ¼)��\n");
	scanf("%s",mulu);						//Ŀ¼������ 
	p = OrderTravsal_parent(T,i);			//���ҵ������ʱ��ֹͣ
	if(mkdir(mulu) == 0)
	{
		if( p != NULL) 
		{
			createtree_label(p,mulu);				//Ϊ��Ŀ¼����һ�����Ľ��
			printf("����\t%s\tĿ¼�ɹ�!\n",mulu);	
		}			
		return p->P_left;					
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
				str->P_right->P_parents = str->P_parents;
				str->P_right = NULL;
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

int main()
{	
	//��ʼ������ 
	struct node *father_Tree = createfather();	
	createtree_label(father_Tree,"1");
	createtree_label(father_Tree->P_left,"1.1");
	create_left_txt(father_Tree->P_left->P_left,"1.1.1");
	create_right_label(father_Tree,"2");
	create_left_txt(father_Tree->P_left->P_right,"2.1");
	create_right_label(father_Tree,"3");	
	char *p = NULL;
/***********************����*******************************/	
	perorder(father_Tree);
	rm_r(father_Tree);
	perorder(father_Tree);
/**********************************************************/
	//�������� 
	printf("�ر�ϵͳ��.........");	
	free_all(father_Tree);	
	return 0;
}
