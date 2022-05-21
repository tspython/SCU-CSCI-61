#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "set.h"

using namespace std;

//Constructors and Destructor
template <class Item>
set<Item>::set() {
	data_count = 0;
	child_count = 0;
}

template <class Item>
set<Item>::set(const set& source) {
	copy_set(source);
}

// MODIFICATION MEMBER FUNCTIONS
template <class Item>
void set<Item>::operator =(const set& source) {
	copy_set(source);
}

template <class Item>
void set<Item>::clear() {
	data_count = 0;
	for (int i = 0; i < child_count; i++)
		subset[i]->clear();
	child_count = 0;
}

template <class Item>
bool set<Item>::insert(const Item& entry) {
	if (!loose_insert(entry))
		return false;
}

template <class Item>
std::size_t set<Item>::erase(const Item& target) {
	

}

//constant member functions
template <class Item>
std::size_t set<Item>::count(const Item& target) const {
	size_t index = 0;
	if (empty())
		return 0;
	while (data[index] < target && index < data_count)
		i++;
	if (index < data_count && !(target < data[index]))
		return 1;
	else if (is_leaf())
		return 0;
	else
		return subset[index]->count(target);
}

//debbugging functions
template <class Item>
void set<Item>::print(int indent) const {
	if (this == NULL)
		return;
	const int EXTRA_INDENT = 4;
	int i;
	cout << setw(indent) << "";
	for (i = 0; i < data_count; i++)
		cout << data[i] << " ";
	cout << endl;

	for (i = 0; i < child_count; i++)
		subset[i]->print(indent + EXTRA_INDENT);
}

//HELPER MEMBER FUNCTIONS
template <class Item>
bool  set<Item>::loose_insert(const Item& entry) {
}

template <class Item>
bool  set<Item>::loose_erase(const Item& target) {

}

template <class Item>
void  set<Item>::remove_biggest(Item& removed_entry) {

}

template <class Item>
void  set<Item>::fix_excess(std::size_t i) {

}

template <class Item>
void  set<Item>::fix_shortage(std::size_t i) {

}


// HELPER MEMBER FUNCTIONS OF MY OWN
template <class Item>
void set<Item>::copy_set(const set& set) {
	data_count = set.data_count;
	for (int i = 0; i < data_count; i++)
		data[i] = set.data[i];
	child_count = set.child_count;
	for (int i = 0; i < child_count; i++)
		subset[i] = set.subset[i];
}
