int dfs(int u, int par, int lev = 0) {
	parent[0][u] = par;
	level[u] = lev;
	int size = 1, max_v = 0;

	for(int i = 0; i < (int)adj[u].size(); i++) {
		int v = adj[u][i];
		int vsize = 0;
		if(v != par) vsize = dfs(v, u, lev+1);
		size += vsize;
		if(vsize > max_v) max_v = vsize, heavy[u] = v;
	} return size;
}

void hld(int u, int h) {
	head[u] = h;
	pos[u] = cur_pos;
	arr[cur_pos++] = num[u];

	if(heavy[u] != -1) hld(heavy[u], h);
	for(int i = 0; i < (int)adj[u].size(); i++) {
		int v = adj[u][i];
		if(v != parent[0][u] && v != heavy[u]) hld(v, v);
	}
}

int query_up(int a, int b) {
	int res = 0;
	for(; head[a] != head[b]; b = parent[0][head[b]]) {
		if(level[head[a]] > level[head[b]]) swap(a, b);
		res += seg.query(1, 1, n, pos[head[b]], pos[b]);
	}
	if(level[a] > level[b]) swap(a, b);
	res += seg.query(1, 1, n, pos[a], pos[b]);
	return res;
}
