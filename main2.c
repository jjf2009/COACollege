#include <stdio.h>
#include <math.h>
#include <string.h>

// Binary to Decimal
// int binaryToDecimal(int bin) {
//     int decimal = 0, base = 1;
//     while (bin > 0) {
//         int rem = bin % 10;
//         decimal += rem * base;
//         base *= 2;
//         bin /= 10;
//     }
//     return decimal;
// }

// Decimal to Binary
void decimalToBinary(char sign,int num) {
    int bin[32], i = 0;
    while(num>0) {
        bin[i++] = num % 2;
        num/= 2;
    }
    bin[i++]=sign=='-'? 1:0;
    printf("%d \n",bin[i]);
    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
    printf("\n");
    twoscomp(bin,i);
}

void twoscomp(int bin[],int i){
     onescomp( bin, i);
}

void onescomp(int bin[],int i){
    for (int j = i - 1; j >= 0; j--)
        bin[i]= bin[i]==1? 1:0;
    for (int j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
    printf("\n");
}







int main() {
    int num1,num2;
    char sign;
    printf("Enter Decimal Number1 with its sign: ");
    scanf("%c %d", &sign,&num1);
    // printf("Enter Decimal Number2: ");
    // scanf("%c %d", &sign,&num2);
    decimalToBinary(sign,num1);
    // decimalToBinary(sign,num2);

    return 0;
}