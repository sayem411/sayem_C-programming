#include<stdio.h>
#include<string.h>
int main()
{
    char s1[30];
    char s2[30];
    int i=0,j=0;
    //fgets(s1,30,stdin);
    //fgets(s2,30,stdin);

    scanf("%s",s1);
    scanf("%s",s2);

    strcat(s1," ");
    strcat(s1,s2);

   for(i=0;s1[i]!='\0';i++){

        if(s1[i]>='A' && s1[i]<='Z')
        {
            s1[i]+=32;

        }
    }
    printf("%s",s1);
    return 0;
}