#include<stdio.h>
#include<string.h>

// Note: All arithmetic functions now operate on strings of length 'n'

void one_complement(char bin[], char result[], int n) {
    for (int i = 0; i < n; i++) {
        result[i] = (bin[i] == '1') ? '0' : '1';
    }
    result[n] = '\0';
}

void two_complement(char bin[], char result[], int n) {
    char one_comp[n + 1];
    one_complement(bin, one_comp, n);
    int carry = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (one_comp[i] == '1' && carry == 1) {
            result[i] = '0';
        } else if (one_comp[i] == '0' && carry == 1) {
            result[i] = '1';
            carry = 0;
        } else {
            result[i] = one_comp[i];
        }
    }
    result[n] = '\0';
}

void add_binary(char a[], char m[], int n) {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';
        int bit2 = m[i] - '0';
        int sum = bit1 + bit2 + carry;
        a[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
}

void sub_binary(char b1[], char b2[], int n) {
    char two_comp[n + 1];
    two_complement(b2, two_comp, n);
    add_binary(b1, two_comp, n);
}

// Shifts (n+1)-bit A and n-bit Q
void shift_left(char a[], char q[], int n) {
    // Shift A left
    for (int i = 0; i < n; i++) {
        a[i] = a[i + 1];
    }
    a[n] = q[0]; // LSB of A gets MSB of Q

    // Shift Q left
    for (int i = 0; i < n - 1; i++) {
        q[i] = q[i + 1];
    }
}

void non_restoring_division(char m[], char q[], int count) {
    int extended_len = count + 1;

    // A and m_ext are (count + 1) bits to handle sign correctly
    char a[extended_len + 1];
    char m_ext[extended_len + 1];
    
    // Initialize A to all zeros
    for (int i = 0; i < extended_len; i++) {
        a[i] = '0';
    }
    a[extended_len] = '\0';
    
    // Extend divisor M with a '0' at the beginning
    m_ext[0] = '0';
    strcpy(m_ext + 1, m);

    printf("\nCycle\tOperation\t\tA (%d bits)\tQ (%d bits)\n", extended_len, count);
    printf("0\tInitial\t\t\t%s\t\t%s\n", a, q);

    for (int i = count; i > 0; i--) {
        if (a[0] == '0') {
            shift_left(a, q, count);
            printf("%d\tShift Left\t\t%s\t\t%s_\n", count - i + 1, a, q);
            sub_binary(a, m_ext, extended_len);
            printf("\tA = A - M\t\t%s\t\t%s_\n", a, q);
        } else { // a[0] == '1'
            shift_left(a, q, count);
            printf("%d\tShift Left\t\t%s\t\t%s_\n", count - i + 1, a, q);
            add_binary(a, m_ext, extended_len);
            printf("\tA = A + M\t\t%s\t\t%s_\n", a, q);
        }

        if (a[0] == '0') {
            q[count - 1] = '1';
        } else {
            q[count - 1] = '0';
        }
        printf("\tSet Q0 = %c\t\t%s\t\t%s\n", q[count - 1], a, q);
    }

    if (a[0] == '1') {
        printf("\nRemainder is negative. Correcting: A = A + M\n");
        add_binary(a, m_ext, extended_len);
    }

    printf("\nFinal Result:\n");
    printf("Quotient (Q) = %s\n", q);
    // The remainder is the last 'count' bits of A
    printf("Remainder (A) = %s\n", a + 1); 
}

int main() {
    int c;
    printf("Enter Number of Bits: ");
    scanf("%d", &c);
    
    if (c <= 0) {
        printf("Number of bits must be positive.\n");
        return 1;
    }

    char b1[c + 1], b2[c + 1];

    printf("Enter Dividend (Unsigned Binary): ");
    scanf("%s", b2);
    printf("Enter Divisor (Unsigned Binary): ");
    scanf("%s", b1);
    
    if(strlen(b1) != c || strlen(b2) != c){
        printf("Error: Dividend and Divisor must be %d bits long.\n", c);
        return 1;
    }

    non_restoring_division(b1, b2, c);

    return 0;
}