struct Node {
    int size, key, prior;
    Node *l, *r;

    Node(int v = 0) {
        size = 1; prior = rand();
        key = v;
        l = r = NULL;
    }
} *root;
typedef Node* pnode;

int sz(pnode t) {
    return t? t->size : 0;
}
void upd_size(pnode t) {
    if(t) t->size = sz(t->l) + sz(t->r) + 1;
}

void split(pnode t, pnode &l, pnode &r, int x) {
    if(!t) l = r = NULL;
    else if(t->key <= x) split(t->r, t->r, r, x), l = t;
    else split(t->l, l, t->l, x), r = t;

    upd_size(t);
}

void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) t = l? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;

    upd_size(t);
}

void insert(pnode &t, pnode it) {
    if(!t) t = it;
    else if(t->prior < it->prior) split(t, it->l, it->r, it->key), t = it;
    else insert(it->key <= t->key? t->l : t->r, it);

    upd_size(t);
}

void erase(pnode &t, int key) {
    if(!t) return;
    else if(t->key == key) {
        pnode tmp = t;
        merge(t, t->l, t->r);
        free(tmp);
    } else erase(key <= t->key? t->l : t->r, key);

    upd_size(t);
}

int getkth(pnode t, int k) {
    int cnt = sz(t->l);
    if(cnt == k-1) return t->key;

    if(cnt >= k) return getkth(t->l, k);
    else return getkth(t->r, k-cnt-1);
}

int countless(int k) {
    pnode l, r;
    split(root, l, r, k-1);
    int ret = sz(l);
    merge(root, l, r);
    return ret;
}

bool find(pnode t, int x) {
    if(!t) return 0;
    if(t->key == x) return 1;

    else if(x < t->key) return find(t->l, x);
    else return find(t->r, x);
}

void insert(int x) {
    insert(root, new Node(x));
}

void traverse(pnode t, int level = 0) {
    if(!t) return;
    traverse(t->l, level+1);
    cout << t->key << "(" << level << ") ";
    traverse(t->r, level+1);
}
