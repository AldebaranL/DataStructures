#include "Splay.h"
void update(node* p) {
	p->size = 1;
	if (p->l)p->size += p->l->size;
	if (p->r)p->size += p->r->size;
}
bool ifr(node* p) {
	if (p->fa->r == p)return 1;
	return 0;
}
void build(int l, int r, node*& p,int a[]) {
	int mid = (l + r) >> 1;
	p = new node(a[mid]);
	if (l == r) return;
	if (l < mid) {
		build(l, mid - 1, p->l,a);
		p->l->fa = p;
	}
	if (mid < r) {
		build(mid + 1, r, p->r,a);
		p->r->fa = p;
	}
	update(p);
}
Splay::Splay(int n, int an[]){
	build(0, n + 1, root, an);
}
void Splay::freet(node* p) {
	if (p->l)freet(p->l);
	if (p->r)freet(p->r);
	if (p->fa) {
		if (ifr(p))p->fa->r = NULL;
		else p->fa->l = NULL;
	}
	else root = NULL;
	delete p;
}
Splay::~Splay() {
	freet(root);
}

void Splay::zag(node* p) {
	node* q = p->r;
	if (q->l) {
		q->l->fa = p;
	}
	if (p->fa) {
		if (ifr(p))p->fa->r = q;
		else p->fa->l = q;
	}
	else root = q;
	p->r = q->l;
	q->l = p;
	q->fa = p->fa;
	p->fa = q;
	update(p);
	update(q);
}
void Splay::zig(node* p) {
	node* q = p->l;
	if (q->r) {
		q->r->fa = p;
	}
	if (p->fa) {
		if (ifr(p))p->fa->r = q;
		else p->fa->l = q;
	}
	else root = q;
	p->l = q->r;
	q->r = p;
	q->fa = p->fa;
	p->fa = q;
	update(p);
	update(q);
}

void Splay::turn(node* p, node* tar) {
	//	push(p->fa);
	//	push(p);
	while (p->fa != tar) {
		if (ifr(p))zag(p->fa);
		else zig(p->fa);
	}
}
void push(node* p) {
	if (p->lazy == 0)return;
	node* t = p->l;
	p->l = p->r;
	p->r = t;
	if (p->l)p->l->lazy = 1 - p->l->lazy;
	if (p->r)p->r->lazy = 1 - p->r->lazy;
	p->lazy = 0;
}
node* findkth(int k, node* p) {
	if (k <= 0) {
		cout << '!'; return 0;
	}
	if (k > p->size) {
		cout << '#'; return 0;
	}
	push(p);
	int now = 1;
	if (p->l)now += p->l->size;
	if (k == now)return p;
	if (k > now)return findkth(k - now, p->r);
	if (k < now)return findkth(k, p->l);
}
void printt(node* p, int a) {
	push(p);
	if (p->l)printt(p->l, a + 1);
	cout << (p->k) << '-' << a << ' ';
	if (p->r)printt(p->r, a + 1);
}
void Splay::print() {
	printt(root, 0);
}

void Splay::change(int l, int r, node* p) {//cout<<'!';
	node* n1 = findkth(l, p);
	node* n2 = findkth(r + 2, p);
	//	cout<<n1->k<<' '<<n1->size<<' '<<n2->k<<' '<<n2->size;
	turn(n1, 0);//cout<<'!';
	turn(n2, n1);
	root->r->l->lazy = 1 - root->r->l->lazy;
}