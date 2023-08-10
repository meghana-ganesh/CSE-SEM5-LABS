#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(int argc,char* argv[])
{
	int a=13;
    float b=5.5;
    char c='a';
    char str[]="hello";
  	printf("a=%d b=%f c=%c str=%s hexadecimal for a=%x \n",a,b,c,str,a);
}