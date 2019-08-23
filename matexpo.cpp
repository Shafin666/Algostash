ll mod;

matrix mul(matrix a, matrix b) {
	matrix C(a.size(), vector<ll>(b[0].size()));
	for(ll i = 0; i < a.size(); i++)
		for(ll j = 0; j < b[0].size(); j++)
			for(ll k = 0; k < a.size(); k++)
				C[i][j] = (C[i][j] + (a[i][k]*b[k][j]) % mod) % mod;
	return C;
}
matrix power(matrix a, ll n) {
	if(n == 1) return a;
	matrix x = power(a, n/2);
	x = mul(x, x);
	if(n & 1) x = mul(x, a);
	return x;
}
