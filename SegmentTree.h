#pragma once
#include<iostream>
using namespace std;

class node {
public:
	int a, b;//����a��b
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
	SegmentTree(int a[], int n);//����
	~SegmentTree();//�ͷ���
	void printT();//�����
	void segAdd(int x, int y, int k);//������x��y����k
	long long getSum(int x, int y);//������x��y�ĺ�
};

