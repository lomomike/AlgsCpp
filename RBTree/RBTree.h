#pragma once

#ifndef min
#undef min
#endif

#ifndef max
#undef max
#endif

#include <iostream>

namespace algs {

	template <
		typename TKey,
		typename TValue,
		typename TComp = std::less<TKey>
	>
		class RBTree
	{
		static constexpr bool black = false;
		static constexpr bool red = true;
		
		struct Node
		{
			Node* parent;
			Node* left;
			Node* right;

			TKey& key;
			TValue& value;
			bool color;

			Node(TKey& key, TValue& value) :
				parent(nullptr),
				left(nullptr),
				right(nullptr),
				key(key),
				value(value),
				color(red)
			{
			}
		};

	public:

		explicit RBTree() :
			comp(),
			root(nullptr)
		{
		}

		explicit RBTree(const TComp& comp) :
			comp(comp),
			root(nullptr)
		{
		}

		~RBTree()
		{
			clean(root);
		}

		TValue& find(const TKey& key) const;

		std::pair<TKey&, TValue&> min() const;

		std::pair<TKey&, TValue&> max() const;

		TKey& successor(const TKey& key) const;

		TKey& predecessor(const TKey& key) const;

		void print() const
		{
			print(root);
		}

	private:
		bool static isRed(const Node* node)
		{
			if (node == nullptr) return false;
			return node->color;
		}

		void clean(Node* node)
		{
			if (node == nullptr)
				return;

			clean(node->left);
			clean(node->right);

			delete node;
		}

		Node* findMinNode(Node* node) const;

		Node* findMaxNode(Node* node) const;

		Node* findNode(TKey& key) const;

		void print(Node* nodePtr) const;

	private:
		TComp comp;
		Node * root;
	};

	template <typename TKey, typename TValue, typename TComp>
	TValue& RBTree<TKey, TValue, TComp>::find(const TKey& key) const
	{
		Node* ptr = findNode(key);

		if (ptr == nullptr)
			throw std::exception("Cannot find node");

		return ptr->value;
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RBTree<TKey, TValue, TComp>::min() const
	{
		Node* minNode = findMinNode(this->root);
		if (minNode == nullptr)
			throw std::exception("Cannot find node");

		return std::make_pair(minNode->key, minNode->value);
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RBTree<TKey, TValue, TComp>::max() const
	{
		Node* maxNode = findMaxNode(this->root);
		if (maxNode == nullptr)
			throw std::exception("Cannot find node");

		return std::make_pair(maxNode->key, maxNode->value);
	}

	template <typename TKey, typename TValue, typename TComp>
	TKey& RBTree<TKey, TValue, TComp>::successor(const TKey& key) const
	{
		Node* keyNode = findNode(key);

		if (keyNode == nullptr)
			throw std::exception("Cannot find node");

		if (keyNode->right != nullptr)
		{
			Node* ptr = findMinNode(keyNode->right);
			return ptr->key;
		}

		Node* ptr = keyNode->parent;

		while (ptr != nullptr && keyNode == ptr->right)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		if (ptr == nullptr)
			throw std::exception("Cannot find successor");

		return ptr->key;
	}

	template <typename TKey, typename TValue, typename TComp>
	TKey& RBTree<TKey, TValue, TComp>::predecessor(const TKey& key) const
	{
		Node* keyNode = findNode(key);

		if (keyNode == nullptr)
			throw std::exception("Cannot find node");

		if (keyNode->left != nullptr)
		{
			Node* ptr = findMaxNode(keyNode->left);
			return ptr->key;
		}

		Node* ptr = keyNode->parent;

		while (ptr != nullptr && keyNode == ptr->left)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		if (ptr == nullptr)
			throw std::exception("Cannot find predecessor");

		return ptr->key;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RBTree<TKey, TValue, TComp>::Node*
		RBTree<TKey, TValue, TComp>::findMinNode(Node* node) const
	{
		Node* ptr = node;

		while (ptr->left != nullptr)
		{
			ptr = ptr->left;
		}

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RBTree<TKey, TValue, TComp>::Node*
		RBTree<TKey, TValue, TComp>::findMaxNode(Node* node) const
	{
		Node* ptr = node;

		while (ptr->right != nullptr)
		{
			ptr = ptr->right;
		}

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RBTree<TKey, TValue, TComp>::Node*
		RBTree<TKey, TValue, TComp>::findNode(TKey& key) const
	{
		Node * ptr = root;

		while (ptr != nullptr && ptr->key != key)
		{
			if (comp(key, ptr->key))
			{
				ptr = ptr->left;
			}
			else
			{
				ptr = ptr->right;
			}
		}

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	void RBTree<TKey, TValue, TComp>::print(Node* node) const
	{
		if (node == nullptr)
			return;

		print(node->left);
		std::cout << node->key << " (" << node->value << ") ";
		print(node->right);
	}

}

