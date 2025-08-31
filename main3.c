
#include <stdio.h>
#include <string.h>
// FuncƟon prototypes
int add_binary(char [], char [], int);
void shiŌ_right(char [], char [], int, int*);
void mulƟply(char [], char [], int);

int main() {
int c;
prinƞ("Enter Number of Bits: ");
scanf("%d", &c);
char b1[c + 1], b2[c + 1]; // +1 for null terminator
prinƞ("Enter First Number (Unsigned Binary): ");
scanf("%s", b1);
prinƞ("Enter Second Number (Unsigned Binary): ");
scanf("%s", b2);
mulƟply(b1, b2, c);
return 0;
}
// Add binary MulƟplicand into Accumulator (same length) and return carry
int add_binary(char a[], char m[], int n) {
int carry = 0;
for (int i = n - 1; i >= 0; i--) {
int bit1 = a[i] - '0';
int bit2 = m[i] - '0';
int sum = bit1 + bit2 + carry;
a[i] = (sum % 2) + '0';
carry = sum / 2;
}
return carry;
}
// Logical leŌ shiŌ of A and Q together
void shiŌ_right(char a[], char q[], int n, int*c) {
// ShiŌ Q Right
for (int i = n-1; i > 0; i--) {
q[i] = q[i - 1];
}
q[0] = a[n-1]; // Bring first bit of Q into last bit of A

// ShiŌ Q leŌ
for (int i = n-1; i > 0; i--) {
a[i] = a[i - 1];
}
a[0] = (*c) + '0';
*c = 0;
}
// MulƟply two binary numbers using shiŌ-add method (leŌ shiŌ)
void mulƟply(char m[], char q[], int count) {
char a[count + 1]; // Accumulator
int c=0;
for (int i = 0; i < count; i++){
a[i] = '0';
}
a[count] = '\0';
prinƞ("C\tA\tQ\tM");
prinƞ("\n%d\t%s\t%s\t%s\tIniƟal Values\n\n", c, a, q,m);
for (int step = 0; step < count; step++) {
if (q[count-1] == '1') {
c=add_binary(a, m, count);
prinƞ("%d\t%s\t%s\t%s\t A <- A + M\n",c, a, q,m);
}
shiŌ_right(a, q, count, &c);
prinƞ("%d\t%s\t%s\t%s\t SHIFT\n\n", c, a, q,m);
}
prinƞ("\nFinal Product: %s%s\n", a, q);
}
Output:
Conclusion: