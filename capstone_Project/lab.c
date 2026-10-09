#include <stdio.h>
void forward(int front,int right,int left ,int back){
if(front!=0 && front !=1 ||right!=0 && right !=1 || left!=0 && left !=1 ||back!=0 && back !=1){
printf("invalid! \n");
 
}
else if(front==0){
printf("move forward\n");
}
else{
printf(" blocked\n");
printf("stop\n");
}
}
void turn_left(int front,int right,int left ,int back){
if(front!=0 && front !=1 ||right!=0 && right !=1 || left!=0 && left !=1 ||back!=0 && back !=1)
{
printf("invalid! \n");
 
}
else if(left==0)
{
printf("turn left\n");
}
else{
printf(" blocked\n");
printf("stop\n");
}}
void turn_right(int front,int right,int left ,int back){
if(front!=0 && front !=1 ||right!=0 && right !=1 || left!=0 && left !=1 ||back!=0 && back !=1)
{
printf("invalid! \n");
 
}
else if(right==0){
printf("turn right\n");
}
else{
printf(" blocked\n");
printf("stop\n");
}}
void backward(int front,int right,int left ,int back){
if(front!=0 && front !=1 ||right!=0 && right !=1 || left!=0 && left !=1 ||back!=0 && back !=1)
{
printf("invalid! \n");
 
}
else if(back==0)
{
printf("move backward\n");
}
else{
printf(" blocked\n");
printf("stop\n");
}}
int main()
{
int front,right,left,back,choice;
while(1){
printf("----UGV----\n");
printf("1. forward\n 2. right turn\n 3. left turn\n 4. backward\n");
printf("enter your direction: ");
scanf("%d",&choice);
if(choice<1 || choice>4){
printf("invalid\n");
continue;
}
 
printf("---sensor data---\n");
printf("enter data for front(0/1): ");
scanf("%d",&front);
printf("enter data for right(0/1): ");
scanf("%d",&right);
printf("enter data for left(0/1): ");
scanf("%d",&left);
printf("enter data for back (0/1): ");
scanf("%d",&back);
}
if(choice==1){
forward(front,right,left,back);
 
}
else if(choice==3){
turn_left(front,right,left,back);
}
else if(choice==2){
turn_right(front,right,left,back);
}
else if(choice==4){
backward(front,right,left,back);
}
return 0;
}