const ll maxn = 2e5+10;
ll a[maxn], n, m, magic;

struct node {
	ll l, r;
	ll pre, suf, sum, mx;
}; vector<node> T;

node build(ll l, ll r) {
	node ret;
	ret.l = l, ret.r = r;
	ret.mx = ret.pre = ret.suf = -1e16-7;
	ret.sum = 0;
	
	ll sum = 0;
	for(ll i = l; i <= r; i++) {
		sum = max(sum + a[i], a[i]);
		ret.mx = max(ret.mx, sum);
		ret.sum += a[i];
	}

	for(ll i = l, p = 0, q = 0; i <= r; i++) {
		p += a[i]; ret.pre = max(ret.pre, p);
		q += a[r+l-i]; ret.suf = max(ret.suf, q);
	}
	return ret;
}

node merge(node a, node b) {
	node c;
	c.pre = max(a.pre, a.sum + b.pre);
	c.suf = max(b.suf, b.sum + a.suf);
	c.sum = a.sum + b.sum;
	c.mx = max(a.mx, b.mx);
	c.mx = max(c.mx, a.suf + b.pre);
	return c;
}

node id() {
	node ret;
	ret.pre = -1e16-7; ret.suf = -1e16-7;
	ret.sum = 0;
	ret.mx = -1e16-7;
	return ret;
}

void init() {
	T.clear();
	for(ll i = 0; i < m; i += magic) {
		T.push_back(build(i, min(i + magic - 1, m-1)));
	}
}

ll split(ll x) {
	if(x == 0) return 0;

	ll sz = 0, k = -1, lft;
	for(ll i = 0; i < (ll) T.size(); i++) {
		ll here = T[i].r - T[i].l + 1;
		if(sz + here > x) {
			k = i; lft = x - sz;
			break;
		} sz += here;
	}
	if(k == -1) return T.size();
	if(lft == 0) return k;

	node a = build(T[k].l, T[k].l + lft - 1);
	node b = build(T[k].l + lft, T[k].r);

	T.erase(T.begin()+k);
	T.insert(T.begin()+k, a); T.insert(T.begin()+k+1, b);

	return k+1;
}

void erase(ll k) {
	ll j = split(k);
	split(k+1);
	T.erase(T.begin()+j);
}

void insert(ll k, ll x) {
	a[m++] = x;
	ll j = split(k);
	T.insert(T.begin()+j, build(m-1, m-1));
}

ll query(ll l, ll r) {
	node ret = id();
	l = split(l); r = split(r+1);

	for(ll i = l; i < r; i++) {
		ret = merge(ret, T[i]);
	}
	return ret.mx;
}

void rebuild() {
	vector<ll> b;
	for(auto p : T) {
		for(ll i = p.l; i <= p.r; i++)
			b.pb(a[i]);
	}
	m = 0;
	for(auto it : b) a[m++] = it;

	init();
	b.clear();
}

//inside main

cin >> n >> q; m = n;
for(ll i = 0; i < n; i++) cin >> a[i];
magic = sqrt(n);
init();

//after query
if((int)T.size() > 3 * magic) rebuild();
