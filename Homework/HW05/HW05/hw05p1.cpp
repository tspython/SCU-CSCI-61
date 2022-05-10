/*
#include <iostream>
#include "bag6.h"
#include "bintree.h"
using namespace std;

int main() {

	bag<char> b;

	b.insert('S');
	b.insert('F');
	b.insert('E');
	b.insert('V');
	b.insert('D');
	b.insert('U');
	b.insert('J');
	b.insert('P');
	b.insert('O');
	b.insert('T');

	cout << "tree before any removals" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('S');
	cout << "tree after removing s" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('F');
	cout << "tree after removing f" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('E');
	cout << "tree after removing e" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('V');
	cout << "tree after removing v" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('D');
	cout << "tree after removing d" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('U');
	cout << "tree after removing u" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('J');
	cout << "tree after removing j" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('P');
	cout << "tree after removing p" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	b.erase_one('O');
	cout << "tree after removing o" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;
	b.erase_one('T');

	cout << "tree after removing t" << endl;
	print(b.get_root_ptr(), b.size());
	cout << endl;

	return 0;
}
*/