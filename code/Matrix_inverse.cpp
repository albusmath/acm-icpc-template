void inverse(int n, double A[maxn][maxn], double B[maxn][maxn]) { 
	// input: A n*n inverseable matrix
	// output: B n*n matrix
	static double tmp[maxn][maxn*2];

	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++)
			tmp[i][j] = A[i][j];

	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++)
			if (i == j) {
				tmp[i][n + j] = 1.0;
			} else {
				tmp[i][n + j] = 0.0;
			}
		
	for (int i = 1;i <= n;i++) {
		int pos = -1;
		double v = 0.0;
		for (int j = i;j <= n;j++) {
			if (fabs(tmp[j][i]) > fabs(v) + 1e-9) {
				v = tmp[j][i];
				pos = j;
			}
		}
		if (pos == -1) continue ;
		for (int k = 1;k <= n*2;k++) swap(tmp[pos][k], tmp[i][k]);
		for (int k = 1;k <= n*2;k++) tmp[i][k] /= v;
		for (int j = 1;j <= n;j++) if (j != i) {
			v = tmp[j][i];
			for (int k = 1;k <= n*2;k++) {
				tmp[j][k] -= v * tmp[i][k];
			}
		}
	}
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++)
			B[i][j] = tmp[i][n + j];
}
