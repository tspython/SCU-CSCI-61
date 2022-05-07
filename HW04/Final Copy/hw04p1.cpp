/*
* FILE: hw04p1.cpp
* Author: Tushar Shrivastav
* Class: CSCI 61
*/

#include <iostream>
#include "bintree.h"
#include "bag6.h"

using namespace std;

//prototypes----------------------------------------------//
template <class Item>
void btn_to_heap(binary_tree_node<Item>*& root_ptr);

template <class Item>
void heapify(binary_tree_node<Item>*& root_ptr, int size);
//--------------------------------------------------------//

int main() {
	bag<int> b;

	b.insert(50);
	b.insert(5);
	b.insert(10);
	b.insert(122);
	b.insert(35);
	b.insert(9);
	b.insert(5);

	cout << "tree before heapify:" << endl;
	print(b.get_root(), b.size());
	heapify(b.get_root_ptr(), b.size());
	cout << endl;

	cout << "tree after heapify:" << endl;
	cout << endl;
	print(b.get_root(), b.size());

	return 0;
}

template <class Item>
void heapify(binary_tree_node<Item>*& root_ptr, int depth)
{
	for (int i = 0; i < depth; i++)
		btn_to_heap(root_ptr);
}


template <class Item>
void btn_to_heap(binary_tree_node<Item>*& root_ptr)
{
	int largest = root_ptr->data();
	bool flag = false;
	binary_tree_node<Item>* left_ptr = root_ptr->left();
	binary_tree_node<Item>* right_ptr = root_ptr->right();

	if (root_ptr == nullptr) 
		return;

	if (left_ptr != nullptr && left_ptr->data() > largest) 
		largest = left_ptr->data();


	if (right_ptr != nullptr && right_ptr->data() > largest) {
		largest = right_ptr->data();
		flag = true;
	}

	if (largest != root_ptr->data()) {
		if (flag == false) {
			left_ptr->set_data(root_ptr->data());
			root_ptr->set_data(largest);
		}
		else {
			right_ptr->set_data(root_ptr->data());
			root_ptr->set_data(largest);
		}
	}

	if (left_ptr != nullptr) 
		btn_to_heap(left_ptr);

	if (right_ptr != nullptr)
		btn_to_heap(right_ptr);
	
}
