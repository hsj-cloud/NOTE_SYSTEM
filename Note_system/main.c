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

main(int argc, char *argv[]) 
{
	struct DATA *new_data;  //new_data用于作指令判断和保存文件名、文件路径 
	LinkList Ordinary_users;  //生成一个链表（存储普通用户信息） 
	CreateListTail(&Ordinary_users,MEMBER_SIZE);  //尾插法_初始化单链表（普通用户表）
	/***************初始化操作 ——建树*******/ 
	struct node *father_Tree = createfather();				//建立根节点，并在C文件运行目录建立“开始”目录 
	HEAD=father_Tree;
	POINTER=HEAD; 
	char *address = divide_filename(father_Tree->path);		//用于存放 所有笔记文件及文件夹 
	chdir(address);											//将工作指针指到C文件运行目录 
	f_read = fopen("preorder_tree.txt","r");				
	read_filebypre("preorder_tree.txt",&father_Tree); 		//从该TXT文件读取树的数据 
	fclose(f_read);
	chdir(father_Tree->path);
	/****************************************/
	Read_Ordinary_users(&Ordinary_users);  //读入文本文档（Ordinary_users.txt）
	
	system("cls");  //清屏
	menu_first:page_title("————准备中————");  //第一个菜单（笔记管理系统初始化） 
	printf("正在为你读入笔记管理系统\n"
		"————————————————\n"
		"用户信息已更新完毕！\n"
		"笔记信息已更新完毕！\n"
		"————————————————\n"); 
	continue_confirm();  //请按任意键继续
	
	system("cls");  //清屏
	menu_second:page_title("————操作选单————");  //第二个菜单（用户登录界面） 
	printf("请根据想要的服务选择对应的数字\n"
		"————————————————————\n"
		"1.登录账号\n"
		"2.注册账号\n"
		"3.注销账号\n"
		"4.显示所有账号信息\n"
		"5.更新普通用户数据（更新到 Ordinary_users.txt）\n"
		"6.退出系统\n"
		"————————————————————\n");
	
	switch(getchar())
	{
		case'1':
			if((Login_system(&Ordinary_users))==1)  //调用登录系统函数 
			{
				system("cls");  //清屏 
				menu_third:page_title("————操作选单————");  //第三个菜单（与笔记相关的功能） 
				printf("请根据想要的服务选择对应的数字\n"
					"————————————————————\n"
					"1.创建笔记文件\n"
					"2.删除笔记文件\n"
					"3.切换笔记路径\n"
					"4.移动或重名名笔记文件\n"
					"5.使用笔记标签\n"
					"6.对笔记文件排序\n"
					"7.显示笔记文件\n"
					"8.返回上一页\n"
					"————————————————————\n");
					
				switch(getchar())
				{
					case'1':
						system("cls");  //清屏
						menu_fourth_1:page_title("————创建 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"——————————————————————————\n"
							"1.md <要创建的笔记文件夹名> ：创建笔记文件夹\n"
							"2.md -ml <要创建的笔记文件名>：创建笔记文件\n"
							"3.back：返回上一页\n"
							"——————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
						if(new_data->value_1==17)
						{
							md(father_Tree);  //创建目录(在当前工作指针处创建子目录)
						}
						if(new_data->value_1==18)
						{
							create(); 
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏 
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=17&&new_data->value_1!=18&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto  menu_fourth_1;  //回到第四个菜单（与创建功能相关的菜单） 
						}
						break;
					case'2':
						system("cls");  //清屏
						menu_fourth_2:page_title("————删除 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"———————————————————————————\n"
							"1.rm <要删除的笔记文件名>：删除笔记文件\n"
							"2.rm -r <要删除的笔记文件夹名>：删除笔记文件夹\n"
							"3.back：返回上一页\n"
							"———————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
						if(new_data->value_1==10)
						{
							rm(father_Tree);  //对笔记文件进行删除
						}
						if(new_data->value_1==11)
						{
							rm_r(father_Tree);  //删除目录，并在删除目录的同时，将该结点及其左子树上所有的结点删除 
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=10&&new_data->value_1!=11&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_2;  //回到第四个菜单（与删除功能相关的菜单） 
						}
						break;
					case'3':
						system("cls");  //清屏
						menu_fourth_3:page_title("————切换 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"—————————————————————————————————\n"
							"1.cd：将路径切换为当前目录的父目录，若是根目录则则不进行切换\n"
							"2.cd <笔记文件夹路径>：将路径切换为命令中输入的文件夹路径\n"
							"3.back：返回上一页\n"
							"—————————————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理
						if(new_data->value_1==5)
						{
							cd_pre(father_Tree);  //移动到上级目录
						}
						if(new_data->value_1==6)
						{
							cd(father_Tree);  //切换工作目录到指定目录,并返回指向该目录的指针
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=5&&new_data->value_1!=6&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_3;  //回到第四个菜单（与切换功能相关的菜单） 
						}
						break;
					case'4':
						system("cls");  //清屏
						menu_fourth_4:page_title("————移动/重命名 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"——————————————————————————————————————————————\n"
							"1.mv <笔记文件名> <笔记文件夹目录>：将笔记文件移动到指定的文件夹目录下\n"
							"2.mv -a <笔记原文件名> <笔记目标文件名>：将笔记文件进行重命名，从原文件名改为目标文件名\n"
							"3.back：返回上一页\n"
							"——————————————————————————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
						if(new_data->value_1==7)
						{
							move_file();  //移动文件/文件夹 
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==8)
						{
							rename_file();  //重命名文件/文件夹
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=7&&new_data->value_1!=8&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_4;  //回到第四个菜单（与移动/重命名功能相关的菜单） 
						}
						break;
					case'5':
						system("cls");  //清屏 
						menu_fourth_5:page_title("————标签 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"————————————————————————————————————————————————————————\n"
							"1.tag <笔记文件名/笔记文件夹名>：显示指定笔记/文件夹的标签\n"
							"2.tag -add <笔记文件名/笔记文件夹名> “标签内容”：为指定笔记/笔记文件夹增加标签\n"
							"3.tag -del <笔记文件名/笔记文件夹名> “标签内容”：删除指定笔记/文件夹的指定标签\n"
							"4.tag -s “标签内容”：根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名\n"
							"5.tag -sa “标签内容”：根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名和它的路径\n"
							"6.back：返回上一页\n"
							"————————————————————————————————————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
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
							system("cls");  //清屏 
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=12&&new_data->value_1!=13&&new_data->value_1!=14&&new_data->value_1!=15&&new_data->value_1!=16&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_5;  //回到第四个菜单（与标签功能相关的菜单） 
						}
						break;
					case'6':
						system("cls");  //清屏
						menu_fourth_6:page_title("————排序 操作选单————");
						printf("请根据想要的服务输入对应的指令\n"
							"———————————————————————\n"
							"1.sort：按修改时间从近到远排序\n"
							"2.back：返回上一页\n"
							"———————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
						if(new_data->value_1==19)
						{
							Sort();  //对当前目录下的文件及文件夹进行时间排序
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=19&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_6;  //回到第四个菜单（与排序功能相关的菜单） 
						}
						break;
					case'7':
						system("cls");  //清屏 
						menu_fourth_7:page_title("————显示 操作选单————");  //第四类菜单（与显示功能相关的菜单） 
						printf("请根据想要的服务输入对应的指令\n"
							"—————————————————————————————————————————————\n"
							"1.ls：显示所有笔记文件\n"
							"2.ls -a：按照树状结构显示所有笔记文件\n"
							"3.ls <笔记文件夹路径>：显示指定文件下所有的笔记文件\n"
							"4.ls <笔记文件夹路径> grep “搜索内容”：显示指定文件下所有带有搜索内容的笔记文件\n"
							"5.back：返回上一页\n"
							"—————————————————————————————————————————————\n");
						new_data=cmd_manage();  //输入指令和指令处理 
						if(new_data->value_1==1)
						{
							display_ls(father_Tree);  //显示指令一：ls（显示所有笔记文件夹及笔记文件）
							printf("——————————————\n");
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==2)
						{
							display_ls_a(father_Tree);  //显示指令二：ls -a（按树状结构显示所有笔记文件夹和笔记文件）
							printf("——————————————\n");
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==3)
						{
							display_ls_NotePath(father_Tree,new_data->content_1);  //显示指令三：ls <笔记文件夹路径>（显示指定文件下所有的内容（子笔记文件夹和笔记文件））
							printf("——————————————\n");
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==4)
						{
							display_ls_NotePath_grep(father_Tree,new_data->content_1,new_data->content_2);  //显示指令四：ls <笔记文件夹路径> grep "搜索内容" （显示命令指定文件下所有的带有搜索内容的文件夹名及文件名）
							printf("——————————————\n");
							return_confirm();  //等待返回确认的函数
						}
						if(new_data->value_1==100)
						{
							system("cls");  //清屏
							goto menu_third;  //回到第三个菜单 
						}
						if(new_data->value_1!=1&&new_data->value_1!=2&&new_data->value_1!=3&&new_data->value_1!=4&&new_data->value_1!=100)
						{
							system("cls");  //清屏
							goto menu_fourth_7;  //回到第四个菜单（与显示功能相关的菜单） 
						}
						break;
					case'8':
						system("cls");  //清屏 
						goto menu_second;  //回到第二个菜单 
						break; 
				}
				system("cls");  //清屏
				goto menu_third;  //输入的字符或数字不在 menu_third 的选项中，回到 menu_third
			}
			break;
		case'2':Addusers(&Ordinary_users);break;  //注册新用户（尾部插入）
		case'3':Cancelusers(&Ordinary_users);break;  //注销用户
		case'4':Displayusers(&Ordinary_users);break;  //显示用户
		case'5':Updata_Ordinary_users(&Ordinary_users);break;  //更新普通用户数据到文本文档（Ordinary_users.txt）
		case'6':
		address = divide_filename(father_Tree->path);
		chdir(address);										//切换工作路径 
		f_write = fopen("preorder_tree.txt","w");			//将树保存到TXT文件中 
		write_filebypre("preorder_tree.txt",father_Tree);
		fclose(f_write);
		printf("关闭系统中.........");	
		free(address);
		free_all(father_Tree);
		exit(0);break;  //退出系统 
	}
	system("cls");  //清屏
	goto menu_second;  //输入的字符或数字不在 menu_second 的选项中，回到 menu_second
}
