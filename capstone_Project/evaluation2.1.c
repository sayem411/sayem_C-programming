#include <stdio.h>

// Maximum
int maximum(int *p, int n)
{
    int i, max = p[0];

    for(i = 1; i < n; i++)
    {
        if(p[i] > max)
            max = p[i];
    }

    return max;
}

// Minimum
int minimum(int *p, int n)
{
    int i, min = p[0];

    for(i = 1; i < n; i++)
    {
        if(p[i] < min)
            min = p[i];
    }

    return min;
}

// Sorting
void sorting(int *p, int n)
{
    int i, j, temp;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-1-i; j++)
        {
            if(p[j] > p[j+1])
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main()
{
    int a[100], n, i;

    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("\nMaximum = %d", maximum(a, n));

    printf("\nMinimum = %d", minimum(a, n));

    sorting(a, n);

    printf("\nSorted Array: ");

    for(i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}