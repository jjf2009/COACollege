
#include <stdio.h>
#include <math.h>
#include <string.h>

// Binary to Decimal
int binaryToDecimal(int bin) {
    int decimal = 0, base = 1;
    while (bin > 0) {
        int rem = bin % 10;
        decimal += rem * base;
        base *= 2;
        bin /= 10;
    }
    return decimal;
}

// Decimal to Binary
void decimalToBinary(int dec) {
    int bin[32], i = 0;
    while (dec > 0) {
        bin[i++] = dec % 2;
        dec /= 2;
    }
    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
    printf("\n");
}

// Hexadecimal to Decimal
int hexToDecimal(char hex[]) {
    int len = strlen(hex);
    int base = 1, decimal = 0;

    for (int i = len - 1; i >= 0; i--) {
        char ch = hex[i];
        int value;

        if (ch >= '0' && ch <= '9')
            value = ch - '0';
        else if (ch >= 'A' && ch <= 'F')
            value = ch - 'A' + 10;
        else if (ch >= 'a' && ch <= 'f')
            value = ch - 'a' + 10;
        else {
            printf("Invalid Hex Digit: %c\n", ch);
            return -1;
        }

        decimal += value * base;
        base *= 16;
    }
    return decimal;
}

// Decimal to Hexadecimal
void decimalToHex(int num) {
    char hex[16];
    int i = 0;
    while (num > 0) {
        int rem = num % 16;
        hex[i++] = (rem < 10) ? rem + '0' : rem - 10 + 'A';
        num /= 16;
    }
    printf("Hexadecimal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hex[j]);
    printf("\n");
}

// Octal to Decimal
int octalToDecimal(int oct) {
    int decimal = 0, base = 1;
    while (oct > 0) {
        int rem = oct % 10;
        decimal += rem * base;
        base *= 8;
        oct /= 10;
    }
    return decimal;
}

// Decimal to Octal
void decimalToOctal(int num) {
    int oct[16], i = 0;
    while (num > 0) {
        oct[i++] = num % 8;
        num /= 8;
    }
    printf("Octal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", oct[j]);
    printf("\n");
}

int main() {
    int dec, bin, oct;
    char hex[20];

    // printf("Enter Decimal Number: ");
    // scanf("%d", &dec);
    // decimalToBinary(dec);
    // decimalToHex(dec);
    // decimalToOctal(dec);

    // printf("\nEnter Binary Number: ");
    // scanf("%d", &bin);
    // printf("Decimal: %d\n", binaryToDecimal(bin));

    // printf("\nEnter Octal Number: ");
    // scanf("%d", &oct);
    // printf("Decimal: %d\n", octalToDecimal(oct));

    printf("\nEnter Hexadecimal Number: ");
    scanf("%s", hex);
    int htd = hexToDecimal(hex);
    if (htd != -1)
        printf("Decimal: %d\n", htd);

    return 0;
}
