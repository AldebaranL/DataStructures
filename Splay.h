#pragma once
#include<iostream>
using namespace std;
class node {
public:
	int k, size;
	int lazy;
	node* l, * r, * fa;
	node(int a) {
		k = a; lazy = 0; size = 1;
		l = r = fa = NULL;
	}
};
class Splay
{
private:
	void freet(node*);
	void zag(node*);
	void zig(node*);
	void turn(node*, node*);
public:
	node* root;
	Splay(int n, int a[]);//建树
	~Splay();//释放树
	void print();//输出树
	void change(int l, int r, node* p);//将区间l-r翻转，p应输入root
};

