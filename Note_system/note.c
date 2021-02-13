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


Tree HEAD;        //树的头节点
Tree POINTER;     //全局变量，实时指向用户打开的当前目录 
int top = -1;			//堆栈的变量 
FILE *f_write = NULL;	//写进txt文件时的指针 
FILE *f_read = NULL;	//读txt文件时的指针

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

void Read_Ordinary_users(LinkList *L)  //读入文本文档（Ordinary_users.txt）
{
	LinkList p,r;
	FILE *file_p_read;
	file_p_read=fopen("FILE_普通用户_账号_密码\\Ordinary_users.txt","r");
	r=*L;  //r为指向尾部的结点
	int i;
	for(i=0;i<MEMBER_SIZE;i++)
	{
		p=(Node *)malloc(sizeof(Node));  //分配一块内存给结点p
		if(fscanf(file_p_read,"%d",&p->account_number)!=1)
		{
			break;
		}
		fscanf(file_p_read,"%d",&p->code);
		r->next=p;  //把新生成的结点p插入到r的后面
		r=p;  //将当前的结点定义为新的表尾终端结点
	}
	r->next=NULL;
	fclose(file_p_read);
}

void Updata_Ordinary_users(LinkList *L)  //更新普通用户数据到文本文档（Ordinary_users.txt）
{
	system("cls");  //清屏
	page_title("更新普通用户数据");
	LinkList p,q;
	FILE *file_p_write;
	file_p_write=fopen("FILE_普通用户_账号_密码\\Ordinary_users.txt","w");
	p=*L;  //p为指向头部的结点
	p=p->next;
	while(p)
	{
		if(p->account_number!=0&&p->code!=0)
		{
			fprintf(file_p_write,"%d ",p->account_number);
			fprintf(file_p_write,"%d\n",p->code);
		}
		q=p;
		p=p->next;
		free(q);  //释放结点q，清除结点q的数据
	}
	fclose(file_p_write);
	printf("更新普通用户数据成功！\n"
		"————————————————————————\n" 
		"更新后请重启该程序，保证账号密码更新成功！\n"
		"————————————————————————\n");
	return_confirm();  //请按任意键返回
}

void CreateListTail(LinkList *L,int n)  //尾插法_初始化单链表
{
	system("cls");  //清屏
	page_title("初始化用户表");
	printf("这一步为初始化普通用户表。\n"
		"——————————————————\n");
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
	int i=0;
	int sign;  //sign起到标志的作用
	int a[MEMBER_SIZE];  //暂存用户，用于检验账号是否重复注册
	LinkList p,s;
	p=*L;  //p为指向头部的结点
	while(p->next)  //p->next==NULL时，循环结束，即p为链表中最后一个结点
	{
		p=p->next;
		a[i]=p->account_number;
		i++;
	}
	s=(LinkList)malloc(sizeof(Node));  //分配一块内存给结点s
	printf("请输入你要注册的账号：\n");
	scanf("%d",&s->account_number);
	printf("请输入你的密码：\n");
	scanf("%d",&s->code);
	for(i=0;i<MEMBER_SIZE;i++)
	{
		if(s->account_number==a[i])
		{
			printf("该账号已经登记过了！\n"
				"————————————————\n");
			sign=-1;
			return_confirm();  //请按任意键返回
		}
	}
	if(sign!=-1)
	{
		p->next=s;
		s->next=NULL;
		printf("注册成功！\n"
			"——————————\n");
		return_confirm();  //请按任意键返回
	}
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

void display_ls(Tree T)  //显示指令一：ls（显示所有笔记文件夹及笔记文件）
{
	//page_title("显示指令一：ls");
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

void display_ls_a(Tree T)  //显示指令二：ls -a（按树状结构显示所有笔记文件夹和笔记文件）
{
	//system("cls");  //清屏
	//page_title("显示指令二：ls -a");
	printf("该功能暂时未完善完毕，暂不开放使用\n");
}

void display_left_child(Tree T)  //用于遍历某个结点的子文件夹或子文件（遍历它的左子树）
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

void display_ls_NotePath(Tree T,char content_1[])  //显示指令三：ls <笔记文件夹路径>（显示指定文件下所有的内容（子笔记文件夹和笔记文件））
{
	//page_title("显示指令三：ls <笔记文件夹路径>");
	if(strcmp(content_1,T->path)==0)  //目标路径匹配成功
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
	display_ls_NotePath(T->P_left,content_1);  //目标路径若匹配失败，先遍历它的左子树，后遍历它的右子树
	display_ls_NotePath(T->P_right,content_1);
}

void display_ls_NotePath_grep(Tree T,char content_1[],char content_2[])  //显示指令四：ls <笔记文件夹路径> grep "搜索内容" （显示命令指定文件下所有的带有搜索内容的文件夹名及文件名）
{
	//page_title("显示指令四：ls <笔记文件夹路径> grep “搜索内容”");
	int i,j;
	char child_string[260];
	//printf("1");  测试 
	int length_child_string;
	length_child_string=strlen(content_1);
	for(j=260;j>1;j--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
	{
		child_string[j]=content_1[j-1];
	}
	child_string[0]=length_child_string;
	char parents_string[260];
	int length_parents_string;
	length_parents_string=strlen(T->path);
	for(i=260;i>1;i--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
	{
		parents_string[i]=T->path[i-1];
	}
	parents_string[0]=length_parents_string;

	if(KMP_Algorithm(child_string,parents_string)!=0)  //第一次child_string和parents_string是做目标路径的调整
	{
		for(j=260;j>1;j--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
		{
			child_string[j]=content_2[j-1];
		}
		length_child_string=strlen(content_2);
		child_string[0]=length_child_string;
		for(i=260;i>1;i--)  //由于KMP算法中，字符数组第一个位置存储该字符串的长度，故作如此调整
		{
			parents_string[i]=T->name[i-1];
		}
		length_parents_string=strlen(T->name);
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
			display_ls_NotePath_grep(T->P_left,content_1,content_2);  //匹配成功后，左递归，遍历他的左子树
		}
	}
	display_ls_NotePath_grep(T->P_left,content_1,content_2);  //若匹配失败，则先遍历它的左子树，后遍历它的右子树
	display_ls_NotePath_grep(T->P_right,content_1,content_2);
}

/*********************************************************************************/



/*********************************政佳的部分**************************************/
/******************************函数内部的函数*************************************/

/*********************堆栈*********************************/
void push(struct node **a,struct node * elem){
    a[++top]=elem;
}
//弹栈函数
void pop( ){
    if (top==-1) {
        return ;
    }
    top--;
}

//拿到栈顶元素
struct node *getTop(struct node **a){
    return a[top];
}
/**********************************************************/

/******************************函数的内部函数*************************************/
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
	sprintf(father_Tree->tag_1,"---");
	sprintf(father_Tree->tag_2,"---");
	sprintf(father_Tree->tag_3,"---");
	father_Tree->P_left = NULL;
	father_Tree->P_parents = NULL;
	father_Tree->P_right = NULL;
	father_Tree->time = 0;
	chdir(father_Tree->path);						//将工作指针切换到“开始”目录
	return father_Tree;
}

struct node *createtree_label(struct node *father,const char *name)			//创建目录
{		//father指的是该目录的父目录的结点(不一定是上一个结点) 		//name是该目录的名称
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
	sprintf(Node_Tree->tag_1,"---");
	sprintf(Node_Tree->tag_2,"---");
	sprintf(Node_Tree->tag_3,"---");
	if(father->P_left != NULL)					//该父目录有左孩子
	{
		str = right_travel(father->P_left);
		str->P_right = Node_Tree;
		Node_Tree->P_parents = str;
	}
	else										//该父目录无左孩子
	{
		father->P_left = Node_Tree;
		Node_Tree->P_parents = father;
	}
	chdir(Node_Tree->path);						//将工作指针指向新目录
	POINTER = Node_Tree;
	return Node_Tree;
}

struct node *create_left_txt(struct node *father,const char *name)	//增加子结点_笔记文件
{	//father指的是目录的父目录的结点(不一定是上一个结点)
	struct node *Node_Tree = (struct node *)malloc( sizeof(struct node) );
	struct node *str = NULL;
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
		return;
	}
	else
	{
		str = strstr(pat,path);						//如果用户输入的是相对路径
		if( str != NULL )							//输入的是绝对路径的子路径，则指针不为空
		{
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
	return NULL;
	free(pat);
	free(p);
}

struct node *find_first(struct node *father_Tree,struct node *Node_Tree,const char *path)
{			//利用路径找到结点的第一个父结点
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
	/************将path_n的最后一个‘\’删除*******************/
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

struct node *OrderTravsal_parent(struct node *T,const char *path)//前序遍历,查看结点的孩子是否有相同路径
{																//有的话，要返回该结点父目录的指针
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
		memset(pat,0,sizeof(pat));								//清空
		sprintf(pat,p->path);									//把p->path复制到pat里面去
		if( strcmp(path,pat) == 0 )
		{
			if( p->P_parents == NULL || p->P_parents->P_right != p)		//这句还有点问题
			{
				return p;
			}
			else
			{
				a = find_first(T,p,path);		//找到父目录的结点
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

void perorder(struct node *T)				//打印树
{
	if(T == NULL)
	{
		return;
	}
	printf("文件名称:%s\t文件路径:%s\n",T->name,T->path);
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


/******************************直接调用的函数***********************************/
void cd_pre(struct node *T)    			//移动到上级目录
{
	char *i = get_path();						//获取当前路径
	char *p = NULL;
	struct node *str = OrderTravsal(T,i);	//在树中寻找该路径的结点，并返回指向它的指针
	if( str->P_parents == NULL )				//如果父结点为空，即该结点为根节点
	{
		printf("切换失败！请查看是否为根目录！\n");
		system("pause");
	}
	else
	{
		if( chdir(str->P_parents->path) == 0 )	//切换到父结点的路径
		{
			printf("切换到上级目录！\n");
			p = get_path();
			printf("当前所在目录为：%s\n",p);
			system("pause");
		}
		else
		{
			printf("切换失败！发生未知错误\n");
			system("pause");
		}
	}
}

struct node *cd(struct node *T)			//切换工作目录到指定目录,并返回指向该目录的指针
{
	char *path= NULL;
	char *str = NULL;
	char *i = get_path(); 
	path = (char *)malloc( sizeof(char[260]) );
	printf("————可输入您要切换到的文件夹的绝对路径!————\n");
	printf("————注意路径中的 '\\' 要成对出现————\n");
	printf("————也可以这样输入： 目录\\目录\\文件('开始'不必输入)————\n");
	printf("————若要返回开始目录，输入 开始 即可————\n");
	printf("请输入：");
	scanf("%s",path);
	if( strcmp(path,"开始")==0 || strcmp(path,"开始\\")==0 || strcmp(path,"\\开始")==0 || strcmp(path,"\\开始\\")==0)
	{										//如果用户是要回到“开始”菜单
		chdir(T->path); 					//直接切换到根节点
		printf("切换成功!\n");
		str = get_path();
		printf("当前所在目录为：%s\n",str);
		system("pause");
		return T;							// 并返回指向根结点的指针
	}
	struct node *p = OrderTravsal(T,path);					//找到后把指针弄出来
	if( p != NULL)
	{
		chdir(T->path);						//切换工作指针到开始目录
		if(chdir(path) == 0)
		{
			printf("切换成功！\n");
			str = get_path();
			printf("当前所在目录为：%s\n",str);
			POINTER = p;
			system("pause");
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
		system("pause");
	}
	free(path);
}


void md(struct node *T)  			//创建目录(在当前工作指针处创建子目录)
{											//需要输入指向树根的指针
	char *mulu = NULL;						//创建完成后，会返回指向该新目录的指针,并将工作指针移到这里
	char *i = get_path();					//获取当前路径
	struct node *p = NULL;					//如果当前目录已有子目录，会创建在子目录右子树的最下面
	struct node *str = NULL;
	mulu = (char *)malloc( sizeof(char [260]) );
	printf("当前所在目录:%s\n",i);
	printf("请输入目录名称(注意：是创建该目录下的子目录)：");
	scanf("%s",mulu);						//目录的名称
	p = OrderTravsal_parent(T,i);			//当找到当前路径所在目录的父目录的结点时就停止
	/*还要看看该父目录结点有没有左子树，左子树上有没有右子树*/
	if(mkdir(mulu) == 0)
	{
		if( p != NULL)
		{
			createtree_label(p,mulu);				//为该目录创建一个树的结点
			printf("创建 %s 目录成功!\n",mulu);
			system("pause");
		}
		else
		{
			printf("系统文件出现故障！请查看是否被修改!\n");
			system("pause");
		}
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
			chdir(T->path);
			if(remove_mulu(str->path) == 3)
			{
				printf("删除中.....\n");
				//删除str指向的结点，然后把右节点上的接上
				//如果str是别人的左孩子，需要把str->P_right替代str的位置
				free_all(str->P_left);
				str->P_left = NULL;  //处理掉str的左孩子
				if(str->P_parents->P_left == str)		//如果没有人的右指针指向str
				{
					str->P_parents->P_left = str->P_right;	//就把str右边第一个变成str父结点的左孩子
					if(str->P_right != NULL)
					{
						str->P_right = str->P_parents;		//让右边第一个的父指针指向新的父结点
					}
				}
				else
				{
					str->P_parents->P_right = str->P_right;	//如果有人的右指针指向str
					if(str->P_right != NULL)
					{
						str->P_parents->P_right->P_parents = str->P_parents;
					}
				}
				str->P_right = NULL;
				str = NULL;
				free(str);
				printf("删除目录 %s 成功!\n",mulu);
				system("pause");
			}
			else
			{
				printf("删除目录失败！\n");
				system("pause");
			}
		}
		else
		{
			printf("未找到该名称的文件！\n");
			system("pause");
		}
	}
	else
	{
		printf("未找到该名称的文件！\n");
		system("pause");
	}
	free(mulu);
}

void rm(struct node *T)												//对笔记文件进行删除
{
	char *name = NULL;
	name = (char *)malloc( sizeof(T->name) );
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
				system("pause");
			}
			else
			{
				printf("删除失败!\n");
				system("pause");
			}
		}
		else
		{
			printf("无此名称的文件！删除失败！\n");
			system("pause");
		}
	}
	else
	{
		printf("无此名称的文件！删除失败！\n");
		system("pause");
	}
}
/*******************************************************************************/

/*********************文件的输入输出**********************/

void full_filename(struct node *Node_Tree)  //补全路径函数封装
{					//输入指向树结点的指针
	char *p = get_path();					//获取C文件的工作路径，等会用来补全相对路径
	if(strcmp(Node_Tree->path,"(null)") == 0)
	{
		strcat(p,"\\开始");					//开始目录存进去的相对路径是NULL
		sprintf(Node_Tree->path,p);			//用p覆盖树的路径
	}
	else
	{
		strcat(p,Node_Tree->path);			//把相对路径复制在p的后面，这样p就是完整的了
		sprintf(Node_Tree->path,p);			//用p覆盖树的路径
	}

}

char *cut_filename(struct node *Node_Tree)	//分解绝对路径函数封装
{											//path——"D:\C程序\文件的递归查找\开始\2"
	char *delim = "\\开始\\";				//以‘\’为分隔的符号
	char *p = NULL ;
	char str[260];
	sprintf(str,Node_Tree->path);			//分隔后的字符  \开始\2
	p = strstr(str,delim);
	return p;
}

void write_filebypre(const char *filename,struct node *T)	//前序写入文件，若子节点为空，则设为 #
{
	char *address = NULL;
	if( T == NULL)
	{
		return;
	}
	address = cut_filename(T);
    fprintf(f_write,"%2d%50s%120s%20s%20s%20s%10d\n",T->label,T->name,address,T->tag_1,T->tag_2,T->tag_3,T->time);
    if(T->P_left == NULL)
    {
    	fprintf(f_write,"%2d%50s%120s%20s%20s%20s%10d\n",3,"#","---","---","---","---",0);
	}
	else
	{
		write_filebypre(filename,T->P_left);
	}

    if(T->P_right == NULL)
    {
    	fprintf(f_write,"%2d%50s%120s%20s%20s%20s%10d\n",3,"#","---","---","---","---",0);
		return;
	}
	else
	{
		write_filebypre(filename,T->P_right);
	}
}

void read_filebypre(const char *filename,struct node **T)  //从文件读出树
{
	struct node temdata;
    if(f_read == NULL)
	{
		f_read = fopen(filename,"w+");
		f_write = fopen("preorder_tree.txt","w");			//将树保存到TXT文件中 
		write_filebypre("preorder_tree.txt",(*T));
		fclose(f_write);
		return ;
	}
    fscanf(f_read,"%2d%50s%120s%20s%20s%20s%10d\n",&temdata.label,temdata.name,temdata.path,temdata.tag_1,temdata.tag_2,temdata.tag_3,&temdata.time);
    //就算后面，fscanf也只是读有字符的

	if ( temdata.label == 3 && strcmp(temdata.name,"#") == 0 )
	{
		*T = NULL;
	}	
    else
	{
        *T = (struct node *)malloc( sizeof(struct node) );
        (*T)->label = temdata.label;
        (*T)->time = temdata.time;
        sprintf( (*T)->path,temdata.path );
		full_filename( (*T) );
		sprintf( (*T)->tag_1,temdata.tag_1 );
		sprintf( (*T)->tag_2,temdata.tag_2 );
		sprintf( (*T)->tag_3,temdata.tag_3 );
		sprintf( (*T)->name,temdata.name );
		
        read_filebypre(filename,&(*T)->P_left);
        read_filebypre(filename,&(*T)->P_right);
    }
}

/*******************************************************************************/



/*********************************文辉的部分************************************/


struct DATA* cmd_manage()
{
	char shuru[540];//输入的值输入的例子 tag -add <title> "neirong"
	char first[5];
	char second[262];
	char third[262];
	char forth[262];
	char change1[260];//记录文件名
	char change2[260];//记录标签内容
	printf("请输入对应操作的指令：\n"
		"——————————————\n");
	gets ( shuru );
	memset ( first, 0, sizeof ( first ) );
	sscanf ( shuru, "%[^ ]", first );//第一个空格前
	sscanf ( shuru, "%*[^ ] %[^ ]", second );//第二个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %[^ ]", third );//第三个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %*[^ ] %[^ ]", forth );
	memset ( change1, 0, sizeof ( change1 ) );//清除缓存（没清之前有错误）
	memset ( change2, 0, sizeof ( change2 ) );
	struct DATA *data=(struct DATA*)malloc(sizeof(struct DATA));


    if ( strcmp ( "back", first ) == 0 )
	{
		data->value_1=100;
		//data->value_2=0;
	}

	else if ( strcmp ( "ls", first ) == 0 && strlen ( shuru ) == 2 )
	{
		data->value_1=1;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "ls", first ) == 0 && strcmp ( "-a", second ) == 0 )
	{
		data->value_1=2;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' && strcmp ( "grep", third ) == 0 && forth[0] == '"' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=4;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=3;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "cd", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=6;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "cd", first ) == 0 )
	{
		//printf ( "%s", first );
		data->value_1=5;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "mv", first ) == 0 && second[0] == '<' && third[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sscanf ( third, "<%[^>]", change2 );//去除<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=7;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "mv", first ) == 0 && strcmp ( "-a", second ) == 0 && third[0] == '<' && forth[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "<%[^>]", change2 );//去除<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=8;  //返回值（用于作指令判断）
	}
	/*else if ( strcmp ( "mv", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' && forth[0] == '<' )
	{
		//data->value_1=1;
		//data->value_2=1;
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "<%[^>]", change2 );//去除<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=9;  //返回值（用于作指令判断）
	}*/
	else if ( strcmp ( "rm", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=10;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "rm", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=11;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "tag", first ) == 0 && second[0] == '<' )
	{

		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=12;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-add",second)==0 && third[0] == '<' && forth[0] == '"' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=13;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-del",second)==0 && third[0] == '<' && forth[0] == '"' )
	{

		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=14;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "tag", first ) == 0 && strcmp("-s",second) ==0&& third[0] == '"' )
	{
		//data->value_1=0;
		//data->value_2=1;
		sscanf ( third, "\"%[^\"]", change1 );
		//printf ( "%s", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=15;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-sa",second) ==0&& third[0] == '"' )
	{
		//data->value_1=1;
		//data->value_2=0;
		sscanf ( third, "\"%[^\"]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=16;  //返回值（用于作指令判断）
	}
	else if ( strcmp ( "md", first ) == 0 && second[0] == '<' )
	{
		//data->value_1=2;
		//data->value_2=1;
		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=17;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "md", first ) == 0 && strcmp ( "-ml", second ) == 0 && third[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=18;  //返回值（用于作指令判断）
	}

	else if ( strcmp ( "sort", first ) == 0  )  //&& second[0] == '<'（多出来不需要的部分）
	{
		//sscanf ( second, "<%[^>]", change1 );
		//sprintf(data->content_1,"%s",change1);
		data->value_1=19;  //返回值（用于作指令判断）
	}
	else {
		//printf("wrong cmd\n");
	}
	return data;


	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^“]“%[^”]",sda);

	*///printf("%s",str);
	//printf("%s %s %s",first,second,third);
	//printf("%s",shuru);



}

struct node* creattree ( char *file_name, char*tag_name )
{
	struct node* newnode = ( struct node* ) malloc ( sizeof ( struct node ) );
	sprintf ( newnode->name, "%s", file_name );
	sprintf(newnode->tag_1,"%s","---");
	sprintf(newnode->tag_2,"%s","---");
	sprintf(newnode->tag_3,"%s","---");
	sprintf ( newnode->tag_1, "%s", tag_name );
	newnode->label=0;
	newnode->P_left = NULL;
	newnode->P_right = NULL;
	return newnode;
};


void search_file_tag ( struct node*tree, char *search_name ) //根节点

{


	if ( tree == NULL )
	{
		return;
	}
	struct node* stack[10];
	int stacktop = -1;
	struct node*pmove = tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->P_left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strcmp(pmove->tag_1,"---")!=0 )
					printf ( "标签1：%s\n", pmove->tag_1 );
				if ( strcmp(pmove->tag_2,"---")!=0 )
					printf ( "标签2；%s\n", pmove->tag_2 );
				if ( strcmp(pmove->tag_3,"---")!=0 )
					printf ( "标签3；%s\n", pmove->tag_3 );
				break;
			}
			else
			{
				pmove = pmove->P_right;
			}





		}

	}
}
void search_add_file_tag ( struct node*tree, char*search_name, char* tag_name ) //根节点
{
	if(strlen(tag_name)>20){
	       printf("the tag_name is too long\n");
	       return;}
	if ( tree == NULL )
		return;
	struct node* stack[10];
	int stacktop = -1;
	struct node*pmove = tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->P_left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strcmp(pmove->tag_1,"---")==0)
				{
					memset(pmove->tag_1,0,sizeof(pmove->tag_1));
					sprintf ( pmove->tag_1, "%s", tag_name );
					printf ( "添加到tag-1\n" );
					break;
				}
				else
				{
					if ( strcmp(pmove->tag_2,"---")==0)
					{
						memset(pmove->tag_2,0,sizeof(pmove->tag_2));
						sprintf ( pmove->tag_2, "%s", tag_name );
						printf ( "添加到tag-2\n" );
						break;
					}
					else
					{
						if (strcmp(pmove->tag_3,"---")==0)
						{
							memset(pmove->tag_3,0,sizeof(pmove->tag_3));
							sprintf ( pmove->tag_3, "%s", tag_name );
							printf ( "添加到tag-3\n" );
							break;
						}
						else
						{
							printf ( "all tags are full\n" );
							break;
						}
					}
				}


			}
			else
			{
				pmove = pmove->P_right;
			}
		}

	}



}
void search_delect_file_tag ( struct node*tree, char*search_name, char*tag_name ) //根节点
{
	if ( tree == NULL )
		return;
	struct node* stack[10];
	int stacktop = -1;
	struct node*pmove = tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->P_left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strcmp(pmove->tag_1,"---")==0 && strcmp(pmove->tag_1,"---")==0 && strcmp(pmove->tag_1,"---")==0 )
				{
					printf ( "no tags\n" );
					break;
				}
				else
				{
					if ( strcmp ( tag_name, pmove->tag_1 ) == 0 )
					{

						memset ( pmove->tag_1, 0, sizeof ( pmove->tag_1 ) );
						printf ( "删除tag_1成功\n" );
						break;
					}
					else if ( strcmp ( tag_name, pmove->tag_2 ) == 0 )
					{
						memset ( pmove->tag_2, 0, sizeof ( pmove->tag_2 ) );
						printf ( "删除tag_2成功\n" );
						break;
					}
					else if ( strcmp ( tag_name, pmove->tag_3 ) == 0 )
					{
						memset ( pmove->tag_3, 0, sizeof ( pmove->tag_3 ) );
						printf ( "删除tag_3成功\n" );
						break;
					}

					printf ( "no such tag\n" );
					break;


				}




			}
			else
			{
				pmove = pmove->P_right;
			}
		}

	}
}
void tag_s ( struct node*tree, char*tag_name ) //当前目录根节点
{


	if ( tree == NULL )
		return;
	struct node* stack[10];
	int stacktop = -1;
	struct node*pmove = tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->P_left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 1 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "'%s'\n", pmove->name );
				}
				pmove = pmove->P_right;
			}
			else
				pmove = pmove->P_right;
		}


	}
}
void tag_sa ( struct node*tree, char*tag_name ) //当前目录根节点
{
	if ( tree == NULL )
		return;
	struct node* stack[10];
	int stacktop = -1;
	struct node*pmove = tree;
	while ( stacktop != -1 || pmove )
	{
		while ( pmove )
		{
			stack[++stacktop] = pmove;
			pmove = pmove->P_left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 0 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "文件名：%s\t", pmove->name );
					printf ( "路径：%s\n", pmove->path );
				}
					pmove = pmove->P_right;
			}

			else
				pmove = pmove->P_right;
		}

	}
}

/************************************************************************************/


/***********************************丹叶的部分***************************************/


void move_file(void){    //移动文件/文件夹
	//system("cls");  //清屏
	//page_title("移动指令一：mv <笔记文件名> <笔记文件夹目录>");
	char oldpath[260],newpath[260];  //oldname旧路径，newname新路径
	printf("请输入您要移动的文件或文件夹：");
	scanf("%s",oldpath);
	printf("请输入文件或文件夹的目标位置");
	scanf("%s",newpath);
	Tree p1;    //记录被移动文件/文件夹的结点位置
	Tree p2;    //记录目标位置的上一级
	int i,len_newpath;
	len_newpath = strlen(newpath);
	for( i=len_newpath-1;i>=0;i--){           //找到目标位置的上一级目录
		if(newpath[i]==92) break ;
	}
	int j=0;
	char newpath_post[260];
	while((j+i+1)<len_newpath){
		newpath_post[j]=newpath[j+i+1];  //newpath后缀
		j++;
	}
	newpath_post[j]='\0';
	if(!check(newpath_post,POINTER)) {
		printf("移动失败！\n新路径必须包含该文件夹的名字\n");
		return ;
	}
	if(rename(oldpath,newpath)!=0) {
		perror("rename");
		return ;
	}

	char newpath_pre[260];    //newpath的上一级路径
	for(j=0;j<i;j++){
		newpath_pre[j]=newpath[j];    //可能是相对路径，也可能是绝对路径
	}
	p1=search(oldpath,p1);      //在树中找到旧路径下的文件/文件夹，并用p1记录其位置
	p2=search(newpath_pre,p2);  //p2：新路径的上一级
    if(p2==NULL)
    return ;
	strcpy(newpath,p2->path);
	strcat(newpath,"\\");
	strcat(newpath,newpath_post); //移动后的绝对路径
	printf("移动后的绝对路径：%s\n",newpath);
	p1->time=Today();    //更新 最近修改时间
	Tree p=p1->P_parents;        //分离结点
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
			change_path(len_oldpath,newpath,p1->P_left);  //改p1左子树的路径
		}
		else {               //被移动的是文件 ,插在文件夹之后，原有文件之前
			p=p2->P_left;
			while(p->P_right!=NULL&&p->P_right->label==0) p=p->P_right;
			p1->P_right=p->P_right;
			if(p->P_right) p->P_right->P_parents=p1;
			p->P_right=p1;
			p1->P_parents=p;
		}
	}
	printf("移动成功！\n当前所在文件夹为：%s\n",POINTER->path);
	return ; 
  }

int check(char name[],Tree p){  //查重：在p指向的目录下查找是否有名字为name的文件/目录
	if(p->P_left==NULL)
		return 0;     //当前目录下无文件或文件夹
	p=p->P_left;
	while(p!=NULL){
		if(!strcmp(p->name,name))  return 1;  //找到重名文件/文件夹
		else p=p->P_right;
	}
	return 0;    //未找到重名文件/文件夹
}


void rename_file(void){  //重命名文件/文件夹
	//system("cls");  //清屏
	//page_title("重命名指令一：mv -a <笔记原文件名> <笔记目标文件名>");

	char newname[260];
	char oldname[260];
	printf("请输入要重命名的文件名：");
	scanf("%s",oldname);
	Tree p=POINTER->P_left;
	while(p!=NULL) {
		if(!strcmp(p->name,oldname)) break;
		else  p=p->P_right;
	}
	if(p==NULL) {
		printf("该文件不存在!\n");
		return ;
	}
	printf("请输入新名字: ");
	scanf("%s",newname);
	while(strlen(newname)>260){
		printf("名字过长，请输入260个字以内的新名字：\n");
		scanf("%s",newname);
	}
	if(check(newname,POINTER))  {      //在当前目录中查看是否出现重名
		printf("文件重名！请重新输入新文件名！");
		return ;
	}
	int len_oldpath=strlen(p->path);
	char newpath[260];
	strcpy(newpath,POINTER->path);
	strcat(newpath,"\\");
	strcat(newpath,newname);
	if(!rename(oldname,newname)){ //以绝对路径进行重命名
		    strcpy(p->name,newname);  //实际文件（夹）的名字和树节点储存的名字都要改
			strcpy(p->path,newpath);
			p->time=Today();        //更新 最近修改时间
			change_path(len_oldpath,newpath,p->P_left);  //改p及其左子树的路径
		}
		else{
			printf("重命名失败！\n");
			perror("rename");
		}
	return ;
}

Tree search(char path[],Tree p){  //查找，找到给定路径文件/文件夹所在的结点,并让指针p指向该结点
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
	    if(path[1]!='.'&&path[2]!=92) {
	    	char path_all[260];
	    	strcpy(path_all,p->path);
	    	strcat(path_all,"\\");
	    	strcat(path_all,path);
	    	return search(path_all,p);
		}
		else{
		    int i=2;
			int len=strlen(path);
			Tree q=p->P_parents;
			while(i<len&&path[i]==92){
				while(!strstr(p->path,q->path)){
					q=q->P_parents;
				}
				p=q;
				q=p->P_parents;
				i=i+3;
			}
			if(i-2==len) return p;
			else{
				char* path_post=(char*)malloc(sizeof(char)*(len-i+2));
				int j; 
		        for(j=0;j<len-i+1;j++)
			        path_post[j]==path[j+i-2];   //除去 ..\ 后的路径
			    printf("%s\n",path_post);
			    char* path_all;
		        strcpy(path_all,p->path);
		        strcat(path_all,"\\");
	            strcat(p->path,path_post);   //完整路径，即求出要找的文件（夹）的绝对路径
				while(p!=NULL){
			         if(!strcmp(path_all,p->path)) return p;
    	             if(strstr(path_all,p->path)) p=p->P_left;
	                 else p=p->P_right;
		        }
	            }}}
	return NULL;    //不执行上面语句中的返回，说明该路径下的文件（夹）不存在

}
void change_path(int len_oldpath,char* newpath,Tree p){  //先序遍历改路径
	if(p!=NULL) {
		int len_path=strlen(p->path);      //原路径长度
	    int len=len_path - len_oldpath;
	    char* path_post=(char*)malloc(sizeof(char)*(len+1));
		int i;
		for(i=0;i<len;i++){
		    path_post[i]=p->path[i+len_oldpath];  //路径不变的部分；oldpath：路径要变为newname的部分
	    }
	    path_post[i]='\0';
	    strcpy(p->path,newpath);
	    strcat(p->path,"\\");
		strcat(p->path,path_post);    //求出绝对路径
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
	//system("cls");  //清屏
	//page_title("排序指令一：sort（按照时间排序）");
	Tree p=POINTER->P_left;
	Tree s=POINTER->P_left;
	Tree head_file=NULL,p_file;  //
	Tree head_folder=NULL,p_folder;  //
	Tree q;
	int flag_file=0,flag_folder=0;
	int n=0,m=0;
	Tree t=NULL;
	Tree tf=NULL;
	while(POINTER->P_left!=NULL){
		n=0;
		m=0;
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
		if(t!=NULL){
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
		    t=NULL;
		}

		if(tf!=NULL){
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
		tf=NULL;
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

void create(void){  //创建txt文件
	//system("cls");  //清屏
	//page_title("创建指令二：md -ml");
    printf("当前所在的路径为：");
    printf("%s\n",POINTER->path);
	char name[260];
	printf("请输入文件名字：");
	scanf("%s",name);
	if(check(name,POINTER)){  //先检查文件是否重名
		printf("文件重名！\n");
		return;
	}
	FILE* fp=fopen(name,"w");  //创建文件
	if(fp==0){
		printf("创建失败！\n");
		return ;
	}
	fclose(fp);
	Tree pNew=(Tree)malloc(sizeof(BiTree));
	pNew->label = 1;
	strcpy(pNew->tag_1,"---");
	strcpy(pNew->tag_2,"---");
	strcpy(pNew->tag_3,"---");
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
		Tree p=POINTER->P_left;
        while(p->P_right!=NULL&&p->P_right->label==0){ //将结点插在文件夹之后，原有文件之前
        	p=p->P_right;
		}
		pNew->P_parents=p;
		pNew->P_right=p->P_right;
		if(p->P_right != NULL) p->P_right->P_parents = pNew;
		p->P_right=pNew;
	}
	printf("创建成功！\n");
	printf("——————————————\n");
	continue_confirm();  //等待继续确认的函数
	return ;
}

/************************************************************************************/
