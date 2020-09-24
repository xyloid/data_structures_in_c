// gcc factorial.c -o factorial
// ./factorial

#include <stdio.h>
#include <time.h>

// Note: 0! = 1
// TODO: Implement iterative solution here
unsigned long factorial(unsigned long n) {
	unsigned long result = 1;
	while (n > 0) {
		result *= n--;
	}
	return result;
}

int factorial_int(int n) {
	int result = 1;
	while (n > 0) {
		result *= n--;
	}
	return result;
}

// TODO: Implement recursive solution here
unsigned long factorial_rec(unsigned long n) {
	return n > 1 ? n * factorial_rec(n - 1) : 1;
}
// For comparing int and unsigned long.
int factorial_rec_int(int n) {
	return n > 1 ? n * factorial_rec_int(n - 1) : 1;
}

int main() {
	// Size of data types.
	printf("int : %lu\n", sizeof(int));
	printf("unsigned long int : %lu\n\n", sizeof(unsigned long));

	// Tests.
	printf("Iterative solution:\n");
	printf(" factorial(10) = %lu\n", factorial(10));
	printf(" factorial_int(10) = %d\n", factorial_int(10));
	printf("\n factorial(15) = %lu\n", factorial(15));
	printf(" factorial_int(15) = %d\n", factorial_int(15));
	printf("Recursive solution:\n");
	printf("\n factorial_rec(10) = %lu\n", factorial_rec(10));
	printf(" factorial_rec_int(10) = %d\n", factorial_rec_int(10));
	printf("\n factorial_rec(15) = %lu\n", factorial_rec(15));
	printf(" factorial_rec_int(15) = %d\n", factorial_rec_int(15));
	printf("\n\n\n");

	// Test on overflow
	int j = 0;
	for (j = 0; j < 22; j++) {
		printf("factorial(%d)    = %lu\n", j, factorial(j));
		printf("factorial_int(%d)= %d\n\n", j, factorial_int(j));
	}

	printf("\n\n\n");

	// Test the time. Comparing the iterative and recursive solution.
	// n =[1 - 63]
	clock_t start, end;
	double time_used;
	unsigned long int n = 0;
	// Have to use a large sample since single function execution is too
	// fast for any timer. If we use clock() to capture time before and after
	// If only measure one single function call. The precision will be horrible.
	int sample_size = 1000000;
	int i;
	// Even if unsinged long int overflow, the number of steps shouldn't change.
	unsigned long range = 21;
	while (n < range) {
		printf("%lu\t", n);
		time_used = 0.0;

		start = clock();
		for (i = 0; i < sample_size; i++) {
			factorial(n);
		}
		end = clock();
		// Unit: nanosecond.
		time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000000;
		time_used /= sample_size;

		printf("%.2f\t", time_used);
		time_used = 0.0;

		start = clock();
		for (i = 0; i < sample_size; i++) {
			factorial_rec(n);
		}
		end = clock();
		// Unit: nanosecond.
		time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000000;
		time_used /= sample_size;
		printf("%.2f\n", time_used);

		n++;
	}

	return 0;
}
