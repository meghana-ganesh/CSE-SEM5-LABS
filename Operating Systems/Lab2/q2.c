#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
void printdir(char *dir)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	dp = opendir(dir);
	if(!dp)
	{
		printf("cannot open directory.");
		exit(0);
	}
	chdir(dir);
	while(entry = readdir(dp))
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
				continue;
			printf(" %s ",entry->d_name);
			printdir(entry->d_name);
		}
		else
		{
			printf("%s\n",entry->d_name);
		}
	}
	printf("\n");
	chdir("..");
}
int main()
{
	char dir[256];
	printf("enter directory name:");
	scanf("%s",dir);
	printdir(dir);
}