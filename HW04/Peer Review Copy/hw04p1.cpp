#include <iostream>
#include "bintree.h"
#include "bag6.h"

using namespace std;


template <class Item>
void btree_to_heap(binary_tree_node<Item>*& root_ptr, int depth);

template <class Item>
void heapify(binary_tree_node<Item>*& root_ptr);

int main() {
	bag<int> b;

	b.insert(50);
	b.insert(5);
	b.insert(10);
	b.insert(122);
	b.insert(35);
	b.insert(9);
	b.insert(5);

	btree_to_heap(b.get_root_ptr(), b.size());
	return 0;
}

template <class Item>
void btree_to_heap(binary_tree_node<Item>*& root_ptr, int depth) {
	for (int i = 0; i < depth; i++)
		heapify(root_ptr);
}

template <class Item>
void heapify(binary_tree_node<Item>*& root_ptr) {
	int largest = root_ptr->data();
	int l0Rr = 0;
	binary_tree_node<Item>* left = root_ptr->left();
	binary_tree_node<Item>* right = root_ptr->right();

	if (root_ptr = nullptr)
		return;
	if (left != nullptr && (left->data() > largest))
		largest = left->data();
	if (right != nullptr && right->data()) {
		largest = right->data();
		l0Rr = 1;
	}

	if (largest != root_ptr->data()) {
		//swapping action
		if (l0Rr == 0) {
			left->set_data(root_ptr->data());
			root_ptr->set_data(largest);
		}
		else {
			right->set_data(root_ptr->data());
			root_ptr->set_data(largest);
		}
	}

	if (left != nullptr) {
		heapify(left);
	}
	if (right != nullptr) {
		heapify(right);
	}
}
