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


Tree HEAD;        //����ͷ�ڵ�
Tree POINTER;     //ȫ�ֱ�����ʵʱָ���û��򿪵ĵ�ǰĿ¼ 
int top = -1;			//��ջ�ı��� 
FILE *f_write = NULL;	//д��txt�ļ�ʱ��ָ�� 
FILE *f_read = NULL;	//��txt�ļ�ʱ��ָ��

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

void Read_Ordinary_users(LinkList *L)  //�����ı��ĵ���Ordinary_users.txt��
{
	LinkList p,r;
	FILE *file_p_read;
	file_p_read=fopen("FILE_��ͨ�û�_�˺�_����\\Ordinary_users.txt","r");
	r=*L;  //rΪָ��β���Ľ��
	int i;
	for(i=0;i<MEMBER_SIZE;i++)
	{
		p=(Node *)malloc(sizeof(Node));  //����һ���ڴ�����p
		if(fscanf(file_p_read,"%d",&p->account_number)!=1)
		{
			break;
		}
		fscanf(file_p_read,"%d",&p->code);
		r->next=p;  //�������ɵĽ��p���뵽r�ĺ���
		r=p;  //����ǰ�Ľ�㶨��Ϊ�µı�β�ն˽��
	}
	r->next=NULL;
	fclose(file_p_read);
}

void Updata_Ordinary_users(LinkList *L)  //������ͨ�û����ݵ��ı��ĵ���Ordinary_users.txt��
{
	system("cls");  //����
	page_title("������ͨ�û�����");
	LinkList p,q;
	FILE *file_p_write;
	file_p_write=fopen("FILE_��ͨ�û�_�˺�_����\\Ordinary_users.txt","w");
	p=*L;  //pΪָ��ͷ���Ľ��
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
		free(q);  //�ͷŽ��q��������q������
	}
	fclose(file_p_write);
	printf("������ͨ�û����ݳɹ���\n"
		"������������������������������������������������\n" 
		"���º��������ó��򣬱�֤�˺�������³ɹ���\n"
		"������������������������������������������������\n");
	return_confirm();  //�밴���������
}

void CreateListTail(LinkList *L,int n)  //β�巨_��ʼ��������
{
	system("cls");  //����
	page_title("��ʼ���û���");
	printf("��һ��Ϊ��ʼ����ͨ�û���\n"
		"������������������������������������\n");
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
	int i=0;
	int sign;  //sign�𵽱�־������
	int a[MEMBER_SIZE];  //�ݴ��û������ڼ����˺��Ƿ��ظ�ע��
	LinkList p,s;
	p=*L;  //pΪָ��ͷ���Ľ��
	while(p->next)  //p->next==NULLʱ��ѭ����������pΪ���������һ�����
	{
		p=p->next;
		a[i]=p->account_number;
		i++;
	}
	s=(LinkList)malloc(sizeof(Node));  //����һ���ڴ�����s
	printf("��������Ҫע����˺ţ�\n");
	scanf("%d",&s->account_number);
	printf("������������룺\n");
	scanf("%d",&s->code);
	for(i=0;i<MEMBER_SIZE;i++)
	{
		if(s->account_number==a[i])
		{
			printf("���˺��Ѿ��Ǽǹ��ˣ�\n"
				"��������������������������������\n");
			sign=-1;
			return_confirm();  //�밴���������
		}
	}
	if(sign!=-1)
	{
		p->next=s;
		s->next=NULL;
		printf("ע��ɹ���\n"
			"��������������������\n");
		return_confirm();  //�밴���������
	}
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

void display_ls(Tree T)  //��ʾָ��һ��ls����ʾ���бʼ��ļ��м��ʼ��ļ���
{
	//page_title("��ʾָ��һ��ls");
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

void display_ls_a(Tree T)  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ���
{
	//system("cls");  //����
	//page_title("��ʾָ�����ls -a");
	printf("�ù�����ʱδ������ϣ��ݲ�����ʹ��\n");
}

void display_left_child(Tree T)  //���ڱ���ĳ���������ļ��л����ļ�������������������
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

void display_ls_NotePath(Tree T,char content_1[])  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ�����
{
	//page_title("��ʾָ������ls <�ʼ��ļ���·��>");
	if(strcmp(content_1,T->path)==0)  //Ŀ��·��ƥ��ɹ�
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
	display_ls_NotePath(T->P_left,content_1);  //Ŀ��·����ƥ��ʧ�ܣ��ȱ������������������������������
	display_ls_NotePath(T->P_right,content_1);
}

void display_ls_NotePath_grep(Tree T,char content_1[],char content_2[])  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ�����
{
	//page_title("��ʾָ���ģ�ls <�ʼ��ļ���·��> grep ���������ݡ�");
	int i,j;
	char child_string[260];
	//printf("1");  ���� 
	int length_child_string;
	length_child_string=strlen(content_1);
	for(j=260;j>1;j--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
	{
		child_string[j]=content_1[j-1];
	}
	child_string[0]=length_child_string;
	char parents_string[260];
	int length_parents_string;
	length_parents_string=strlen(T->path);
	for(i=260;i>1;i--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
	{
		parents_string[i]=T->path[i-1];
	}
	parents_string[0]=length_parents_string;

	if(KMP_Algorithm(child_string,parents_string)!=0)  //��һ��child_string��parents_string����Ŀ��·���ĵ���
	{
		for(j=260;j>1;j--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
		{
			child_string[j]=content_2[j-1];
		}
		length_child_string=strlen(content_2);
		child_string[0]=length_child_string;
		for(i=260;i>1;i--)  //����KMP�㷨�У��ַ������һ��λ�ô洢���ַ����ĳ��ȣ�������˵���
		{
			parents_string[i]=T->name[i-1];
		}
		length_parents_string=strlen(T->name);
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
			display_ls_NotePath_grep(T->P_left,content_1,content_2);  //ƥ��ɹ�����ݹ飬��������������
		}
	}
	display_ls_NotePath_grep(T->P_left,content_1,content_2);  //��ƥ��ʧ�ܣ����ȱ������������������������������
	display_ls_NotePath_grep(T->P_right,content_1,content_2);
}

/*********************************************************************************/



/*********************************���ѵĲ���**************************************/
/******************************�����ڲ��ĺ���*************************************/

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
	sprintf(father_Tree->tag_1,"---");
	sprintf(father_Tree->tag_2,"---");
	sprintf(father_Tree->tag_3,"---");
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
	sprintf(Node_Tree->tag_1,"---");
	sprintf(Node_Tree->tag_2,"---");
	sprintf(Node_Tree->tag_3,"---");
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
	POINTER = Node_Tree;
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
		return;
	}
	else
	{
		str = strstr(pat,path);						//����û�����������·��
		if( str != NULL )							//������Ǿ���·������·������ָ�벻Ϊ��
		{
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
		system("pause");
	}
	else
	{
		if( chdir(str->P_parents->path) == 0 )	//�л���������·��
		{
			printf("�л����ϼ�Ŀ¼��\n");
			p = get_path();
			printf("��ǰ����Ŀ¼Ϊ��%s\n",p);
			system("pause");
		}
		else
		{
			printf("�л�ʧ�ܣ�����δ֪����\n");
			system("pause");
		}
	}
}

struct node *cd(struct node *T)			//�л�����Ŀ¼��ָ��Ŀ¼,������ָ���Ŀ¼��ָ��
{
	char *path= NULL;
	char *str = NULL;
	char *i = get_path(); 
	path = (char *)malloc( sizeof(char[260]) );
	printf("����������������Ҫ�л������ļ��еľ���·��!��������\n");
	printf("��������ע��·���е� '\\' Ҫ�ɶԳ��֡�������\n");
	printf("��������Ҳ�����������룺 Ŀ¼\\Ŀ¼\\�ļ�('��ʼ'��������)��������\n");
	printf("����������Ҫ���ؿ�ʼĿ¼������ ��ʼ ���ɡ�������\n");
	printf("�����룺");
	scanf("%s",path);
	if( strcmp(path,"��ʼ")==0 || strcmp(path,"��ʼ\\")==0 || strcmp(path,"\\��ʼ")==0 || strcmp(path,"\\��ʼ\\")==0)
	{										//����û���Ҫ�ص�����ʼ���˵�
		chdir(T->path); 					//ֱ���л������ڵ�
		printf("�л��ɹ�!\n");
		str = get_path();
		printf("��ǰ����Ŀ¼Ϊ��%s\n",str);
		system("pause");
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
			POINTER = p;
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
		system("pause");
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
			chdir(T->path);
			if(remove_mulu(str->path) == 3)
			{
				printf("ɾ����.....\n");
				//ɾ��strָ��Ľ�㣬Ȼ����ҽڵ��ϵĽ���
				//���str�Ǳ��˵����ӣ���Ҫ��str->P_right���str��λ��
				free_all(str->P_left);
				str->P_left = NULL;  //�����str������
				if(str->P_parents->P_left == str)		//���û���˵���ָ��ָ��str
				{
					str->P_parents->P_left = str->P_right;	//�Ͱ�str�ұߵ�һ�����str����������
					if(str->P_right != NULL)
					{
						str->P_right = str->P_parents;		//���ұߵ�һ���ĸ�ָ��ָ���µĸ����
					}
				}
				else
				{
					str->P_parents->P_right = str->P_right;	//������˵���ָ��ָ��str
					if(str->P_right != NULL)
					{
						str->P_parents->P_right->P_parents = str->P_parents;
					}
				}
				str->P_right = NULL;
				str = NULL;
				free(str);
				printf("ɾ��Ŀ¼ %s �ɹ�!\n",mulu);
				system("pause");
			}
			else
			{
				printf("ɾ��Ŀ¼ʧ�ܣ�\n");
				system("pause");
			}
		}
		else
		{
			printf("δ�ҵ������Ƶ��ļ���\n");
			system("pause");
		}
	}
	else
	{
		printf("δ�ҵ������Ƶ��ļ���\n");
		system("pause");
	}
	free(mulu);
}

void rm(struct node *T)												//�Աʼ��ļ�����ɾ��
{
	char *name = NULL;
	name = (char *)malloc( sizeof(T->name) );
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
				system("pause");
			}
			else
			{
				printf("ɾ��ʧ��!\n");
				system("pause");
			}
		}
		else
		{
			printf("�޴����Ƶ��ļ���ɾ��ʧ�ܣ�\n");
			system("pause");
		}
	}
	else
	{
		printf("�޴����Ƶ��ļ���ɾ��ʧ�ܣ�\n");
		system("pause");
	}
}
/*******************************************************************************/

/*********************�ļ����������**********************/

void full_filename(struct node *Node_Tree)  //��ȫ·��������װ
{					//����ָ��������ָ��
	char *p = get_path();					//��ȡC�ļ��Ĺ���·�����Ȼ�������ȫ���·��
	if(strcmp(Node_Tree->path,"(null)") == 0)
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

void write_filebypre(const char *filename,struct node *T)	//ǰ��д���ļ������ӽڵ�Ϊ�գ�����Ϊ #
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

void read_filebypre(const char *filename,struct node **T)  //���ļ�������
{
	struct node temdata;
    if(f_read == NULL)
	{
		f_read = fopen(filename,"w+");
		f_write = fopen("preorder_tree.txt","w");			//�������浽TXT�ļ��� 
		write_filebypre("preorder_tree.txt",(*T));
		fclose(f_write);
		return ;
	}
    fscanf(f_read,"%2d%50s%120s%20s%20s%20s%10d\n",&temdata.label,temdata.name,temdata.path,temdata.tag_1,temdata.tag_2,temdata.tag_3,&temdata.time);
    //������棬fscanfҲֻ�Ƕ����ַ���

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



/*********************************�ĻԵĲ���************************************/


struct DATA* cmd_manage()
{
	char shuru[540];//�����ֵ��������� tag -add <title> "neirong"
	char first[5];
	char second[262];
	char third[262];
	char forth[262];
	char change1[260];//��¼�ļ���
	char change2[260];//��¼��ǩ����
	printf("�������Ӧ������ָ�\n"
		"����������������������������\n");
	gets ( shuru );
	memset ( first, 0, sizeof ( first ) );
	sscanf ( shuru, "%[^ ]", first );//��һ���ո�ǰ
	sscanf ( shuru, "%*[^ ] %[^ ]", second );//�ڶ����ո�ǰ
	sscanf ( shuru, "%*[^ ] %*[^ ] %[^ ]", third );//�������ո�ǰ
	sscanf ( shuru, "%*[^ ] %*[^ ] %*[^ ] %[^ ]", forth );
	memset ( change1, 0, sizeof ( change1 ) );//������棨û��֮ǰ�д���
	memset ( change2, 0, sizeof ( change2 ) );
	struct DATA *data=(struct DATA*)malloc(sizeof(struct DATA));


    if ( strcmp ( "back", first ) == 0 )
	{
		data->value_1=100;
		//data->value_2=0;
	}

	else if ( strcmp ( "ls", first ) == 0 && strlen ( shuru ) == 2 )
	{
		data->value_1=1;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "ls", first ) == 0 && strcmp ( "-a", second ) == 0 )
	{
		data->value_1=2;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' && strcmp ( "grep", third ) == 0 && forth[0] == '"' )
	{
		sscanf ( second, "<%[^>]", change1 );//ȥ��<>
		sscanf ( forth, "\"%[^\"]", change2 );//ȥ��""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=4;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=3;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "cd", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=6;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "cd", first ) == 0 )
	{
		//printf ( "%s", first );
		data->value_1=5;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "mv", first ) == 0 && second[0] == '<' && third[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//ȥ��<>
		sscanf ( third, "<%[^>]", change2 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=7;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "mv", first ) == 0 && strcmp ( "-a", second ) == 0 && third[0] == '<' && forth[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sscanf ( forth, "<%[^>]", change2 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=8;  //����ֵ��������ָ���жϣ�
	}
	/*else if ( strcmp ( "mv", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' && forth[0] == '<' )
	{
		//data->value_1=1;
		//data->value_2=1;
		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sscanf ( forth, "<%[^>]", change2 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=9;  //����ֵ��������ָ���жϣ�
	}*/
	else if ( strcmp ( "rm", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=10;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "rm", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=11;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "tag", first ) == 0 && second[0] == '<' )
	{

		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=12;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-add",second)==0 && third[0] == '<' && forth[0] == '"' )
	{
		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sscanf ( forth, "\"%[^\"]", change2 );//ȥ��""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=13;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-del",second)==0 && third[0] == '<' && forth[0] == '"' )
	{

		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sscanf ( forth, "\"%[^\"]", change2 );//ȥ��""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
		data->value_1=14;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "tag", first ) == 0 && strcmp("-s",second) ==0&& third[0] == '"' )
	{
		//data->value_1=0;
		//data->value_2=1;
		sscanf ( third, "\"%[^\"]", change1 );
		//printf ( "%s", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=15;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-sa",second) ==0&& third[0] == '"' )
	{
		//data->value_1=1;
		//data->value_2=0;
		sscanf ( third, "\"%[^\"]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=16;  //����ֵ��������ָ���жϣ�
	}
	else if ( strcmp ( "md", first ) == 0 && second[0] == '<' )
	{
		//data->value_1=2;
		//data->value_2=1;
		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
		data->value_1=17;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "md", first ) == 0 && strcmp ( "-ml", second ) == 0 && third[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//ȥ��<>
		sprintf(data->content_1,"%s",change1);
		data->value_1=18;  //����ֵ��������ָ���жϣ�
	}

	else if ( strcmp ( "sort", first ) == 0  )  //&& second[0] == '<'�����������Ҫ�Ĳ��֣�
	{
		//sscanf ( second, "<%[^>]", change1 );
		//sprintf(data->content_1,"%s",change1);
		data->value_1=19;  //����ֵ��������ָ���жϣ�
	}
	else {
		//printf("wrong cmd\n");
	}
	return data;


	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^��]��%[^��]",sda);

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


void search_file_tag ( struct node*tree, char *search_name ) //���ڵ�

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
		}//��¼����ߵ����нڵ�
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strcmp(pmove->tag_1,"---")!=0 )
					printf ( "��ǩ1��%s\n", pmove->tag_1 );
				if ( strcmp(pmove->tag_2,"---")!=0 )
					printf ( "��ǩ2��%s\n", pmove->tag_2 );
				if ( strcmp(pmove->tag_3,"---")!=0 )
					printf ( "��ǩ3��%s\n", pmove->tag_3 );
				break;
			}
			else
			{
				pmove = pmove->P_right;
			}





		}

	}
}
void search_add_file_tag ( struct node*tree, char*search_name, char* tag_name ) //���ڵ�
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
		}//��¼����ߵ����нڵ�
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strcmp(pmove->tag_1,"---")==0)
				{
					memset(pmove->tag_1,0,sizeof(pmove->tag_1));
					sprintf ( pmove->tag_1, "%s", tag_name );
					printf ( "��ӵ�tag-1\n" );
					break;
				}
				else
				{
					if ( strcmp(pmove->tag_2,"---")==0)
					{
						memset(pmove->tag_2,0,sizeof(pmove->tag_2));
						sprintf ( pmove->tag_2, "%s", tag_name );
						printf ( "��ӵ�tag-2\n" );
						break;
					}
					else
					{
						if (strcmp(pmove->tag_3,"---")==0)
						{
							memset(pmove->tag_3,0,sizeof(pmove->tag_3));
							sprintf ( pmove->tag_3, "%s", tag_name );
							printf ( "��ӵ�tag-3\n" );
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
void search_delect_file_tag ( struct node*tree, char*search_name, char*tag_name ) //���ڵ�
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
		}//��¼����ߵ����нڵ�
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
						printf ( "ɾ��tag_1�ɹ�\n" );
						break;
					}
					else if ( strcmp ( tag_name, pmove->tag_2 ) == 0 )
					{
						memset ( pmove->tag_2, 0, sizeof ( pmove->tag_2 ) );
						printf ( "ɾ��tag_2�ɹ�\n" );
						break;
					}
					else if ( strcmp ( tag_name, pmove->tag_3 ) == 0 )
					{
						memset ( pmove->tag_3, 0, sizeof ( pmove->tag_3 ) );
						printf ( "ɾ��tag_3�ɹ�\n" );
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
void tag_s ( struct node*tree, char*tag_name ) //��ǰĿ¼���ڵ�
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
		}//��¼����ߵ����нڵ�
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
void tag_sa ( struct node*tree, char*tag_name ) //��ǰĿ¼���ڵ�
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
		}//��¼����ߵ����нڵ�
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 0 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "�ļ�����%s\t", pmove->name );
					printf ( "·����%s\n", pmove->path );
				}
					pmove = pmove->P_right;
			}

			else
				pmove = pmove->P_right;
		}

	}
}

/************************************************************************************/


/***********************************��Ҷ�Ĳ���***************************************/


void move_file(void){    //�ƶ��ļ�/�ļ���
	//system("cls");  //����
	//page_title("�ƶ�ָ��һ��mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>");
	char oldpath[260],newpath[260];  //oldname��·����newname��·��
	printf("��������Ҫ�ƶ����ļ����ļ��У�");
	scanf("%s",oldpath);
	printf("�������ļ����ļ��е�Ŀ��λ��");
	scanf("%s",newpath);
	Tree p1;    //��¼���ƶ��ļ�/�ļ��еĽ��λ��
	Tree p2;    //��¼Ŀ��λ�õ���һ��
	int i,len_newpath;
	len_newpath = strlen(newpath);
	for( i=len_newpath-1;i>=0;i--){           //�ҵ�Ŀ��λ�õ���һ��Ŀ¼
		if(newpath[i]==92) break ;
	}
	int j=0;
	char newpath_post[260];
	while((j+i+1)<len_newpath){
		newpath_post[j]=newpath[j+i+1];  //newpath��׺
		j++;
	}
	newpath_post[j]='\0';
	if(!check(newpath_post,POINTER)) {
		printf("�ƶ�ʧ�ܣ�\n��·������������ļ��е�����\n");
		return ;
	}
	if(rename(oldpath,newpath)!=0) {
		perror("rename");
		return ;
	}

	char newpath_pre[260];    //newpath����һ��·��
	for(j=0;j<i;j++){
		newpath_pre[j]=newpath[j];    //���������·����Ҳ�����Ǿ���·��
	}
	p1=search(oldpath,p1);      //�������ҵ���·���µ��ļ�/�ļ��У�����p1��¼��λ��
	p2=search(newpath_pre,p2);  //p2����·������һ��
    if(p2==NULL)
    return ;
	strcpy(newpath,p2->path);
	strcat(newpath,"\\");
	strcat(newpath,newpath_post); //�ƶ���ľ���·��
	printf("�ƶ���ľ���·����%s\n",newpath);
	p1->time=Today();    //���� ����޸�ʱ��
	Tree p=p1->P_parents;        //������
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
			change_path(len_oldpath,newpath,p1->P_left);  //��p1��������·��
		}
		else {               //���ƶ������ļ� ,�����ļ���֮��ԭ���ļ�֮ǰ
			p=p2->P_left;
			while(p->P_right!=NULL&&p->P_right->label==0) p=p->P_right;
			p1->P_right=p->P_right;
			if(p->P_right) p->P_right->P_parents=p1;
			p->P_right=p1;
			p1->P_parents=p;
		}
	}
	printf("�ƶ��ɹ���\n��ǰ�����ļ���Ϊ��%s\n",POINTER->path);
	return ; 
  }

int check(char name[],Tree p){  //���أ���pָ���Ŀ¼�²����Ƿ�������Ϊname���ļ�/Ŀ¼
	if(p->P_left==NULL)
		return 0;     //��ǰĿ¼�����ļ����ļ���
	p=p->P_left;
	while(p!=NULL){
		if(!strcmp(p->name,name))  return 1;  //�ҵ������ļ�/�ļ���
		else p=p->P_right;
	}
	return 0;    //δ�ҵ������ļ�/�ļ���
}


void rename_file(void){  //�������ļ�/�ļ���
	//system("cls");  //����
	//page_title("������ָ��һ��mv -a <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>");

	char newname[260];
	char oldname[260];
	printf("������Ҫ���������ļ�����");
	scanf("%s",oldname);
	Tree p=POINTER->P_left;
	while(p!=NULL) {
		if(!strcmp(p->name,oldname)) break;
		else  p=p->P_right;
	}
	if(p==NULL) {
		printf("���ļ�������!\n");
		return ;
	}
	printf("������������: ");
	scanf("%s",newname);
	while(strlen(newname)>260){
		printf("���ֹ�����������260�������ڵ������֣�\n");
		scanf("%s",newname);
	}
	if(check(newname,POINTER))  {      //�ڵ�ǰĿ¼�в鿴�Ƿ��������
		printf("�ļ��������������������ļ�����");
		return ;
	}
	int len_oldpath=strlen(p->path);
	char newpath[260];
	strcpy(newpath,POINTER->path);
	strcat(newpath,"\\");
	strcat(newpath,newname);
	if(!rename(oldname,newname)){ //�Ծ���·������������
		    strcpy(p->name,newname);  //ʵ���ļ����У������ֺ����ڵ㴢������ֶ�Ҫ��
			strcpy(p->path,newpath);
			p->time=Today();        //���� ����޸�ʱ��
			change_path(len_oldpath,newpath,p->P_left);  //��p������������·��
		}
		else{
			printf("������ʧ�ܣ�\n");
			perror("rename");
		}
	return ;
}

Tree search(char path[],Tree p){  //���ң��ҵ�����·���ļ�/�ļ������ڵĽ��,����ָ��pָ��ý��
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
			        path_post[j]==path[j+i-2];   //��ȥ ..\ ���·��
			    printf("%s\n",path_post);
			    char* path_all;
		        strcpy(path_all,p->path);
		        strcat(path_all,"\\");
	            strcat(p->path,path_post);   //����·���������Ҫ�ҵ��ļ����У��ľ���·��
				while(p!=NULL){
			         if(!strcmp(path_all,p->path)) return p;
    	             if(strstr(path_all,p->path)) p=p->P_left;
	                 else p=p->P_right;
		        }
	            }}}
	return NULL;    //��ִ����������еķ��أ�˵����·���µ��ļ����У�������

}
void change_path(int len_oldpath,char* newpath,Tree p){  //���������·��
	if(p!=NULL) {
		int len_path=strlen(p->path);      //ԭ·������
	    int len=len_path - len_oldpath;
	    char* path_post=(char*)malloc(sizeof(char)*(len+1));
		int i;
		for(i=0;i<len;i++){
		    path_post[i]=p->path[i+len_oldpath];  //·������Ĳ��֣�oldpath��·��Ҫ��Ϊnewname�Ĳ���
	    }
	    path_post[i]='\0';
	    strcpy(p->path,newpath);
	    strcat(p->path,"\\");
		strcat(p->path,path_post);    //�������·��
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
	//system("cls");  //����
	//page_title("����ָ��һ��sort������ʱ������");
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
		if(t!=NULL){
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

void create(void){  //����txt�ļ�
	//system("cls");  //����
	//page_title("����ָ�����md -ml");
    printf("��ǰ���ڵ�·��Ϊ��");
    printf("%s\n",POINTER->path);
	char name[260];
	printf("�������ļ����֣�");
	scanf("%s",name);
	if(check(name,POINTER)){  //�ȼ���ļ��Ƿ�����
		printf("�ļ�������\n");
		return;
	}
	FILE* fp=fopen(name,"w");  //�����ļ�
	if(fp==0){
		printf("����ʧ�ܣ�\n");
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
	//���ӽ��
	if(POINTER->P_left==NULL){   //��ǰĿ¼Ϊ���ļ���ʱ��ֱ�����Ӽ���
		pNew->P_parents=POINTER;
		POINTER->P_left=pNew;
		pNew->P_right=NULL;
	}
	else{
		Tree p=POINTER->P_left;
        while(p->P_right!=NULL&&p->P_right->label==0){ //���������ļ���֮��ԭ���ļ�֮ǰ
        	p=p->P_right;
		}
		pNew->P_parents=p;
		pNew->P_right=p->P_right;
		if(p->P_right != NULL) p->P_right->P_parents = pNew;
		p->P_right=pNew;
	}
	printf("�����ɹ���\n");
	printf("����������������������������\n");
	continue_confirm();  //�ȴ�����ȷ�ϵĺ���
	return ;
}

/************************************************************************************/
