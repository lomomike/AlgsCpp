#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>


namespace algs {

	template <
		typename TKey1,
		typename TValue1,
		typename TComp1
	>
	class RandomizedBSTVisualizer;

	// https://habrahabr.ru/post/145388/
	template <
		typename TKey,
		typename TValue,
		typename TComp = std::less<TKey>
	>
	class RandomizedBST
	{
		template <
			typename TKey1,
			typename TValue1,
			typename TComp1
		>
		friend class RandomizedBSTVisualizer;

		struct Node
		{
			Node* left;
			Node* right;
			Node* parent;

			std::pair<TKey, TValue> keyValue;

			unsigned int size;

			Node(const TKey& key, const TValue& value) :
				left(nullptr),
				right(nullptr),
				parent(nullptr),
				keyValue(key, value),
				size(1)
			{ }

			TKey key() const { return keyValue.first; }

			TValue value() const { return keyValue.second; }
		};

	public:
		explicit RandomizedBST() :
			root(nullptr),
			comp()
		{}

		explicit RandomizedBST(const TComp& comp) :
			root(nullptr),
			comp(comp)
		{}

		~RandomizedBST()
		{
			clean(root);
		}

		void insert(const TKey& key, const TValue& value);

		const TValue& find(const TKey& key);

		std::pair<TKey&, TValue&> min();

		std::pair<TKey&, TValue&> max();

		void print() const
		{
			print(root);
		}

		TKey& successor(const TKey& key)
		{
			Node * keyNode = findNode(key);

			if (keyNode == nullptr)
				return nullptr;

			if (keyNode->right != nullptr)
			{
				Node * ptr = findMinNode(keyNode->right);
				return ptr->key();
			}

			Node * ptr = keyNode->parent;

			while (ptr != nullptr && keyNode == ptr->right)
			{
				keyNode = ptr;
				ptr = ptr->parent;
			}

			if (ptr == nullptr)
				throw std::exception();

			return ptr->key();

		}

		TKey& predecessor(const TKey& key)
		{
			Node * keyNode = findNode(key);

			if (keyNode == nullptr)
				return nullptr;

			if (keyNode->left != nullptr)
			{
				Node *ptr = findMaxNode(keyNode->left);
				return ptr->key;
			}

			Node * ptr = keyNode->parent;

			while (ptr != nullptr && keyNode == ptr->left)
			{
				keyNode = ptr;
				ptr = ptr->parent;
			}

			if (ptr == nullptr)
				throw std::exception();

			return ptr->key;
		}

		void remove(const TKey& key)
		{
			root = removeImpl(root, key);
		}

		size_t height() const
		{
			if (root == nullptr)
				return 0;

			std::queue<Node *> queue;

			size_t h = 0;
			queue.push(root);

			while (true)
			{
				int nodeCount = queue.size();

				if (nodeCount == 0)
					return h;
				else
					h++;

				while (nodeCount > 0)
				{
					Node * node = queue.back();
					queue.pop();

					if (node->left != nullptr)
						queue.push(node->left);

					if (node->right != nullptr)
						queue.push(node->right);

					nodeCount--;
				}
			}
		}


	private:
		void clean(Node* node)
		{
			if (node == nullptr)
				return;

			clean(node->left);
			clean(node->right);

			delete node;
		}

		void print(Node * node) const
		{
			if (node == nullptr)
				return;

			print(node->left);
			std::cout << node->key << "(" << node->value << ") ";
			print(node->right);
		}

		Node* findNode(const TKey& key);

		Node* findMinNode(Node* node);

		Node* findMaxNode(Node* node);

		static int getSize(Node *node)
		{
			if (node == nullptr) return 0;
			return node->size;
		}

		void fixSize(Node *node)
		{
			node->size = getSize(node->left) + getSize(node->right) + 1;
		}

		Node * rotateRight(Node *nodePtr);

		Node * rotateLeft(Node *nodePtr);

		Node * insertRoot(Node *node, const TKey& key, const TValue& value)
		{
			if (node == nullptr)
				return new Node(key, value);

			if (comp(key, node->key()))
			{
				Node* newNode = insertRoot(node->left, key, value);
				newNode->parent = node;
				node->left = newNode;
				return rotateRight(node);
			}
			else
			{
				Node* newNode = insertRoot(node->right, key, value);
				newNode->parent = node;
				node->right = newNode;
				return rotateLeft(node);
			}
		}

		Node * insertImpl(Node * node, const TKey& key, const TValue& value)
		{
			if (node == nullptr)
				return new Node(key, value);

			if (rand() % (node->size + 1) == 0)
				return insertRoot(node, key, value);

			if (comp(key, node->key()))
			{
				Node *newNode = insertImpl(node->left, key, value);
				newNode->parent = node;
				node->left = newNode;
			}
			else
			{
				Node *newNode = insertImpl(node->right, key, value);
				newNode->parent = node;
				node->right = newNode;
			}

			fixSize(node);
			return node;
		}

		Node *join(Node *left, Node *right);

		Node *removeImpl(Node *node, const TKey& key)
		{
			if (!node)
				return node;

			if (node->key() == key)
			{
				Node *joinedNode = join(node->left, node->right);
				delete node;
				return joinedNode;
			}
			else if (comp(key, node->key()))
			{
				node->left = removeImpl(node->left, key);
			}
			else
			{
				node->right = removeImpl(node->right, key);
			}
			return node;
		}

		size_t height(Node * nodePtr) const
		{
			if (nodePtr == nullptr)
				return 0;
			return 1 + std::max(height(nodePtr->left), height(nodePtr->right));
		}


	private:
		Node * root;
		TComp comp;
	};


	template <typename TKey, typename TValue, typename TComp>
	void RandomizedBST<TKey, TValue, TComp>::insert(const TKey& key, const TValue& value)
	{
		Node * node = insertImpl(root, key, value);
		root = node;
	}

	template <typename TKey, typename TValue, typename TComp>
	const TValue& RandomizedBST<TKey, TValue, TComp>::find(const TKey& key)
	{
		Node* ptr = findNode(key);

		if (ptr == nullptr)
			return nullptr;

		return ptr->value;
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RandomizedBST<TKey, TValue, TComp>::min()
	{
		Node* ptr = findMinNode(this->root);
		if (ptr == nullptr)
			throw std::exception("Cannot find node");

		return std::make_pair(ptr->key(), ptr->value());
	}

	template <typename TKey, typename TValue, typename TComp>
	std::pair<TKey&, TValue&> RandomizedBST<TKey, TValue, TComp>::max()
	{
		Node* ptr = findMaxNode(this->root);
		if (ptr == nullptr)
			throw std::exception("Cannot find node");

		return std::make_pair(ptr->key(), ptr->value());
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node*
		RandomizedBST<TKey, TValue, TComp>::findNode(const TKey& key)
	{
		Node* ptr = root;

		while (ptr != nullptr && ptr->key() != key)
		{
			if (key < ptr->key())
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node*
		RandomizedBST<TKey, TValue, TComp>::findMinNode(Node* node)
	{
		Node* ptr = node;

		while (ptr->left != nullptr)
			ptr = ptr->left;

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::findMaxNode(Node* node)
	{
		Node *ptr = node;

		while (ptr->right != nullptr)
			ptr = ptr->right;

		return ptr;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::rotateRight(Node* nodePtr)
	{
		Node * tmp = nodePtr->left;
		nodePtr->left = tmp->right;

		if (tmp->right != nullptr)
			tmp->right->parent = nodePtr;

		tmp->parent = nodePtr->parent;
		if (nodePtr->parent == nullptr)
			root = tmp;
		else if (nodePtr == nodePtr->parent->left)
			nodePtr->parent->left = tmp;
		else
			nodePtr->parent->right = tmp;

		tmp->right = nodePtr;
		nodePtr->parent = tmp;

		fixSize(nodePtr);
		return tmp;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::rotateLeft(Node* nodePtr)
	{
		Node * tmp = nodePtr->right;
		nodePtr->right = tmp->left;

		if (tmp->left != nullptr)
			tmp->left->parent = nodePtr;

		tmp->parent = nodePtr->parent;
		if (nodePtr->parent == nullptr)
			root = tmp;
		else if (nodePtr == nodePtr->parent->left)
			nodePtr->parent->left = tmp;
		else
			nodePtr->parent->right = tmp;

		tmp->left = nodePtr;
		nodePtr->parent = tmp;

		fixSize(nodePtr);
		return tmp;
	}

	template <typename TKey, typename TValue, typename TComp>
	typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::join(Node* left, Node* right)
	{
		if (left == nullptr)
			return right;

		if (right == nullptr)
			return left;

		if (rand() % (left->size + right->size) < left->size)
		{
			Node *joinedNode = join(left->right, right);
			if (joinedNode != nullptr)
			{
				joinedNode->parent = left;
			}
			left->right = joinedNode;
			fixSize(left);
			return left;
		}
		else
		{
			Node *joinedNode = join(left, right->left);
			if (joinedNode != nullptr)
			{
				joinedNode->parent = right;
			}
			right->left = joinedNode;
			fixSize(right);
			return right;
		}
	}
}
