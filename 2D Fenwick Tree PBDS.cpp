#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct BinaryIndexedTree {

	ordered_set bit[maxn];

	void insert(int x, int y) {
		for(int i = x; i < maxn; i += i & -i) {
			bit[i].insert({y, x});
		}
	}

	void remove(int x, int y) {
		for(int i = x; i < maxn; i += i & -i) {
			bit[i].erase({y, x});
		}
	}

	int query(int x, int y) {
		int ans = 0;
		for(int i = x; i ; i -= i & -i) {
			ans += bit[i].order_of_key({y+1, 0});
		} return ans;
	}

	int query_sub(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1);
	}
} b;
