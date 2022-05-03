
#include <iostream>
#include "bag6.h"
#include "bintree.h"

using namespace std;

int main() {

	bag<int> b;

	//testing insert
	b.insert(50);
	b.insert(2);
	b.insert(3);
	b.insert(777);
	b.insert(3);
	b.insert(21);
	b.insert(74);

	cout << "tree after insert" << endl;
	print(b.get_root_ptr(), 3);
	
	cout << "number of 3's in tree:" << b.count(3) << endl; //2


	cout << "erasing all 3's from tree (testing bst_remove_all)" << endl;
	b.erase(3);   //going to erase all threes

	
	cout << "number of 3's after erasing:" << b.count(3) << endl; //0

	cout << "tree after removal of all 3's" << endl;
	print(b.get_root_ptr(), 2);

	return 0;
}
