#pragma once
#include<iostream>
using namespace std;

class node {
public:
	int a, b;//区间a到b
	node* l, * r, * fa;
	long long sum;
	long long lazy;
	node(int aa, int bb) {
		a = aa;
		b = bb;
		l = r = fa = NULL;
		sum = lazy = 0;
	}
};
class SegmentTree
{
private:
	void freet(node*);
public:
	int n;
	node* root;
	SegmentTree(int a[], int n);//建树
	~SegmentTree();//释放树
	void printT();//输出树
	void segAdd(int x, int y, int k);//将区间x到y加上k
	long long getSum(int x, int y);//求区间x到y的和
};

