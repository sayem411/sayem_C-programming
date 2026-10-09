#include <stdio.h>
struct product {
    int ID;
    char name[50];
    float price;
    float quantity;
    float total;
};
int main() {
    int i,n,max=0;
    float inventory=0; 
    printf("Enter Number of products: ");
    scanf("%d",&n);
    struct product p[n];
    for (i=0;i<n;i++) {
        printf("Name:");
        scanf("%s",p[i].name);

        printf("ID:"); 
        scanf("%d",&p[i].ID);

        printf("Price:");
            scanf("%f",&p[i].price);

        printf("Quantity:");
         scanf("%f",&p[i].quantity);
        p[i].total=p[i].price*p[i].quantity;
        
        inventory+=p[i].total;      
        if (p[i].total>p[max].total) {  
            max=i;
        }
    }
    for (i=0;i<n;i++){
    printf("Name        :%s\n",p[i].name);
    printf("ID          :%d\n",p[i].ID);
    printf("Price       :%.2f\n",p[i].price);
    printf("Quality     :%.2f\n",p[i].quantity);
    printf("Total Value :%.2f\n",p[i].total);
    }
    printf("Total Inventory Value : %.2f\n", inventory);
    printf("Highest Value Product : %.2f\n",p[max].total);
    return 0;
}