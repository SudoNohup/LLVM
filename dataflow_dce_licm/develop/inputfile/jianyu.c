
#include <stdio.h>

void test(int x) {
	int a, b, c;
	x = x + 1;
	a = x + 2;
	b = a - 3;
	c = a + b;
	return;
}




int sum (int a, int b, int c) {
	int d, e, f;
	if (c > 0) {
		d = a;
	} else {
		d = b;
	}
	f = a + 1;
	return d + f;
}


void test02(int a, int b) {
	int i;
	int x;
	x = a;
	for (i = 0; i < b; i++) {
		x = x + 1;
	}
	return;
}




void test021(int a, int b) {
	int x;
	x = a;
	do {
		x = x + 1;
	} while(b > 0);
	return;
}


void test022(int a) {
	int x;
	x = a;
	do {
		x = x + 1;
	} while(x < 10);
	return;
}




int stdloop123(int a, int b) {
	int i, x = -100;
	for (i = 0; i < -1; i++) {
		x = a + b;
	}
	return x;
}


int cond3(int u, int v) {
	int j;
	int x = 1;
	do {
		printf("%d", x);
		x = 4;
		if (u < v) {
			++u;
		}
		--v;
	} while(v >= 9);
	j = x;
	return j;
}




int cond1(int u, int v) {
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


int hc1(int a, int b) {
	int x;
	int M[100];
	int i = 0, t = 0;
	int N = 20;
	while (i < N) {
		++i;
		t = a * b;
		M[i] = t;
	}
	x = t;
	return x;
}



int hc11(int a, int b) {
	//int a, b, x;
	int x;
	int M[100];
	int i = 0, t = 0;
	int N = 20;
	do {
		++i;
		t = a * b;
		M[i] = t;
	} while (i < N);
	x = t;
	return x;
}




int stdloop(int x) {
	int a = 100;
	int i;
	for (i = 0; i < 10; i++) {
		a = x + 1;
	}
	return a;
}


int test024(int a, int b) {
	int x;
	do {
		do {
			x = a + 1;
		} while(b > 0);
	} while (b - 1 > 0);
	return x;
}



int stdloop1(int x) {
	int a, b, c;
	int i;

	for (i = 0; i < 10; i++) {
		a = x + 1;
		b = x + 2;
		c = a + b;
	}

	return a;
}




int cond25(int u, int v) {
	int j;
	int x = 1;
	do {
		x = 3;
		if (u < v) {
			x = 2;
			++u;
		}
		--v;
	} while (v >= 9);
	j = x;
	return j;
}




void test028(int a, int b) {
	int x;
	x = a;
	do {
		do {
			x = x + 1;
		} while(b > 0);
	} while (b - 1 > 0);
	return;
}




int stdloop0(int x, int y) {
	int a = 100;
	int i;
	do {
		a = x + 1;
	} while (y > 0);
	return a;
}



int hc16(int a, int b) {
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

int hc161(int a, int b) {
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
