#include <stdio.h>
#include <string.h>

void str_to_bin(char *str, int *bin, int n) {
    for (int i = 0; i < n; i++)
        bin[i] = str[i] - '0';
}

void print_bin(int *bin, int n) {
    for (int i = 0; i < n; i++)
        printf("%d", bin[i]);
}

void left_shift(int *A, int *Q, int n) {
    int carry = Q[0];

    // Shift A left
    for (int i = 0; i < n - 1; i++)
        A[i] = A[i + 1];
    A[n - 1] = carry;

    // Shift Q left
    for (int i = 0; i < n - 1; i++)
        Q[i] = Q[i + 1];
    Q[n - 1] = 0;
}

int compare(int *A, int *M, int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] > M[i]) return 1;
        if (A[i] < M[i]) return -1;
    }
    return 0;
}

void subtract(int *A, int *M, int n) {
    int borrow = 0;
    for (int i = n - 1; i >= 0; i--) {
        int diff = A[i] - M[i] - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else borrow = 0;
        A[i] = diff;
    }
}

void add(int *A, int *M, int n) {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

int main() {
    int M[4] = {0}, Q[4] = {0}, A[4] = {0}, n = 4;
    char mstr[9], qstr[9];

    printf("Enter Divisor (4-bit binary): ");
    scanf("%4s", mstr);
    printf("Enter Dividend (4-bit binary): ");
    scanf("%4s", qstr);

    str_to_bin(mstr, M, n);
    str_to_bin(qstr, Q, n);

    printf("\nInitial State:\nA = "); 
    print_bin(A, n);
    printf(" Q = ");
    print_bin(Q, n);
    printf("\n");

    for (int step = 0; step < n; step++) {
        left_shift(A, Q, n);

        // A = A - M
        subtract(A, M, n);

        if (compare(A, M, n) < 0) {

            add(A, M, n);
            Q[n - 1] = 0;
        } else {
            Q[n - 1] = 1;
        }

        printf("\nStep %d:\nA = ", step + 1);
        print_bin(A, n);
        printf(" Q = ");
        print_bin(Q, n);
    }

    printf("\n\nFinal Quotient (Q): ");
    print_bin(Q, n);
    printf("\nFinal Remainder (A): ");
    print_bin(A, n);
    printf("\n");

    return 0;
}
