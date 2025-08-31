#include <stdio.h>
#include <string.h>

// Convert string "10101010" → int array
void str_to_bin(const char *str, int *bin) {
    for (int i = 0; i < 8; i++)
        bin[i] = str[i] - '0';
}

// Print binary array
void print_bin(int *bin, int n) {
    for (int i = 0; i < n; i++)
        printf("%d", bin[i]);
}

// One’s complement
void ones_comp(int *bin, int *res, int n) {
    for (int i = 0; i < n; i++)
        res[i] = bin[i] ? 0 : 1;
}

// Add two binary numbers (2’s complement safe)
void add_bin(int *a, int *b, int *res, int n) {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        res[i] = sum % 2;
        carry = sum / 2;
    }
}

// Two’s complement
void twos_comp(int *bin, int *res, int n) {
    int temp[8];
    ones_comp(bin, temp, n);

    int one[8] = {0};
    one[n - 1] = 1;

    add_bin(temp, one, res, n);
}

// Arithmetic Right Shift (A,Q,Q-1)
void right_shift(int *a, int *q, int *q1, int n) {
    int msb_a = a[0];  // preserve sign bit of A
    int lsb_q = q[n - 1];

    *q1 = lsb_q;

    // shift Q
    for (int i = n - 1; i > 0; i--)
        q[i] = q[i - 1];
    q[0] = a[n - 1];

    // shift A
    for (int i = n - 1; i > 0; i--)
        a[i] = a[i - 1];
    a[0] = msb_a; // sign extend
}

int main() {
    char mstr[9], qstr[9];
    int M[8], Q[8], A[8] = {0}, Q_1 = 0;
    int M_comp[8], temp[8];
    int n = 8;

    printf("Enter Multiplicand (8 bits, 2's complement): ");
    scanf("%8s", mstr);
    printf("Enter Multiplier (8 bits, 2's complement): ");
    scanf("%8s", qstr);

    str_to_bin(mstr, M);
    str_to_bin(qstr, Q);

    twos_comp(M, M_comp, n); // Precompute -M

    printf("\nInitial State:\nA = "); print_bin(A, n);
    printf(" Q = "); print_bin(Q, n);
    printf(" Q-1 = %d\n", Q_1);

    for (int step = 0; step < n; step++) {
        // Step 1: Check Q0 and Q-1
        if (Q[n - 1] == 1 && Q_1 == 0) {
            // A = A - M → A + (-M)
            add_bin(A, M_comp, A, n);
            printf("\nStep %d: A = A - M\n", step + 1);
        } else if (Q[n - 1] == 0 && Q_1 == 1) {
            // A = A + M
            add_bin(A, M, A, n);
            printf("\nStep %d: A = A + M\n", step + 1);
        }

        // Step 2: Arithmetic Right Shift (A,Q,Q-1)
        right_shift(A, Q, &Q_1, n);

        printf("After shift %d:\nA = ", step + 1);
        print_bin(A, n);
        printf(" Q = ");
        print_bin(Q, n);
        printf(" Q-1 = %d\n", Q_1);
    }

    printf("\nFinal Product (A||Q): ");
    print_bin(A, n);
    print_bin(Q, n);
    printf("\n");

    return 0;
}
