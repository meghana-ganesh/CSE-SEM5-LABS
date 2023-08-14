#include<stdio.h>
#include<ctype.h>
#include<string.h>
int main(){
    FILE *rd, *wrt;
    char c;
    char cmp[100];
    char arr[16][10]={"if","else","int","float","char","break","case","continue","default","double","for","while","return","sizeof","struct","void"};
    char name[100];
    int i;
    int flag;
    printf("Enter read file name: ");
    scanf("%s",name);
    rd=fopen(name,"r");
    if(rd==NULL){
        printf("File not found");
    }
    else{
        printf("Enter write file name: ");
        scanf("%s",name);
        wrt=fopen(name,"w");
        c=getc(rd);
        while(c!=EOF){
            i=0;
            flag=0;
            while((c>=65 && c<=90) || (c>=97 && c<=122)){
                name[i]=c;
                i++;
                c=getc(rd);
            }
            name[i]='\0';
            if(i>0){
            for(int j=0;j<16;j++){
                if(strcmp(name,arr[j])==0){
                    flag=1;
                    for(int k=0;k<i;k++){
                        putc(toupper(name[k]),wrt);
                    }
                }
            }}
            if(flag==0 && i>0){
                flag=1;
                    for(int k=0;k<i;k++){
                        putc(name[k],wrt);
                    }
                    //c=getc(rd);
            }
            else if(flag==0 && i==0){
                putc(c,wrt);
                c=getc(rd);
            }
        }
    }
    return 0;
}
