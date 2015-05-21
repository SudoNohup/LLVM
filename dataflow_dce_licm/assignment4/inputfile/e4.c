int hc1(int a, int b) {
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
