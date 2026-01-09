#include <stdio.h>
#include <string.h>

void binary_add(int *carry, char a[], char m[], int n) {
    *carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';     // fixed: use '0' instead of "0"
        int bit2 = m[i] - '0';
        int sum = bit1 + bit2 + *carry;
        a[i] = (sum % 2) + '0';    // fixed: convert back to char
        *carry = sum / 2;
    }
}

void shift_right(int *carry, char a[], char q[], int n) {
    // right shift A
     char lastA = a[n - 1];
    for (int i = n-1; i > 0; i--)
        a[i] = a[i -1];
    a[0] = *carry+'0';               // bring MSB of Q into LSB of A

    // right shift Q
    for (int i = n-1; i > 0; i--)
        q[i] = q[i - 1];
    q[0] =lastA ;                // new LSB 0

    *carry = 0;                 // update carry
}

void binary_multiply(char m[], char q[], int count) {
    char a[32] = {0};              // static size for simplicity
    int n = count;
    int carry = 0;

    for (int i = 0; i < count; i++)
        a[i] = '0';
    a[n+1]='\0';
    printf("\nC\tA\tQ\tM\tOperation\n");
    printf("%d\t%s\t%s\t%s\tInitial Values\n", carry, a, q, m);

    for (int i = 0; i < count; i++) {
        if (q[n-1] == '1')  {// fixed comparison
            binary_add(&carry, a, m, n);
         printf("%d\t%s\t%s\t%s\tA <- A + M\n", carry, a, q, m);
        }
        shift_right(&carry, a, q, n);
        printf("%d\t%s\t%s\t%s\tShift Right\n\n", carry, a, q, m);
    }

    printf("\nAnswer: A = %s, Q = %s\n", a, q);
}

int main() {
    int count;
    printf("Enter Number of Bits: ");
    scanf("%d", &count);           // fixed: must pass &

    char m[32], q[32];

    printf("Enter The Multiplicand: ");
    scanf("%s", m);

    printf("Enter The Multiplier: ");
    scanf("%s", q);

    binary_multiply(m, q, count);
}
