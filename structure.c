#include <stdio.h>
struct student {
    char name[50];
    int id;
    float physics;
    float mathematics;
    float chemistry;
};

int main() {
    struct student s;
    
    // Input
    printf("Enter student name: ");
    scanf("%s", s.name);
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    printf("Enter marks in Physics: ");
    scanf("%f", &s.physics);
    printf("Enter marks in Mathematics: ");
    scanf("%f", &s.mathematics);
    printf("Enter marks in Chemistry: ");
    scanf("%f", &s.chemistry);
    
    float total = s.physics + s.mathematics + s.chemistry;
    float average = total / 3.0;
    
    char grade;
    if (average >= 80)
        grade = 'A';
    else if (average >= 70)
        grade = 'B';
    else if (average >= 60)
        grade = 'C';
    else if (average >= 50)
        grade = 'D';
    else
        grade = 'F';
    
    printf("\n========== Student Report ==========\n");
    printf("Name         : %s\n", s.name);
    printf("ID           : %d\n", s.id);
    printf("Total Marks  : %.2f\n", total);
    printf("Average Marks: %.2f\n", average);
    printf("Grade        : %c\n", grade);
    printf("=====================================\n");
    return 0;
}