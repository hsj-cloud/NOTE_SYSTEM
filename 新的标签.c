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
