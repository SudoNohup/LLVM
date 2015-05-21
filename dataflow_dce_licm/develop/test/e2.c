int cond2(int u, int v) {
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
