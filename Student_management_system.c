#include <stdio.h>       //stander input output lib
#include <stdlib.h>      //stander liberary used to handel memory allocation etc.
#include <string.h>
#define MAX_STUDENTS 100

struct student
{
    char id[20];
	char name[50];
	char dept[50];
	int batch;
	int age;
	float cgpa;

};

// created students array of datatype student
struct student students[MAX_STUDENTS];
int studentCount = 0;

void choice()
{
    printf("Press y for menu, n for exit: ");
    char choice;
    scanf("%c", &choice);
    if (choice == 'y')
    {
        system("cls");
        //printf("\e[1;1H\e[2J");

    }
    else if (choice == 'n')
    {
        printf("Thank You");
        exit(0);
    }
}

void addStudent()
{
    if (studentCount == MAX_STUDENTS)
    {
        printf("Error: Maximum limit of students reached.\n");
        return;
    }

    struct student newStudent;
    getchar();
    printf("Enter Student ID: ");
    gets(newStudent.id);
    printf("Enter Student Name: ");
    gets(newStudent.name);
    printf("Enter Department Name: ");
    gets(newStudent.dept);
    printf("Enter Batch Number: ");
    scanf("%d", &newStudent.batch);
    printf("Enter Student Age: ");
    scanf("%d", &newStudent.age);
    printf("Enter Student CGPA: ");
    scanf("%f", &newStudent.cgpa);
    students[studentCount++] = newStudent;
    printf("Student added successfully.\n");
    getchar();
    choice();
}

void displayStudents()
{
    if (studentCount == 0)
    {
        printf("No students to display.\n");
        return;
    }

    //printf("ID\t\t\tName\t\t\tDepartment\tBatch\tAge\tCgpa\n");
    printf("%-12s%-30s%-13s%-10s%-10s%-10.2s\n", "ID", "Name", "Department", "Batch", "Age", "CGPA");
    for (int i = 0; i < studentCount; i++)
    {
        printf("%-12s%-30s%-13s%-10d%-10d%-10.2f\n",
               students[i].id, students[i].name, students[i].dept, students[i].batch, students[i].age, students[i].cgpa);
    }

    getchar();
    choice();
}

void searchStudent()
{
    int flag = 0;
    if (studentCount == 0)
    {
        printf("No students to search.\n");
        return;
    }

     char search_id[20];
     printf("Enter student ID to search: ");
     getchar();
     gets(search_id);

    for (int i = 0; i < studentCount; i++)
    {

        if (strcmp(students[i].id,search_id)== 0)
        {

            printf("Match Found!!!!\n");
            flag = 1;
            printf("%-12s%-30s%-13s%-10s%-10s%-10.2s\n", "ID", "Name", "Department", "Batch", "Age", "CGPA");
            printf("%-12s%-30s%-13s%-10d%-10d%-10.2f\n",students[i].id, students[i].name, students[i].dept, students[i].batch, students[i].age, students[i].cgpa);
            break;
        }
    }
    if (flag == 0)
    {
        printf("Student not found.\n");
    }
    choice();
}


void updateStudent()
{
    char search_id[20];
    int ch;
    printf("Enter student ID to Update: ");
    getchar();
    gets(search_id);
    int flag = 0;
    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id,search_id) == 0)
        {
        printf("What do you want to update?\n1. Student ID\n2. Student Name\n3. Department Name\n4. Batch Number\n5. Student Age\n6. Student CGPA\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        getchar();
        switch(ch)
        {
            case 1:
                printf("Enter Student ID: ");
                gets(students[i].id);
                break;
            case 2:
                printf("Enter Student Name:  ");
                gets(students[i].name);
                break;
            case 3:
                printf("Enter Department Name: ");
                gets(students[i].dept);
                break;
            case 4:
                printf("Enter Batch Number: ");
                scanf("%d", &students[i].batch);
                break;
            case 5:
                printf("Enter Student Age: ");
                scanf("%d", &students[i].age);
                break;
            case 6:
                printf("Enter Student CGPA: ");
                scanf("%f", &students[i].cgpa);
                break;
            default:
            	printf("Invalid choice. Try again.\n");
        }
        flag=1;
        printf("Student information updated successfully!\n");
        break;
        }
    }
    if (flag == 0)
    {
        printf("Student not found\n");
    }

    //getchar();
    choice();

}

void deleteStudent()
{
    int i, j,delete_id;
    printf("\nEnter Student Id to Delete:");
    scanf("%d",&delete_id);
    for (i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].id,delete_id) == 0)
        {
            for (j = i; j < studentCount - 1; j++)
            {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student with roll number %d deleted successfully!\n", delete_id);
            return;
        }
        else
        {
            printf("Not Found\n");
        }
    }

    getchar();
    choice();

}

void uplodeFile()
{
  FILE *fp;
  int i;
  fp = fopen("students.txt", "a");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
  for (i = 0; i < studentCount; i++)
  {
    fprintf(fp, "%s,%s,%s,%d,%d,%.2f\n",students[i].id, students[i].name, students[i].dept, students[i].batch, students[i].age, students[i].cgpa);
  }
  fclose(fp);

  printf("Data uploaded to file successfully!\n");

  getchar();
  choice();

}


void downloadFile()
{
    FILE *fp;
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    studentCount = 0;
    while (studentCount < MAX_STUDENTS && fscanf(fp, "%[^,] ,%[^,],%[^,],%d,%d,%f\n",
            students[studentCount].id, students[studentCount].name, students[studentCount].dept, &students[studentCount].batch, &students[studentCount].age, &students[studentCount].cgpa) != EOF) {
        studentCount++;
    }

    fclose(fp);
    printf("Students downloaded from file successfully!\n");

    getchar();
    choice();
    /*printf("Press y for menu, n for exit: ");
    char choice;
    scanf("%c", &choice);
    if (choice == 'y')
    {
        system("cls");
        //printf("\e[1;1H\e[2J");

    }
    else if (choice == 'n')
    {
        printf("Thank You");
        exit(0);
    }*/

}




void main()
{
	int choice;
	while(1)
	{
    	//printf("\e[1;1H\e[2J");
    	printf("\n=============================\n");
    	printf("\n= Student Management System =\n");
    	printf("\n=============================\n");
    	printf("1. Add Student\n");
    	printf("2. Display Students\n");
    	printf("3. Search Student\n");
    	printf("4. Update Student\n");
    	printf("5. Delete Student\n");
    	printf("6. Uplode/append data to txt file\n");
    	printf("7. Downlode/read data from txt file\n");
    	printf("0. Exit\n");
    	printf("\n=============================\n");
    	printf("Enter your choice: ");
    	scanf("%d", &choice);
    	switch (choice)
    	{
        	case 1:
            	addStudent();
            	break;
        	case 2:
            	displayStudents();
            	break;
        	case 3:
            	searchStudent();
            	break;
        	case 4:
            	updateStudent();
             	break;
        	case 5:
              	deleteStudent();
              	break;
        	case 6:
            	uplodeFile();
             	break;
        	case 7:
            	downloadFile();
            	break;
        	case 0:
            	printf("Thank You");
            	exit(0);
        	default:
            	printf("Invalid choice. Try again.\n");
            	break;
    	}
	}
}
