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

node* POINTER;     //ȫ�ֱ�����ʵʱָ���û��򿪵ĵ�ǰĿ¼ 
node* HEAD;        //����ͷ�ڵ�

main(int argc, char *argv[]) 
{
	LinkList Ordinary_users;  //����һ�������洢��ͨ�û���Ϣ�� 
	CreateListTail(&Ordinary_users,MEMBER_SIZE);  //β�巨_��ʼ����������ͨ�û���
	char change_1[100];  //��¼�ļ���
	char change_2[100];  //��¼��ǩ����
	
	system("cls");  //����
	menu_first:page_title("��������׼���С�������");  //��һ���˵����ʼǹ���ϵͳ��ʼ���� 
	printf("����Ϊ�����ʼǹ���ϵͳ\n"
		"��������������������������������\n"
		"�û���Ϣ�Ѹ�����ϣ�\n"
		"�ʼ���Ϣ�Ѹ�����ϣ�\n"
		"��������������������������������\n"); 
	continue_confirm();  //�밴���������
	
	systrm("cls");  //����
	menu_second:page_title("������������ѡ����������");  //�ڶ����˵����û���¼���棩 
	printf("�������Ҫ�ķ���ѡ���Ӧ������\n"
		"����������������������������������������\n"
		"1.��¼�˺�\n"
		"2.ע���˺�\n"
		"3.ע���˺�\n"
		"4.��ʾ�����˺���Ϣ\n"
		"5.�˳�ϵͳ\n"
		"����������������������������������������\n");
	
	switch(getchar())
	{
		case'1':
			if((Login_system(&Ordinary_users))==1)  //���õ�¼ϵͳ���� 
			{
				system("cls");  //���� 
				menu_third:page_title("������������ѡ����������");  //�������˵�����ʼ���صĹ��ܣ� 
				printf("�������Ҫ�ķ���ѡ���Ӧ������\n"
					"����������������������������������������\n"
					"1.�����ʼ��ļ�\n"
					"2.ɾ���ʼ��ļ�\n"
					"3.�л��ʼ�·��\n"
					"4.�ƶ��ʼ��ļ�\n"
					"5.ʹ�ñʼǱ�ǩ\n"
					"6.�Աʼ��ļ�����\n"
					"7.��ʾ�ʼ��ļ�\n"
					"8.������һҳ\n"
					"����������������������������������������\n");
					
				switch(getchar())
				{
					case'1':
						system("cls");  //����
						menu_fourth_1:page_title("������������ ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"����������������������������������������������������\n"
							"1.md <Ҫ�����ıʼ��ļ�����> �������ʼ��ļ���\n"
							"2.back��������һҳ\n"
							"����������������������������������������������������\n");
						int command_judgement_1;  //�����ж�ָ��
						command_judgement_1=Command_Processing();  //�����
						if(command_judgement_1==14)
						{
							md(struct node *T);  //����Ŀ¼(�ڵ�ǰ����ָ�봦������Ŀ¼)
						}
						if(command_judgement_1==100)
						{
							system("cls");  //���� 
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_1!=14&&command_judgement_1!=100)
						{
							system("cls");  //����
							goto  menu_fourth_1;  //�ص����ĸ��˵����봴��������صĲ˵��� 
						}
						break;
					case'2':
						system("cls");  //����
						menu_fourth_2:page_title("��������ɾ�� ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"������������������������������������������������������\n"
							"1.rm <Ҫɾ���ıʼ��ļ���>��ɾ���ʼ��ļ�\n"
							"2.rm -r <Ҫɾ���ıʼ��ļ�����>��ɾ���ʼ��ļ���\n"
							"3.back��������һҳ\n"
							"������������������������������������������������������\n");
						int command_judgement_2;  //�����ж�ָ��
						command_judgement_2=Command_Processing();  //�����
						if(command_judgement_2==9)
						{
							rm(struct node *T);  //�Աʼ��ļ�����ɾ��
						}
						if(command_judgement_2==10)
						{
							rm_r(struct node *T);  //ɾ��Ŀ¼������ɾ��Ŀ¼��ͬʱ�����ý�㼰�������������еĽ��ɾ�� 
						}
						if(command_judgement_2==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_2!=9&&command_judgement_2!=10&&command_judgement_2!=100)
						{
							system("cls");  //����
							goto menu_fourth_2;  //�ص����ĸ��˵�����ɾ��������صĲ˵��� 
						}
						break;
					case'3':
						system("cls");  //����
						menu_fourth_3:page_title("���������л� ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"������������������������������������������������������������������\n"
							"1.cd����·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼�����Ǹ�Ŀ¼���򲻽����л�\n"
							"2.cd <�ʼ��ļ���·��>����·���л�Ϊ������������ļ���·��\n"
							"3.back��������һҳ\n"
							"������������������������������������������������������������������\n");
						int command_judgement_3;  //�����ж�ָ��
						command_judgement_3=Command_Processing();  //�����
						if(command_judgement_3==5)
						{
							cd_pre(struct node *T);  //�ƶ����ϼ�Ŀ¼
						}
						if(command_judgement_3==6)
						{
							cd(struct node *T);  //�л�����Ŀ¼��ָ��Ŀ¼,������ָ���Ŀ¼��ָ��
						}
						if(command_judgement_3==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_3!=5&&command_judgement_3!=6&&command_judgement_3!=100)
						{
							system("cls");  //����
							goto menu_fourth_3  //�ص����ĸ��˵������л�������صĲ˵��� 
						}
						break;
					case'4':
						system("cls");  //����
						menu_fourth_4:page_title("���������ƶ�/������ ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"��������������������������������������������������������������������������������������������\n"
							"1.mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>�����ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼��\n"
							"2.mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>�����ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ���\n"
							"3.back��������һҳ\n"
							"��������������������������������������������������������������������������������������������\n");
						int command_judgement_4;  //�����ж�ָ��
						command_judgement_4=Command_Processing();  //�����
						if(command_judgement_4==7)
						{
							move_file();  //�ƶ��ļ�/�ļ��� 
						}
						if(command_judgement_4==8)
						{
							rename_file(void);  //�������ļ�/�ļ���
						}
						if(command_judgement_4==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_4!=7&&command_judgement_4!=8&&command_judgement_4!=100)
						{
							system("cls");  //����
							goto menu_fourth_4;  //�ص����ĸ��˵������ƶ�/������������صĲ˵��� 
						}
						break;
					case'5':
						system("cls");  //���� 
						menu_fourth_5:page_title("����������ǩ ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"����������������������������������������������������������������������������������������������������������������\n"
							"1.tag <�ʼ��ļ���/�ʼ��ļ�����>����ʾָ���ʼ�/�ļ��еı�ǩ\n"
							"2.tag -add <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ���Ϊָ���ʼ�/�ʼ��ļ������ӱ�ǩ\n"
							"3.tag -del <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ���ɾ��ָ���ʼ�/�ļ��е�ָ����ǩ\n"
							"4.tag -s ����ǩ���ݡ������ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���\n"
							"5.tag -sa ����ǩ���ݡ������ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ���������·��\n"
							"6.back��������һҳ\n"
							"����������������������������������������������������������������������������������������������������������������\n");
						int command_judgement_5;  //�����ж�ָ��
						command_judgement_5=Command_Processing();  //�����
						if(command_judgement_5==11)
						{
							//�����ĻԵĺ���_1 
						}
						if(command_judgement_5==12)
						{
							//�����ĻԵĺ���_2 
						}
						if(command_judgement_5==13)
						{
							//�����ĻԵĺ���_3 
						}
						if(command_judgement_5==100)
						{
							system("cls");
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_5!=11&&command_judgement_5!=12&&command_judgement_5!=13&&command_judgement_5!=100)
						{
							system("cls");  //����
							goto menu_fourth_5  //�ص����ĸ��˵������ǩ������صĲ˵��� 
						}
						break;
					case'6':
						system("cls");  //����
						menu_fourth_6:page_title("������������ ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"����������������������������������������������\n"
							"1.sort�����޸�ʱ��ӽ���Զ����\n"
							"2.back��������һҳ\n"
							"����������������������������������������������\n");
						int command_judgement_6;  //�����ж�ָ��
						command_judgement_6=Command_Processing();  //�����
						if(command_judgement_6==15)
						{
							Sort(void);  //�Ե�ǰĿ¼�µ��ļ����ļ��н���ʱ������
						}
						if(command_judgement_6==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_6!=15&&command_judgement_6!=100)
						{
							system("cls");  //����
							goto menu_fourth_6  //�ص����ĸ��˵�������������صĲ˵��� 
						}
						break;
					case'7':
						system("cls");  //���� 
						menu_fourth_7:page_title("����������ʾ ����ѡ����������");  //������˵�������ʾ������صĲ˵��� 
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"������������������������������������������������������������������������������������������\n"
							"1.ls����ʾ���бʼ��ļ�\n"
							"2.ls -a��������״�ṹ��ʾ���бʼ��ļ�\n"
							"3.ls <�ʼ��ļ���·��>����ʾָ���ļ������еıʼ��ļ�\n"
							"4.ls <�ʼ��ļ���·��> grep ���������ݡ�����ʾָ���ļ������д����������ݵıʼ��ļ�\n"
							"5.back��������һҳ\n"
							"������������������������������������������������������������������������������������������\n");
						int command_judgement_7;  //�����ж�ָ�� 
						command_judgement_7=Command_Processing(change_1,change_2);  //�����
						if(command_judgement_7==1)
						{
							display_ls(BiTree T);  //��ʾָ��һ��ls����ʾ���бʼ��ļ��м��ʼ��ļ���
						}
						if(command_judgement_7==2)
						{
							void display_ls_a(BiTree T);  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ���
						}
						if(command_judgement_7==3)
						{
							display_ls_NotePath(BiTree T,change_1);  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ�����
						}
						if(command_judgement_7==4)
						{
							display_ls_NotePath_grep(BiTree T);  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ�����
						}
						if(command_judgement_7==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(command_judgement_7!=1&&command_judgement_7!=2&&command_judgement_7!=3&&command_judgement_7!=4&&command_judgement_7!=100)
						{
							system("cls");  //����
							goto menu_fourth_7  //�ص����ĸ��˵�������ʾ������صĲ˵��� 
						}
						break;
					case'8':
						system("cls");  //���� 
						goto menu_second;  //�ص��ڶ����˵� 
						break; 
				}
				system("cls");  //����
				goto menu_third;  //������ַ������ֲ��� menu_third ��ѡ���У��ص� menu_third
			}
		case'2':Addusers(&Ordinary_users);break;  //ע�����û���β�����룩
		case'3':Cancelusers(&Ordinary_users);break;  //ע���û�
		case'4':Displayusers(&Ordinary_users);break;  //��ʾ�û�
		case'5':exit(0);break;  //�˳�ϵͳ 
	}
	system("cls");  //����
	goto menu_second;  //������ַ������ֲ��� menu_second ��ѡ���У��ص� menu_second
}
