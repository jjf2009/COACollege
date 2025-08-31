#include <stdio.h>
#include <string.h>

void one_complement(char[], char[], int);
void two_complement(char[], char[], int);
void add_binary(char[], char[], char[], int);


int main()
{
    char b1[100], b2[100], sum[100], diff[100], one_comp[100], two_comp[100];
    printf("Enter First Number in Binary for Addition: ");
    scanf("%s", b1);
    printf("Enter Second Number in Binary for Addition: ");
    scanf("%s", b2);

    int n = strlen(b1); // assume both are same length

    // Addition
    add_binary(b1, b2, sum, n);

    printf("\n--- Results (Signed Binary Addition (Two’s Complement), %d-bit) ---\n", n);
    printf("%s + %s = %s\n",b1,b2,sum);

    printf("Enter First Number in Binary for Subtraction : ");
    scanf("%s", b1);
    printf("Enter Second Number in Binary for Subtraction: ");
    scanf("%s", b2);

    n = strlen(b1);

    // One's and Two's complement of b2
    one_complement(b2, one_comp, n);
    two_complement(b2, two_comp, n);

    printf("\nOriginal Binary : %s\n", b2);
    printf("1's Complement : %s\n", one_comp);
    printf("2's Complement : %s\n", two_comp);


    // Subtraction → b1 + (two’s complement of b2)
    char two_comp_b2[100];
    two_complement(b2, two_comp_b2, n);
    add_binary(b1, two_comp_b2, diff, n);
    printf("\n--- Results (Signed Binary Subtraction (Two’s Complement), %d-bit) ---\n", n);
    printf("%s - %s = %s \n",b1,two_comp_b2,diff);
    return 0;
}

void one_complement(char bin[], char result[], int n)
{
    for (int i = 0; i < n; i++)
        result[i] = (bin[i] == '1') ? '0' : '1';
    result[n] = '\0';
}

void two_complement(char bin[], char result[], int n)
{
    one_complement(bin, result, n);
    int carry = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int bit = result[i] - '0';
        int sum = bit + carry;
        result[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
    result[n] = '\0';
}

void add_binary(char bin1[], char bin2[], char result[], int n)
{
    int carry = 0;
    result[n] = '\0';
    for (int i = n - 1; i >= 0; i--)
    {
        int bit1 = bin1[i] - '0';
        int bit2 = bin2[i] - '0';
        int sum = bit1 + bit2 + carry;
        result[i] = (sum % 2) + '0';
        carry = sum / 2;
    }

}


