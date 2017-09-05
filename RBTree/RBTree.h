#pragma once

#ifndef min
#undef min
#endif

#ifndef max
#undef max
#endif

#include <iostream>
#include <algorithm>

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

			std::pair<TKey, TValue> keyValue;

			bool color;

			Node() :
				parent(nullptr),
				left(nullptr),
				right(nullptr),
				keyValue(std::pair<TKey, TValue>()),
				color(red)
			{
			}

			Node(const TKey& key, const TValue& value) :
				parent(nullptr),
				left(nullptr),
				right(nullptr),
				keyValue(std::make_pair(key, value)),
				color(red)
			{
			}

			TKey key() const { return keyValue.first; }

			TValue value() const { return keyValue.second; }
		};

	public:

		explicit RBTree() :
			comp(),
			root(nullptr),
			sentinel(new Node)
		{
			sentinel->left =
				sentinel->right =
				sentinel->parent = sentinel;
			sentinel->color = black;

			root = sentinel;
		}

		explicit RBTree(const TComp& comp) :
			comp(comp),
			root(nullptr),
			sentinel(new Node)
		{
			sentinel->left =
				sentinel->right =
				sentinel->parent = sentinel;
			sentinel->color = black;

			root = sentinel;
		}

		~RBTree()
		{
			clean(root);
			delete sentinel;
		}

		TValue& find(const TKey& key) const;

		std::pair<TKey&, TValue&> min() const;

		std::pair<TKey&, TValue&> max() const;

		TKey& successor(const TKey& key) const;

		TKey& predecessor(const TKey& key) const;

		void insert(const TKey& key, const TValue& value);

		void print() const
		{
			print(root);
		}

		size_t height() const
		{
			return height(this->root);
		}

	private:
		bool static isRed(const Node* node)
		{
			if (node == nullptr) return false;
			return node->color;
		}

		void clean(Node* node)
		{
			if (node == sentinel)
				return;

			clean(node->left);
			clean(node->right);

			delete node;
		}

		Node* findMinNode(Node* node) const;

		Node* findMaxNode(Node* node) const;

		Node* findNode(TKey& key) const;

		void print(Node* nodePtr) const;

		void insertFixup(Node* nodePtr);

		void rotateLeft(Node * nodePtr);

		void rotateRight(Node * nodePtr);

		size_t height(Node * nodePtr) const
		{
			if (nodePtr == sentinel)
				return 0;
			return 1 + std::max(height(nodePtr->left), height(nodePtr->right));
		}

	private:
		TComp comp;
		Node * root;
		Node * sentinel;

	};

	template <typename TKey, typename TValue, typename TComp>
	TValue& RBTree<TKey, TValue, TComp>::find(const TKey& key) const
	{
		Node* ptr = findNode(key);

		if (ptr == sentinel)
			throw std::exception("Cannot find node");

		return ptr->value();
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RBTree<TKey, TValue, TComp>::min() const
	{
		Node* minNode = findMinNode(this->root);
		if (minNode == sentinel)
			throw std::exception("Cannot find node");

		return std::make_pair(minNode->key(), minNode->value());
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RBTree<TKey, TValue, TComp>::max() const
	{
		Node* maxNode = findMaxNode(this->root);
		if (maxNode == sentinel)
			throw std::exception("Cannot find node");

		return std::make_pair(maxNode->key(), maxNode->value());
	}

	template <typename TKey, typename TValue, typename TComp>
	TKey& RBTree<TKey, TValue, TComp>::successor(const TKey& key) const
	{
		Node* keyNode = findNode(key);

		if (keyNode == sentinel)
			throw std::exception("Cannot find node");

		if (keyNode->right != sentinel)
		{
			Node* ptr = findMinNode(keyNode->right);
			return ptr->key();
		}

		Node* ptr = keyNode->parent;

		while (ptr != sentinel && keyNode == ptr->right)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		if (ptr == sentinel)
			throw std::exception("Cannot find successor");

		return ptr->key();
	}

	template <typename TKey, typename TValue, typename TComp>
	TKey& RBTree<TKey, TValue, TComp>::predecessor(const TKey& key) const
	{
		Node* keyNode = findNode(key);

		if (keyNode == sentinel)
			throw std::exception("Cannot find node");

		if (keyNode->left != sentinel)
		{
			Node* ptr = findMaxNode(keyNode->left);
			return ptr->key();
		}

		Node* ptr = keyNode->parent;

		while (ptr != sentinel && keyNode == ptr->left)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		if (ptr == sentinel)
			throw std::exception("Cannot find predecessor");

		return ptr->key();
	}

	template <typename TKey, typename TValue, typename TComp>
	void RBTree<TKey, TValue, TComp>::insert(const TKey& key, const TValue& value)
	{
		Node * newNode = new Node(key, value);
		newNode->left = newNode->right = sentinel;

		Node *tmp = sentinel;
		Node *current = root;

		while (current != sentinel)
		{
			tmp = current;

			if (this->comp(key, current->key()))
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		newNode->parent = tmp;
		if (tmp == sentinel)
		{
			root = newNode;
		}
		else if (comp(key, tmp->key()))
		{
			tmp->left = newNode;
		}
		else
		{
			tmp->right = newNode;
		}

		insertFixup(newNode);
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RBTree<TKey, TValue, TComp>::Node*
		RBTree<TKey, TValue, TComp>::findMinNode(Node* node) const
	{
		Node* ptr = node;

		while (ptr->left != sentinel)
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

		while (ptr->right != sentinel)
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

		while (ptr != sentinel && ptr->key() != key)
		{
			if (comp(key, ptr->key()))
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
		if (node == sentinel)
			return;

		print(node->left);
		std::cout << node->key() << " (" << node->value() << ") ";
		print(node->right);
	}

	template <typename TKey, typename TValue, typename TComp>
	void RBTree<TKey, TValue, TComp>::insertFixup(Node* nodePtr)
	{
		while (nodePtr->parent->color == red) // "Отец" - красный
		{
			if (nodePtr->parent == nodePtr->parent->parent->left)
			{
				Node * tmp = nodePtr->parent->parent->right;
				if (tmp->color == red) 
				{
					// Случай 1.
					// "Дядя" узла nodePtr красный

					// Меняем цве "отца" и "дяди" на черный
					nodePtr->parent->color = black;
					tmp->color = black;

					// Меняем цвет "дедушки" на красный и переходим к нему на следующей итерации.
					nodePtr->parent->parent->color = red;
					nodePtr = nodePtr->parent->parent;
				}
				else 
				{
					// "Дядя" узла nodePtr черный

					if (nodePtr == nodePtr->parent->right)
					{
						// Случай 2.
						// "Дядя" узла nodePtr черный, nodePtr - правый потомок
						// Делаем поворот влево, сводя к случаю 3.

						nodePtr = nodePtr->parent;
						rotateLeft(nodePtr);
					}

					// Случай 3.
					// "Дядя" узла nodePtr черный, nodePtr - левый потомок

					// "Отец" становится черным, а "дедушка" красным.
					// Затем созраняем свойста RB правым поворотом.
					nodePtr->parent->color = black;
					nodePtr->parent->parent->color = red;
					rotateRight(nodePtr->parent->parent);
				}
			}
			else
			{
				// Те же самые ри случая, симметричные первой вертве.

				Node * tmp = nodePtr->parent->parent->left;
				if (tmp->color == red) // Case 1.
				{
					nodePtr->parent->color = black;
					tmp->color = black;
					nodePtr->parent->parent->color = red;
					nodePtr = nodePtr->parent->parent;
				}
				else
				{
					if (nodePtr == nodePtr->parent->left) // Case 2
					{
						nodePtr = nodePtr->parent;
						rotateRight(nodePtr);
					}

					// Case 3
					nodePtr->parent->color = black;
					nodePtr->parent->parent->color = red;
					rotateLeft(nodePtr->parent->parent);
				}
			}
		}

		root->color = black;
	}

	template <typename TKey, typename TValue, typename TComp>
	void RBTree<TKey, TValue, TComp>::rotateLeft(Node* nodePtr)
	{
		Node * tmp = nodePtr->right;
		nodePtr->right = tmp->left;

		if (tmp->left != sentinel)
			tmp->left->parent = nodePtr;

		tmp->parent = nodePtr->parent;
		if (nodePtr->parent == sentinel)
			root = tmp;
		else if (nodePtr == nodePtr->parent->left)
			nodePtr->parent->left = tmp;
		else 
			nodePtr->parent->right = tmp;

		tmp->left = nodePtr;
		nodePtr->parent = tmp;
	}

	template <typename TKey, typename TValue, typename TComp>
	void RBTree<TKey, TValue, TComp>::rotateRight(Node* nodePtr)
	{
		Node * tmp = nodePtr->left;
		nodePtr->left = tmp->right;

		if (tmp->right != sentinel)
			tmp->right->parent = nodePtr;

		tmp->parent = nodePtr->parent;
		if (nodePtr->parent == sentinel)
			root = tmp;
		else if (nodePtr == nodePtr->parent->left)
			nodePtr->parent->left = tmp;
		else
			nodePtr->parent->right = tmp;

		tmp->right = nodePtr;
		nodePtr->parent = tmp;
	}
}

