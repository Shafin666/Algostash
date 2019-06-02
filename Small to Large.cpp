const int maxn = 1e5+10;
int in[maxn], out[maxn], ver[maxn];
int sz[maxn], ans[maxn], idx = 1;
vector<int> adj[maxn];
map<int, int> M;
set<int> s;

void getsz(int u, int par = 0) {
	sz[u] = 1;
	ver[idx] = u;
	in[u] = idx++;

	for(auto v : adj[u]) {
		if(v == par) continue;
		getsz(v, u);
		sz[u] += sz[v];
	} out[u] = idx;
}

void dfs(int u, int par, int keep) {
	int mx = -1, bigchild = -1;

	for(auto v : adj[u]) {
		if(v == par) continue;
		if(sz[v] > mx) bigchild = v;
		mx = max(mx, sz[v]);
	}

	for(auto v : adj[u]) {
		if(v == par || v == bigchild) continue;
		dfs(v, u, 0);
	}

	if(bigchild != -1) dfs(bigchild, u, 1);

	for(auto v : adj[u]) {
		if(v == par || v == bigchild) continue;
		for(int p = in[v]; p < out[v]; p++)
			s.insert(ver[p]);
	} s.insert(u);

	cout << u << ": ";
	for(auto it : s) cout << it << " "; cout << endl;

	if(not keep)
		for(int p = in[u]; p < out[u]; p++)
			s.erase(ver[p]);
}
