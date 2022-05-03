// FILE: bag6.h (part of the namespace main_savitch_10)
// TEMPLATE CLASS PROVIDED: bag<Item>
//     (a container template class for a collection of items)
//
// TYPEDEFS for the bag<Item> class:
//   bag<Item>::value_type
//     bag<Item>::value_type is the data type of the items in the bag. It may
//     be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, a copy constructor, an assignment operator, and a
//     less-than operator forming a strict weak ordering.
//
//   bag<Item>::size_type
//     bag<Item>::size_type is the data type of any variable that keeps track
//     of how many items are in a bag.
//
// CONSTRUCTOR for the bag<Item> class:
//   bag( )
//     Postcondition: The bag is empty.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//   size_type erase(const Item& target)
//     Postcondition: All copies of target have been removed from the bag. The
//     return value is the number of copies removed (which could be zero).
//
//   bool erase_one(const Item& target)
//     Postcondition: If target was in the bag, then one copy of target has been
//     removed from the bag; otherwise the bag is unchanged. A true return value
//     indicates that one copy was removed; false indicates that nothing was
//     removed.
//
//   void insert(const Item& entry)
//     Postcondition: A new copy of entry has been inserted into the bag.
//
//   void operator +=(const bag& addend)
//     Postcondition: Each item in addend has been added to this bag.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//   size_type size( ) const
//     Postcondition: Return value is the total number of items in the bag.
//
//   size_type count(const Item& target) const
//     Postcondition: Return value is number of times target is in the bag.
//
// NONMEMBER FUNCTIONS for the bag class:
//   bag operator +(const bag& b1, const bag& b2)
//     Postcondition: The bag returned is the union of b1 and b2.
//
// VALUE SEMANTICS for the bag class:
//   Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by the bag: 
//   If there is insufficient dynamic memory, then the following functions
//   throw bad_alloc: The constructors, insert, operator +=, operator +, and
//   the assignment operator.

#ifndef BAG6_H 
#define BAG6_H
#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions

template <class Item>
class bag
{
public:
    // TYPEDEFS
    typedef std::size_t size_type;
    typedef Item value_type;
    // CONSTRUCTORS and DESTRUCTOR
    bag();
    bag(const bag& source);
    ~bag();
    // MODIFICATION functions
    size_type erase(const Item& target);
    bool erase_one(const Item& target);
    void insert(const Item& entry);
    void operator +=(const bag& addend);
    void operator =(const bag& source);
    // CONSTANT functions
    size_type size() const;
    size_type count(const Item& target) const;
    binary_tree_node<Item>* get_root_ptr() {
        return root_ptr;
    }

private:
    binary_tree_node<Item>* root_ptr; // Root pointer of binary search tree
    void insert_all(binary_tree_node<Item>* addroot_ptr);
};

// NONMEMBER functions for the bag<Item> template class
template <class Item>
bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);

// FILE: bag6.template
// -------------------------------------------------------------------------
// This is a partial implementation of the bag template class from Section
// 10.5 of "Data Structures and Other Objects Using C++". The parts marked
// with ***STUDENT WORK*** are left as a project for data structures
// students. Some additional discussion of this project is available at
// http://www.cs.colorado.edu/~main/projects/chap10a.html
// -------------------------------------------------------------------------
// TEMPLATE CLASS IMPLEMENTED: bag<Item> (see bag6.h for documentation)
// INVARIANT of the ADT:
//   root_ptr is the root pointer of a binary search tree that contains the
//   bag's items.

#include <cassert>
#include <cstdlib>

template <class Item>
void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
// Precondition: root_ptr is a root pointer of a non-empty binary
// search tree.
// Postcondition: The largest item in the binary search tree has been
// removed, and root_ptr now points to the root of the new (smaller)
// binary search tree. The reference parameter, removed, has been set
// to a copy of the removed item.
{
	if (root_ptr == NULL)
		return;
	else if (root_ptr->right() == NULL){
		removed = root_ptr->data();
		binary_tree_node <Item>* to_delete = root_ptr;
		root_ptr = root_ptr->left();
		delete to_delete;
	}
	else
		bst_remove_max(root_ptr->right(), removed);
}

template <class Item>
bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
// Precondition: root_ptr is a root pointer of a binary search tree
// or may be NULL for an empty tree).
// Postcondition: If target was in the tree, then one copy of target
// has been removed, and root_ptr now points to the root of the new
// (smaller) binary search tree. In this case the function returns true.
// If target was not in the tree, then the tree is unchanged (and the
// function returns false).
{
	binary_tree_node<Item>* oldroot_ptr;

	if (root_ptr == NULL)
	{   // Empty tree
		return false;
	}

	if (target < root_ptr->data())
	{   // Continue looking in the left subtree
		return bst_remove(root_ptr->left(), target);
	}

	if (target > root_ptr->data())
	{   // Continue looking in the right subtree
		return bst_remove(root_ptr->right(), target);
	}

	if (root_ptr->left() == NULL)
	{   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->right();
		delete oldroot_ptr;
		return true;
	}

	// If code reaches this point, then we must remove the target from
	// the current node. We'll actually replace this target with the
	// maximum item in our left subtree.
	bst_remove_max(root_ptr->left(), root_ptr->data());
	return true;
}

template <class Item>
typename bag<Item>::size_type bst_remove_all(binary_tree_node<Item>*& root_ptr, const Item& target)
// Precondition: root_ptr is a root pointer of a binary search tree
// or may be NULL for an empty tree).
// Postcondition: All copies of target have been removed from the tree
// has been removed, and root_ptr now points to the root of the new
// (smaller) binary search tree. The return value tells how many copies
// of the target were removed.
{
	/** STUDENT WORK - complete this function
	 ** Note: This implementation is similar to bst_remove, except that
	 ** all occurrences of the target must be removed, and the return
	 ** value is the number of copies that were removed.
	 */

	binary_tree_node<Item>* oldroot_ptr;

	if (root_ptr == NULL)
	{   // Empty tree
		return 0;
	}

	if (target < root_ptr->data())
	{   // Continue looking in the left subtree
		return bst_remove_all(root_ptr->left(), target);
	}

	if (target > root_ptr->data())
	{   // Continue looking in the right subtree
		return bst_remove_all(root_ptr->right(), target);
	}

	if (root_ptr->left() == NULL)
	{   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
		oldroot_ptr = root_ptr;
		root_ptr = root_ptr->right();
		delete oldroot_ptr;
		return 1;
	}

	// If code reaches this point, then we must remove the target from
	// the current node. We'll actually replace this target with the
	// maximum item in our left subtree. We then continue
	// searching for more copies of the target to remove.
	// This continued search must start at the current root (since
	// the maximum element that we moved up from our left subtree
	// might also be a copy of the target).
	/* STUDENT WORK */
	bst_remove_max(root_ptr->left(), root_ptr->data());
	return 1 + bst_remove_all(root_ptr, target);
}

template <class Item>
bag<Item>::bag() {
	root_ptr = NULL;
}

template <class Item>
bag<Item>::bag(const bag<Item>& source)
	// Library facilities used: bintree.h
{
	root_ptr = tree_copy(source.root_ptr);
}

template <class Item>
bag<Item>::~bag()
	// Header file used: bintree.h
{
	tree_clear(root_ptr);
}

template <class Item>
typename bag<Item>::size_type bag<Item>::size() const
	// Header file used: bintree.h
{
	return tree_size(root_ptr);
}

template <class Item>
void bag<Item>::insert(const Item& entry)
// Header file used: bintree.h
{
	binary_tree_node<Item>* cursor;
	//Add first node of the binary search tree
	if (root_ptr == NULL)
	{
		root_ptr = new binary_tree_node<Item>(entry);
		return;
	}
	//move down tree and add new leaf
	else {
		cursor = root_ptr;
		binary_tree_node<Item>* new_entry;
		new_entry = new binary_tree_node<Item>(entry);
		bool finished = false;

		while (!finished) {
			if (cursor->data() < entry) {
				if (cursor->right() == NULL) {
					cursor->set_right(new_entry);
					finished = true;
				}
				cursor = cursor->right();
			}
			else {
				if (cursor->left() == NULL) {
					cursor->set_left(new_entry);
					finished = true;
				}
				cursor = cursor->left();
			}

		}
	}
}

template <class Item>
typename bag<Item>::size_type bag<Item>::count(const Item& target) const
{
	size_type answer = 0;
	binary_tree_node<Item>* cursor;

	cursor = root_ptr;
	/* STUDENT WORK */
	if (root_ptr == NULL)
		return answer;
	else {
		while (cursor != NULL) {

			if (cursor->data() < target)
				cursor = cursor->right();

			else if(cursor->data() > target)
				cursor = cursor->left();

			else if (cursor->data() == target) {
				answer++;
				cursor = cursor->left();
			}

		}
	}

	return answer;
}

template <class Item>
typename bag<Item>::size_type bag<Item>::erase(const Item& target)
{
	return bst_remove_all(root_ptr, target);
}

template <class Item>
bool bag<Item>::erase_one(const Item& target)
{
	return bst_remove(root_ptr, target);
}

template <class Item>
void bag<Item>::operator =(const bag<Item>& source)
	// Header file used: bintree.h
{
	if (root_ptr == source.root_ptr)
		return;
	tree_clear(root_ptr);
	root_ptr = tree_copy(source.root_ptr);
}

template <class Item>
void bag<Item>::operator +=(const bag<Item>& addend)
{
	if (root_ptr == addend.root_ptr)
	{
		bag<Item> copy = addend;
		insert_all(copy.root_ptr);
	}
	else
		insert_all(addend.root_ptr);
}

template <class Item>
bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
{
	bag<Item> answer = b1;
	answer += b2;
	return answer;
}

template <class Item>
void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
	// Precondition: addroot_ptr is the root pointer of a binary search tree that
	// is separate for the binary search tree of the bag that activated this
	// method.
	// Postcondition: All the items from the addroot_ptr's binary search tree
	// have been added to the binary search tree of the bag that activated this
	// method.
{
	if (addroot_ptr != NULL)
	{
		insert(addroot_ptr->data());
		insert_all(addroot_ptr->left());
		insert_all(addroot_ptr->right());
	}
}

#endif
