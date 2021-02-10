#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct DATA{
	int value_1;
	int value_2;
	char content_1[260];
	char content_2[260];
};
struct DATA* cmd_manage()
{
	char shuru[100];//输入的值输入的例子 tag -add <title> "neirong"
	char first[100];
	char second[100];
	char third[100];
	char forth[100];
	char change1[260];//记录文件名
	char change2[260];//记录标签内容
	gets ( shuru );
	memset ( first, 0, sizeof ( first ) );
	sscanf ( shuru, "%[^ ]", first );//第一个空格前
	sscanf ( shuru, "%*[^ ] %[^ ]", second );//第二个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %[^ ]", third );//第三个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %*[^ ] %[^ ]", forth );
	memset ( change1, 0, sizeof ( change1 ) );//清除缓存（没清之前有错误）
	memset ( change2, 0, sizeof ( change2 ) );
	struct DATA *data=(struct DATA*)malloc(sizeof(struct DATA));


        if ( strcmp ( "back", first ) == 0 )
	{
		data->value_1=0;
		data->value_2=0;

	}

	else if ( strcmp ( "ls", first ) == 0 && strlen ( shuru ) == 2 )
	{

	}


	else if ( strcmp ( "ls", first ) == 0 && strcmp ( "-a", second ) == 0 )
	{
		data->value_1=2;
		data->value_2=0;

	}
	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' && strcmp ( "grep", third ) == 0 && forth[0] == '"' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);

	}
	else if ( strcmp ( "ls", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);



	}

	else if ( strcmp ( "cd", first ) == 0 )
	{
		printf ( "%s", first );
	}
	else if ( strcmp ( "cd", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "mv", first ) == 0 && second[0] == '<' && third[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sscanf ( third, "<%[^>]", change2 );//去除<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
	}
	else if ( strcmp ( "mv", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' && forth[0] == '<' )
	{
		data->value_1=1;
		data->value_2=1;
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "<%[^>]", change2 );//去除<>
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
	}
	else if ( strcmp ( "rm", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "rm", first ) == 0 && strcmp ( "-r", second ) == 0 && third[0] == '<' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sprintf(data->content_1,"%s",change1);
	}



	else if ( strcmp ( "tag", first ) == 0 && strcmp("-add",second)==0 && third[0] == '<' && forth[0] == '"' )
	{
		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-del",second)==0 && third[0] == '<' && forth[0] == '"' )
	{

		sscanf ( third, "<%[^>]", change1 );//去除<>
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		sprintf(data->content_1,"%s",change1);
		sprintf(data->content_2,"%s",change2);
	}
	else if ( strcmp ( "tag", first ) == 0 && second[0] == '<' )
	{

		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-s",second) ==0&& third[0] == '"' )
	{
		data->value_1=0;
		data->value_2=1;
		sscanf ( third, "\"%[^\"]", change1 );
		printf ( "%s", change1 );
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "tag", first ) == 0 && strcmp("-sa",second) ==0&& third[0] == '"' )
	{
		data->value_1=1;
		data->value_2=0;
		sscanf ( third, "\"%[^\"]", change1 );
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "md", first ) == 0 && second[0] == '<' )
	{
		data->value_1=2;
		data->value_2=1;
		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
	}
	else if ( strcmp ( "sort", first ) == 0 && second[0] == '<' )
	{
		sscanf ( second, "<%[^>]", change1 );
		sprintf(data->content_1,"%s",change1);
	}
	else {
		printf("wrong cmd\n");
	}
	return data;


	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^“]“%[^”]",sda);

	*///printf("%s",str);
	//printf("%s %s %s",first,second,third);
	//printf("%s",shuru);



};
int main()
{
	/*      char str[100];
	        char buf[100];
	        char sda[100];
	        sscanf("tag -add <wenjian> “neirong”","%[^<]",str);
	        sscanf("tag -add <wenjian> “neirong”","%*[^<]<%[^>]",buf);
	        sscanf("tag -add <wenjian> “neirong”","%*[^“]“%[^”]",sda);
	        printf("%s %s %s",str,buf,sda);
	        return 0;
	        */


	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^“]“%[^”]",sda);

	*///printf("%s",str);
	//printf("%s %s %s",first,second,third);
	//printf("%s",shuru);
	struct DATA*new_data;
	new_data=cmd_manage();
	return 0;


}
