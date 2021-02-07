#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conin.h>
#include "note.h"

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
	display_ls(T->P_right_child); 
	display_ls(T->P_left_child); 
}

void display_ls_a(BiTree T)  //显示指令二：ls -a（按树状结构显示所有笔记文件夹和笔记文件） 
{
	
}

void display_ls_NotePath(BiTree T)  //显示指令三：ls <笔记文件夹路径>（显示指定文件下所有的内容（子笔记文件夹和笔记文件）） 
{
	system("cls");  //清屏 
	page_title("显示指令三：ls <笔记文件夹路径>");
	//if(*monitor_1==0)
	//{
		char target_path[260];  //所要查找的指定目标路径 
		printf("请输入你所指定的路径：\n");
		scanf("%s",target_path);
		//*monitor_1=1;  //引入指针变量 monitor_1（监视器1），可以用于监控递归时是否再进行指定路径的输入 
	//}
	if(KMP_Algorithm(target_path,T->path)!=0)  //指定目标路径配对成功
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
		display_ls_NotePath(T->P_left_child);  //左递归，遍历它的左孩子 
	}
}

void display_ls_NotePath_grep(BiTree T)  //显示指令四：ls <笔记文件夹路径> grep "搜索内容" （显示命令指定文件下所有的带有搜索内容的文件夹名及文件名） 
{
	system("cls");  //清屏
	page_title("显示指令四：ls <笔记文件夹路径> grep “搜索内容”");
	int i,j;
	//if(*monitor_2==0)
	//{
		char target_path[260];  //所要查找的指定目标路径
		printf("请输入你所指定的路径：\n");
		scanf("%s",target_path);
		//*monitor_2=1;  //引入指针变量 monitor_2（监视器2），可以用于监控递归时是否再进行指定路径的输入
	//}
	//if(*monitor_3==0)
	//{
		char child_string[20];
		printf("请输入你所指定的_搜索内容：\n");
		scanf("%s",child_string);
		int length_child_string;
		length_child_string=strlen(child_string);
		for(j=20;j>1;j--)
		{
			child_string[j]=child_string[j-1];
		}
		child_string[0]=length_child_string;
		//*monitor_3=1;  ////引入指针变量 monitor_3（监视器3），可以用于监控递归时是否再进行搜索内容的输入
	//}
	if(KMP_Algorithm(target_path,T->path)!=0)
	{
		char parents_string[20];
		int length_parents_string;
		length_parents_string=strlen(parents_string);
		parents_string[0]=length_parents_string;
		for(i=1;i<20;i++)
		{
			parents_string[i]=T->name[i-1];
		}
		if((Index_KMP(child_string,parents_string))!=0)  //指定目标路径配对成功 
		{
			if(T=NULL)
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
			display_ls_NotePath_grep(T->P_left_child);  //左递归，遍历它的左孩子 
		}
	}
}

void sort_date(BiTree T)  //根据时间日期进行排序 
{
	
}
