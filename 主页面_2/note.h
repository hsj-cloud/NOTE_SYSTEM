#ifndef __NOTE_H__
#define __NOTE_H__

#define MEMBER_SIZE 100  //图书馆先存在100个管理员和普通用户（100其实可以用任何数字代替，只为了用户表初始化用）

typedef struct Node
{
	int account_number;  //账号（图书证号） 
	int code;  //密码
	struct Node *next; 
}Node,*LinkList,Ordinary_users;  //结点，链表，普通用户

struct DATA{  //该结构体用来做指令判断和保存文件名、路径
	int value_1;  //用来做指令判断 
	int value_2;  //用来做指令判断
	char content_1[260];  //用于保存文件名 
	char content_2[260];  //用于保存路径 
};

typedef struct node    //合并之后的树 
{
	int label;         //标签：1：代表文件；0：代表文件夹 
	char name[260];    //文件（夹）名字 
	char path[260];    //文件（夹）路径 
	char *tag_1[10];   //三个标签 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //最近修改时间 
	struct BiTNode* P_left;      //指向左孩子的指针 
	struct BiTNode* P_right;     //指向右孩子的指针 
	struct BiTNode* P_parents;   //指向父结点的指针
}Tree,*Tree; 

/*     每个人各自的树 
typedef struct BiTNode  //世佳使用的树 
{           
	int label;         //标签：1：代表文件；0：代表文件夹 
	char name[260];    //文件（夹）名字 
	char path[260];    //文件（夹）路径 
	char *tag_1[10];   //三个标签 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //最近修改时间 
	struct BiTNode* P_left;      //指向左孩子的指针 
	struct BiTNode* P_right;     //指向右孩子的指针 
	struct BiTNode* P_parents;   //指向父结点的指针 
}BiTNode,*BiTree; 

struct node  //政佳使用的树
{           
 int label;         //标签：1：代表文件；0：代表文件夹 
 char name[260];    //文件（夹）名字 
 char path[260];    //文件（夹）路径 
 char *tag_1[10];   //三个标签 
 char *tag_2[10];
 char *tag_3[10];
 int time;          //最近修改时间 
 struct node* P_left;      //指向左孩子的指针 
 struct node* P_right;     //指向右孩子的指针 
 struct node* P_parents;   //指向父结点的指针 
};

struct node  //文辉使用的树 
{
	int label;
	char path[260];
	char name[260];
	char tag_1[10];
	char tag_2[10];
	char tag_3[10];
	struct node *left;
	struct node *right;
	struct node *father;
};

typedef struct node  //丹叶使用的树 
{           
	int label;         //标签：1：代表文件；0：代表文件夹 
	char name[260];    //文件（夹）名字 
	char path[260];    //文件（夹）路径 
	char *tag_1[10];   //三个标签 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //最近修改时间 
	struct node* P_left;      //指向左孩子的指针 
	struct node* P_right;     //指向右孩子的指针 
	struct node* P_parents;   //指向父结点的指针 
}node;
*/

/*****************************************世佳的函数**********************************************/ 
void page_title(char *menu_item);  //显示整体标题的函数
void return_confirm();  //等待返回确认的函数
void continue_confirm();  //等待继续确认的函数
void Read_Ordinary_users(LinkList *L);  //读入文本文档（Ordinary_users.txt）
void Updata_Ordinary_users(LinkList *L);  //更新普通用户数据到文本文档（Ordinary_users.txt）
void CreateListTail(LinkList *L,int n);  //尾插法_初始化单链表
void Addusers(LinkList *L);  //注册新用户（尾部插入）
void Cancelusers(LinkList *L);  //注销用户
void Displayusers(LinkList *L);  //显示用户
int Login_system(LinkList *L);  //登录系统
void get_nextval(char child_string[],int *nextval);  //获得nextval数组的函数
int KMP_Algorithm(char child_string[],char parents_string[]);  //KMP算法（做与字符串有关的匹配）
void display_ls(Tree T);  //显示指令一：ls（显示所有笔记文件夹及笔记文件）
void display_ls_a(Tree T);  //显示指令二：ls -a（按树状结构显示所有笔记文件夹和笔记文件）
void display_left_child(Tree T);  //用于遍历某个结点的子文件夹或子文件 
void display_ls_NotePath(Tree T,char content_1[]);  //显示指令三：ls <笔记文件夹路径>（显示指定文件下所有的内容（子笔记文件夹和笔记文件））
void display_ls_NotePath_grep(Tree T,char content_1[],char content_2[]);  //显示指令四：ls <笔记文件夹路径> grep "搜索内容" （显示命令指定文件下所有的带有搜索内容的文件夹名及文件名）
/*************************************************************************************************/

/******************************************政佳的函数*********************************************/ 
int remove_mulu(const char *dir);
struct node *right_travel(struct node *T);		//遍历右子树，找到下一个为空的指针并返回
char *get_path();							//获取当前目录
void free_all(struct node *T);									//释放空间
void del_NodeTree(struct node *Node_Tree);							//删除笔记的结点
struct node *createfather();							//创建树的根结点
struct node *createtree_label(struct node *father,const char *name);		//创建子目录
struct node *create_right_label(struct node *father,const char *name);			//创建同级目录
struct node *create_left_txt(struct node *father,const char *name);	//增加子结点为笔记文件
struct node *Travsal_name(struct node *T,char *name);			//前序遍历,查看结点是否有相同名字
void PreOrderTravsal(struct node *T,const char *path);		//前序遍历,查看是否有相同路径
struct node *OrderTravsal(struct node *T,const char *path);		//前序遍历,查看结点是否有相同路径
struct node *OrderTravsal_parent(struct node *T,const char *path);  //前序遍历,查看结点的孩子是否有相同路径
void perorder(struct node *T);
void cd_pre(struct node *T);    			//移动到上级目录
struct node *cd(struct node *T);			//切换工作目录到指定目录,并返回指向该目录的指针
struct node *md(struct node *T);  			//创建目录(在当前工作指针处创建子目录)
void rm_r(struct node *T); 							/*删除目录，并在删除目录的同时 */
void rm(struct node *T);												//对笔记文件进行删除
/*************************************************************************************************/

/********************************************文辉的函数*******************************************/
struct DATA* cmd_manage();  //命令处理
void select_menu();
void search_file_tag (Tnode *tree);  //根节点
void search_add_file_tag (Tnode *tree);  //根节点
void search_delect_file_tag (Tnode *tree);  //根节点
void tag_s (Tnode *tree);  //当前目录根节点
void tag_sa (Tnode *tree);  //当前目录根节点
/**************************************************************************************************/ 

/*********************************************丹叶的函数*******************************************/
void move_file(void);    //移动文件/文件夹
int check(char name[],Tree p);  //查重：在p指向的目录下查找是否有名字为name的文件/目录
void rename_file(void);  //重命名文件/文件夹
Tree search(char path[],Tree p);  //查找，找到给定路径文件/文件夹所在的结点,并让指针p指向该结点
void change_path(int len_oldpath,char* newpath,Tree p);  //先序遍历改路径
int Today(void);  //获取当前时间
void Sort(void);  //对当前目录下的文件及文件夹进行时间排序
void create(void);  //创建txt文件
int check(char name[],Tree p);  //查重：在p指向的目录下查找是否有名字为name的文件/目录
/**************************************************************************************************/

#endif
