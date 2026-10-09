#include <stdio.h>
#include <string.h>

int main() {
    char name[1000];
    int i, wordCount = 1;

    printf("Enter full name: ");
    fgets(name, sizeof(name), stdin);
    int len = strlen(name);

    for(i = 0; name[i] != '\0'; i++) {
        if(name[i] == ' ') {
            wordCount++;
        }
    }

    printf("Total characters (excluding spaces) = %d\n", len);
    printf("Number of words = %d\n", wordCount);

    printf("Initials = ");
    printf("%c.", name[0]); 

    for(i = 0; name[i] != '\0'; i++) {
        if(name[i] == ' ' && name[i+1] != '\0') {
            printf("%c.", name[i+1]);
        }
    }

    printf("\n");

    return 0;
}