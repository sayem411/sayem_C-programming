#include <stdio.h>

/* ---------- 1. Full pyramid ---------- */
void full_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++)
         printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) 
        printf("*");
        printf("\n");
    }
}

/* ---------- 2. Inverted pyramid ---------- */
void inverted_pyramid(int n) {
    for (int i = n; i >= 1; i--) {
        for (int s = 1; s <= n - i; s++)
         printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++)
         printf("*");
        printf("\n");
    }
}

/* ---------- 3. Left half pyramid ---------- */
void left_half_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
         printf("* ");
        printf("\n");
    }
}

/* ---------- 4. Right half pyramid ---------- */
void right_half_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) 
        printf("  ");
        for (int j = 1; j <= i; j++) 
        printf("* ");
        printf("\n");
    }
}

/* ---------- 5. Inverted left half pyramid ---------- */
void inverted_left_half(int n) {
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) 
        printf("* ");
        printf("\n");
    }
}

/* ---------- 6. Inverted right half pyramid ---------- */
void inverted_right_half(int n) {
    for (int i = n; i >= 1; i--) {
        for (int s = 1; s <= n - i; s++)
         printf("  ");
        for (int j = 1; j <= i; j++)
         printf("* ");
        printf("\n");
    }
}

/* ---------- 7. Hollow pyramid ---------- */
void hollow_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++)
         printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (i == n || j == 1 || j == 2 * i - 1)
             printf("*");
            else printf(" ");
        }
        printf("\n");
    }
}

/* ---------- 8. Diamond ---------- */
void diamond(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }
}

/* ---------- 9. Hollow diamond ---------- */
void hollow_diamond(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (j == 1 || j == 2 * i - 1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) {
            if (j == 1 || j == 2 * i - 1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
}

/* ---------- 10. Number pyramid ---------- */
void number_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("%d", i % 10);
        printf("\n");
    }
}

/* ---------- 11. Palindromic number pyramid ---------- */
void palindrome_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= i; j++) printf("%d", j % 10);
        for (int j = i - 1; j >= 1; j--) printf("%d", j % 10);
        printf("\n");
    }
}

/* ---------- 12. Alphabet pyramid ---------- */
void alphabet_pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) printf(" ");
        for (int j = 1; j <= i; j++) printf("%c", 'A' + (j - 1) % 26);
        for (int j = i - 1; j >= 1; j--) printf("%c", 'A' + (j - 1) % 26);
        printf("\n");
    }
}

/* ---------- 13. Floyd's triangle ---------- */
void floyds_triangle(int n) {
    int num = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) printf("%d ", num++);
        printf("\n");
    }
}

/* ---------- 14. Pascal's triangle ---------- */
void pascals_triangle(int n) {
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < n - i - 1; s++) printf("  ");
        int c = 1;
        for (int j = 0; j <= i; j++) {
            printf("%4d", c);
            c = c * (i - j) / (j + 1);
        }
        printf("\n");
    }
}

/* ---------- main ---------- */
int main(void) {
    int n;
    printf("Enter number of rows: ");
    scanf("%d", &n);

    if (n < 1) {
    printf("Invalid input!\n");
    return 1;
}

    printf("\n1. Full pyramid\n"); 
    full_pyramid(n);

    printf("\n2. Inverted pyramid\n");           
    inverted_pyramid(n);

    printf("\n3. Left half pyramid\n");          
    left_half_pyramid(n);

    printf("\n4. Right half pyramid\n");         
    right_half_pyramid(n);

    printf("\n5. Inverted left half pyramid\n"); 
    inverted_left_half(n);

    printf("\n6. Inverted right half pyramid\n");
    inverted_right_half(n);

    printf("\n7. Hollow pyramid\n");             
    hollow_pyramid(n);

    printf("\n8. Diamond\n");                    
    diamond(n);

    printf("\n9. Hollow diamond\n");            
    hollow_diamond(n);

    printf("\n10. Number pyramid\n");            
    number_pyramid(n);
    
    printf("\n11. Palindromic number pyramid\n");
    palindrome_pyramid(n);
    
    printf("\n12. Alphabet pyramid\n");          
    alphabet_pyramid(n);

    printf("\n13. Floyd's triangle\n");          
    floyds_triangle(n);

    printf("\n14. Pascal's triangle\n");         
    pascals_triangle(n);

    return 0;
}