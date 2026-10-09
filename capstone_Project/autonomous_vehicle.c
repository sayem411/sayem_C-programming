#include<stdio.h>

int main()
{
    int front, left, right;
    printf("\n-------Autonomous Vehicle----------\n");
    printf("\nEnter front sensor value(0=Clear, 1=Block): ");
    scanf("%d",&front);
    printf("\nEnter left sensor value(0=Clear, 1=Block): ");
    scanf("%d",&left);
    printf("\nEnter right sensor value(0=Clear, 1=Block): ");
    scanf("%d",&right);
    
    if(front != 0 && front != 1 || left != 0 && left!= 1 || right != 0 && right != 1)
    {
        printf("\nInvalid sensor value");
        return 0;
    }
    else if(front == 0)
    {
        printf("\nMove forward");
    }
    else if(front == 1 && left == 0)
    {
        printf("\nTurn left");
    }
    else if(front == 1 && left == 1 && right == 0)
    {
        printf("\nTurn right");
    }
    else
    {
        printf("\nAll directions are blocked");
        printf("\nStops");
    }
}