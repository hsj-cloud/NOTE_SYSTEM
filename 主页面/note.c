#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h> 
#include <dirent.h>
#include <time.h>
#include <io.h>
#include <Windows.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "note.h"
#define MEMBER_SIZE 100  //图书馆先存在100个管理员和普通用户（100其实可以用任何数字代替，只为了用户表初始化用）

/*************************************世佳的部分*************************************/ 
void page_title(char *menu_item)  //显示整体标题的函数 
{
	printf("\t\t\t欢迎使用笔记管理系统\n"
	    "————————————————————————————————————\n"
		"\n——%s——\n",menu_item); 
}

void return_confirm()  //等待返回确认的函数 
{
	printf("请按任意键返回！\n");
	getch();
}

void continue_confirm()  //等待继续确认的函数
{
	printf("请按任意键继续！\n");
	getch();
}

void CreateListTail(LinkList *L,int n)  //尾插法_初始化单链表
{
	system("cls");  //清屏 
	page_title("初始化用户表");
	printf("这一步分别初始化管理员表和普通用户表。\n"
		"———————————————————————\n");
	LinkList p,r;
	int i;
	*L=(LinkList)malloc(sizeof(Node));
	r=*L;  //r为指向尾部的结点 
	for(i=0;i<n;i++)
	{
		p=(Node *)malloc(sizeof(Node));  //分配一块内存给结点p 
		p->account_number=0;  //用户表（包括管理员表与普通用户表）初始化时，把账号初始化为0 
		p->code=0;  //用户表初始化时，把密码初始化为0
		r->next=p;  //把新生成的结点p插入到r的后面 
		r=p;  //将当前的结点定义为新的表尾终端结点
	}
	r->next=NULL;
	printf("初始化成功！\n"
		"——————————\n");
	continue_confirm();  //请按任意键继续
	system("cls");  //清屏 
}

void Addusers(LinkList *L)  //注册新用户（尾部插入） 
{
	system("cls");  //清屏 
	page_title("注册新用户");
	LinkList p,s; 
	p=*L;  //p为指向头部的结点 
	while(p->next)  //p->next==NULL时，循环结束，即p为链表中最后一个结点
	{ 
		p=p->next;
	}
	s=(LinkList)malloc(sizeof(Node));  //分配一块内存给结点s 
	printf("请输入你要注册的账号(管理员注册时需在最前面添加999三个数字)：\n");  //管理员增加999主要是为了起到标识的作用 
	scanf("%d",&s->account_number);
	printf("请输入你的密码：\n");
	scanf("%d",&s->code);
	p->next=s;
	s->next=NULL;
	printf("注册成功！\n"
		"——————————\n");
	return_confirm();  //请按任意键返回 
}

void Cancelusers(LinkList *L)  //注销用户 
{
	int sign=0;  //sign起到标志的作用 
	system("cls");  //清屏 
	page_title("注销用户");
	printf("请输入你要注销的账号：\n");
	int cancel_account_number;
	scanf("%d",&cancel_account_number);
	printf("请输入要注销的账号的密码：\n");
	int cancel_code;
	scanf("%d",&cancel_code);
	LinkList p,q;
	p=*L;  //p为指向头部的结点
	while(p->next)  //p->next==NULL时，循环结束，即p为链表中最后一个结点
	{
		if(cancel_account_number==p->next->account_number&&cancel_code==p->next->code)  //用户表中存在要注销的账号，且密码正确 
		{
			q=p->next;
			p->next=q->next;
			free(q);  //释放结点q，清除结点q的数据 
			sign=1;
			printf("注销成功！\n"
				"——————————\n");
			return_confirm();  //请按任意键返回
			break;
		}
		if(cancel_account_number==p->next->account_number&&cancel_code!=p->next->code)  //用户表中存在要注销的账号，但密码错误 
		{
			sign=-1;
			printf("密码错误，注销失败！\n"
				"—————————————\n");
			return_confirm();  //请按任意键返回
			break;
		}
		p=p->next;
	}
	if(sign==0)
	{
		printf("没有找到要注销的账号！\n"
			"——————————————\n");
		return_confirm();  //请按任意键返回
	}
}

void Displayusers(LinkList *L)  //显示用户 
{
	int i=1;
	int length=0;  //链表长度（用来反映当前用户表的人数） 
	system("cls");  //清屏 
	page_title("显示用户");
	LinkList p;
	p=*L;  //p为指向头部的结点
	p=p->next;
	while(p)  //p==NULL时，循环结束 
	{
		if(p->account_number!=0&&p->code!=0)
		{
			printf("%d.账号：%d\n",i,p->account_number);
			i++;
			length++; 
		}
		p=p->next;
	}
	printf("该类用户表目前人数为%d\n",length);
	printf("—————————————\n");
	return_confirm();  //请按任意键返回
}

int Login_system(LinkList *L)  //登录系统 
{
	system("cls");  //清屏 
	page_title("登录系统");
	int sign=0;  //sign起到标志的作用 
	printf("请输入你要登录的账号：\n");
	int Login_account_number;
	scanf("%d",&Login_account_number);
	printf("请输入你的密码：\n");
	int Login_code;
	scanf("%d",&Login_code);
	LinkList p;
	p=*L;  //p为指向头部的结点
	while(p)
	{
		if(Login_account_number==p->account_number&&Login_code==p->code)  //账号和密码均正确 
		{
			printf("登录成功！\n"
				"——————————\n");
			sign=1;
			continue_confirm();  //请按任意键继续 
			break;
		}
		p=p->next;
	}
	if(sign==0)
	{
		printf("账号或密码发生错误，登录失败！\n"
			"——————————————————\n");
		return_confirm();  //请按任意键返回
	}
	return sign;
}

void get_nextval(char child_string[],int *nextval)  //获得nextval数组的函数 
{
	int i,j;
	i=1;
	j=0;
	nextval[1]=0;
	while(i<child_string[0])  //child_string[0]表示字符串child_string的长度 
	{
		if(j==0||child_string[i]==child_string[j])  //child_string[i]表示后缀的单个字符，child_string[j]表示前缀的单个字符 
		{
			++i;
			++j;
			if(child_string[i]!=child_string[j])  //前缀的单个字符不与所对应的后缀字符相同 
			{
				nextval[i]=j;  
			}
			else  //前缀的单个字符与所对应的后缀字符相同
			{
				nextval[i]=nextval[j];  //与前缀字符相同，将前缀的nextval值赋给nextval在i位置时的值（nextval省去重复操作的一步） 
			}
		}
		else
		{
			j=nextval[j];
		}
	}
}

int KMP_Algorithm(char child_string[],char parents_string[])  //KMP算法（做与字符串有关的匹配） 
{
	int i=1;  //i用于主串parents_string当前位置的下标值，位置从1开始 
	int j=1;  //j用于子串child_string当前位置的下标值，位置从1开始 
	int nextval[255];  //nextval数组 
	get_nextval(child_string,nextval);  //获得nextval数组 
	while(i<=parents_string[0]&&j<=child_string[0])  //i小于主串的长度，j小于子串的长度，循环继续 
	{
		if(j==0||parents_string[i]==child_string[j])
		{
			++i;
			++j;
		}
		else
		{
			j=nextval[j];
		}
	}
	if(j>child_string[0])
	{
		return i-child_string[0];  //若配对成功（主串中存在与子串相同的片段），返回子串在主串第一次出现的位置 
	}
	else
	{
		return 0;  //若配对失败（主串中不存在与子串相同的片段），返回0以代表失败 
	}
}

void display_ls(BiTree T)  //显示指令一：ls（显示所有笔记文件夹及笔记文件） 
{
	system("cls");  //清屏
	page_title("显示指令一：ls");
	if(T==NULL)  //前序遍历，显示每一个结点的名字，同时区分结点属于文件夹还是文件 
	{
		return;
	}
	if(T->label==0)
	{
		printf("这是一个笔记文件夹，名字为：%s\n",T->name);
	}
	if(T->label==1)
	{
		printf("这是一个笔记文件，名字为：%s\n",T->name);
	}
	display_ls(T->P_right);
	display_ls(T->P_left);
}

void display_ls_a(BiTree T)  //显示指令二：ls -a（按树状结构显示所有笔记文件夹和笔记文件） 
{
	system("cls");  //清屏
	page_title("显示指令二：ls -a");
	printf("该功能暂时未完善完毕，暂不开放使用\n"); 
}

void display_left_child(BiTree T)  //用于遍历某个结点的子文件夹或子文件（遍历它的左子树） 
{
	if(T==NULL)
	{
		return;
	}
	if(T->label==0)
	{
		printf("这是一个笔记文件夹，名字为：%s\n",T->name);
	}
	if(T->label==1)
	{
		printf("这是一个笔记文件，名字为：%s\n",T->name);
	}
	display_left_child(T->P_left);  //左递归，遍历它的左孩子 
}

void display_ls_NotePath(BiTree T,char change_1[])  //显示指令三：ls <笔记文件夹路径>（显示指定文件下所有的内容（子笔记文件夹和笔记文件）） 
{
	system("cls");  //清屏 
	page_title("显示指令三：ls <笔记文件夹路径>");
	if(strcmp(change_1,T->path))  //目标路径匹配成功 
	{
		if(T==NULL)
		{
			return;
		}
		if(T->label==0)
		{
			printf("这是一个笔记文件夹，名字为：%s\n",T->name);
		}
		if(T->label==1)
		{
			printf("这是一个笔记文件，名字为：%s\n",T->name);
		}
		display_left_child(T->P_left);  //遍历打印该结点的左子树 
	}
	display_ls_NotePath(T->P_left,change_1);  //目标路径若匹配失败，先遍历它的左子树，后遍历它的右子树 
	display_ls_NotePath(T->P_right,change_1);
}

void display_ls_NotePath_grep(BiTree T,char change_1[],char change_2[])  //显示指令四：ls <笔记文件夹路径> grep "搜索内容" （显示命令指定文件下所有的带有搜索内容的文件夹名及文件名） 
{
	system("cls");  //清屏
	page_title("显示指令四：ls <笔记文件夹路径> grep “搜索内容”");
	int i,j;
	char child_string[20];
	int length_child_string;
	length_child_string=strlen(child_string);
	for(j=100;j>1;j--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整 
	{
		child_string[j]=change_1[j-1];
	}
	child_string[0]=length_child_string;
	char parents_string[20];
	int length_parents_string;
	length_parents_string=strlen(parents_string);
	for(i=1;i<20;i++)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
	{
		parents_string[i]=T->path[i-1];
	}
	parents_string[0]=length_parents_string;
	
	if(KMP_Algorithm(child_string,parents_string)!=0)  //第一次child_string和parents_string是做目标路径的调整 
	{
		for(j=100;j>1;j--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
		{
			child_string[j]=change_2[j-1];
		}
		length_child_string=strlen(child_string);
		child_string[0]=length_child_string;
		for(i=1;i<20;i++)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
		{
			parents_string[i]=T->name[i-1];
		}
		length_parents_string=strlen(parents_string);
		parents_string[0]=length_parents_string;
		if((KMP_Algorithm(child_string,parents_string))!=0)  //第二次child_string和parents_string是做搜索内容的调整
		{
			if(T==NULL)
			{
				return;
			}
			if(T->label==0)
			{
				printf("这是一个笔记文件夹，名字为：%s\n",T->name);
			}
			if(T->label==1)
			{
				printf("这是一个笔记文件，名字为：%s\n",T->name);
			}
			display_ls_NotePath_grep(T->P_left,change_1,change_2);  //匹配成功后，左递归，遍历他的左子树 
		}
	}
	display_ls_NotePath_grep(T->P_left,change_1,change_2);  //若匹配失败，则先遍历它的左子树，后遍历它的右子树 
	display_ls_NotePath_grep(T->P_right,change_1,change_2);
}

/*********************************************************************************/



/*********************************政佳的部分**************************************/ 
/******************************函数内部的函数*************************************/ 
int sign = 0;  //全局变量 sign 
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
	system("cls");  //清屏
	page_title("切换指令一：cd"); 
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
	system("cls");  //清屏
	page_title("切换指令二：cd <笔记文件夹路径>");					
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
	system("cls");                          //清屏
	page_title("创建指令一：md"); 
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
	system("cls");  //清屏
	page_title("删除指令二：rm -r <要删除的笔记文件夹名>"); 
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
	system("cls");                                                  //清屏
	page_title("删除指令一：rm <要删除的笔记文件名>"); 
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



/*********************************文辉的部分************************************/


int Command_Processing(char change_1[],char change_2[])  //命令处理 
{
	/*      char str[100];
	        char buf[100];
	        char sda[100];
	        sscanf("tag -add <wenjian> “neirong”","%[^<]",str);
	        sscanf("tag -add <wenjian> “neirong”","%*[^<]<%[^>]",buf);
	        sscanf("tag -add <wenjian> “neirong”","%*[^“]“%[^”]",sda);
	        printf("%s %s %s",str,buf,sda);
	        return 0;
	        */
	//system("mode con cp select=65001");
	system("cls");
	page_title("指令输入");
	char input[100];  //输入的值输入的例子 tag -add <title> "neirong"
	char first[100];
	char second[100];
	char third[100];
	char forth[100];
	//char change_1[100];  //记录文件名
	//char change_2[100];  //记录标签内容
	printf("请输入你的指令：\n");
	gets(input);
	memset (first,0,sizeof(first));
	sscanf (input,"%[^ ]",first);//第一个空格前
	sscanf (input,"%*[^ ] %[^ ]",second);//第二个空格前
	sscanf (input,"%*[^ ] %*[^ ] %[^ ]",third);//第三个空格前
	sscanf (input,"%*[^ ] %*[^ ] %*[^ ] %[^ ]",forth);
	memset (change_1,0,sizeof(change_1));  //清除缓存（没清之前有错误）
	memset (change_2,0,sizeof (change_2));



	if(strcmp("ls",first)==0&&strlen(input)==2)
	{
		//printf("first");
		return 1;
	}
	else if(strcmp("ls",first)==0&&strcmp("-a",second)==0)
	{
		//printf("second");
		return 2;
	}
	else if(strcmp("ls",first)==0&&second[0]=='<')
	{
		sscanf(second,"<%[^>]",change_1);  //去除<>
		//printf("%s", change_1);  //检测
		return 3;
	}
	else if (strcmp("ls",first)==0&& second[0] == '<' && strcmp("grep",third)==0 && forth[0] == '"' )
	{
		sscanf(second,"<%[^>]",change_1);  //去除<>
		//printf("%s\n",change_1 );  //检测
		sscanf(forth,"\"%[^\"]", change_2);  //去除""
		//printf("%s",change_2 );
		return 4;
	}
	else if(strcmp("cd",first)==0)
	{
		//printf("%s",first);
		return 5;
	}
	else if(strcmp("cd",first)==0&&second[0]=='<')
	{
		sscanf(second,"<%[^>]", change_1);  //去除<>
		//printf("%s",change_1);  //检测
		return 6;
	}
	else if(strcmp("mv",first)==0&&second[0]=='<'&&third[0]=='<')
	{
		sscanf(second,"<%[^>]",change_1);  //去除<>
		//printf("%s",change_1 );  //检测
		sscanf(third,"<%[^>]",change_2);  //去除<>
		//printf("%s",change_2);  //检测
		return 7;
	}
	else if(strcmp("mv",first)==0&&strcmp("-r",second)==0&&third[0]=='<'&&forth[0]=='<')
	{
		sscanf(third,"<%[^>]",change_1);  //去除<>
		//printf("%s",change_1 );  //检测
		sscanf(forth,"<%[^>]",change_2 );  //去除<>
		//printf("%s",change_2);  //检测
		return 8;
	}
	else if(strcmp("rm",first)==0&&second[0]=='<')
	{
		sscanf(second,"<%[^>]",change_1);  //去除<>
		//printf("%s",change_1 );  //检测
		return 9;
	}
	else if(strcmp("rm",first)==0&&strcmp("-r",second)==0&&third[0]=='<')
	{
		sscanf(third,"<%[^>]",change_1 );  //去除<>
		//printf("%s",change_1 );//检测
		return 10;
	}


	if(strcmp("tag",first)==0&& second[0] == '-' && third[0] == '<' && forth[0] == '"' )
	{

		sscanf(third, "<%[^>]", change_1 );  //去除<>
		//printf("%s",change_1 );  //检测
		sscanf(forth,"\"%[^\"]",change_2 );  //去除""
		//printf("%s",change_2 );  //检测
		return 11; 
	}
	if( strcmp("tag",first)==0&& second[0] == '<' )
	{

		sscanf(second,"<%[^>]",change_1 );
		//printf("%s\n",change_1 );
		return 12;
	}
	if(strcmp("tag",first)==0 && second[0] == '-' && third[0] == '"' )
	{

		sscanf(third,"\"%[^\"]",change_2 );
		//printf("%s",change_2 );
		return 13;
	}
	if(strcmp("md",first)==0&& second[0] == '<' )
	{
		sscanf(second,"<%[^>]",change_1);
		//printf("%s\n",change_1);
		return 14;
	}
	if(strcmp("sort",first)==0&& second[0] == '<' )
	{
		sscanf (second,"<%[^>]",change_1);
		//printf ("%s\n",change_1);
		return 15;
	}


	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^“]“%[^”]",sda);

	*///printf("%s",str);
	//printf("%s %s %s",first,second,third);
	//printf("%s",shuru);
	//return 0;


}

void select_menu()
{
	char input[200];
	scanf ( "%s", input );
	char *p;

	p = strtok ( input, " " );
	if ( p )
		printf ( "%s", p );
	p = strtok ( NULL, " " );
	if(p)
		printf ( "%s", p );
}




void search_file_tag (Tnode *tree) //根节点
{

	char search_name[260];
	scanf ( "%s", search_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = *tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				printf ( "%s %s %s", pmove->tag_1, pmove->tag_2, pmove->tag_3 );
				break;
			}
			else
			{
				pmove = pmove->right;
			}
		}

	}
}

void search_add_file_tag (Tnode *tree) //根节点
{

	char search_name[260];
	scanf ( "%s", search_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = *tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strlen ( pmove->tag_1 ) == 0 )
					scanf ( "%s", pmove->tag_1 );
				else
				{
					if ( strlen ( pmove->tag_2 ) == 0 )
						scanf ( "%s", pmove->tag_2 );
					else
					{
						if ( strlen ( pmove->tag_3 ) == 0 )
							scanf ( "%s", pmove->tag_3 );
						else
						{
							printf ( "all tags are full\n" );
						}
					}
				}


			}
			else
			{
				pmove = pmove->right;
			}
		}

	}



}

void search_delect_file_tag (Tnode *tree) //根节点
{
	char search_name[260];
	scanf ( "%s", search_name );
	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = *tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strlen ( pmove->tag_1 ) == 0 && strlen ( pmove->tag_2 ) == 0 && strlen ( pmove->tag_3 ) == 0 )
				{
					printf ( "no tags\n" );
					break;
				}
				else
				{
					if ( strcmp ( tag_name, pmove->tag_1 ) == 0 )
						memset ( pmove->tag_1, 0, sizeof ( pmove->tag_1 ) );
					printf ( "删除成功\n" );
					break;
					if ( strcmp ( tag_name, pmove->tag_2 ) == 0 )
						memset ( pmove->tag_2, 0, sizeof ( pmove->tag_2 ) );
					printf ( "删除成功\n" );
					break;
					if ( strcmp ( tag_name, pmove->tag_3 ) == 0 )
						memset ( pmove->tag_3, 0, sizeof ( pmove->tag_3 ) );
					printf ( "删除成功\n" );
					break;


				}




			}
			else
			{
				pmove = pmove->right;
			}
		}

	}
}

void tag_s (Tnode *tree) //当前目录根节点
{

	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = *tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 1 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "%s", pmove->name );
					break;
				}
				else
					pmove = pmove->right;
			}

			else
				pmove = pmove->right;
		}

	}
}

void tag_sa (Tnode *tree) //当前目录根节点
{

	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = *tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 0 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "%s", pmove->path );
					break;
				}
				else
					pmove = pmove->right;
			}

			else
				pmove = pmove->right;
		}

	}
}

/************************************************************************************/


/***********************************丹叶的部分***************************************/


void move_file(){    //移动文件/文件夹 
	system("cls");  //清屏
	page_title("移动指令一：mv <笔记文件名> <笔记文件夹目录>"); 
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
	len_newpath = strlen(newpath);
	for( i=len_newpath;i>=0;i--){           //找到目标位置的上一级目录 
		if(newpath[i]==92) return ;         // '\'的ASCII码为92     
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
	
	p1->time=Today();    //更新 最近修改时间 
	
	node * p=p1->P_parents;        //分离结点 
	if(strstr(p1->path,p->path)) p->P_left=p1->P_right; 
	else p->P_right=p1->P_right;
	if(p1->P_right!=NULL) p1->P_right->P_parents = p;
	p1->P_right=NULL; 
	p1->P_parents=NULL;
	
	int len_oldpath=strlen(p1->path);    //旧路径的长度 
	strcpy(p1->path,newpath);            //改p1的路径   
	
	//连接结点 
	if(p2->P_left==NULL) {
		p2->P_left=p1;
		p1->P_parents=p2;
	}
	else {
		if(p1->label==0){     //被移动的是文件夹 ，类似头插法 
			p=p2->P_left;
			p2->P_left = p1;
			p->P_parents=p1;
			p1->P_parents = p2;
			p1->P_right = p;
			change_path(len_oldpath,newpath,p->P_left);  //改p1左子树的路径 
		}
		else {               //被移动的是文件 ,插在文件夹之后，原有文件之前 
			p=p2->P_left;
			while(p->P_right!=NULL&&p->label==0) p=p->P_right;
			p1->P_right=p->P_right;
			if(p->P_right) p->P_right->P_parents=p1;
			p->P_right=p1;
			p1->P_parents=p;
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
	system("cls");  //清屏
	page_title("重命名指令一：mv <笔记原文件名> <笔记目标文件名>");
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
	int i;
	for( i=0;i<(len_oldpath-len_oldname);i++){
		path_pre[i]=POINTER->path[i];
	} 
	char* newpath=strcat(path_pre,newname);
		if(!rename(POINTER->path,newpath)){ //以绝对路径进行重命名 
		    strcpy(POINTER->name,newname);  //实际文件（夹）的名字和树节点储存的名字都要改
			strcpy(POINTER->path,newpath);
			POINTER->time=Today();        //更新 最近修改时间 
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
	    int i=2,j;
		int len=strlen(path);
	    while(i<len&&path[i]=='/'){   //有几个就回退几个目录 
	    	p=p->P_parents;
			i=i+3;
		}
		char* path_post=(char*)malloc(sizeof(char)*(len-i+2));
		for(j=0;j<len-i+2;j++){
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
		int i;
		for(i=0;i<len;i++){
		    path_post[i]=p->path[i+len_oldpath];  //路径不变的部分；oldpath：路径要变为newname的部分 
	    }
	    char* path_new=strcat(newpath,path_post);
	    strcpy(p->path,path_new);     //求出绝对路径 
		change_path(len_oldpath,newpath,p->P_left);
	    change_path(len_oldpath,newpath,p->P_right);
	} 
	return;
}

int Today(void){   //获取当前时间 
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

void Sort(void){  //对当前目录下的文件及文件夹进行时间排序
	system("cls");  //清屏
	page_title("排序指令一：sort（按照时间排序）"); 
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
			if(s->label==0){    //文件夹 
				if(s->time > n){
					t=s;
					n=s->time;
				}
			}
			else {    //文件 
				if(s->time > m){
					tf=s;
					m=s->time;
				}
			}
		}
		
		q=t->P_parents;    //分离结点 
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

void create(char* name){  //创建txt文件
	system("cls");  //清屏
	page_title("创建指令二："); 
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


/************************************************************************************/
