#pragma once
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif


template <
	typename TKey,
	typename TValue,
	typename TComp = std::less<TKey>
>
class RandomizedBST
{
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

	void insert(TKey key, TValue value);

	TValue* find(TKey key);
	
	std::pair<TKey, TValue> min();

	std::pair<TKey, TValue> max();

	void print() const
	{
		print(root);
	}

	TKey* successor(TKey key)
	{
		Node * keyNode = findNode(key);

		if (keyNode == nullptr)
			return nullptr;

		if (keyNode->right != nullptr)
		{
			Node * ptr = findMinNode(keyNode->right);
			return &ptr->key;
		}

		Node * ptr = keyNode->parent;

		while (ptr != nullptr && keyNode == ptr->right)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		return ptr == nullptr ? nullptr : &(ptr->key);

	}

	TKey* predecessor(TKey key)
	{
		Node * keyNode = findNode(key);

		if (keyNode == nullptr)
			return nullptr;

		if (keyNode->left != nullptr)
		{
			Node *ptr = findMaxNode(keyNode->left);
			return &ptr->key;
		}

		Node * ptr = keyNode->parent;

		while (ptr != nullptr && keyNode == ptr->left)
		{
			keyNode = ptr;
			ptr = ptr->parent;
		}

		return ptr == nullptr ? nullptr : &(ptr->key);

	}

	void remove(TKey key)
	{
		Node *keyNode = findNode(key);

		if (keyNode == nullptr)
			return;

		if (keyNode->left == nullptr)
		{
			// Нет левого потомка - подставляем правый
			transplant(keyNode, keyNode->right);
		}
		else if (keyNode->right == nullptr)
		{
			// Есть левый, но нет правого - подставляем левый
			transplant(keyNode, keyNode->left);
		}
		else
		{
			// Есть оба потомка. Ищем следующий за удаляемым элемент и подставляем его.
			Node * minimum = findMinNode(keyNode->right);
			if (minimum->parent != keyNode)
			{
				transplant(minimum, minimum->right);
				minimum->right = keyNode->right;
				minimum->right->parent = minimum;
			}

			transplant(keyNode, minimum);
			minimum->left = keyNode->left;
			minimum->left->parent = minimum;
		}

		delete keyNode;
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

	Node* findNode(TKey key);

	Node* findMinNode(Node* node);

	Node* findMaxNode(Node* node);

	void transplant(Node * prevNode, Node * newNode);

	int getSize(Node *node) const
	{
		if (node == nullptr) return 0;
		return node->size;
	}

	void fixSize(Node *node) const
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
			node->left = insertRoot(node->left, key, value);
			return rotateRight(node);
		}
		else
		{
			node->right = insertRoot(node->right, key, value);
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
			node->left = insert(node->left, key, value);
		else
			node->right = insert(node->right, key, value);

		fixSize(node);
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
void RandomizedBST<TKey, TValue, TComp>::insert(TKey key, TValue value)
{
	Node * newNode = new Node(key, value);

	Node *tmp = nullptr;
	Node *current = root;

	while (current != nullptr)
	{
		tmp = current;

		if (newNode->key < current->key)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	newNode->parent = tmp;
	if (tmp == nullptr)
	{
		root = newNode;
	}
	else if (newNode->key < tmp->key)
	{
		tmp->left = newNode;
	}
	else
	{
		tmp->right = newNode;
	}
}

template <typename TKey, typename TValue, typename TComp>
TValue* RandomizedBST<TKey, TValue, TComp>::find(TKey key)
{
	Node* ptr = findNode(key);

	if (ptr == nullptr)
		return nullptr;

	return &ptr->value;
}

template <typename TKey, typename TValue, typename TComp>
std::pair<TKey, TValue> RandomizedBST<TKey, TValue, TComp>::min()
{
	Node* ptr = findMinNode(this->root);
	return std::make_pair(ptr->key, ptr->value);
}

template <typename TKey, typename TValue, typename TComp>
std::pair<TKey, TValue> RandomizedBST<TKey, TValue, TComp>::max()
{
	Node* ptr = findMaxNode(this->root);

	return std::make_pair(ptr->key, ptr->value);
}

template <typename TKey, typename TValue, typename TComp>
typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::findNode(TKey key)
{
	Node* ptr = root;

	while (ptr != nullptr && ptr->key != key)
	{
		if (key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}

	return ptr;
}

template <typename TKey, typename TValue, typename TComp>
typename RandomizedBST<TKey, TValue, TComp>::Node* RandomizedBST<TKey, TValue, TComp>::findMinNode(Node* node)
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
void RandomizedBST<TKey, TValue, TComp>::transplant(Node* prevNode, Node* newNode)
{
	if (prevNode->parent == nullptr)
		root = newNode;
	else if (prevNode == prevNode->parent->left)
		prevNode->parent->left = newNode;
	else
		prevNode->parent->right = newNode;

	if (newNode != nullptr)
		newNode->parent = prevNode->parent;

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

