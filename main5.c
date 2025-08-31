// Implement a C program to perform division of two unsigned binary numbers using restoring division algorithm. 
#include<stdio.h>
#include<string.h>

void str_to_bin(const char *str, int *bin) {
    for (int i = 0; i < 4; i++)
        bin[i] = str[i] - '0';
}

void print_bin(int *bin, int n) {
    for (int i = 0; i < n; i++)
        printf("%d", bin[i]);
}

void left_shift(int *a, int *q, int n) {
    int msb_q = q[0]; 
    // shift Q
    for (int i = 0; i<=n-1; i++)
        q[i] = q[i+1];

        q[n-1]=0;

    // shift A
    for (int i =1; i > 0; i++)
        a[i] = a[i - 1];
        a[n-1]=msb_q;

}








int main(){
    int M[4]={0}, Q[4]={0}, A[4]={0},n=4;
    char mstr[9], qstr[9];
    printf("Enter Divisor Number in Binary:");
    scanf("%8s", mstr);
    printf("Enter Dividend Number in Binary:");
    scanf("%8s", qstr);

    str_to_bin(mstr, M);
    str_to_bin(qstr, Q);

    printf("\nInitial State:\nA = "); 
    print_bin(A, n);
    printf(" Q = ");
    print_bin(Q, n);
    printf("\n");
    
      for (int step = 0; step < n; step++) {
        printf(" Qbefore =");
        print_bin(Q, n);
        left_shift(A, Q, n);
        // if (Q[n - 1] == 1 && Q_1 == 0) {
        //     // A = A - M → A + (-M)
        //     add_bin(A, M_comp, A, n);
        //     printf("\nStep %d: A = A - M\n", step + 1);
        // } else if (Q[n - 1] == 0 && Q_1 == 1) {
        //     // A = A + M
        //     add_bin(A, M, A, n);
        //     printf("\nStep %d: A = A + M\n", step + 1);
        // }
        printf("\n");
        // printf("After shift %d:\nA = ", step + 1);
        // print_bin(A, n);
        printf(" Q = ");
        print_bin(Q, n);
         printf("\n");
    }

    // printf("\nFinal Product (A||Q): ");
    // print_bin(A, n);
    // print_bin(Q, n);
    // printf("\n");

    return 0;

}