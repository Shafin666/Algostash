const int maxn = 1e5+10;
int p[maxn], root[maxn];
vector<int> adj[maxn];
int w[maxn];

struct edge {
	int u, v, c;
}; vector<edge> edges;

int find(int x) {
	return (p[x] == x)? x : p[x] = find(p[x]);
}

int join(int a, int b) {
	if(p[a] > p[b]) return p[a] = b;
	else return p[b] = a;
}

int main()
{
	int n, m; cin >> n >> m;

	for(int i = 1; i <= n; i++) p[i] = i, root[i] = i;
	int N = n+1;

	for(int i = 1; i <= m; i++) {
		int u, v, c; cin >> u >> v >> c;
		edges.pb({u, v, c});
	}
	sort(edges.begin(), edges.end(), [] (edge a, edge b) {return a.c < b.c;});

	for(auto e : edges) {
		int u = find(e.u);
		int v = find(e.v);
		if(u == v) continue;

		int k = join(u, v);
		adj[N].pb(root[u]); adj[root[u]].pb(N);
		adj[N].pb(root[v]); adj[root[v]].pb(N);

		w[N] = e.c;
		root[k] = N++;
	}

    return 0;
}
