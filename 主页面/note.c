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
#define MEMBER_SIZE 100  //ͼ����ȴ���100������Ա����ͨ�û���100��ʵ�������κ����ִ��棬ֻΪ���û����ʼ���ã�

/*************************************���ѵĲ���*************************************/ 
void page_title(char *menu_item)  //��ʾ�������ĺ��� 
{
	printf("\t\t\t��ӭʹ�ñʼǹ���ϵͳ\n"
	    "������������������������������������������������������������������������\n"
		"\n����%s����\n",menu_item); 
}

void return_confirm()  //�ȴ�����ȷ�ϵĺ��� 
{
	printf("�밴��������أ�\n");
	getch();
}

void continue_confirm()  //�ȴ�����ȷ�ϵĺ���
{
	printf("�밴�����������\n");
	getch();
}

void CreateListTail(LinkList *L,int n)  //β�巨_��ʼ��������
{
	system("cls");  //���� 
	page_title("��ʼ���û���");
	printf("��һ���ֱ��ʼ������Ա�����ͨ�û���\n"
		"����������������������������������������������\n");
	LinkList p,r;
	int i;
	*L=(LinkList)malloc(sizeof(Node));
	r=*L;  //rΪָ��β���Ľ�� 
	for(i=0;i<n;i++)
	{
		p=(Node *)malloc(sizeof(Node));  //����һ���ڴ�����p 
		p->account_number=0;  //�û�����������Ա������ͨ�û�����ʼ��ʱ�����˺ų�ʼ��Ϊ0 
		p->code=0;  //�û����ʼ��ʱ���������ʼ��Ϊ0
		r->next=p;  //�������ɵĽ��p���뵽r�ĺ��� 
		r=p;  //����ǰ�Ľ�㶨��Ϊ�µı�β�ն˽��
	}
	r->next=NULL;
	printf("��ʼ���ɹ���\n"
		"��������������������\n");
	continue_confirm();  //�밴���������
	system("cls");  //���� 
}

void Addusers(LinkList *L)  //ע�����û���β�����룩 
{
	system("cls");  //���� 
	page_title("ע�����û�");
	LinkList p,s; 
	p=*L;  //pΪָ��ͷ���Ľ�� 
	while(p->next)  //p->next==NULLʱ��ѭ����������pΪ���������һ�����
	{ 
		p=p->next;
	}
	s=(LinkList)malloc(sizeof(Node));  //����һ���ڴ�����s 
	printf("��������Ҫע����˺�(����Աע��ʱ������ǰ�����999��������)��\n");  //����Ա����999��Ҫ��Ϊ���𵽱�ʶ������ 
	scanf("%d",&s->account_number);
	printf("������������룺\n");
	scanf("%d",&s->code);
	p->next=s;
	s->next=NULL;
	printf("ע��ɹ���\n"
		"��������������������\n");
	return_confirm();  //�밴��������� 
}

void Cancelusers(LinkList *L)  //ע���û� 
{
	int sign=0;  //sign�𵽱�־������ 
	system("cls");  //���� 
	page_title("ע���û�");
	printf("��������Ҫע�����˺ţ�\n");
	int cancel_account_number;
	scanf("%d",&cancel_account_number);
	printf("������Ҫע�����˺ŵ����룺\n");
	int cancel_code;
	scanf("%d",&cancel_code);
	LinkList p,q;
	p=*L;  //pΪָ��ͷ���Ľ��
	while(p->next)  //p->next==NULLʱ��ѭ����������pΪ���������һ�����
	{
		if(cancel_account_number==p->next->account_number&&cancel_code==p->next->code)  //�û����д���Ҫע�����˺ţ���������ȷ 
		{
			q=p->next;
			p->next=q->next;
			free(q);  //�ͷŽ��q��������q������ 
			sign=1;
			printf("ע���ɹ���\n"
				"��������������������\n");
			return_confirm();  //�밴���������
			break;
		}
		if(cancel_account_number==p->next->account_number&&cancel_code!=p->next->code)  //�û����д���Ҫע�����˺ţ���������� 
		{
			sign=-1;
			printf("�������ע��ʧ�ܣ�\n"
				"��������������������������\n");
			return_confirm();  //�밴���������
			break;
		}
		p=p->next;
	}
	if(sign==0)
	{
		printf("û���ҵ�Ҫע�����˺ţ�\n"
			"����������������������������\n");
		return_confirm();  //�밴���������
	}
}

void Displayusers(LinkList *L)  //��ʾ�û� 
{
	int i=1;
	int length=0;  //�����ȣ�������ӳ��ǰ�û���������� 
	system("cls");  //���� 
	page_title("��ʾ�û�");
	LinkList p;
	p=*L;  //pΪָ��ͷ���Ľ��
	p=p->next;
	while(p)  //p==NULLʱ��ѭ������ 
	{
		if(p->account_number!=0&&p->code!=0)
		{
			printf("%d.�˺ţ�%d\n",i,p->account_number);
			i++;
			length++; 
		}
		p=p->next;
	}
	printf("�����û���Ŀǰ����Ϊ%d\n",length);
	printf("��������������������������\n");
	return_confirm();  //�밴���������
}

int Login_system(LinkList *L)  //��¼ϵͳ 
{
	system("cls");  //���� 
	page_title("��¼ϵͳ");
	int sign=0;  //sign�𵽱�־������ 
	printf("��������Ҫ��¼���˺ţ�\n");
	int Login_account_number;
	scanf("%d",&Login_account_number);
	printf("������������룺\n");
	int Login_code;
	scanf("%d",&Login_code);
	LinkList p;
	p=*L;  //pΪָ��ͷ���Ľ��
	while(p)
	{
		if(Login_account_number==p->account_number&&Login_code==p->code)  //�˺ź��������ȷ 
		{
			printf("��¼�ɹ���\n"
				"��������������������\n");
			sign=1;
			continue_confirm();  //�밴��������� 
			break;
		}
		p=p->next;
	}
	if(sign==0)
	{
		printf("�˺Ż����뷢�����󣬵�¼ʧ�ܣ�\n"
			"������������������������������������\n");
		return_confirm();  //�밴���������
	}
	return sign;
}

void get_nextval(char child_string[],int *nextval)  //���nextval����ĺ��� 
{
	int i,j;
	i=1;
	j=0;
	nextval[1]=0;
	while(i<child_string[0])  //child_string[0]��ʾ�ַ���child_string�ĳ��� 
	{
		if(j==0||child_string[i]==child_string[j])  //child_string[i]��ʾ��׺�ĵ����ַ���child_string[j]��ʾǰ׺�ĵ����ַ� 
		{
			++i;
			++j;
			if(child_string[i]!=child_string[j])  //ǰ׺�ĵ����ַ���������Ӧ�ĺ�׺�ַ���ͬ 
			{
				nextval[i]=j;  
			}
			else  //ǰ׺�ĵ����ַ�������Ӧ�ĺ�׺�ַ���ͬ
			{
				nextval[i]=nextval[j];  //��ǰ׺�ַ���ͬ����ǰ׺��nextvalֵ����nextval��iλ��ʱ��ֵ��nextvalʡȥ�ظ�������һ���� 
			}
		}
		else
		{
			j=nextval[j];
		}
	}
}

int KMP_Algorithm(char child_string[],char parents_string[])  //KMP�㷨�������ַ����йص�ƥ�䣩 
{
	int i=1;  //i��������parents_string��ǰλ�õ��±�ֵ��λ�ô�1��ʼ 
	int j=1;  //j�����Ӵ�child_string��ǰλ�õ��±�ֵ��λ�ô�1��ʼ 
	int nextval[255];  //nextval���� 
	get_nextval(child_string,nextval);  //���nextval���� 
	while(i<=parents_string[0]&&j<=child_string[0])  //iС�������ĳ��ȣ�jС���Ӵ��ĳ��ȣ�ѭ������ 
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
		return i-child_string[0];  //����Գɹ��������д������Ӵ���ͬ��Ƭ�Σ��������Ӵ���������һ�γ��ֵ�λ�� 
	}
	else
	{
		return 0;  //�����ʧ�ܣ������в��������Ӵ���ͬ��Ƭ�Σ�������0�Դ���ʧ�� 
	}
}

void display_ls(BiTree T)  //��ʾָ��һ��ls����ʾ���бʼ��ļ��м��ʼ��ļ��� 
{
	system("cls");  //����
	page_title("��ʾָ��һ��ls");
	if(T==NULL)  //ǰ���������ʾÿһ���������֣�ͬʱ���ֽ�������ļ��л����ļ� 
	{
		return;
	}
	if(T->label==0)
	{
		printf("����һ���ʼ��ļ��У�����Ϊ��%s\n",T->name);
	}
	if(T->label==1)
	{
		printf("����һ���ʼ��ļ�������Ϊ��%s\n",T->name);
	}
	display_ls(T->P_right);
	display_ls(T->P_left);
}

void display_ls_a(BiTree T)  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ��� 
{
	system("cls");  //����
	page_title("��ʾָ�����ls -a");
	printf("�ù�����ʱδ������ϣ��ݲ�����ʹ��\n"); 
}

void display_left_child(BiTree T)  //���ڱ���ĳ���������ļ��л����ļ������������������� 
{
	if(T==NULL)
	{
		return;
	}
	if(T->label==0)
	{
		printf("����һ���ʼ��ļ��У�����Ϊ��%s\n",T->name);
	}
	if(T->label==1)
	{
		printf("����һ���ʼ��ļ�������Ϊ��%s\n",T->name);
	}
	display_left_child(T->P_left);  //��ݹ飬������������ 
}

void display_ls_NotePath(BiTree T,char change_1[])  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ����� 
{
	system("cls");  //���� 
	page_title("��ʾָ������ls <�ʼ��ļ���·��>");
	if(strcmp(change_1,T->path))  //Ŀ��·��ƥ��ɹ� 
	{
		if(T==NULL)
		{
			return;
		}
		if(T->label==0)
		{
			printf("����һ���ʼ��ļ��У�����Ϊ��%s\n",T->name);
		}
		if(T->label==1)
		{
			printf("����һ���ʼ��ļ�������Ϊ��%s\n",T->name);
		}
		display_left_child(T->P_left);  //������ӡ�ý��������� 
	}
	display_ls_NotePath(T->P_left,change_1);  //Ŀ��·����ƥ��ʧ�ܣ��ȱ������������������������������ 
	display_ls_NotePath(T->P_right,change_1);
}

void display_ls_NotePath_grep(BiTree T,char change_1[],char change_2[])  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ����� 
{
	system("cls");  //����
	page_title("��ʾָ���ģ�ls <�ʼ��ļ���·��> grep ���������ݡ�");
	int i,j;
	char child_string[20];
	int length_child_string;
	length_child_string=strlen(child_string);
	for(j=100;j>1;j--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵��� 
	{
		child_string[j]=change_1[j-1];
	}
	child_string[0]=length_child_string;
	char parents_string[20];
	int length_parents_string;
	length_parents_string=strlen(parents_string);
	for(i=1;i<20;i++)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
	{
		parents_string[i]=T->path[i-1];
	}
	parents_string[0]=length_parents_string;
	
	if(KMP_Algorithm(child_string,parents_string)!=0)  //��һ��child_string��parents_string����Ŀ��·���ĵ��� 
	{
		for(j=100;j>1;j--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
		{
			child_string[j]=change_2[j-1];
		}
		length_child_string=strlen(child_string);
		child_string[0]=length_child_string;
		for(i=1;i<20;i++)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
		{
			parents_string[i]=T->name[i-1];
		}
		length_parents_string=strlen(parents_string);
		parents_string[0]=length_parents_string;
		if((KMP_Algorithm(child_string,parents_string))!=0)  //�ڶ���child_string��parents_string�����������ݵĵ���
		{
			if(T==NULL)
			{
				return;
			}
			if(T->label==0)
			{
				printf("����һ���ʼ��ļ��У�����Ϊ��%s\n",T->name);
			}
			if(T->label==1)
			{
				printf("����һ���ʼ��ļ�������Ϊ��%s\n",T->name);
			}
			display_ls_NotePath_grep(T->P_left,change_1,change_2);  //ƥ��ɹ�����ݹ飬�������������� 
		}
	}
	display_ls_NotePath_grep(T->P_left,change_1,change_2);  //��ƥ��ʧ�ܣ����ȱ������������������������������ 
	display_ls_NotePath_grep(T->P_right,change_1,change_2);
}

/*********************************************************************************/



/*********************************���ѵĲ���**************************************/ 
/******************************�����ڲ��ĺ���*************************************/ 
int sign = 0;  //ȫ�ֱ��� sign 
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
	system("cls");  //����
	page_title("�л�ָ��һ��cd"); 
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
	system("cls");  //����
	page_title("�л�ָ�����cd <�ʼ��ļ���·��>");					
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
	system("cls");                          //����
	page_title("����ָ��һ��md"); 
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
	system("cls");  //����
	page_title("ɾ��ָ�����rm -r <Ҫɾ���ıʼ��ļ�����>"); 
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
	system("cls");                                                  //����
	page_title("ɾ��ָ��һ��rm <Ҫɾ���ıʼ��ļ���>"); 
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



/*********************************�ĻԵĲ���************************************/


int Command_Processing(char change_1[],char change_2[])  //����� 
{
	/*      char str[100];
	        char buf[100];
	        char sda[100];
	        sscanf("tag -add <wenjian> ��neirong��","%[^<]",str);
	        sscanf("tag -add <wenjian> ��neirong��","%*[^<]<%[^>]",buf);
	        sscanf("tag -add <wenjian> ��neirong��","%*[^��]��%[^��]",sda);
	        printf("%s %s %s",str,buf,sda);
	        return 0;
	        */
	//system("mode con cp select=65001");
	system("cls");
	page_title("ָ������");
	char input[100];  //�����ֵ��������� tag -add <title> "neirong"
	char first[100];
	char second[100];
	char third[100];
	char forth[100];
	//char change_1[100];  //��¼�ļ���
	//char change_2[100];  //��¼��ǩ����
	printf("���������ָ�\n");
	gets(input);
	memset (first,0,sizeof(first));
	sscanf (input,"%[^ ]",first);//��һ���ո�ǰ
	sscanf (input,"%*[^ ] %[^ ]",second);//�ڶ����ո�ǰ
	sscanf (input,"%*[^ ] %*[^ ] %[^ ]",third);//�������ո�ǰ
	sscanf (input,"%*[^ ] %*[^ ] %*[^ ] %[^ ]",forth);
	memset (change_1,0,sizeof(change_1));  //������棨û��֮ǰ�д���
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
		sscanf(second,"<%[^>]",change_1);  //ȥ��<>
		//printf("%s", change_1);  //���
		return 3;
	}
	else if (strcmp("ls",first)==0&& second[0] == '<' && strcmp("grep",third)==0 && forth[0] == '"' )
	{
		sscanf(second,"<%[^>]",change_1);  //ȥ��<>
		//printf("%s\n",change_1 );  //���
		sscanf(forth,"\"%[^\"]", change_2);  //ȥ��""
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
		sscanf(second,"<%[^>]", change_1);  //ȥ��<>
		//printf("%s",change_1);  //���
		return 6;
	}
	else if(strcmp("mv",first)==0&&second[0]=='<'&&third[0]=='<')
	{
		sscanf(second,"<%[^>]",change_1);  //ȥ��<>
		//printf("%s",change_1 );  //���
		sscanf(third,"<%[^>]",change_2);  //ȥ��<>
		//printf("%s",change_2);  //���
		return 7;
	}
	else if(strcmp("mv",first)==0&&strcmp("-r",second)==0&&third[0]=='<'&&forth[0]=='<')
	{
		sscanf(third,"<%[^>]",change_1);  //ȥ��<>
		//printf("%s",change_1 );  //���
		sscanf(forth,"<%[^>]",change_2 );  //ȥ��<>
		//printf("%s",change_2);  //���
		return 8;
	}
	else if(strcmp("rm",first)==0&&second[0]=='<')
	{
		sscanf(second,"<%[^>]",change_1);  //ȥ��<>
		//printf("%s",change_1 );  //���
		return 9;
	}
	else if(strcmp("rm",first)==0&&strcmp("-r",second)==0&&third[0]=='<')
	{
		sscanf(third,"<%[^>]",change_1 );  //ȥ��<>
		//printf("%s",change_1 );//���
		return 10;
	}


	if(strcmp("tag",first)==0&& second[0] == '-' && third[0] == '<' && forth[0] == '"' )
	{

		sscanf(third, "<%[^>]", change_1 );  //ȥ��<>
		//printf("%s",change_1 );  //���
		sscanf(forth,"\"%[^\"]",change_2 );  //ȥ��""
		//printf("%s",change_2 );  //���
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
	sscanf(shuru,"%*[^��]��%[^��]",sda);

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




void search_file_tag (Tnode *tree) //���ڵ�
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
		}//��¼����ߵ����нڵ�
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

void search_add_file_tag (Tnode *tree) //���ڵ�
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
		}//��¼����ߵ����нڵ�
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

void search_delect_file_tag (Tnode *tree) //���ڵ�
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
		}//��¼����ߵ����нڵ�
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
					printf ( "ɾ���ɹ�\n" );
					break;
					if ( strcmp ( tag_name, pmove->tag_2 ) == 0 )
						memset ( pmove->tag_2, 0, sizeof ( pmove->tag_2 ) );
					printf ( "ɾ���ɹ�\n" );
					break;
					if ( strcmp ( tag_name, pmove->tag_3 ) == 0 )
						memset ( pmove->tag_3, 0, sizeof ( pmove->tag_3 ) );
					printf ( "ɾ���ɹ�\n" );
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

void tag_s (Tnode *tree) //��ǰĿ¼���ڵ�
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
		}//��¼����ߵ����нڵ�
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

void tag_sa (Tnode *tree) //��ǰĿ¼���ڵ�
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
		}//��¼����ߵ����нڵ�
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


/***********************************��Ҷ�Ĳ���***************************************/


void move_file(){    //�ƶ��ļ�/�ļ��� 
	system("cls");  //����
	page_title("�ƶ�ָ��һ��mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>"); 
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
		else {               //���ƶ������ļ� ,�����ļ���֮��ԭ���ļ�֮ǰ 
			p=p2->P_left;
			while(p->P_right!=NULL&&p->label==0) p=p->P_right;
			p1->P_right=p->P_right;
			if(p->P_right) p->P_right->P_parents=p1;
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
	system("cls");  //����
	page_title("������ָ��һ��mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>");
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
	int i;
	for( i=0;i<(len_oldpath-len_oldname);i++){
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
	    int i=2,j;
		int len=strlen(path);
	    while(i<len&&path[i]=='/'){   //�м����ͻ��˼���Ŀ¼ 
	    	p=p->P_parents;
			i=i+3;
		}
		char* path_post=(char*)malloc(sizeof(char)*(len-i+2));
		for(j=0;j<len-i+2;j++){
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
		int i;
		for(i=0;i<len;i++){
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

void Sort(void){  //�Ե�ǰĿ¼�µ��ļ����ļ��н���ʱ������
	system("cls");  //����
	page_title("����ָ��һ��sort������ʱ������"); 
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
			if(s->label==0){    //�ļ��� 
				if(s->time > n){
					t=s;
					n=s->time;
				}
			}
			else {    //�ļ� 
				if(s->time > m){
					tf=s;
					m=s->time;
				}
			}
		}
		
		q=t->P_parents;    //������ 
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

void create(char* name){  //����txt�ļ�
	system("cls");  //����
	page_title("����ָ�����"); 
	if(check(name,POINTER)){  //�ȼ���ļ��Ƿ����� 
		printf("�ļ�������\n");
		return;
	}
	FILE* fp=fopen(name,"r");  //�����ļ� 
	if(fp==0){
		printf("����ʧ�ܣ�\n");
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
	//���ӽ�� 
	if(POINTER->P_left==NULL){   //��ǰĿ¼Ϊ���ļ���ʱ��ֱ�����Ӽ��� 
		pNew->P_parents=POINTER;
		POINTER->P_left=pNew;
		pNew->P_right=NULL;
	}
	else{
		node* p=POINTER->P_left;
        while(p->P_right!=NULL&&p->label==0){ //���������ļ���֮��ԭ���ļ�֮ǰ 
        	p=p->P_right;
		}
		pNew->P_parents=p;
		pNew->P_right=p->P_right;
		if(p->P_right != NULL) p->P_right->P_parents = pNew;  
		p->P_right=pNew;
		
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


/************************************************************************************/
