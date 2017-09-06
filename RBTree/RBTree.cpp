// RBTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "RBTree.h"
#include "RBTreeVisuzlizer.h"
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
	algs::RBTree<int, int> rb_tree;
	BST<int, int> bst;

	for (int x = 100 /** 1000*/; x > 0; x--)
	{
		rb_tree.insert(x, x);
		//bst.insert(x, x);
	}

	algs::RBTreeVisualizer<int, int> visualizer(rb_tree);
	std::string filename = "rbTree.dot";
	visualizer.saveDot(filename);

	cout << endl << "RB Tree Height " << rb_tree.height() << endl;
	cout << "BST Tree Height " << bst.height() << endl;
	
	//for (int x = 100 * 1000; x > 50 * 1000; x--)
	//{
	//	rb_tree.remove(x);
	//	//bst.remove(x);
	//}

	cout << endl << "RB Tree Height " << rb_tree.height() << endl;
	cout << "BST Tree Height " << bst.height() << endl;

	return 0;
}

