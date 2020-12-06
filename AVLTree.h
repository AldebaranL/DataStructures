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
	void print(node<T>*, int);//�����ʱ����
	int findrank(T x);//������б�xС��Ԫ�ظ���+1
	T findkth(int k, node<T>*);//������е�k���Ԫ�ص�keyֵ
	T getnex(T x);//�������x�ĺ�̵�keyֵ
	T getpre(T x);//�������x��ǰ����keyֵ
	void delet(T x);//ɾ��һ��keyֵΪx��Ԫ��
	node<T>* findx(T x, node<T>*);//�������keyֵΪx��Ԫ�صĵ�ַ
	void insert(int x, node<T>*&);//����һ��keyֵΪx��Ԫ��
};

