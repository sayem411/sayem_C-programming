#include <stdio.h>

int main() {
    int arif, fahmid, joy;
    printf("Enter ages of Arif, Fahmid, and Joy: ");
    scanf("%d %d %d", &arif, &fahmid, &joy);

    if (arif < fahmid && arif < joy)
        printf("Arif is the youngest.\n");
    else if (fahmid < arif && fahmid < joy)
        printf("Fahmid is the youngest.\n");
    else
        printf("Joy is the youngest.\n");
    return 0;
}