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

main(int argc, char *argv[]) 
{
	struct DATA *new_data;  //new_data������ָ���жϺͱ����ļ������ļ�·�� 
	LinkList Ordinary_users;  //����һ�������洢��ͨ�û���Ϣ�� 
	CreateListTail(&Ordinary_users,MEMBER_SIZE);  //β�巨_��ʼ����������ͨ�û���
	/***************��ʼ������ ��������*******/ 
	struct node *father_Tree = createfather();				//�������ڵ㣬����C�ļ�����Ŀ¼��������ʼ��Ŀ¼ 
	HEAD=father_Tree;
	POINTER=HEAD; 
	char *address = divide_filename(father_Tree->path);		//���ڴ�� ���бʼ��ļ����ļ��� 
	chdir(address);											//������ָ��ָ��C�ļ�����Ŀ¼ 
	f_read = fopen("preorder_tree.txt","r");				
	read_filebypre("preorder_tree.txt",&father_Tree); 		//�Ӹ�TXT�ļ���ȡ�������� 
	fclose(f_read);
	chdir(father_Tree->path);
	/****************************************/
	Read_Ordinary_users(&Ordinary_users);  //�����ı��ĵ���Ordinary_users.txt��
	
	system("cls");  //����
	menu_first:page_title("��������׼���С�������");  //��һ���˵����ʼǹ���ϵͳ��ʼ���� 
	printf("����Ϊ�����ʼǹ���ϵͳ\n"
		"��������������������������������\n"
		"�û���Ϣ�Ѹ�����ϣ�\n"
		"�ʼ���Ϣ�Ѹ�����ϣ�\n"
		"��������������������������������\n"); 
	continue_confirm();  //�밴���������
	
	system("cls");  //����
	menu_second:page_title("������������ѡ����������");  //�ڶ����˵����û���¼���棩 
	printf("�������Ҫ�ķ���ѡ���Ӧ������\n"
		"����������������������������������������\n"
		"1.��¼�˺�\n"
		"2.ע���˺�\n"
		"3.ע���˺�\n"
		"4.��ʾ�����˺���Ϣ\n"
		"5.������ͨ�û����ݣ����µ� Ordinary_users.txt��\n"
		"6.�˳�ϵͳ\n"
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
					"4.�ƶ����������ʼ��ļ�\n"
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
							"2.md -ml <Ҫ�����ıʼ��ļ���>�������ʼ��ļ�\n"
							"3.back��������һҳ\n"
							"����������������������������������������������������\n");
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==17)
						{
							md(father_Tree);  //����Ŀ¼(�ڵ�ǰ����ָ�봦������Ŀ¼)
						}
						if(new_data->value_1==18)
						{
							create(); 
						}
						if(new_data->value_1==100)
						{
							system("cls");  //���� 
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=17&&new_data->value_1!=18&&new_data->value_1!=100)
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
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==10)
						{
							rm(father_Tree);  //�Աʼ��ļ�����ɾ��
						}
						if(new_data->value_1==11)
						{
							rm_r(father_Tree);  //ɾ��Ŀ¼������ɾ��Ŀ¼��ͬʱ�����ý�㼰�������������еĽ��ɾ�� 
						}
						if(new_data->value_1==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=10&&new_data->value_1!=11&&new_data->value_1!=100)
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
						new_data=cmd_manage();  //����ָ���ָ���
						if(new_data->value_1==5)
						{
							cd_pre(father_Tree);  //�ƶ����ϼ�Ŀ¼
						}
						if(new_data->value_1==6)
						{
							cd(father_Tree);  //�л�����Ŀ¼��ָ��Ŀ¼,������ָ���Ŀ¼��ָ��
						}
						if(new_data->value_1==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=5&&new_data->value_1!=6&&new_data->value_1!=100)
						{
							system("cls");  //����
							goto menu_fourth_3;  //�ص����ĸ��˵������л�������صĲ˵��� 
						}
						break;
					case'4':
						system("cls");  //����
						menu_fourth_4:page_title("���������ƶ�/������ ����ѡ����������");
						printf("�������Ҫ�ķ��������Ӧ��ָ��\n"
							"��������������������������������������������������������������������������������������������\n"
							"1.mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>�����ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼��\n"
							"2.mv -a <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>�����ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ���\n"
							"3.back��������һҳ\n"
							"��������������������������������������������������������������������������������������������\n");
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==7)
						{
							move_file();  //�ƶ��ļ�/�ļ��� 
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==8)
						{
							rename_file();  //�������ļ�/�ļ���
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=7&&new_data->value_1!=8&&new_data->value_1!=100)
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
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==12)
						{
							search_file_tag(father_Tree,new_data->content_1); 
						}
						if(new_data->value_1==13)
						{
							search_add_file_tag(father_Tree,new_data->content_1,new_data->content_2);
						}
						if(new_data->value_1==14)
						{
							search_delect_file_tag(father_Tree,new_data->content_1,new_data->content_2);
						}
						if(new_data->value_1==15)
						{
							tag_s(father_Tree,new_data->content_1); 
						}
						if(new_data->value_1==16)
						{
							tag_sa(father_Tree,new_data->content_1); 
						}
						if(new_data->value_1==100)
						{
							system("cls");  //���� 
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=12&&new_data->value_1!=13&&new_data->value_1!=14&&new_data->value_1!=15&&new_data->value_1!=16&&new_data->value_1!=100)
						{
							system("cls");  //����
							goto menu_fourth_5;  //�ص����ĸ��˵������ǩ������صĲ˵��� 
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
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==19)
						{
							Sort();  //�Ե�ǰĿ¼�µ��ļ����ļ��н���ʱ������
						}
						if(new_data->value_1==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=19&&new_data->value_1!=100)
						{
							system("cls");  //����
							goto menu_fourth_6;  //�ص����ĸ��˵�������������صĲ˵��� 
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
						new_data=cmd_manage();  //����ָ���ָ��� 
						if(new_data->value_1==1)
						{
							display_ls(father_Tree);  //��ʾָ��һ��ls����ʾ���бʼ��ļ��м��ʼ��ļ���
							printf("����������������������������\n");
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==2)
						{
							display_ls_a(father_Tree);  //��ʾָ�����ls -a������״�ṹ��ʾ���бʼ��ļ��кͱʼ��ļ���
							printf("����������������������������\n");
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==3)
						{
							display_ls_NotePath(father_Tree,new_data->content_1);  //��ʾָ������ls <�ʼ��ļ���·��>����ʾָ���ļ������е����ݣ��ӱʼ��ļ��кͱʼ��ļ�����
							printf("����������������������������\n");
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==4)
						{
							display_ls_NotePath_grep(father_Tree,new_data->content_1,new_data->content_2);  //��ʾָ���ģ�ls <�ʼ��ļ���·��> grep "��������" ����ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ�����
							printf("����������������������������\n");
							return_confirm();  //�ȴ�����ȷ�ϵĺ���
						}
						if(new_data->value_1==100)
						{
							system("cls");  //����
							goto menu_third;  //�ص��������˵� 
						}
						if(new_data->value_1!=1&&new_data->value_1!=2&&new_data->value_1!=3&&new_data->value_1!=4&&new_data->value_1!=100)
						{
							system("cls");  //����
							goto menu_fourth_7;  //�ص����ĸ��˵�������ʾ������صĲ˵��� 
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
			break;
		case'2':Addusers(&Ordinary_users);break;  //ע�����û���β�����룩
		case'3':Cancelusers(&Ordinary_users);break;  //ע���û�
		case'4':Displayusers(&Ordinary_users);break;  //��ʾ�û�
		case'5':Updata_Ordinary_users(&Ordinary_users);break;  //������ͨ�û����ݵ��ı��ĵ���Ordinary_users.txt��
		case'6':
		address = divide_filename(father_Tree->path);
		chdir(address);										//�л�����·�� 
		f_write = fopen("preorder_tree.txt","w");			//�������浽TXT�ļ��� 
		write_filebypre("preorder_tree.txt",father_Tree);
		fclose(f_write);
		printf("�ر�ϵͳ��.........");	
		free(address);
		free_all(father_Tree);
		exit(0);break;  //�˳�ϵͳ 
	}
	system("cls");  //����
	goto menu_second;  //������ַ������ֲ��� menu_second ��ѡ���У��ص� menu_second
}
