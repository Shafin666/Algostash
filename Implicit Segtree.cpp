//Based off of LOJ 1089

struct Node {
    Node *l, *r;
    int val;

    Node() : l(NULL), r(NULL), val(0) { }
}; 
Node *root = new Node();

int maxn = 1e8+7;

/*void traverse(Node *at) {
    if(at->l == NULL && at->r == NULL) {
        printf("%d[%d, %d]\n", at->val, at->L, at->R);//cout << at->val << " ";
        return;
    }
    printf("%d[%d, %d]\n", at->val, at->L, at->R);
    if(at->l != NULL) traverse(at->l);
    if(at->r != NULL) traverse(at->r);
}*/

void clear(Node *at) {
    if(at->l == NULL && at->r == NULL) {
        free(at); return;
    }
    if(at->l != NULL) clear(at->l);
    if(at->r != NULL) clear(at->r);
}


void modify(Node *at, int L, int R, int l, int r, int k) {
    if(L > r || R < l) return;
    if(L >= l && R <= r) {
        at->val += k;
        return;
    }
    int mid = (L+R)/2;

    if(mid >= l) {
        if(at->l == NULL) at->l = new Node();
        modify(at->l, L, mid, l, r, k);
    }
    if(r > mid) {
        if(at->r == NULL) at->r = new Node();
        modify(at->r, mid+1, R, l, r, k);
    }
}

int get(Node *at, int L, int R, int idx) {
    if(at == NULL) return 0;
    if(L == R) return at->val;

    int mid = (L+R)>>1; 
    int ans = at->val;
    if(idx <= mid) ans += get(at->l, L, mid, idx);
    else ans += get(at->r, mid+1, R, idx);
    return ans;
}
