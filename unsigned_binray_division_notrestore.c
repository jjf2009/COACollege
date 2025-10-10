#include <stdio.h>
#include <string.h>

void add_binary(char a[], char b[], int n)
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
}

void twos_complement(char x[], int n)
{
    for (int i = 0; i < n; i++)
        x[i] = (x[i] == '0') ? '1' : '0';
    
    char one[n + 1];
    memset(one, '0', n);
    one[n - 1] = '1';
    one[n] = '\0';
    add_binary(x, one, n);
}

void shift_left(char a[], char q[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = a[i + 1];
    a[n] = q[0];
    
    for (int i = 0; i < n - 1; i++)
        q[i] = q[i + 1];
    q[n - 1] = '0';
}

void divide(char q[], char m[], int n)
{
    char a[n + 2];      
    char m_ext[n + 2];  
    char m_neg[n + 2]; 
    
    memset(a, '0', n + 1);
    a[n + 1] = '\0';
    
    m_ext[0] = '0';  
    strcpy(m_ext + 1, m);

    strcpy(m_neg, m_ext);
    twos_complement(m_neg, n + 1);
    
    printf("\nA\t\tQ\t\tM\t\tOperation\n");
    printf("%s\t%s\t%s\tInitial Values\n", a, q, m);
    
    for (int step = 0; step < n; step++)
    {
        shift_left(a, q, n);
        printf("%s\t%s\t%s\tLeft Shift\n", a, q, m);
        
        if (a[0] == '0') 
        {
            add_binary(a, m_neg, n + 1);
            printf("%s\t%s\t%s\tA>=0: A=A-M\n", a, q, m);
        }
        else 
        {
            add_binary(a, m_ext, n + 1);
            printf("%s\t%s\t%s\tA<0: A=A+M\n", a, q, m);
        }
        
        if (a[0] == '0')
            q[n - 1] = '1';
        else
            q[n - 1] = '0';
        
        printf("%s\t%s\t%s\tSet Q0=%c\n", a, q, m, q[n-1]);
    }

    if (a[0] == '1')
    {
        add_binary(a, m_ext, n + 1);
        printf("%s\t%s\t%s\tFinal Correction: A=A+M\n", a, q, m);
    }
    

    char remainder[n + 1];
    strcpy(remainder, a + 1);
    
    printf("\nFinal Quotient (Q): %s\n", q);
    printf("Final Remainder (A): %s\n", remainder);
}

int main()
{
    int n=8;
    
    char dividend[n + 1], divisor[n + 1];
    
    printf("Enter Dividend (Binary in 8 bit format ): ");
    scanf("%s", dividend);
    printf("Enter Divisor (Binary in 8 bit format): ");
    scanf("%s", divisor);
    
    divide(dividend, divisor, n);
    
    return 0;
}