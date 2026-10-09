#include<stdio.h>
#include<string.h>
int main(){
    char str[100],sub[100];
    int start,i;
    fgets(str,sizeof(str),stdin);
    scanf("%d",&start);
    for( i=0;i<strlen(str);i++){
        sub[i]=str[start+i];
    }
sub[i]='\0';
printf("Sub string:%s",sub);
    return 0;
}