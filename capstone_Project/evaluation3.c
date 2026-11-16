#include <stdio.h>
#include <string.h>

struct Employee {
    int   empId;
    char  name[31];  
    float salary;
};

void giveRaise(struct Employee *e, float percent)
{
    e->salary += e->salary * percent / 100.0f;
    printf("Inside giveRaiseBy salary = %.2f\n", e->salary);
}

void tryRaiseByValue(struct Employee e, float percent)
{
    e.salary += e.salary * percent / 100.0f;
    printf("Inside tryRaiseByValue salary salary = %.2f\n", e.salary);
}

int main(void)
{
    struct Employee emp={1,"Sayem",50000};

    printf("Initial salary: %.2f\n\n", emp.salary);

  
    tryRaiseByValue(emp, 10);

    printf("After tryRaiseByValue salary = %.2f\n", emp.salary);

    giveRaise(&emp, 20);
    printf("After giveRaise salary = %.2f\n", emp.salary);

    return 0;
}