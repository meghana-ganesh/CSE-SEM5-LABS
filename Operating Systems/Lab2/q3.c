#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
void sort(char arr[][100],int n)
{
	char s[100];
	for(int i=0;i<n+1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(strcmp(arr[i],arr[j])>0)
	        {
	            strcpy(s,arr[i]);
	            strcpy(arr[i],arr[j]);
	            strcpy(arr[j],s);
	        }
		}
	}
}
void printdir(char *dir)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char arr[100][100];
	dp = opendir(dir);
	if(!dp)
	{
		printf("cannot open directory");
		exit(0);
	}
	int k = 0;
	while(entry = readdir(dp))
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
				continue;
		}
		strcpy(arr[k++],entry->d_name);
	}
	chdir("..");
	sort(arr,k);
	for(int i=0;i<k;i++)
	{
		printf("%s\n",arr[i]);
	}
}
int main()
{
	char dir[256];
	printf("enter the directory name:");
	scanf("%s",dir);
	printdir(dir);
}