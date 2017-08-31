// RBTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "RBTree.h"
#include "../BSTree/BST.h"
#include <map>
#include <random>

using namespace std;

char shiftA(int x)
{
	return static_cast<char>('A' + x - 1);
}

int main()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist;

	vector<int> v;
	v.reserve(10000000);


	algs::RBTree<int, int> tree;
	BST<int, int> bst;

	/*for(int i = 0; i < 10000000; ++i)
	{
		int value = dist(rng);
		v.push_back(value);
	}*/

	//for(auto x : v)
	for (int x = 100 * 1000; x > 0; x--)
	{
		tree.insert(x, x);
		bst.insert(x, x);
	}

	

	/*tree.insert(5, shiftA(5));
	tree.insert(2, shiftA(2));
	tree.insert(3, shiftA(3));
	tree.insert(1, shiftA(1));
	tree.insert(7, shiftA(7));
	tree.insert(8, shiftA(8));
	tree.insert(6, shiftA(6));*/

	//tree.print();

	cout << endl << "RB Tree Height " << tree.height() << endl;
	cout << endl << "BST Tree Height " << bst.height() << endl;

    return 0;
}

