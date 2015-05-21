int stdloop(int x) {
	int a, b, c;
	int i;

	for (i = 0; i < 10; i++) {
		a = x + 1;
		b = x + 2;
		c = a + b;
	}

	return a;
}
