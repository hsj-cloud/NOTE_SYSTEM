#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
/*	char str[100];
	char buf[100];
	char sda[100];
	sscanf("tag -add <wenjian> ¡°neirong¡±","%[^<]",str);
	sscanf("tag -add <wenjian> ¡°neirong¡±","%*[^<]<%[^>]",buf);
	sscanf("tag -add <wenjian> ¡°neirong¡±","%*[^¡°]¡°%[^¡±]",sda);
	printf("%s %s %s",str,buf,sda);
	return 0;
	*/
	char shuru[100];
	char str[100];
	char buf[100];
	char sda[100];
	scanf("%s",shuru);
	sscanf(shuru,"%[^<]",str);
	sscanf(shuru,"%*[^<]<%[^>]",buf);
	sscanf(shuru,"%*[^¡°]¡°%[^¡±]",sda);
	printf("%s %s %s",str,buf,sda);
	return 0;


}
