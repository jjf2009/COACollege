#include <stdio.h>
#include <string.h>

void twocompleted(char m[], int n) {
    for (int i = 0; i < n; i++)
        m[i] = (m[i] == '1') ? '0' : '1';

    int carry = 1;
    for (int i = n - 1; i >= 0; i--) {
        int bit1 = m[i] - '0';
        int sum = bit1 + carry;
        m[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
}

void shift_right(char a[], char q[], char *q_, int n) {
    *q_ = q[n - 1];       // Q0 stored into q_
    char lastA = a[n - 1];

    for (int i = n - 1; i > 0; i--)
        q[i] = q[i - 1];
    q[0] = lastA;

    for (int i = n - 1; i > 0; i--)
        a[i] = a[i - 1];

    a[0] = a[1];          // arithmetic shift -> keep sign bit of A
}

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

void signed_binary_multiply(char m[], char q[], int count) {
    char a[32], m_twocomp[32];
    char q_ = '0';
    int n = count;

    for (int i = 0; i < n; i++) {
        a[i] = '0';
        m_twocomp[i] = m[i];
    }
    a[n] = '\0';
    q[n] = '\0';
    m_twocomp[n] = '\0';

    twocompleted(m_twocomp, n);
printf("\nA\tQ\tQ_1\tM\tOperation\n");
printf("%s\t%s\t%c\t%s\tInitial\n", a, q, q_, m);

for (int i = 0; i < n; i++) {
    if (q[n - 1] == '0' && q_ == '1') {
        binary_add(a, m, n);
        printf("%s\t%s\t%c\t%s\tA <- A + M\n", a, q, q_, m);
    } else if (q[n - 1] == '1' && q_ == '0') {
        binary_add(a, m_twocomp, n);
        printf("%s\t%s\t%c\t%s\tA <- A + (-M)\n", a, q, q_, m);
    }

    shift_right(a, q, &q_, n);
    printf("%s\t%s\t%c\t%s\tShift\n", a, q, q_, m);
}

printf("\nFinal Result = %s%s\n", a, q);


    printf("\nFinal Result = %s%s\n", a, q);
}

int main() {
    int count;
    printf("Enter Number of Bits: ");
    scanf("%d", &count);

    char m[32], q[32];

    printf("Enter The Multiplicand: ");
    scanf("%s", m);

    printf("Enter The Multiplier: ");
    scanf("%s", q);

    signed_binary_multiply(m, q, count);
}
