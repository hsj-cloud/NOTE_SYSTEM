#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
	char shuru[100];//输入的值输入的例子 tag -add <title> "neirong"
	char first[100];
	char second[100];
	char third[100];
	char forth[100];
	char change1[100];//记录文件名
	char change2[100];//记录标签内容
	gets ( shuru );
	memset (first,0,sizeof(first));
	sscanf ( shuru, "%[^ ]", first );//第一个空格前
	sscanf ( shuru, "%*[^ ] %[^ ]", second );//第二个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %[^ ]", third );//第三个空格前
	sscanf ( shuru, "%*[^ ] %*[^ ] %*[^ ] %[^ ]", forth );
	memset ( change1, 0, sizeof ( change1 ) );//清除缓存（没清之前有错误）
	memset ( change2, 0, sizeof ( change2 ) );

	printf("%s",forth);

	if(strcmp("ls",first)==0&&strlen(shuru)==2)
	{
		printf("first");
	}
	else if(strcmp("ls",first)==0&&strcmp("-a",second)==0)
	{
		printf("second");
	}
	else if(strcmp("ls",first)==0&&second[0]=='<')
	{
		sscanf ( second, "<%[^>]", change1 );//去除<>
		printf ( "%s", change1 );//检测
	}
	else if(strcmp("ls",first)==0&&second[0]=='<'&&strcmp("grep",third)==0&&forth[0]=='"')
	{

		sscanf ( second, "<%[^>]", change1 );//去除<>
		printf ( "%s", change1 );//检测
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		printf ( "%s", change2 );
	}
	else if(strcmp("cd",first)==0)
	{
		printf("%s",first);
	}

	if (strcmp("tag",first)==0&& second[0] == '-' && third[0] == '<' && forth[0] == '"' )
	{

		sscanf ( third, "<%[^>]", change1 );//去除<>
		printf ( "%s", change1 );//检测
		sscanf ( forth, "\"%[^\"]", change2 );//去除""
		printf ( "%s", change2 );
	}
	if ( strcmp("tag",first)==0&& second[0] == '<' )
	{

		sscanf ( second, "<%[^>]", change1 );
		printf ( "%s\n", change1 );
	}
	if (strcmp("tag",first)==0 && second[0] == '-' && third[0] == '"' )
	{

		sscanf ( third, "\"%[^\"]", change2 );
		printf ( "%s", change2 );
	}

	/*sscanf(shuru,"%[]",kong);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^“]“%[^”]",sda);

	*///printf("%s",str);
	//printf("%s %s %s",first,second,third);
	//printf("%s",shuru);
	return 0;


}
