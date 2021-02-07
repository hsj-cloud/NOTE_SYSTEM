#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conin.h>
#include "note.h"

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
	display_ls(T->P_right_child); 
	display_ls(T->P_left_child); 
}

void display_ls_a(BiTree T)  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ��� 
{
	
}

void display_ls_NotePath(BiTree T)  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ����� 
{
	system("cls");  //���� 
	page_title("��ʾָ������ls <�ʼ��ļ���·��>");
	//if(*monitor_1==0)
	//{
		char target_path[260];  //��Ҫ���ҵ�ָ��Ŀ��·�� 
		printf("����������ָ����·����\n");
		scanf("%s",target_path);
		//*monitor_1=1;  //����ָ����� monitor_1��������1�����������ڼ�صݹ�ʱ�Ƿ��ٽ���ָ��·�������� 
	//}
	if(KMP_Algorithm(target_path,T->path)!=0)  //ָ��Ŀ��·����Գɹ�
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
		display_ls_NotePath(T->P_left_child);  //��ݹ飬������������ 
	}
}

void display_ls_NotePath_grep(BiTree T)  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ����� 
{
	system("cls");  //����
	page_title("��ʾָ���ģ�ls <�ʼ��ļ���·��> grep ���������ݡ�");
	int i,j;
	//if(*monitor_2==0)
	//{
		char target_path[260];  //��Ҫ���ҵ�ָ��Ŀ��·��
		printf("����������ָ����·����\n");
		scanf("%s",target_path);
		//*monitor_2=1;  //����ָ����� monitor_2��������2�����������ڼ�صݹ�ʱ�Ƿ��ٽ���ָ��·��������
	//}
	//if(*monitor_3==0)
	//{
		char child_string[20];
		printf("����������ָ����_�������ݣ�\n");
		scanf("%s",child_string);
		int length_child_string;
		length_child_string=strlen(child_string);
		for(j=20;j>1;j--)
		{
			child_string[j]=child_string[j-1];
		}
		child_string[0]=length_child_string;
		//*monitor_3=1;  ////����ָ����� monitor_3��������3�����������ڼ�صݹ�ʱ�Ƿ��ٽ����������ݵ�����
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
		if((Index_KMP(child_string,parents_string))!=0)  //ָ��Ŀ��·����Գɹ� 
		{
			if(T=NULL)
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
			display_ls_NotePath_grep(T->P_left_child);  //��ݹ飬������������ 
		}
	}
}

void sort_date(BiTree T)  //����ʱ�����ڽ������� 
{
	
}
