int num[100005], n;

struct Node {
    int val;
    Node *l, *r;

    Node() : val(0), l(NULL), r(NULL) {}
} *root[100005];

Node* merge(Node* L, Node* R) {
    Node *ret = new Node();

    ret->l = L; ret->r = R;
    ret->val = L->val + R->val;
    return ret;
}

Node* init(int L, int R) {
    if(L == R) {
        Node *ret = new Node();
        ret->val = num[L];
        return ret;
    } 
    int mid = L+R>>1;
    return merge(init(L, mid),
                 init(mid+1, R));
}

Node* modify(Node *at, int L, int R, int idx, int v) {
    if(L > idx || R < idx) return at;
    if(L == R) {
        Node *ret = new Node();
        ret->val = at->val + v;
        return ret;
    }
    int mid = L+R>>1;
    return merge(modify(at->l, L, mid, idx, v),
                 modify(at->r, mid+1, R, idx, v));
}

int query(Node *at, int L, int R, int l, int r) {
    if(L > r || R < l) return 0;
    if(L >= l && R <= r) return at->val;

    int mid = L+R>>1;
    return query(at->l, L, mid, l, r) + query(at->r, mid+1, R, l, r);
}

void traverse(Node *at) {
    if(at->l != NULL) traverse(at->l);
    cout << at->val << " ";
    if(at->r != NULL) traverse(at->r);
}

int kth(Node *a, Node *b, int L, int R, int k) {
    if(L == R) return L;
    int cnt = a->l->val - b->l->val;

    int mid = L + R >> 1;
    if(cnt >= k) return kth(a->l, b->l, L, mid, k);
    else return kth(a->r, b->r, mid+1, R, k-cnt);
}
