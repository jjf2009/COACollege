#include <stdio.h>

void binary_add(char a[], char m[], int n) {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';
        int bit2 = m[i] - '0';
        int sum = bit1 + bit2 + carry;
        a[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
}

void twocomplement(char m[], int n) {
    for (int i = 0; i < n; i++)
        m[i] = (m[i] == '1') ? '0' : '1';

    int carry = 1;
    for (int i = n - 1; i >= 0; i--) {
        int bit = m[i] - '0';
        int sum = bit + carry;
        m[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
}

void shift_left(char a[], char q[], int n) {
    char msbQ = q[0];

    for (int i = 0; i < n - 1; i++)
        a[i] = a[i + 1];
    a[n - 1] = msbQ;

    for (int i = 0; i < n - 1; i++)
        q[i] = q[i + 1];

    // last bit of Q set later depending on subtract result
}

void unsigned_binary_division(char m[], char q[], int count) {
    int n = count;

    char a[32];
    char m_twocomp[32];

    for (int i = 0; i < n; i++) {
        a[i] = '0';
        m_twocomp[i] = m[i];
    }

    a[n] = '\0';
    q[n] = '\0';
    m_twocomp[n] = '\0';

    twocomplement(m_twocomp, n);

    printf("\nCycle | A\t\tQ\t\tOperation\n");
    printf("-----------------------------------------------\n");
    printf("Init  | %s\t%s\tInitial Load\n", a, q);

    for (int i = 0; i < n; i++) {

        // SHIFT
        shift_left(a, q, n);
        printf("%d     | %s\t%s\tShift Left\n", i + 1, a, q);

        // A = A - M using 2's complement
        binary_add(a, m_twocomp, n);
        printf("      | %s\t%s\tA = A - M\n", a, q);

        if (a[0] == '1') {
            binary_add(a, m, n); // restore
            q[n - 1] = '0';
            printf("      | %s\t%s\tRestore -> Q[n-1]=0\n", a, q);
        } else {
            q[n - 1] = '1';
            printf("      | %s\t%s\tSet Q[n-1]=1\n", a, q);
        }
    }

    printf("\n-----------------------------------------------\n");
    printf("Final Quotient : %s\nFinal Remainder: %s\n", q, a);
}


int main() {
    int count;
    printf("Enter Number of Bits: ");
    scanf("%d", &count);

    char m[32], q[32];

    printf("Enter Dividend: ");
    scanf("%s", q);

    printf("Enter Divisor: ");
    scanf("%s", m);

    unsigned_binary_division(m, q, count);
    return 0;
}
