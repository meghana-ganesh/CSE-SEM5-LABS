#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
int main()
{
	DIR *dp;
	char dir[256];
	printf("enter directory name:");
	scanf("%s",dir);
	struct dirent *entry;
	struct stat statbuf;
	dp = opendir(dir);
	if(!dp)
	{
		printf("\ncannot open directory");
		exit(0);
	}
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
			continue;
		printf(" %s ",entry->d_name);
		if(S_ISDIR(statbuf.st_mode))
			printf(S_ISDIR(statbuf.st_mode)? "d":"-");
		printf(statbuf.st_mode & S_IRUSR? "r":"-");
		printf(statbuf.st_mode & S_IWUSR? "r":"-");
		printf(statbuf.st_mode & S_IXUSR ? "x":"-");
		printf(statbuf.st_mode & S_IRGRP ? "r":"-");
		printf(statbuf.st_mode & S_IWGRP ? "w":"-");
		printf(statbuf.st_mode & S_IXGRP ? "x":"-");
		printf(statbuf.st_mode & S_IROTH ? "r":"-");
		printf(statbuf.st_mode & S_IWOTH ? "w":"-");
		printf(statbuf.st_mode & S_IXOTH ? "x":"-");
	}
	closedir(dp);
}