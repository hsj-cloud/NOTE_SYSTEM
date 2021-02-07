#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "serch.h"

/******************************函数的内部函数*************************************/ 
int sign = 0;
/**
* 递归删除目录(删除该目录以及该目录包含的文件和目录)
* @dir:要删除的目录绝对路径
*/
int remove_mulu(const char *dir)
{
	char cur_dir[] = ".";
	char up_dir[] = "..";
	char dir_name[128];
	DIR *dirp;
	struct dirent *dp;
	struct stat dir_stat;
	// 参数传递进来的目录不存在，直接返回
	if ( 0 != access(dir, F_OK) ) 
	{
		return 0;
	}
	// 获取目录属性失败，返回错误
	if ( 0 > stat(dir, &dir_stat) ) 
	{
		printf("获取目录属性失败！\n");
		return -1;
	}
	if ( S_ISREG(dir_stat.st_mode) ) 
	{	// 普通文件直接删除
		remove(dir);
	} 
	else if ( S_ISDIR(dir_stat.st_mode) ) 
	{	// 目录文件，递归删除目录中内容
		dirp = opendir(dir);
		while ( (dp=readdir(dirp)) != NULL ) 
		{
			// 忽略 . 和 ..
			if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) )
			{
				continue;
			}			
			sprintf(dir_name, "%s/%s", dir, dp->d_name);
			remove_mulu(dir_name);   // 递归调用
		}
		closedir(dirp);
		rmdir(dir);		// 删除空目录
	} 
	else 
	{
		printf("删除失败!\n");
		return 0;	
	}
	return 3;
}

struct node *right_travel(struct node *T)		//遍历右子树，找到下一个为空的指针并返回 
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

char *get_path()							//获取当前目录 
{
	char *strpwd = NULL;
	strpwd = (char *)malloc(sizeof(char[MAX_PATH]));	
	getcwd(strpwd,MAX_PATH);
	return strpwd;
}

void free_all(struct node *T)									//释放空间 
{
	if(T == NULL )
	{
		return;
	}
	free_all(T->P_left);
	free_all(T->P_right);										//后续遍历free结点 
	free(T);
}

void del_NodeTree(struct node *Node_Tree)							//删除笔记的结点 
{																	//笔记结点无左孩子 
	Node_Tree->P_parents = Node_Tree->P_right; 						//父结点指向笔记结点的右孩子 
	free(Node_Tree); 												//释放该结点的空间 
}

struct node *createfather()							//创建树的根结点 
{
	struct node *father_Tree = (struct node *)malloc( sizeof(struct node) );
	char *i = get_path();
	father_Tree->label = 0;
	sprintf(father_Tree->path,i);
	strcat(father_Tree->path,"\\开始");				//以这个路径为系统的主目录
	sprintf(father_Tree->name,"开始");				//起始目录设置名字为 “开始”		 
	father_Tree->P_left = NULL;
	father_Tree->P_parents = NULL;
	father_Tree->P_right = NULL;
	father_Tree->time = 0;
	chdir(father_Tree->path);						//将工作指针切换到“开始”目录 
	return father_Tree;
}

struct node *createtree_label(struct node *father,const char *name)			//创建子目录 
{
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	Node_Tree->label = 0;
	strcpy(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\");      //在父结点的路径上增加“\\name”——就是子结点的路径 
/*	"D:\C程序\文件的递归查找\开始\1"  这个是例子 
	"D:\C程序\文件的递归查找\开始\1\新建文本文档.txt"*/
	strcat(Node_Tree->path,name);
	sprintf(Node_Tree->name,name);	
	Node_Tree->P_left = NULL;
	Node_Tree->P_parents = father;
	father->P_left = Node_Tree;
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	chdir(Node_Tree->path);						//将工作指针指向新目录
	return Node_Tree;
}

struct node *create_right_label(struct node *father,const char *name)			//创建同级目录 
{																	//father指的是该目录的父目录 		//name是该目录的名称 
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	struct node *str = NULL;
	Node_Tree->label = 0;											//该文件类型为目录 
	Node_Tree->P_left = NULL;	
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	sprintf(Node_Tree->name,name);
	strcpy(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\"); 
	strcat(Node_Tree->path,name);
	//在父结点的路径上增加“\\name”——就是子结点的路径 
   	/*	"D:\C程序\文件的递归查找\开始\1"  这个是例子  */
	/*"D:\C程序\文件的递归查找\开始\1\新建文本文档.txt" */
	if(father->P_left != NULL)
	{
		str = right_travel(father->P_left);
	}
	str->P_right = Node_Tree;
	Node_Tree->P_parents = str->P_right;
	chdir(Node_Tree->path);						//将工作指针指向新目录 
	return Node_Tree;
}

struct node *create_left_txt(struct node *father,const char *name)	//增加子结点为笔记文件 
{
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	Node_Tree->label = 1;
	sprintf(Node_Tree->path,father->path);
	strcat(Node_Tree->path,"\\");	//在父结点的路径上增加“\\name”——就是子结点的路径 
/*	"D:\C程序\文件的递归查找\开始\1"  这个是例子 
	"D:\C程序\文件的递归查找\开始\1\新建文本文档.txt"*/
	strcat(Node_Tree->path,name);
	strcat(Node_Tree->path,".txt");
	sprintf(Node_Tree->name,name);
	strcat(Node_Tree->name,".txt");
	Node_Tree->P_left = NULL;
	Node_Tree->P_parents = father;
	Node_Tree->P_right = NULL;
	Node_Tree->time = 0;
	father->P_left = Node_Tree;
	return Node_Tree;							//并返回指向该文件的指针 
}

struct node *Travsal_name(struct node *T,char *name)			//前序遍历,查看结点是否有相同名字 
{																//有的话，要返回指向该结点的指针 
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
		sprintf(pat,p->name);								//把p->name复制到pat里面去
		if( strcmp(name,pat) == 0 )			//找到名字并且该文件是笔记而不是目录 
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

void PreOrderTravsal(struct node *T,const char *path)		//前序遍历,查看是否有相同路径 
{
	char *str = NULL;
	if(T == NULL)
	{
		return;
	}
	char *pat = NULL;
	pat = (char *)malloc( sizeof(T->path) );
	sprintf(pat,T->path);									//把T.path复制到pat里面去 
	if( strcmp(path,pat) == 0 )
	{
		sign = 1;									//找到了便置1,sign初值为0 
		return;
	}
	else
	{
		str = strstr(pat,path);						//如果用户输入的是相对路径 
		if( str != NULL )							//输入的是绝对路径的子路径，则指针不为空 
		{
			sign = 1;
			return;
		}
	}
	free(pat);					
	PreOrderTravsal(T->P_left,path);
	PreOrderTravsal(T->P_right,path);
}

struct node *OrderTravsal(struct node *T,const char *path)		//前序遍历,查看结点是否有相同路径 
{																//有的话，要返回指向该结点的指针 
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
		sprintf(pat,p->path);									//把p->path复制到pat里面去
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

struct node *OrderTravsal_parent(struct node *T,const char *path)//前序遍历,查看结点的孩子是否有相同路径 
{																//有的话，要返回指向该结点的指针 
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
		sprintf(pat,p->path);									//把p->path复制到pat里面去
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
	printf("文件名称:%s\t文件路径:%s\n",T->name,T->path);
	perorder(T->P_left);
	perorder(T->P_right);
}

/*******************************************************************************/


/******************************直接调用的函数***********************************/
void cd_pre(struct node *T)    			//移动到上级目录 
{
	char *i = get_path();						//获取当前路径 
	char *p = NULL;
	struct node *str = OrderTravsal(T,i);	//在树中寻找该路径的结点，并返回指向它的指针 
	if( str->P_parents == NULL )				//如果父结点为空，即该结点为根节点 
	{
		printf("切换失败！请查看是否为根目录！\n");
	}
	else
	{
		if( chdir(str->P_parents->path) == 0 )	//切换到父结点的路径
		{
			printf("切换成功！\n");
			p = get_path();
			printf("当前所在目录为：%s\n",p);
		}
		else
		{
			printf("切换失败！发生未知错误\n");
		}
	}		
}

struct node *cd(struct node *T)			//切换工作目录到指定目录,并返回指向该目录的指针 
{											
	char *path= NULL;
	char *str = NULL;			
	path = (char *)malloc( sizeof(char[260]) );
	printf("请输入您要切换到的文件夹绝对路径!\t");
	printf("注意路径中的 '\\' 要成对出现\n");
	printf("也可以这样输入： 目录\\目录\\文件"); 
	scanf("%s",path);
	if( strcmp(path,"开始")==0 || strcmp(path,"开始\\")==0 || strcmp(path,"\\开始")==0 || strcmp(path,"\\开始\\")==0)
	{										//如果用户是要回到“开始”菜单 
		chdir(T->path); 					//直接切换到根节点 
		printf("切换成功!\n");
		str = get_path();
		printf("当前所在目录为：%s\n",str);
		return T;							// 并返回指向根结点的指针 
	} 
	sign = 0;												//重新置0 
	PreOrderTravsal(T,path);								//需要输入指向树根的指针 
	struct node *p = OrderTravsal(T,path);					//找到后把指针弄出来
	if(sign == 1 && p != NULL)									
	{
		chdir(T->path);
		if(chdir(path) == 0)
		{
			printf("切换成功！\n");
			str = get_path();
			printf("当前所在目录为：%s\n",str);
			return p;										//切换后，会将该位置的指针返回 
		}
		else
		{
			printf("切换失败！\n");
			system("pause");
		}
	}
	else
	{
		printf("无此目录！\n");
	}	
	free(path);
}


struct node *md(struct node *T)  			//创建目录(在当前工作指针处创建子目录)
{											//需要输入指向树根的指针 
	char *mulu = NULL;						//创建完成后，会返回指向该新目录的指针,并将工作指针移到这里 
	char *i = get_path();					//获取当前路径 
	struct node *p = NULL;
	mulu = (char *)malloc( sizeof(char [260]) );
	printf("当前所在目录:%s\n",i);
	printf("请输入目录名称(注意：是创建该目录下的子目录)：\n");
	scanf("%s",mulu);						//目录的名称 
	p = OrderTravsal_parent(T,i);			//当找到父结点时就停止
	if(mkdir(mulu) == 0)
	{
		if( p != NULL) 
		{
			createtree_label(p,mulu);				//为该目录创建一个树的结点
			printf("创建\t%s\t目录成功!\n",mulu);	
		}			
		return p->P_left;					
	}
	else
	{
		printf("创建失败！\n");
		system("pause");
	}
} 

void rm_r(struct node *T)  							/*删除目录，并在删除目录的同时 */
{												/*将该结点及其左子树上所有的结点删除 */
	char *mulu = NULL;			 
	mulu = (char *)malloc(sizeof(T->name));
	printf("请输入您要删除的目录名称：");
	scanf("%s",mulu);
	struct node *str = Travsal_name(T,mulu);
	if(str != NULL )
	{	
		if(str->label == 0)
		{
			if(remove_mulu(str->path) == 3)
			{
				printf("删除中.....\n");
				//删除str该结点，然后把右节点上的接上 
				free_all(str->P_left);
				str->P_left = NULL;
				str->P_parents->P_right = str->P_right;
				str->P_right->P_parents = str->P_parents;
				str->P_right = NULL;
				free(str);							
				printf("删除目录 %s 成功!\n",mulu);
			}
			else
			{
				printf("删除目录失败！\n");
			}
		}
		else
		{
			printf("未找到该名称的文件！\n");
		}
	}
	else
	{
		printf("未找到该名称的文件！\n");
	} 
	free(mulu);	
} 
 
void rm(struct node *T)												//对笔记文件进行删除 
{		
	char *name = NULL;
	name = (char *)malloc( sizeof(T->name) );
	sign = 0;
	printf("请输入要删除笔记的名字:");
	scanf("%s",name);
	strcat(name,".txt");
	struct node *str = Travsal_name(T,name);						//遍历查看是否有该名字的结点
	if( str != NULL )												//如果确实有 
	{
		if(str->label == 1)
		{
			if( remove(str->path) == 0 )								//删除该文件 
			{
				del_NodeTree(str);										//删除该结点 
				printf("删除成功！\n");
			}	
			else
			{
				printf("删除失败!\n");
			} 
		}
		else
		{
			printf("无此名称的文件！删除失败！\n");
		}
	}
	else
	{
		printf("无此名称的文件！删除失败！\n");
	}
} 
 
/*******************************************************************************/

int main()
{	
	//初始化操作 
	struct node *father_Tree = createfather();	
	createtree_label(father_Tree,"1");
	createtree_label(father_Tree->P_left,"1.1");
	create_left_txt(father_Tree->P_left->P_left,"1.1.1");
	create_right_label(father_Tree,"2");
	create_left_txt(father_Tree->P_left->P_right,"2.1");
	create_right_label(father_Tree,"3");	
	char *p = NULL;
/***********************测试*******************************/	
	perorder(father_Tree);
	rm_r(father_Tree);
	perorder(father_Tree);
/**********************************************************/
	//结束操作 
	printf("关闭系统中.........");	
	free_all(father_Tree);	
	return 0;
}
