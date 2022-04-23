/*
#include <iostream>

using namespace std;

int count_binary_tree(int num_of_nodes);


int main() {
	int num = 0;
	cout << "Enter Number of Nodes in Binary Tree: ";
	cin >> num;
	cout << endl;
	cout << count_binary_tree(num) << endl;
	return 0;
}

int count_binary_tree(int num_of_nodes) {
	if (num_of_nodes <= 1) //base case
		return 1;
	else {
		int count = 0;
		for (int i = 0; i < num_of_nodes; i++)
			count += count_binary_tree(i) * count_binary_tree(num_of_nodes - i - 1);
		return count;
	}
}
*/
