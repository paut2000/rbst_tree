#pragma once

#include <ostream>

template <typename T, typename K>
class RBST
{
private:

	struct Node {
		T value;
		K key;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		int subtree_size = 0;

		Node(Node* parent, const T value, const K key);
		Node* successor();
		Node* predecessor();

	} *head = nullptr;

	int visited_node_quantity = 0;

	int quantity = 0;

	void recursion_add(Node* node, Node* parent, const T& value, const K& key);
	void root_insert(Node* node, const T& value, const K& key);
	Node* recursion_find(Node* node, const K& key);
	void recursion_out(Node* node, const int depth, int& max_depth);
	void recursion_clean(Node* node);
	Node* recursion_join(Node* node1, Node* node2);

public:

	RBST();
	RBST(const RBST& rbst);
	~RBST();

	int size();
	void clean();
	bool empty();
	T& at(const K key);
	bool find(const K key);
	void add(const T value, const K key);
	bool remove(const K key);
	void out();
	int get_visited_node_quantity();

	class iterator
	{
	private:

		friend class RBST;

		RBST* rbst = nullptr;
		Node* ptr = nullptr;

		iterator(RBST* rbst, Node* node);

	public:

		const iterator& operator=(const iterator&);
		T& operator*();
		const iterator& operator++();
		const iterator operator++(int);
		const iterator& operator--();
		const iterator operator--(int);

		const bool operator==(const iterator&);
		const bool operator!=(const iterator&);

	};

	const iterator begin();
	const iterator end();

	class reverse_iterator
	{
	private:

		friend class RBST;

		RBST* rbst = nullptr;
		Node* ptr = nullptr;

		reverse_iterator(RBST* rbst, Node* node);

	public:

		const reverse_iterator& operator=(const reverse_iterator&);
		T& operator*();
		const reverse_iterator& operator++();
		const reverse_iterator operator++(int);
		const reverse_iterator& operator--();
		const reverse_iterator operator--(int);

		const bool operator==(const reverse_iterator&);
		const bool operator!=(const reverse_iterator&);

	};

	const reverse_iterator rbegin();
	const reverse_iterator rend();

};

template<typename T, typename K>
void RBST<T, K>::recursion_add(Node* node, Node* parent, const T& value, const K& key)
{
	visited_node_quantity++;

	if (!node) {
		node = new Node(parent, value, key);
		if (parent->key > node->key) parent->left = node;
		else parent->right = node;
	}
	else if (node->key == key) throw std::invalid_argument("Такой ключ уже существует");
	else if (double(rand()) / RAND_MAX < 1 / (double(node->subtree_size) + 1)) {
		root_insert(node, value, key);
		return;
	}
	else if (node->key < key)
		recursion_add(node->right, node, value, key);
	else
		recursion_add(node->left, node, value, key);
	node->subtree_size++;
}

template<typename T, typename K>
void RBST<T, K>::root_insert(Node* node, const T& value, const K& key)
{
	if (recursion_find(node, key)) throw std::invalid_argument("Такой ключ уже существует");
	Node* new_node = new Node(node->parent, value, key);
	new_node->subtree_size = node->subtree_size + 1;
	if (node->key > new_node->key)
		new_node->right = node;
	else
		new_node->left = node;
	if (node->parent)
		if (node->parent->left == node) node->parent->left = new_node;
		else node->parent->right = new_node;
	else
		head = new_node;
	node->parent = new_node;
}

template<typename T, typename K>
typename RBST<T, K>::Node* RBST<T, K>::recursion_find(Node* node, const K& key)
{
	visited_node_quantity++;

	if (!node) return nullptr;
	if (node->key == key) return node;
	else if (node->key < key) return recursion_find(node->right, key);
	else  return recursion_find(node->left, key);
}

template<typename T, typename K>
void RBST<T, K>::recursion_out(Node* node, const int depth, int& max_depth)
{
	if (depth > max_depth) max_depth = depth;
	if (node->left) recursion_out(node->left, depth + 1, max_depth);
	for (int i = 0; i < depth * 4; i++)
		std::cout << ' ';
	std::cout << node->key << "," << node->value << "," << node->subtree_size << std::endl;
	if (node->right) recursion_out(node->right, depth + 1, max_depth);
}

template<typename T, typename K>
void RBST<T, K>::recursion_clean(Node* node)
{
	visited_node_quantity++;

	if (node->left) recursion_clean(node->left);
	if (node->right) recursion_clean(node->right);
	delete node;
}

template<typename T, typename K>
typename RBST<T, K>::Node* RBST<T, K>::recursion_join(Node* node1, Node* node2)
{
	visited_node_quantity++;

	if (!node1) return node2;
	if (!node2) return node1;
	if (double(rand()) / RAND_MAX < node1->subtree_size / (double(node1->subtree_size) + node2->subtree_size)) {
		node1->right = recursion_join(node1->right, node2);
		node1->right->parent = node1;
		node1->subtree_size += node2->subtree_size;
		return node1;
	}
	else {
		node2->left = recursion_join(node1, node2->left);
		node2->left->parent = node2;
		node2->subtree_size += node1->subtree_size;
		return node2;
	}
}

template<typename T, typename K>
RBST<T, K>::RBST()
{
}

template<typename T, typename K>
RBST<T, K>::RBST(const RBST& rbst)
{
}

template<typename T, typename K>
RBST<T, K>::~RBST()
{
	clean();
}

template<typename T, typename K>
int RBST<T, K>::size()
{
	return quantity;
}

template<typename T, typename K>
void RBST<T, K>::clean()
{
	visited_node_quantity = 0;

	if (head) recursion_clean(head);
	head = nullptr;
	quantity = 0;
}

template<typename T, typename K>
bool RBST<T, K>::empty()
{
	return !quantity;
}

template<typename T, typename K>
T& RBST<T, K>::at(const K key)
{
	visited_node_quantity = 0;

	if (head) return recursion_find(head, key)->value;
	else throw std::runtime_error("Дерево пустое");
}

template<typename T, typename K>
bool RBST<T, K>::find(const K key)
{
	visited_node_quantity = 0;

	return recursion_find(head, key);
}

template<typename T, typename K>
void RBST<T, K>::add(const T value, const K key)
{
	visited_node_quantity = 0;

	if (!head) {
		head = new Node(nullptr, value, key);
		head->subtree_size++;
	}
	else {
		recursion_add(head, nullptr, value, key);
	}
	quantity++;
}

template<typename T, typename K>
bool RBST<T, K>::remove(const K key)
{
	visited_node_quantity = 0;

	Node* node = recursion_find(head, key);
	if (node) {
		if (node->parent) {
			Node* new_subtree = recursion_join(node->left, node->right);
			if (node->parent->left == node) node->parent->left = new_subtree;
			else node->parent->right = new_subtree;
			if (new_subtree) new_subtree->parent = node->parent;
			Node* ptr = new_subtree;
			if (ptr) ptr = ptr->parent;
			while (ptr) {
				if (ptr) ptr->subtree_size--;
				if (ptr) ptr = ptr->parent;
			}
		}
		else {
			head = recursion_join(node->left, node->right);
			if (head) head->parent = nullptr;
		}
		delete node;
		quantity--;
		return true;
	}
	return false;
}

template<typename T, typename K>
void RBST<T, K>::out()
{
	int max_depth = 0;
	if (head) recursion_out(head, 0, max_depth);
	std::cout << "Максимальная глубина: " << max_depth + 1 << std::endl;
	if (quantity)
		std::cout << "Теоретическая оценка: " << 4.3 * log(quantity) - 1.9 * log(log(quantity)) - 4 << std::endl;
}

template<typename T, typename K>
int RBST<T, K>::get_visited_node_quantity()
{
	return visited_node_quantity;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator RBST<T, K>::begin()
{
	Node* node = head;
	if (node)
		while (node->left)
			node = node->left;
	return iterator(this, node);
}

template<typename T, typename K>
const typename RBST<T, K>::iterator RBST<T, K>::end()
{
	return iterator(this, nullptr);
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator RBST<T, K>::rbegin()
{
	Node* node = head;
	if (node)
		while (node->right)
			node = node->right;
	return reverse_iterator(this, node);
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator RBST<T, K>::rend()
{
	return reverse_iterator(this, nullptr);
}

template<typename T, typename K>
RBST<T, K>::Node::Node(Node* parent, const T value, const K key)
{
	this->key = key;
	this->value = value;
	this->parent = parent;
}

template<typename T, typename K>
typename RBST<T, K>::Node* RBST<T, K>::Node::successor()
{
	Node* next = this->right;
	if (next) {
		if (!next->left)
			return next;
		else {
			while (next->left)
				next = next->left;
			return next;
		}
	}
	else {
		Node* parent = this->parent;
		next = this;
		while (parent && parent->left != next) {
			next = parent;
			parent = parent->parent;
		}
		if (!parent)
			return nullptr;
		return parent;
	}
}

template<typename T, typename K>
typename RBST<T, K>::Node* RBST<T, K>::Node::predecessor()
{
	Node* prev = this->left;
	if (prev) {
		if (!prev->right)
			return prev;
		else {
			while (prev->right)
				prev = prev->right;
			return prev;
		}
	}
	else {
		Node* parent = this->parent;
		prev = this;
		while (parent && parent->right != prev) {
			prev = parent;
			parent = parent->parent;
		}
		if (!parent)
			return nullptr;
		return parent;
	}
}

template<typename T, typename K>
RBST<T, K>::iterator::iterator(RBST* rbst, Node* node)
{
	this->rbst = rbst;
	this->ptr = node;
}

template<typename T, typename K>
RBST<T, K>::reverse_iterator::reverse_iterator(RBST* rbst, Node* node)
{
	this->rbst = rbst;
	this->ptr = node;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator& RBST<T, K>::iterator::operator=(const iterator& it)
{
	this->ptr = it.ptr;
	this->rbst = it.rbst;
	return *this;
}

template<typename T, typename K>
T& RBST<T, K>::iterator::operator*()
{
	return this->ptr->value;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator& RBST<T, K>::iterator::operator++()
{
	ptr = ptr->successor();
	return *this;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator RBST<T, K>::iterator::operator++(int)
{
	iterator befor = iterator(rbst, ptr);
	++(*this);
	return befor;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator& RBST<T, K>::iterator::operator--()
{
	ptr = ptr->predecessor();
	return *this;
}

template<typename T, typename K>
const typename RBST<T, K>::iterator RBST<T, K>::iterator::operator--(int)
{
	iterator befor = iterator(rbst, ptr);
	--(*this);
	return befor;
}

template<typename T, typename K>
const bool RBST<T, K>::iterator::operator==(const iterator& it)
{
	return it.ptr == this->ptr;
}

template<typename T, typename K>
const bool RBST<T, K>::iterator::operator!=(const iterator& it)
{
	return it.ptr != this->ptr;
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator& RBST<T, K>::reverse_iterator::operator=(const reverse_iterator& it)
{
	this->ptr = it.ptr;
	this->rbst = it.rbst;
	return *this;
}

template<typename T, typename K>
T& RBST<T, K>::reverse_iterator::operator*()
{
	return this->ptr->value;
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator& RBST<T, K>::reverse_iterator::operator++()
{
	ptr = ptr->predecessor();
	return *this;
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator RBST<T, K>::reverse_iterator::operator++(int)
{
	reverse_iterator befor = reverse_iterator(rbst, ptr);
	++(*this);
	return befor;
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator& RBST<T, K>::reverse_iterator::operator--()
{
	ptr = ptr->successor();
	return *this;
}

template<typename T, typename K>
const typename RBST<T, K>::reverse_iterator RBST<T, K>::reverse_iterator::operator--(int)
{
	reverse_iterator befor = reverse_iterator(rbst, ptr);
	--(*this);
	return befor;
}

template<typename T, typename K>
const bool RBST<T, K>::reverse_iterator::operator==(const reverse_iterator& it)
{
	return it.ptr == this->ptr;
}

template<typename T, typename K>
const bool RBST<T, K>::reverse_iterator::operator!=(const reverse_iterator& it)
{
	return it.ptr != this->ptr;
}