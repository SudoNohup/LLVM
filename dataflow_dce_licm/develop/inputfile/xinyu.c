int test7(int a, int b) {
	int x = 1, y = 1, z = 1;
	do {
		x = a + b;
		do {
			y = a + b;
		} while(z < a);
	} while(z < b);
	return x;
}
