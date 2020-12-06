#include "AVLTree.h"
template<typename T>
AVLTree<T>::AVLTree() {
	root = NULL;
}

template<typename T>
AVLTree<T>::~AVLTree() {

}

template<typename T>
void AVLTree<T>::print(node<T>* p, int h) {
	if (!p) {
		cout << "(空)" << endl;
		return;
	}
	cout << h << '(' << p->key << ',' << p->h << ',' << p->size << ')' << endl;
	if (p->ls)print(p->ls, h + 1);
	if (p->rs)print(p->rs, h + 1);
}
template<typename T>
void AVLTree<T>::update(node<T>* p) {
	int lh = 0, rh = 0;
	p->size = 1;
	if (p->ls) {
		p->size += p->ls->size;
		lh = p->ls->h;
	}
	if (p->rs) {
		p->size += p->rs->size;
		rh = p->rs->h;
	}
	p->bf = rh - lh;
	p->h = (lh > rh) ? lh : rh;
	p->h++;
}
template<typename T>
bool AVLTree<T>::isr(node<T>* p) {
	if (p->pa->rs == p)return 1;
	return 0;
}
template<typename T>
void AVLTree<T>::zag(node<T>* p) {
	node<T>* q = p->rs;
	q->pa = p->pa;
	if (p->pa) {
		if (isr(p))p->pa->rs = q;
		else p->pa->ls = q;
	}
	else root = q;
	p->rs = q->ls;
	if (p->rs)p->rs->pa = p;
	q->ls = p;
	p->pa = q;
	update(p);
	update(q);
}
template<typename T>
void AVLTree<T>::zig(node<T>* p) {
	node<T>* q = p->ls;
	q->pa = p->pa;
	if (p->pa) {
		if (isr(p))p->pa->rs = q;
		else p->pa->ls = q;
	}
	else root = q;
	p->ls = q->rs;
	if (p->ls)p->ls->pa = p;
	q->rs = p;
	p->pa = q;
	update(p);
	update(q);
}
template<typename T>
void AVLTree<T>::balance(node<T>* p) {
	if (p->bf > 1) {
		if (p->rs->bf == 1) {
			zag(p);
		}
		else if (p->rs->bf == -1) {
			zig(p->rs);
			zag(p);
		}
		else {
			zag(p);
		}
	}
	if (p->bf < -1) {
		if (p->ls->bf == -1) {
			zig(p);
		}
		else if (p->ls->bf == 1) {
			zag(p->ls);
			zig(p);
		}
		else {
			zig(p);
		}
	}
}
template<typename T>
void AVLTree<T>::insert(int k, node<T>*& p) {
	if (!p) {
		p = new node<T>(k);
		return;
	}
	if (k < p->key) {
		insert(k, p->ls);
		p->ls->pa = p;
	}
	else {
		insert(k, p->rs);
		p->rs->pa = p;
	}
	update(p);
	balance(p);
}
template<typename T>
node<T>*  AVLTree<T>::findx(T x, node<T>*p){
	if (!p)return NULL;
	if (p->key == x)return p;
	if (p->key < x)return findx(x, p->rs);
	if (p->key > x)return findx(x, p->ls);
}
template<typename T>
void AVLTree<T>::delet(T k) {
	node<T>* t = findx(k, root);
	if (!t) {
		cout << k << "不存在！" << endl;
		return;
	}
	while (t->rs || t->ls) {
		if (t->bf < 0)zig(t);
		else zag(t);
	}
	if (!t->pa) {
		delete root;
		root = NULL;
		return;
	}
	else {
		if (isr(t)) {
			t = t->pa;
			delete t->rs;
			t->rs = NULL;
		}
		else {
			t = t->pa;
			delete t->ls;
			t->ls = NULL;
		}
	}
	while (t) {
		update(t);
		balance(t);
		t = t->pa;
	}
}
template<typename T>
T AVLTree<T>::getpre(T k) {
	T ans = -inf;
	node<T>* t = root;
	while (t) {
		if (t->key<k && t->key>ans)ans = t->key;
		if (k <= t->key)t = t->ls;
		else t = t->rs;
	}
	return ans;
}
template<typename T>
T AVLTree<T>::getnex(T k) {
	T ans = inf;
	node<T>* t = root;
	while (t) {
		if (t->key > k && t->key < ans)ans = t->key;
		if (k < t->key)t = t->ls;
		else t = t->rs;
	}
	return ans;
}
template<typename T>
T AVLTree<T>::findkth(int k, node<T>* p) {
	if (k <= 0 || k > this->root->size) {
		cout << "没有第" << k << "个！" << endl;
		return (T)0;
	}
	int l = 1;
	if (p->ls)l += p->ls->size;
	if (k == l)return p->key;
	if (k < l)return findkth(k, p->ls);
	if (k > l)return findkth(k - l, p->rs);
}
template<typename T>
int AVLTree<T>::findrank(T k) {
	int ans = 1;
	node<T>* t = root;
	while (t) {
		if (k > t->key) {
			ans += 1;
			if (t->ls)ans += t->ls->size;
			t = t->rs;
		}
		else {
			t = t->ls;
		}
	}
	return ans;
}
