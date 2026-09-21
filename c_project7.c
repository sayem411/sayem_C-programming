#include <stdio.h>
#define MAX_LENGTH 100
 
int main()
{
    int data[MAX_LENGTH];
    int length = 0;
    int value, index;
    int input;
 
    do {
        printf("Menu: \n\n");
        printf("1. Add\n");
        printf("2. Insert\n");
        printf("3. Edit\n");
        printf("4. Delete\n");
        printf("5. Display\n");
        printf("6. Clear\n");
        printf("0. Exit\n\n");
 
        printf("Enter a menu: ");
        scanf("%d", &input);
 
        printf("_____________Result___________\n");
        switch (input) {
 
        case 0:
            break;
 
        case 1: 
            if (length >= MAX_LENGTH) {
                printf("Array is full, cannot add.\n");
                break;
            }
            printf("Please enter an integer value: ");
            scanf("%d", &value);
            data[length] = value;
            printf("%d inserted at index %d\n", value, length);
            length++;
            break;
 
        case 2: 
            if (length >= MAX_LENGTH) {
                printf("Array is full, cannot insert.\n");
                break;
            }
            printf("Please enter an integer value: ");
            scanf("%d", &value);
            printf("Please enter an index between 0-%d: ", length);
            scanf("%d", &index);
            if (index < 0 || index > length) {
                printf("Invalid index.\n");
                break;
            }
            for (int i = length; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = value;
            length++;
            printf("%d inserted at index %d\n", value, index);
            break;
 
        case 3: 
            if (length == 0) {
                printf("There is no data\n");
                break;
            }
            printf("Please enter an index between 0-%d: ", length - 1);
            scanf("%d", &index);
            if (index < 0 || index >= length) {
                printf("Invalid index.\n");
                break;
            }
            printf("Please enter a new integer value: ");
            scanf("%d", &value);
            data[index] = value;
            printf("Data updated at index %d to %d\n", index, value);
            break;
 
        case 4: 
            if (length == 0) {
                printf("There is no data\n");
                break;
            }
            printf("Please enter an index between 0-%d: ", length - 1);
            scanf("%d", &index);
            if (index < 0 || index >= length) {
                printf("Invalid index.\n");
                break;
            }
            {
                int dv = data[index];
                for (int i = index; i < length - 1; i++) {
                    data[i] = data[i + 1];
                }
                data[length - 1] = 0;
                length--;
                printf("Deleted value %d at index %d\n", dv, index);
            }
            break;
 
        case 5: 
            if (length == 0) {
                printf("There is no data\n");
            } else {
                printf("DATA: ");
                for (int i = 0; i < length; i++) {
                    printf("%d\t", data[i]);
                }
                printf("\n");
            }
            break;
 
        case 6: 
            for (int i = 0; i < length; i++) {
                data[i] = 0;
            }
            length = 0;
            printf("Data cleared\n");
            break;
 
        default:
            printf("Invalid input\n");
            break;
        }
        printf("__Result End\n");
 
    } while (input != 0);
 
    return 0;
}
 
