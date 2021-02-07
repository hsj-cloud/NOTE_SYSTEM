#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void select();
void search_file_tag ( struct treenode*tree ) ;
void search_add_file_tag ( struct treenode*tree ) ;
void search_delect_file_tag ( struct treenode*tree ); //���ڵ�
void tag_s ( struct treenode*tree ); //��ǰĿ¼���ڵ�
void tag_sa ( struct treenode*tree ); //��ǰĿ¼���ڵ�

typedef struct treenode
{
	int label;
	char path[260];
	char name[260];
	int size;
	char tag_1[10];
	char tag_2[10];
	char tag_3[10];
	treenode *left;
	treenode *right;
} Tnode;
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




void search_file_tag ( struct treenode*tree ) //���ڵ�

{

	char search_name[260];
	scanf ( "%s", search_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = tree;
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
void search_add_file_tag ( struct treenode*tree ) //���ڵ�
{

	char search_name[260];
	scanf ( "%s", search_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = tree;
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
void search_delect_file_tag ( struct treenode*tree ) //���ڵ�
{
	char search_name[260];
	scanf ( "%s", search_name );
	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = tree;
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
void tag_s ( struct treenode*tree ) //��ǰĿ¼���ڵ�
{

	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = tree;
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
void tag_sa ( struct treenode*tree ) //��ǰĿ¼���ڵ�
{

	char tag_name[10];
	scanf ( "%s", tag_name );
	if ( tree == NULL )
		return;
	struct treenode* stack[10];
	int stacktop = -1;
	struct treenode*pmove = tree;
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


int main ( void )
{
	select_menu();
	return 0;
}
