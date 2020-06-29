vector<ll> factor;

ll mult(ll a, ll b, ll mod) {
    ll result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

ll rho(ll n){
    if(n%2==0)return 2;
    ll x = rand()%n+1;
    ll c = rand()%n+1;
    ll y = x;
    ll g = 1;
   
    while(g==1){
        x = (mult(x, x, n) + c)%n;    
        y = (mult(y, y, n) + c)%n;
        y = (mult(y, y, n) + c)%n;
        ll h = (x > y)? x-y : y-x;
        g = __gcd(h, n);
    }
    return g;
}

ll binpower(ll base, ll e, ll mod) {
    ll result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = mult(result, base, mod);
        base = mult(base, base, mod);
        e >>= 1;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, ll s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (ll r = 1; r < s; r++) {
        x = mult(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(ll n) { 
    if (n < 2)
        return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

void factorize(ll n) {
    if(n == 1) return;
    if(MillerRabin(n)) {
        factor.pb(n);
        return;
    }
    ll d = rho(n);
    factorize(d);
    factorize(n/d);
}
