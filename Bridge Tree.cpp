const int maxn = 1e5+10;

vector<int> adj[maxn], g[maxn];
int U[maxn], V[maxn];
bool bridge[maxn], visited[maxn];
int dfstime[maxn], tym = 0;
int cmp = 1;
queue<int> Q[maxn];

int other(int u, int e) {
    return U[e] == u? V[e] : U[e];
}

int dfs(int u, int edge) {
    visited[u] = 1, dfstime[u] = ++tym;
    int low = tym;

    for(int i = 0; i < (int) g[u].size(); i++) {
        int e = g[u][i];
        int v = other(u, e);

        if(not visited[v]) low = min(low, dfs(v, e));
        else if(e != edge) low = min(low, dfstime[v]);
    }
    if(low == dfstime[u] && edge != -1) bridge[edge] = 1;
    return low;
}

void dfs2(int s) {
    int currcomp = cmp;
    Q[cmp].push(s);
    visited[s] = 1;

    while(not Q[cmp].empty()) {
        int u = Q[cmp].front();
        Q[cmp].pop();

        for(int i = 0; i < (int) g[u].size(); i++) {
            int e = g[u][i];
            int v = other(u, e);

            if(visited[v]) continue;

            if(bridge[e]) {
                cmp++;
                adj[currcomp].pb(cmp);
                adj[cmp].pb(currcomp);
                dfs2(v);
            }
            else {
                Q[currcomp].push(v);
                visited[v] = 1;
            }
        }
    }
}

void maketree() {
    dfs(1, -1);
    memset(visited, 0, sizeof visited);
    dfs2(1);
}
