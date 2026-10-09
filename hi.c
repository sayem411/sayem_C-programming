#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);
    int compare = strcmp(str1, str2);

    if(compare == 0)
        printf("Strings are equal");
    else
        printf("Strings are not equal");

    return 0;
}