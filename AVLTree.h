#pragma once
#include<iostream>
using namespace std;

template<typename  T>
class node {
public:
		int h, bf, size;
		T key;
		node* ls, * rs, * pa;
		node(T k) {
			key = k;
			ls = rs = pa = NULL;
			h = size = 1;
			bf = 0;
		}
	};

template<typename  T>
class AVLTree
{
private:
	void zag(node<T>*);
	void zig(node<T>*);
	void balance(node<T>*);
	void update(node<T>*);
	bool isr(node<T>*);
	const T inf = 1e7;
public:
	AVLTree();
	~AVLTree();
	node<T>* root;
	void print(node<T>*, int);//输出此时的树
	int findrank(T x);//输出树中比x小的元素个数+1
	T findkth(int k, node<T>*);//输出树中第k大的元素的key值
	T getnex(T x);//输出树中x的后继的key值
	T getpre(T x);//输出树中x的前驱的key值
	void delet(T x);//删除一个key值为x的元素
	node<T>* findx(T x, node<T>*);//输出树中key值为x的元素的地址
	void insert(int x, node<T>*&);//插入一个key值为x的元素
};

