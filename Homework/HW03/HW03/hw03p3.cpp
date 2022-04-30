#include <iostream>
#include "bag6.h"

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

	cout << "l" << endl;
	cout << b.count(3) << endl; //2
	cout << "l" << endl;

	b.erase(3); //going to erase all threes

	cout << b.count(3) << endl; //0

	return 0;
}