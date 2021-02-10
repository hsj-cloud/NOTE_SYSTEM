#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct node
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
/*struct node* creattree ( char *file_name, char*tag_name )
{
	struct node* newnode = ( struct node* ) malloc ( sizeof ( struct node ) );
	sprintf ( newnode->name, "%s", file_name );
	sprintf ( newnode->tag_1, "%s", tag_name );
	newnode->label=0;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
};*/


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
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strlen ( pmove->tag_1 ) != 0 )
					printf ( "%s\n", pmove->tag_1 );
				if ( strlen ( pmove->tag_2 ) != 0 )
					printf ( "%s\n", pmove->tag_2 );
				if ( strlen ( pmove->tag_3 ) != 0 )
					printf ( "%s\n", pmove->tag_3 );
				break;
			}
			else
			{
				pmove = pmove->right;
			}





		}

	}
}
void search_add_file_tag ( struct node*tree, char*search_name, char* tag_name ) //根节点
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
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( strcmp ( search_name, pmove->name ) == 0 )
			{
				if ( strlen ( pmove->tag_1 ) == 0 )
				{
					sprintf ( pmove->tag_1, "%s", tag_name );
					printf ( "添加到tag-1\n" );
					break;
				}
				else
				{
					if ( strlen ( pmove->tag_2 ) == 0 )
					{
						sprintf ( pmove->tag_2, "%s", tag_name );
						printf ( "添加到tag-2\n" );
						break;
					}
					else
					{
						if ( strlen ( pmove->tag_3 ) == 0 )
						{
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
				pmove = pmove->right;
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
			pmove = pmove->left;
		}//记录最左边的所有节点
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
					{

						memset ( pmove->tag_1, 0, sizeof ( pmove->tag_1 ) );
						printf ( "删除tag_1成功\n" );
						break;
					}
					if ( strcmp ( tag_name, pmove->tag_2 ) == 0 )
					{
						memset ( pmove->tag_2, 0, sizeof ( pmove->tag_2 ) );
						printf ( "删除tag_2成功\n" );
						break;
					}
					if ( strcmp ( tag_name, pmove->tag_3 ) == 0 )
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
				pmove = pmove->right;
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
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 1 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{
					printf ( "%s\t", pmove->name );


				}

				pmove = pmove->right;
			}

			else
				pmove = pmove->right;
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
			pmove = pmove->left;
		}//记录最左边的所有节点
		if ( stacktop != -1 )
		{
			pmove = stack[stacktop--];
			if ( pmove->label == 0 )
			{
				if ( strcmp ( tag_name, pmove->tag_1 ) == 0 || strcmp ( tag_name, pmove->tag_2 ) == 0 || strcmp ( tag_name, pmove->tag_3 ) == 0 )
				{


					printf ( "%s\t", pmove->name );
					printf ( "%s\t", pmove->path );
				}
					pmove = pmove->right;
			}

			else
				pmove = pmove->right;
		}

	}
}
void insertnode ( struct node* curnode, struct node*lnode, struct node*rnode )
{
	curnode->left = lnode;
	curnode->right = rnode;
}

int main ( void )
{
/*	struct node*A = creattree ( "Aa", "sadsd" );
	struct node*B = creattree ( "Bb", "ads" );
	struct node*C = creattree ( "Cc", "dsad" );
	struct node*D = creattree ( "Dd", "dasd" );
	struct node*E = creattree ( "Ee", "wr" );
	struct node*F = creattree ( "Ff", "asd" );
	struct node*G = creattree ( "Gg", "vvv" );
	struct node*K = creattree ( "Kk", "ddd" );
	insertnode ( A, B, C );
	insertnode ( B, D, E );
	insertnode ( C, F, G );
	insertnode ( F, NULL, K );
	search_add_file_tag ( A, "Ee", "bi" );
	search_delect_file_tag ( A, "Dd", "e" );*/
	return 0;
}
