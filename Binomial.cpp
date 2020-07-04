const int maxn = 1e5+10, mod = 1e9+7;
int fact[maxn], inv[maxn];

int bigmod(int a, int b) {
    if(b == 0) return 1;
    ll x = bigmod(a, b/2);
    x = (x * x) % mod;
    if(b & 1) x = (x * a) % mod;
    return x;
}
void init() {
    fact[0] = 1;
    for(int i = 1; i < maxn; i++) 
        fact[i] = (ll) fact[i-1] * i % mod;
    inv[maxn-1] = bigmod(fact[maxn-1], mod-2);
    for(int i = maxn-2; i >= 0; i--) 
        inv[i] = (ll) inv[i+1] * (i+1) % mod;
}
int ncr(int n, int r) {
    int ret = (ll) fact[n] * inv[n-r] % mod;
    return (ll) ret * inv[r] % mod;
}
