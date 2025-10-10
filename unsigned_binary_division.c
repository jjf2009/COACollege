#include <stdio.h>
#include <string.h>

int add_binary(char[], char[], int);
void twos_complement(char[], int);
void shift_left(char[], char[], int);
void divide(char[], char[], int);

int add_binary(char a[], char b[], int n)
{
    int carry = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int bit1 = a[i] - '0';
        int bit2 = b[i] - '0';
        int sum = bit1 + bit2 + carry;
        a[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
    return carry;
}

void twos_complement(char x[], int n)
{
    for (int i = 0; i < n; i++)
        x[i] = (x[i] == '0') ? '1' : '0';
    char one[n + 1];
    for (int i = 0; i < n - 1; i++)
        one[i] = '0';
    one[n - 1] = '1';
    one[n] = '\0';
    add_binary(x, one, n);
}
void shift_left(char a[], char q[], int n)
{
    char firstQ = q[0];

    for (int i = 0; i < n - 1; i++)
        a[i] = a[i + 1];
    a[n - 1] = firstQ;

    for (int i = 0; i < n - 1; i++)
        q[i] = q[i + 1];
    q[n - 1] = '0';
}
void divide(char m[], char q[], int n)
{
    char a[n + 1]; 
    char m_neg[n + 1]; 
    for (int i = 0; i < n; i++)
        a[i] = '0';
    a[n] = '\0';
    strcpy(m_neg, m);
    twos_complement(m_neg, n); 
    printf("\nA\tQ\tM\tOperation\n");
    printf("%s\t%s\t%s\tInitial Values\n", a, q, m);

    for (int step = 0; step < n; step++)
    {
        shift_left(a, q, n);
        printf("%s\t%s\t%s\tShift Left\n", a, q, m);

        add_binary(a, m_neg, n); 
        printf("%s\t%s\t%s\tA <- A - M\n", a, q, m);

        if (a[0] == '1') 
        {
            add_binary(a, m, n); 
            q[n - 1] = '0';
            printf("%s\t%s\t%s\tA negative → Restore, Q0=0\n", a, q, m);
        }
        else
        {
            q[n - 1] = '1';
            printf("%s\t%s\t%s\tA positive → Q0=1\n", a, q, m);
        }
    }

    printf("\nFinal Quotient (Q): %s\n", q);
    printf("Final Remainder (A): %s\n", a);
}

int main()
{
    int n;
    printf("Enter Number of Bits: ");
    scanf("%d", &n);

    char b1[n + 1], b2[n + 1]; 
    printf("Enter Dividend (Unsigned Binary): ");
    scanf("%s", b1);
    printf("Enter Divisor (Unsigned Binary): ");
    scanf("%s", b2);

    divide(b2, b1, n); 

    return 0;
}
