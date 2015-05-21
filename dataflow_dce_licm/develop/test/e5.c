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
