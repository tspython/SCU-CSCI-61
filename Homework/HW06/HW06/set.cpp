#include <iostream>
#include <cstdlib> // Provides size_t
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
	// Pseudocode for the public insert member function
	//pseudocode for insert
		//if (!loose_insert(entry))
			//Return false since loose_insert did not add a new entry to the set.
		//if (data_count > MAXIMUM)
			//Fix the root of the entire tree so that it no longer has too many entries.
			//Return true.
	if (!loose_insert(entry))
		return false;
	if (data_count > MAXIMUM) 
		fix_root(); //see below for implementaion of fixing root 
	return true;
}

template <class Item>
std::size_t set<Item>::erase(const Item& target) {
	// Pseudocode for the public erase member function
	//pseudocode for
		//removal
		//if (!loose_erase(target))
			//Return false since loose_erase did not remove an entry from the set.
		//if ((data_count == 0) && (child_count == 1))
			//Fix the root of the entire tree so that it no longer has zero entries.
				
	//did not remove entry
	if (!loose_erase(target))
		return false;
	//fix root
	if ((data == 0) && (child_count == 1)) {
		set<Item>* s = subset[0];

		for (int i = 0; i < s->data_count; i++)
			data[i] = s->data[i];
		for (int j = 0; j < s->child_count; j++)
			subset[j] = s->subset[j];
		delete s;
	}
	return true;
}

//constant member functions
template <class Item>
std::size_t set<Item>::count(const Item& target) const {
	size_t i = 0;
	if (empty())
		return 0;
	while (data[i] < target && i < data_count)
		i++;
	if (i < data_count && !(target < data[i]))
		return 1;
	else if (is_leaf())
		return 0;
	else
		return subset[i]->count(target);
}

//debugging functions
template <class Item>
void set<Item>::print(int indent) const {
	// This is a temporary public function for use by the programmer who implements the set
	// class. The function prints a representation of the set’s B-tree. The entries of the root node
	// are printed with an indentation given by the parameter, and each subtree has an extra
	// four spaces of indentation.
	// Library facilities used: iostream (provides cout), and iomanip (provides setw)

	const int EXTRA_INDENTATION = 4;
	size_t i;
	std::cout << setw(indent) << ""; // Print the indentation.
	// Print the data from the root.
	for (i = 0; i < data_count; ++i)
		cout << data[i] << " ";
	cout << endl;

	// Print the subtrees.
	for (i = 0; i < child_count; ++i)
		subset[i]->print(indent + EXTRA_INDENTATION);
}


//HELPER MEMBER FUNCTIONS
template <class Item>
bool  set<Item>::loose_insert(const Item& entry) {
	// Precondition: The entire B-tree is valid.
	// Postcondition: If entry was already in the set, then the set is unchanged
	// and the return value is false. Otherwise, the entry has been added to the
	// set, the return value is true, and the entire B-tree is still
	// valid EXCEPT that the number of entries in the root of this set might be
	// one more than the allowed maximum

	//Make a local variable, i, equal to the first index such that data[i] is not
	//less than entry.If there is no such index, then set i equal to data_count,
	//indicating that all of the entries are less than the target
	int i = 0;
	while ((data[i] < entry) && (i < data_count)) 
		i++;
	/*
	if (we found the new entry at data[i])
	pseudocode for 
	the loose insert
	2a. Return false with no further work (since the new entry is
	already in the set)
	*/
	if (data[i] == entry)
		return false;
	/*
	else if (the root has no children)
	2b. Add the new entry to the root at data[i]. (The original entries 
	at data[i] and afterwards must be shifted right to make room for 
	the new entry.) Return true to indicate that we added the entry.
	*/
	else if (is_leaf()) {
		for (int j = data_count; j > i; j--)
			data[j] = data[j - 1];

		data[i] = entry;
		data_count++;
		return true;
	}
	/*
	else
		{ 2c. Save the value from this recursive call:
		subset[i]->loose_insert(entry);
		Then check whether the root of subset[i] now has an excess
		entry; if so, then fix that problem.
		Return the saved value from the recursive call.
		}
	*/
	else {
		bool inserted = subset[i]->loose_insert(entry);
		if (subset[i]->data_count > MAXIMUM)
			subset[i]->fix_excess(i);
		return inserted;
	}
}

template <class Item>
bool  set<Item>::loose_erase(const Item& target) {
	// Precondition: The entire B-tree is valid.
	// Postcondition: If target was not in the set, then the set is unchanged and 
	// the return value is false. Otherwise, the target has been removed, the
	// return value is true, and the entire B-tree is still valid
	// EXCEPT that the number of entries in the root of this set might be one
	// less than the allowed minimum

	/*
	// Removing a target entry from a set (loose erase)
	1. Make a local variable, i, equal to the first index such that data[i] is not 
	less than target. If there is no such index, then set i equal to 
	data_count, indicating that all of the entries are less than the target.

	2. Deal with one of these four possibilities:
		2a.The root has no children, and we did not find the target: In this case,
		there is no work to do, since the target is not in the set (return false).

		2b.The root has no children, and we found the target: In this case,
		remove the target from the data array, and return true.

		2c.The root has children, and we did not find the target (see following).

		2d.The root has children, and we found the target (see following).
	*/

	//STEP 1
	int i = 0;
	while ((data[i] < target) && (i < data_count))
		i++;
	//no such index set to data_count;
	
	//STEP 2
	/* 2a */
	if (is_leaf() && !(i < data_count) && !(target < data[i]))
		return false;

	/* 2b */
	if (is_leaf() && (i < data_count) && !(target < data[i])) {
		//erasing target
		for (int j = i; j < data_count; j++)
			data[j] = data[j + 1];
		data_count--;
		return true;
	}

	/* 2c */
	else if (!is_leaf() && !(i < data_count) && !(target < data[i])) {
		subset[i]->loose_erase(target);

		if (subset[i]->data_count < MINIMUM)
			fix_shortage(i);

		return true;
	}

	/*2d*/
	else if (!is_leaf() && (i < data_count) && !(target < data[i])) {
		subset[i]->remove_biggest(data[i]);

		if (subset[i]->data_count < MINIMUM)
			fix_shortage(i);

		return true;
	}
}	

template <class Item>
void  set<Item>::remove_biggest(Item& removed_entry) {
	// Precondition: (data_count > 0) and the entire B-tree is valid.
	// Postcondition: The largest item in the set has been removed, and a copy 
	// of this removed entry has been placed in removed_entry. The entire 
	// B-tree is still valid, EXCEPT that the number of entries in the root of this
	// set might be one less than the allowed minimum

	/*if the root has no children. In this case,
	we copy the last item of data into the reference parameter, removed_entry.
	Then we subtract one from data_count. */
	if (is_leaf()) {
		data_count--;
		removed_entry = data[data_count];
	}
	/*What if the root has children? In this case, we make a recursive call to remove
	the largest entry from the rightmost child.*/
	else {
		subset[child_count - 1]->remove_biggest(removed_entry);

		/*So, after the recursive call, you should check the number
		of entries in the root of subset[child_count-1]. If the number of entries is less
		than MINIMUM, then call fix_shortage(child_count-1).*/
		if (subset[child_count - 1]->data_count < MINIMUM)
			fix_shortage(child_count - 1);
	}
}

template <class Item>
void  set<Item>::fix_excess(std::size_t i) {
	// Precondition: (i < child_count) and the entire B-tree is valid EXCEPT that
	// subset[i] has MAXIMUM + 1 entries.
	// Postcondition: The tree has been rearranged so that the entire B-tree is
	// valid EXCEPT that the number of entries in the root of this set might be
	// one more than the allowed maximum

	/*Fixing a Child with an Excess Entry
		To fix a child with MAXIMUM + 1 entries, the child node is split
		into two nodes that each contain MINIMUM entries. This
		leaves one extra entry, which is passed upward to the parent
	*/

	//VARS TO USE
	//new left and right childs
	set<Item>* left = new set<Item>;
	set<Item>* right = new set<Item>;

	
	if (data[i] != 0) {
		for (int j = data_count; j >= 0; j--) {
			if (i < j)
				data[j] = data[j - 1];
			else {
				data[i] = subset[i]->data[subset[i]->data_count / 2];
				data_count++;
				break;
			}
		}
	}
	else {
		data[i] = subset[i]->data[subset[i]->data_count / 2];
		data_count++;
	}

	left->data_count = 1;
	right->data_count = 1;

	//copy 
	for (int j = 0; j < MINIMUM; j++) {
		left->data[j] = subset[i]->data[j];
		right->data[j] = subset[i]->data[j + 2];
	}

	//middle
	int i2 = subset[i]->child_count / 2;
	
	for (int j = 0; j < i2; j++) {
		left->subset[j] = subset[i]->subset[j];
		right->subset[j] = subset[i]->subset[j + i2];
	}

	for (int j = child_count; j > (i + 1); j--) 
		subset[j] = subset[j - 1];

	if (i2 > 0) {
		left->child_count = 2;
		right->child_count = 2;
	}

	subset[child_count] = new set<Item>();
	for (int j = child_count; j > i; j--) 
		subset[j] = subset[j - 1];
	

	child_count++;
	subset[i] = left;
	subset[i + 1] = right;
	
}


template <class Item>
void  set<Item>::fix_shortage(std::size_t i) {
	cout << "reached fix_shortage" << endl;
	// Precondition: (i < child_count) and the entire B-tree is valid EXCEPT that
	// subset[i] has MINIMUM - 1 entries.
	// Postcondition: The tree has been rearranged so that the entire B-tree is
	// valid EXCEPT that the number of entries in the root of this set might be
	// one less than the allowed minimum.

	/*
	    Case 1 of fix_shortage: Transfer an extra entry from subset[i-1].
		Suppose that subset[i-1] has more than the minimum number of entries.
		Then we can carry out these transfers
		a. Transfer data[i-1] down to the front of subset[i]->data.
		Remember to shift over the existing entries to make room, and 
		add one to subset[i]->data_count.

		b. Transfer the final item of subset[i-1]->data up to replace data[i-1],
		and subtract one from subset[i-1]->data_count.

		c. If subset[i-1] has children, transfer the final child of subset[i-1] over 
		to the front of subset[i]. This involves shifting over the existing array 
		subset[i]->subset to make room for the new child pointer at 
		subset[i]->subset[0]. Also add one to subset[i]->child_count,
		and subtract one from subset[i-1]->child_count.
		*/
	
	//subset[i-1]
	if (i > 0 && subset[i-1] -> data_count > MINIMUM) { //initial condition
		case_one(i);
	}


	/*
	* Case 2 for fix_shortage: Transfer an extra entry from subset[i+1].
	* Another possibility is to transfer an extra entry from subset[i+1]. The work is
	* similar to what you have just seen for transferring an entry from subset[i-1]
	*/
	else if (i < child_count && subset[i + 1]->data_count > MINIMUM) { //initial condition
		case_two(i);
	}

	/*
	* 
	* Case 3 for fix_shortage: Combine subset[i] with subset[i-1].
	* Suppose that subset[i-1] is present (in other words, i>0), but it has only
	* MINIMUM entries. In this case, we cannot transfer an entry from subset[i-1],
	* but we can combine subset[i] with subset[i-1]. The combining occurs in
	* three steps
	* 
	* a. Transfer data[i-1] down to the end of subset[i-1]->data. This 
	* actually removes the item from the root, so shift data[i], data[i+1],
	* and so on, leftward to fill in the gap. Also remember to subtract one from 
	* data_count, and add one to subset[i-1]->data_count.
	* 
	* b. Transfer all the items and children from subset[i] to the
	* end of subset[i-1]. Remember to update the values of 
	* subset[i-1]->data_count and subset[i-1]->child_count. Also set 
	* subset[i]->data_count and subset[i]->child_count to zero.
	* 
	* c. Delete the node subset[i], and shift subset[i+1], subset[i+2], and 
	* so on, leftward to fill in the gap. Also reduce child_count by one.
	*/
	else if (i > 0 && subset[i-1]->data_count == MINIMUM) { //initial condition
		case_three(i);
	}


	/*
	* Case 4 for fix_shortage: Combine subset[i] with subset[i+1].
	* Our fourth case is to combine the problem subset with subset[i+1]. The work
	* is similar to what you have just seen for combining with subset[i-1].
	* You now have enough information to write the fix_shortage member
	* function. You should emphasize a clear logical structure to determine which of
	* the four cases is appropriate. Your implementation will be cleaner if you provide
	* four new private member functions to do the actual work in each of the four
	* cases
	*/
	else{
		case_four(i);
	}

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

template <class Item>
void set<Item>::fix_root() {
	/*The first part copies all entries and child pointers from the root to a newly allocated
	node and clears out the root, leaving it with one child (which is the newly allocated node) and no entries*/

	//new node
	set<Item>* s = new set<Item>();
	s->data_count = data_count;
	s->child_count = child_count;

	//copy entries and pointers
	for (int i = 0; i < child_count; i++)
		s->data[i] = data[i];
	for (int j = 0; j < child_count; j++)
		s->subset[j] = subset[j];

	//leaving it with one child (which is the newly allocated node) and no entries*
	data_count = 0;
	child_count = 1;

	subset[0] = s;
	/*
	* Once we have shifted things in this way, the problem is now with the child of
	* the root. We can fix this problem by splitting the subset[0] of the root into two
	* nodes and passing the middle entry upward. In fact, if you are careful in writing
	* fix_excess, this splitting can be carried out by calling fix_excess(0).
	*/

	//splitting
	fix_excess(0);
}

//seperate sub-functions for clarity algorithms for each described in the original fix_shortage() function;
template <class Item>
void set<Item>::case_one(size_t i) {
	//a.
	for (int j = subset[i]->data_count; j > 0; j--)
		subset[i]->data[j] = subset[i]->data[j - 1];

	//b. 
	subset[i]->data[0] = data[i - 1];
	subset[i]->data_count++;
	data[i - 1] = subset[i - 1]->data[subset[i - 1]->data_count - 1];
	subset[i - 1]->data_count--;

	//c.
	if (!subset[i - 1]->is_leaf()) { //if subset[i-1] has children

		for (int j = subset[i]->child_count; j > 0; j--)
			subset[i]->subset[j] = subset[i]->subset[j - 1];

		subset[i]->subset[0] = subset[i - 1]->subset[child_count - 1];
		subset[i - 1]->subset[child_count - 1] = nullptr;
		subset[i]->child_count++;
		subset[i - 1]->child_count--;
	}
}

template <class Item>
void set<Item>::case_two(size_t i) {
	subset[i]->data_count++;
	subset[i]->data[subset[i]->data_count - 1] = data[i];
	data[i] = subset[i + 1]->data[0];

	for(int j = 0; subset[i + 1]->data_count; j++)
		subset[i + 1]->data[j] = subset[i + 1]->data[j + 1];

	subset[i + 1]->data_count--;

	if (!(subset[i + 1]->is_leaf())) {
		subset[i]->subset[subset[i]->child_count++] = subset[i + 1]->subset[0];

		for(int j = 0; j < subset[i]->child_count; j++)
			subset[i + 1]->subset[j] = subset[i + 1]->subset[j + 1];

		subset[i]->child_count++;
		subset[i + 1]->child_count--;
	}
}

template <class Item>
void set<Item>::case_three(size_t i) {
	subset[i - 1]->data[subset[i - 1]->data_count] = data[i - 1];

	for (int j = i - 1; j < data_count; j++)
		data[j] = data[j + 1];
	data_count--;
	subset[i - 1]->data_count++;

	for (int j = 0; j < subset[i]->data_count; j++)
		subset[i - 1]->data[subset[i - 1]->data_count++] = subset[i]->data[j];
	

	for (int j = 0; j < subset[i]->child_count; j++)
		subset[i - 1]->subset[(subset[i - 1]->child_count) ++] = subset[i]->subset[j];
	

	subset[i]->data_count = 0;
	subset[i]->child_count = 0;
	delete subset[i];

	for (i = i; i < child_count; i++)
		subset[i] = subset[i + 1];

	child_count--;
}

//SIMILAR IMPLEMENTATION TO CASE_THREE
template <class Item>
void set<Item>::case_four(size_t i) {

	subset[i]->data[subset[i]->data_count] = data[i + 1];
	for (int j = 1; j < data_count; j++)
		data[j - 1] = data[j];
	data_count--;
	subset[i]->data_count++;
	
	child_count--;

	//transfer data/child
	for (int j = 0; j < subset[i + 1]->data_count; j++)
		subset[i]->data[subset[i]->data_count++] = subset[i + 1]->data[j];
	
	for (int j = 0; j < subset[i + 1]->child_count; j++)
		subset[i]->subset[subset[i]->child_count++] = subset[i + 1]->subset[j];

	subset[i + 1]->data_count = 0;
	subset[i + 1]->data_count = 0;

	for (int j = i + 1; j < child_count; j++)
		subset[j] = subset[j + 1];
	
}

int main() {
	set<int> tree;

	tree.insert(5);
	tree.insert(19);
	tree.insert(3);
	tree.insert(503003);
	tree.insert(22);
	tree.insert(34443);
	tree.insert(21);
	tree.insert(34);
	tree.insert(70);
	tree.insert(69);
	tree.insert(420);
	tree.insert(313);
	tree.insert(7);
	tree.insert(3212);
	tree.insert(8);
	tree.insert(193);
	tree.insert(37);
	tree.insert(666);
	tree.insert(99);
	tree.insert(212);
	tree.insert(1);
	tree.insert(0);
	tree.insert(47);

	tree.print(0);

	tree.erase(19);
	tree.print(0);

	tree.erase(34443);
	tree.print(0);

	tree.erase(7);
	tree.print(0);

	tree.erase(69);
	tree.print(0);

	tree.erase(193);
	tree.print(0);

	tree.erase(3);
	tree.print(0);

	tree.erase(21);
	tree.print(0);

	tree.erase(420);
	tree.print(0);

	tree.erase(70);
	tree.print(0);
	return 0;
}