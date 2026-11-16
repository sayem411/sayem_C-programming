#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int roll;
    char name[30];
    float marks;
};

int main()
{
    struct student *ptr = (struct student*)malloc(sizeof(struct student));
    ptr->roll = 01;
    strcpy(ptr->name, "Sayem");
    printf("Roll: %d\n", ptr->roll);
    printf("Name: %s\n", ptr->name);
}