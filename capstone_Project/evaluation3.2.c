#include <stdio.h>

struct student
{
    int roll;
    char name[30];
    float marks;
};

int main()
{
    struct student s = {1, "Durjoy", 25.5};
    struct student *ptr = &s;

    printf("Roll: %d\n", (*ptr).roll);
    printf("Roll: %d\n", ptr->roll);
}