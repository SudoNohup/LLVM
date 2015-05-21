int hc1(int a, int b) {
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
