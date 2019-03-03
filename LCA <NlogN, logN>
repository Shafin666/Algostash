int lca(int u, int v) {
	if(level[u] < level[v]) swap(u, v);
	int i, k;
	
	if(level[u] != level[v]) {
		for(i = 17; i >= 0; i--) {
			if(parent[i][u] != -1 && level[parent[i][u]] >= level[v]) u = parent[i][u];
		}
	}
	if(u == v) return u;
	for(i = 17; i >= 0; i--) {
		if(parent[i][u] != -1 && parent[i][u] != parent[i][v]) {
			u = parent[i][u];
			v = parent[i][v];
		}
	} return parent[0][u];
}

//inside main

memset(parent, -1, sizeof parent);
for(i = 1; 1 << i < n; i++)
			for(j = 1; j <= n; j++)
				if(parent[i-1][j] != -1) parent[i][j] = parent[i-1][parent[i-1][j]];
