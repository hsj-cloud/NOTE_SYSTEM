#ifndef __NOTE_H__
#define __NOTE_H__

#define MEMBER_SIZE 100  //ͼ����ȴ���100������Ա����ͨ�û���100��ʵ�������κ����ִ��棬ֻΪ���û����ʼ���ã�

typedef struct Node
{
	int account_number;  //�˺ţ�ͼ��֤�ţ� 
	int code;  //����
	struct Node *next; 
}Node,*LinkList,Ordinary_users;  //��㣬������ͨ�û�

struct DATA{  //�ýṹ��������ָ���жϺͱ����ļ�����·��
	int value_1;  //������ָ���ж� 
	int value_2;  //������ָ���ж�
	char content_1[260];  //���ڱ����ļ��� 
	char content_2[260];  //���ڱ���·�� 
};

typedef struct node    //�ϲ�֮����� 
{
	int label;         //��ǩ��1�������ļ���0�������ļ��� 
	char name[260];    //�ļ����У����� 
	char path[260];    //�ļ����У�·�� 
	char *tag_1[10];   //������ǩ 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //����޸�ʱ�� 
	struct BiTNode* P_left;      //ָ�����ӵ�ָ�� 
	struct BiTNode* P_right;     //ָ���Һ��ӵ�ָ�� 
	struct BiTNode* P_parents;   //ָ�򸸽���ָ��
}Tree,*Tree; 

/*     ÿ���˸��Ե��� 
typedef struct BiTNode  //����ʹ�õ��� 
{           
	int label;         //��ǩ��1�������ļ���0�������ļ��� 
	char name[260];    //�ļ����У����� 
	char path[260];    //�ļ����У�·�� 
	char *tag_1[10];   //������ǩ 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //����޸�ʱ�� 
	struct BiTNode* P_left;      //ָ�����ӵ�ָ�� 
	struct BiTNode* P_right;     //ָ���Һ��ӵ�ָ�� 
	struct BiTNode* P_parents;   //ָ�򸸽���ָ�� 
}BiTNode,*BiTree; 

struct node  //����ʹ�õ���
{           
 int label;         //��ǩ��1�������ļ���0�������ļ��� 
 char name[260];    //�ļ����У����� 
 char path[260];    //�ļ����У�·�� 
 char *tag_1[10];   //������ǩ 
 char *tag_2[10];
 char *tag_3[10];
 int time;          //����޸�ʱ�� 
 struct node* P_left;      //ָ�����ӵ�ָ�� 
 struct node* P_right;     //ָ���Һ��ӵ�ָ�� 
 struct node* P_parents;   //ָ�򸸽���ָ�� 
};

struct node  //�Ļ�ʹ�õ��� 
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

typedef struct node  //��Ҷʹ�õ��� 
{           
	int label;         //��ǩ��1�������ļ���0�������ļ��� 
	char name[260];    //�ļ����У����� 
	char path[260];    //�ļ����У�·�� 
	char *tag_1[10];   //������ǩ 
	char *tag_2[10];
	char *tag_3[10];
	int time;          //����޸�ʱ�� 
	struct node* P_left;      //ָ�����ӵ�ָ�� 
	struct node* P_right;     //ָ���Һ��ӵ�ָ�� 
	struct node* P_parents;   //ָ�򸸽���ָ�� 
}node;
*/

/*****************************************���ѵĺ���**********************************************/ 
void page_title(char *menu_item);  //��ʾ�������ĺ���
void return_confirm();  //�ȴ�����ȷ�ϵĺ���
void continue_confirm();  //�ȴ�����ȷ�ϵĺ���
void Read_Ordinary_users(LinkList *L);  //�����ı��ĵ���Ordinary_users.txt��
void Updata_Ordinary_users(LinkList *L);  //������ͨ�û����ݵ��ı��ĵ���Ordinary_users.txt��
void CreateListTail(LinkList *L,int n);  //β�巨_��ʼ��������
void Addusers(LinkList *L);  //ע�����û���β�����룩
void Cancelusers(LinkList *L);  //ע���û�
void Displayusers(LinkList *L);  //��ʾ�û�
int Login_system(LinkList *L);  //��¼ϵͳ
void get_nextval(char child_string[],int *nextval);  //���nextval����ĺ���
int KMP_Algorithm(char child_string[],char parents_string[]);  //KMP�㷨�������ַ����йص�ƥ�䣩
void display_ls(Tree T);  //��ʾָ��һ��ls����ʾ���бʼ��ļ��м��ʼ��ļ���
void display_ls_a(Tree T);  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ���
void display_left_child(Tree T);  //���ڱ���ĳ���������ļ��л����ļ� 
void display_ls_NotePath(Tree T,char content_1[]);  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ�����
void display_ls_NotePath_grep(Tree T,char content_1[],char content_2[]);  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ�����
/*************************************************************************************************/

/******************************************���ѵĺ���*********************************************/ 
int remove_mulu(const char *dir);
struct node *right_travel(struct node *T);		//�������������ҵ���һ��Ϊ�յ�ָ�벢����
char *get_path();							//��ȡ��ǰĿ¼
void free_all(struct node *T);									//�ͷſռ�
void del_NodeTree(struct node *Node_Tree);							//ɾ���ʼǵĽ��
struct node *createfather();							//�������ĸ����
struct node *createtree_label(struct node *father,const char *name);		//������Ŀ¼
struct node *create_right_label(struct node *father,const char *name);			//����ͬ��Ŀ¼
struct node *create_left_txt(struct node *father,const char *name);	//�����ӽ��Ϊ�ʼ��ļ�
struct node *Travsal_name(struct node *T,char *name);			//ǰ�����,�鿴����Ƿ�����ͬ����
void PreOrderTravsal(struct node *T,const char *path);		//ǰ�����,�鿴�Ƿ�����ͬ·��
struct node *OrderTravsal(struct node *T,const char *path);		//ǰ�����,�鿴����Ƿ�����ͬ·��
struct node *OrderTravsal_parent(struct node *T,const char *path);  //ǰ�����,�鿴���ĺ����Ƿ�����ͬ·��
void perorder(struct node *T);
void cd_pre(struct node *T);    			//�ƶ����ϼ�Ŀ¼
struct node *cd(struct node *T);			//�л�����Ŀ¼��ָ��Ŀ¼,������ָ���Ŀ¼��ָ��
struct node *md(struct node *T);  			//����Ŀ¼(�ڵ�ǰ����ָ�봦������Ŀ¼)
void rm_r(struct node *T); 							/*ɾ��Ŀ¼������ɾ��Ŀ¼��ͬʱ */
void rm(struct node *T);												//�Աʼ��ļ�����ɾ��
/*************************************************************************************************/

/********************************************�ĻԵĺ���*******************************************/
struct DATA* cmd_manage();  //�����
void select_menu();
void search_file_tag (Tnode *tree);  //���ڵ�
void search_add_file_tag (Tnode *tree);  //���ڵ�
void search_delect_file_tag (Tnode *tree);  //���ڵ�
void tag_s (Tnode *tree);  //��ǰĿ¼���ڵ�
void tag_sa (Tnode *tree);  //��ǰĿ¼���ڵ�
/**************************************************************************************************/ 

/*********************************************��Ҷ�ĺ���*******************************************/
void move_file(void);    //�ƶ��ļ�/�ļ���
int check(char name[],Tree p);  //���أ���pָ���Ŀ¼�²����Ƿ�������Ϊname���ļ�/Ŀ¼
void rename_file(void);  //�������ļ�/�ļ���
Tree search(char path[],Tree p);  //���ң��ҵ�����·���ļ�/�ļ������ڵĽ��,����ָ��pָ��ý��
void change_path(int len_oldpath,char* newpath,Tree p);  //���������·��
int Today(void);  //��ȡ��ǰʱ��
void Sort(void);  //�Ե�ǰĿ¼�µ��ļ����ļ��н���ʱ������
void create(void);  //����txt�ļ�
int check(char name[],Tree p);  //���أ���pָ���Ŀ¼�²����Ƿ�������Ϊname���ļ�/Ŀ¼
/**************************************************************************************************/

#endif
