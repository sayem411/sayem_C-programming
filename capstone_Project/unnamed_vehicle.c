#include<stdio.h>

void forward(int front,int left,int right,int back)
{
    if(front != 0 && front != 1 || left != 0 && left != 1 || right !=0 && right != 1 || back!=0 && back!=1)
    {
        printf("\nInvalid sensor value.");
    }
    else if(front == 0)
    {
        printf("\n Move forward.");
    }
    else if(front ==1)
    {
        printf("\nFront direction is blocked.");
    }
}
void left_turn(int front,int left,int right,int back)
{
    if(front != 0 && front != 1 || left != 0 && left != 1 || right !=0 && right != 1 || back!=0 && back!=1)
    {
        printf("\nInvalid sensor value.");
    }
    else if(left == 0)
    {
        printf("\n Turn Left.");
    }
    else if(left ==1)
    {
        printf("\nLeft direction is blocked.");
    }
}
void right_turn(int front,int left,int right,int back)
{
    if(front != 0 && front != 1 || left != 0 && left != 1 || right !=0 && right != 1 || back!=0 && back!=1)
    {
        printf("\nInvalid sensor value.");
    }
    else if(right == 0)
    {
        printf("\n Turn Right.");
    }
    else if(right ==1)
    {
        printf("\nRight direction is blocked.");
    }
}
void backward(int front,int left,int right,int back)
{
    if(front != 0 && front != 1 || left != 0 && left != 1 || right !=0 && right != 1 || back!=0 && back!=1)
    {
        printf("\nInvalid sensor value.");
    }
    else if(back == 0)
    {
        printf("\n Move backward.");
    }
    else if(back ==1)
    {
        printf("\nBack direction is blocked.");
    }
}

int main()
{
    int front, left, right, back, n;
    while(1){
    printf("\n------Unmanned Vehicle--------\n");
    printf("\n1. Forward\n2. Left\n3. Right\n4. Backward");

    printf("\nEnter your direction: ");
    scanf("%d",&n);

    if(n<1 || n>4)
    {
        printf("\nInvalid direction");
        continue;
    }


    printf("\n-----Sensor Value--------\n");
    printf("Enter front sensor value(0=clear, 1=block): ");
    scanf("%d",&front);
    printf("Enter left sensor value e(0=clear, 1=block): ");
    scanf("%d",&left);
    printf("Enter right sensor value(0=clear, 1=block): ");
    scanf("%d",&right);
    printf("Enter back sensor value(0=clear, 1=block): ");
    scanf("%d",&back);
}
    if(n==1)
    {
        forward(front,left,right,back);
    }
    else if(n==2)
    {
        left_turn(front,left,right,back);
    }
    else if(n==3)
    {
        right_turn(front,left,right,back);
    }
    else if(n==4)
    {
        backward(front,left,right,back);
    }

    return 0;
}