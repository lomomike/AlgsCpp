#pragma once

#include "RandomizedBST.h"
#include <string>
#include <fstream>

namespace algs
{
	using namespace std;

	template <
		typename TKey,
		typename TValue,
		typename TComp
	>
	class RandomizedBSTVisualizer
	{
		using NodePtr = typename RandomizedBST<TKey, TValue, TComp>::Node*;

	public:
		
		explicit RandomizedBSTVisualizer(const RandomizedBST<TKey, TValue, TComp>& tree)
			: tree(tree), num_of_sentinels(0)
		{
		}

		void saveDot(const string& fileName) const
		{
			num_of_sentinels = 0;
			ofstream file(fileName);

			file << "digraph RBTree {" << endl;
			file << "\t" << "graph" << " [ordering=out dpi = 300]" << endl;

			printDOT_Pass1(file, tree.root);
			printDOT_Pass2(file, tree.root);
			file << "}";
			file.close();
		}

	private:
		void printDOT_Pass1(ofstream &file, NodePtr node) const
		{
			if (node == nullptr)
				return;

			file << "\t" << "node" << node->key() << " [label=" << node->key() << "]" << endl;
			
			printDOT_Pass1(file, node->left);
			printDOT_Pass1(file, node->right);
		}

		void printDOT_Pass2(ofstream &file, NodePtr node) const
		{
			if (node == nullptr)
				return;

			if (node->left != nullptr)
			{
				file << "\t" << "node" << node->key() << " -> " << "node" << node->left->key() << endl;
			}
			else
			{
				file << "\t" << "NIL" << num_of_sentinels << " [shape=box label=NIL]" << endl;
				file << "\t" << "node" << node->key() << " -> NIL" << num_of_sentinels++ << endl;
			}

			if (node->right !=nullptr)
			{
				file << "\t" << "node" << node->key() << " -> " << "node" << node->right->key() << endl;
			}
			else
			{
				file << "\t" << "NIL" << num_of_sentinels << " [shape=box label=NIL]" << endl;
				file << "\t" << "node" << node->key() << " -> NIL" << num_of_sentinels++ << endl;
			}

			printDOT_Pass2(file, node->left);
			printDOT_Pass2(file, node->right);
		}
	private:
		const RandomizedBST<TKey, TValue, TComp>& tree;
		mutable int num_of_sentinels;
	};
}