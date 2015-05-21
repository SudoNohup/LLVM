#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int test1(int x) {
	int a, b, c;
	x = x + 1;
	a = x + 2;
	b = a - 3;
	c = a + b;
	return c;
}

int test2(int x) {
	int a, b, c;
	for (int i = 0; i < 1000000000; i++) {
		x = x + 1;
		a = x + 2;
		b = a - 3;
		c = a + b;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = x + 1;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
		x = a + b;
	}
	return 0;
}

void test3(int a) {
	int x;
	x = a;
	do {
		x = x + 1;
		++a;
	} while(a < 1000000000);
	return;
}

int main() {
	clock_t start, finish;
	double  duration;
	int a = 1, b = 2;

	start = clock();

	test1(1);
	test2(1);
	test3(1);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );

	return 0;
}
