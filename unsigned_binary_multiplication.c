#include <stdio.h>
#include <string.h>

int add_binary(char[], char[], int);
void shift_right(char[], char[], int, int *);
void multiply(char[], char[], int);

int add_binary(char a[], char m[], int n)
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
    return carry;
}

void shift_right(char a[], char q[], int n, int *c)
{

    char lastA = a[n - 1];

    for (int i = n - 1; i > 0; i--)
    {
        q[i] = q[i - 1];
    }
    q[0] = lastA; 

    for (int i = n - 1; i > 0; i--)
    {
        a[i] = a[i - 1];
    }
    a[0] = (*c) + '0'; 

    *c = 0; 
}
void multiply(char m[], char q[], int n)
{
    char a[n + 1]; 
    int c = 0;   
    for (int i = 0; i < n; i++)
        a[i] = '0';
    a[n] = '\0';

    printf("\nC\tA\tQ\tM\tOperation\n");
    printf("%d\t%s\t%s\t%s\tInitial Values\n", c, a, q, m);

    for (int step = 0; step < n; step++)
    {
        if (q[n - 1] == '1')
        {
            c = add_binary(a, m, n);
            printf("%d\t%s\t%s\t%s\tA <- A + M\n", c, a, q, m);
        }
        shift_right(a, q, n, &c);
        printf("%d\t%s\t%s\t%s\tShift Right\n\n", c, a, q, m);
    }

    printf("Final Product: %s%s\n", a, q);
}

int main()
{
    int n;
    printf("Enter Number of Bits: ");
    scanf("%d", &n);

    char b1[n + 1], b2[n + 1]; 
    printf("Enter First Number (Unsigned Binary): ");
    scanf("%s", b1);
    printf("Enter Second Number (Unsigned Binary): ");
    scanf("%s", b2);

    multiply(b1, b2, n);

    return 0;
}
