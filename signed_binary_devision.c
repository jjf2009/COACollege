#include <stdio.h>
#include <string.h>

void add_binary(char[], char[], int);
void twos_complement(char[], char[], int);
void shift_right(char[], char[], int *, int);
void multiply(char[], char[], int);


void add_binary(char a[], char m[], int n)
{
    int carry = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int bit1 = a[i] - '0';
        int bit2 = m[i] - '0';
        int sum = bit1 + bit2 + carry;
        a[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
}

void twos_complement(char in[], char out[], int n)
{
    char one[n + 1];
    strcpy(out, in);

    for (int i = 0; i < n; i++)
        out[i] = (out[i] == '0') ? '1' : '0';

    for (int i = 0; i < n; i++)
        one[i] = '0';
    one[n - 1] = '1';
    one[n] = '\0';

    add_binary(out, one, n);
}

void shift_right(char a[], char q[], int *q_1, int n)
{
    char msbA = a[0];      
    char lsbQ = q[n - 1];   

    *q_1 = lsbQ - '0';      

    for (int i = n - 1; i > 0; i--)
        q[i] = q[i - 1];
    q[0] = a[n - 1];

    for (int i = n - 1; i > 0; i--)
        a[i] = a[i - 1];
    a[0] = msbA;
}
\
void divide(char m[], char q[], int n)
{
    char a[n + 1];
    char m_neg[n + 1]; 
    int q_1 = 0;

    for (int i = 0; i < n; i++)
        a[i] = '0';
    a[n] = '\0';

    twos_complement(m, m_neg, n);

    printf("\nA\tQ\tQ-1\tOperation\n");
    printf("%s\t%s\t%d\tInitial Values\n", a, q, q_1);

    for (int step = 0; step < n; step++)
    {
        if (q[n - 1] == '1' && q_1 == 0)
        {
            add_binary(a, m_neg, n);
            printf("%s\t%s\t%d\tA = A - M\n", a, q, q_1);
        }
        else if (q[n - 1] == '0' && q_1 == 1)
        {
            add_binary(a, m, n);
            printf("%s\t%s\t%d\tA = A + M\n", a, q, q_1);
        }
        else
        {
            printf("%s\t%s\t%d\tNo Operation\n", a, q, q_1);
        }

        // Shift Right
        shift_right(a, q, &q_1, n);
        printf("%s\t%s\t%d\tShift Right\n\n", a, q, q_1);
    }

    printf("Final Product: %s%s\n", a, q);
}

int main()
{
    int n = 4; 
    char m[n + 1], q[n + 1];

    printf("Enter Multiplicand (4-bit signed binary): ");
    scanf("%s", m);
    printf("Enter Multiplier (4-bit signed binary): ");
    scanf("%s", q);

    divide(m, q, n);

    return 0;
}
