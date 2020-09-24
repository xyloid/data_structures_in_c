#include<stdio.h>

/* Compute base to the n-th power. */
double power(double base, double n) {
    return n > 1 ? base * power(base, --n) : base;
}

int main() {
    int n;
    /* i ranges in 1-10. */
    for (n = 1; n < 11; n++)
        printf("power(2,%2d) = %f\n", n, power(2, n));
    return 0;
}
