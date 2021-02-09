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
	char shuru[100];
	char first[100];
	char second[100];
	char third[100];
	char forth[100];
	char change1[100];
	char change2[100];
	gets ( shuru );
	sscanf ( shuru, "%[^ ]", first );
	sscanf ( shuru, "%*[^ ] %[^ ]", second );
	sscanf ( shuru, "%*[^ ] %*[^ ] %[^ ]", third );
	sscanf ( shuru, "%*[^ ] %*[^ ] %*[^ ] %[^ ]", forth );
	memset ( change1, 0, sizeof ( change1 ) );
	memset ( change2, 0, sizeof ( change2 ) );
	printf ( "%s\n", second );
	//      printf("%s\n",forth);
	if ( first[0] == 't' && second[0] == '-' && third[0] == '<' && forth[0] == '"' )
	{

		sscanf ( third, "<%[^>]", change1 );
		printf ( "%s", change1 );
		sscanf ( forth, "\"%[^\"]", change2 );
		printf ( "%s", change2 );
	}
	if ( first[0] == 't' && second[0] == '<' )
	{

		sscanf ( second, "<%[^>]", change1 );
		printf ( "%s\n", change1 );
	}
	if ( first[0] == 't' && second[0] == '-' && third[0] == '"' )
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
