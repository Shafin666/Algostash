struct cht {
	vector<ll> m, b;
	int ptr = 0;

	bool bad(int l1, int l2, int l3) {
		return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]) <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);
	}
  
	void add(ll _m, ll _b) {
		m.pb(_m); b.pb(_b);
		int sz = m.size();

		while(sz >= 3 && bad(sz-3, sz-2, sz-1)) {
			sz--;
			m.erase(m.end()-2);
			b.erase(b.end()-2);
		}
	}
  
	ll f(ll i, ll x) { return m[i]*x + b[i]; }
	
	ll query(ll x) {
		int lo = 0, hi = m.size()-1;

		while(lo < hi) {
			int mid = (lo + hi) >> 1;

			if(f(mid, x) > f(mid+1, x)) hi = mid;
			else lo = mid+1;
		}
		return f(lo, x);
	}
} ds;
