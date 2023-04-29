#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;

long long t[N * 4]; // array for tree
long long tag[N * 4]; // tag array for tree

int a[N]; //input array

void push(int u, int l, int r) {
	if (l == r || tag[u] == -1) return;
	
	tag[u + u] = tag[u];
	tag[u + u + 1] = tag[u];
	
	int m = l + r >> 1;
	
	t[u + u] = tag[u] * 1ll * (m - l + 1); //left son's value
	t[u + u + 1] = tag[u] * 1ll * (r - m); //right son's value 
	 
	tag[u] = -1; 
}

//build a segment tree
void build(int u, int l, int r) { 
	tag[u] = -1;
	if (l == r) {
		t[u] = a[l];
		return;
	}
	int m = l + r >> 1;
	build(u + u, l, m);
	build(u + u + 1, m + 1, r);
	
	t[u] = t[u + u] + t[u + u + 1];
}

//get data on segment
long long get(int u, int ul, int ur, int l, int r) {
	push(u, ul, ur);
	if (l > ur || ul > r) return 0;
	if (l <= ul && ur <= r) return t[u];
	int um = ul + ur >> 1;
	return get(u + u, ul, um, l, r) 
			+ get(u + u + 1, um + 1, ur, l, r);
} 

//update on point
void update(int u, int l, int r, int pos, int val) {
	push(u, l, r);
	if (l == r) {
		t[u]  = val;
		return;
	}
	int m = l + r >> 1;
	if (pos <= m) update(u + u, l, m, pos, val);
	else update(u + u + 1, m + 1, r, pos, val);
	
	t[u] = t[u + u] + t[u + u + 1];
}

//update on segment
void update(int u, int ul, int ur, int l, int r, int val) {
	push(u, ul, ur);
	if (l > ur || ul > r) return;
	if (l <= ul && ur <= r) {
		long long len = ur - ul + 1;
		long long new_val = len * 1ll * val;
		
		t[u] = new_val;
		tag[u] = val;
		return;
	}
	
	int um = ul + ur >> 1;
	
	update(u + u, ul, um, l, r, val);
	update(u + u + 1, um + 1, ur, l, r, val);
	
	t[u] = t[u + u] + t[u + u + 1];
}


int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	build(1, 1, n);
	int q;
	cin >> q;
	while (q--) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int l, r;
			cin >> l >> r;
			cout << get(1, 1, n, l, r) << endl;
		}
		if (tp == 2) {
			int pos, val;
			cin >> pos >> val;
			update(1, 1, n, pos, val);
		}
		if (tp == 3) {
			int l, r, x;
			cin >> l >> r >> x;
			update(1, 1, n, l, r, x);
		}
	}
}
