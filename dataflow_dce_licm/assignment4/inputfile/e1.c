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
