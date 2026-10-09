#include <stdio.h>

int main() {
    int array[100], i, n, pos;

    printf("Enter number of elements in array: ");
    scanf("%d", &n);

    printf("Enter %d elements: \n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &array[i]);

    printf("Enter the position where you want to delete: ");
    scanf("%d", &pos);

    // ডিলিট করার লজিক: এলিমেন্টগুলোকে এক ঘর বামে সরানো
    for (i = pos - 1; i < n - 1; i++) {
        array[i] = array[i + 1];
    }

    n--; // অ্যারের সাইজ ১ কমিয়ে দেওয়া হলো

    printf("Resultant array is: \n");
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    return 0;
}