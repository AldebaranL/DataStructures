#include "SegmentTree.h"

void build(int l, int r, node*& p,int an[]) {
	p = new node(l, r);
	if (l == r) {
		p->sum = an[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, p->l,an);
	p->l->fa = p;
	build(1 + mid, r, p->r,an);
	p->r->fa = p;
	p->sum = p->l->sum + p->r->sum;
}
SegmentTree::SegmentTree(int a[], int n) {
	this->n = n;
	build(1, n, root, a);
}
SegmentTree::~SegmentTree() {
	freet(root);
}
void SegmentTree::freet(node* p) {
	if (p->l)freet(p->l);
	if (p->r)freet(p->r);
	if (p->fa) {
		if (p->fa->b == p->b)p->fa->r = NULL;
		else p->fa->l = NULL;
	}
	else root = NULL;
	delete p;
}

void print(node* p) {
	cout << p->a << '-' << p->b << ':' << p->sum << endl;
	if (p->l) print(p->l);
	if (p->r) print(p->r);
}
void SegmentTree::printT() {
	print(root);
}

void add(int x, int y, int k, node* p) {
	int a = p->a, b = p->b;
	if (x<a || y>b)cout << "wrong!";
	int m = (a + b) >> 1;
	if (x == a && y == b) {
		p->lazy += k;
		return;
	}
	p->sum += (y - x + 1) * k;
	if (y <= m)add(x, y, k, p->l);
	else {
		if (x > m)add(x, y, k, p->r);
		else {
			add(x, m, k, p->l);
			add(m + 1, y, k, p->r);
		}
	}
}
void SegmentTree::segAdd(int x, int y, int k) {
	add(x, y, k, root);
}

void push(node* p) {
	p->sum += (p->b - p->a + 1) * p->lazy;
	if (p->l)p->l->lazy += p->lazy;
	if (p->r)p->r->lazy += p->lazy;
	p->lazy = 0;
}
long long findsum(int x, int y, node* p) {
	push(p);
	int a = p->a, b = p->b;
	if (x<a || y>b)cout << "wrong!";
	int m = (a + b) >> 1;

	if (x == a && y == b)return p->sum;
	if (y <= m) {
		return findsum(x, y, p->l);
	}
	else {
		if (x > m)return findsum(x, y, p->r);
		else {
			long long t1 = findsum(x, m, p->l);
			long long t2 = findsum(m + 1, y, p->r);
			return t1 + t2;
		}
	}
}
long long SegmentTree::getSum(int x, int y) {
	return findsum(x, y, root);
}
