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

int main(){
    struct Employee e={1,"Sayem",50000};

    printf("Initial salary: %.2f\n\n", e.salary);

  
    tryRaiseByValue(e, 10);

    printf("After tryRaiseByValue salary = %.2f\n", e.salary);

    giveRaise(&e, 20);
    printf("After giveRaiseBy salary = %.2f\n", e.salary);

    return 0;
}