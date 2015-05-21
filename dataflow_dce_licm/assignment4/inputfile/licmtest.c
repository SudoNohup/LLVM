#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int test1(int a, int b) {
	int i, x = -100;
	for (i = 0; i < -1; i++) {
		x = a + b;
	}
	return x;
}


int test2(int u, int v) {
	int j;
	int x = 1;
	do {
		//printf("%d ", x);
		x = 4;
		if (u < v) {
			++u;
		}
		--v;
	} while(v >= 9);
	j = x;
	return j;
}

int test3(int u, int v) {
	int j;
	int x = 1;
	do {
		if (u < v) {
			x = 2;
			u = u + 1;
		}
		--v;
	} while (v >=9);
	j = x;
	return j;
}

int test4(int a, int b) {
	int x;
	int M[2000000];
	int i = 0, t = 0;
	int N = 1000000;
	while (i < N) {
		++i;
		t = a * b;
		M[i] = t;
	}
	x = t;
	return x;
}


int test5(int a, int b) {
	//int a, b, x;
	int x;
	int M[2000000];
	int i = 0, t = 0;
	int N = 1000000;
	do {
		++i;
		t = a * b;
		M[i] = t;
	} while (i < N);
	x = t;
	return x;
}

int test6(int a, int b) {
	int x;
	do {
		do {
			x = a + 1;
			--b;
		} while(b > 0);
		--b;
	} while (b + 1 > 0);
	return x;
}

int test7(int x) {
	int a, b, c;
	int i;

	for (i = 0; i < 1000000000; i++) {
		a = x + 1;
		b = x + 2;
		c = a + b;
	}

	return a;
}

int test8(int a, int b) {
	int x;
	int M[100];
	int *p = &M[0];
	int i = 0, t = 0;
	int j = 0;
	int N = 20;
	do {
		++i;
		t = a * b;
		p[i] = t;
		t = 0;
		p++;
		p[j] = t;
	} while (i < N);
	x = t;
	return x;
}

int test9(int a, int b) {
	int x;
	int M[100];
	int i = 0, t = 0;
	int j = 0;
	int N = 20;
	do {
		++i;
		t = a * b;
		M[i] = t;
		t = 0;
		M[j] = t;
	} while (i < N);
	x = t;
	return x;
}


int main() {
	clock_t start, finish;
	double  duration;
	int a = 1, b = 2;

	start = clock();

	test1(1, 2);
	test2(2, 100000000);
	test3(2, 100000000);
	test4(3, 4);
	test5(3, 4);
	test6(0, 1000000000);
	test7(10);
	test8(3, 4);
	test9(3, 4);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );

	return 0;
}



