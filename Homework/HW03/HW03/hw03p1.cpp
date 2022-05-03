/*
#include <iostream>

using namespace std;

int count_binary_tree(int num_of_nodes);

//EXPLANATION OF CODE
/*
*  Q: Use recursion to argue that there are 5 different binary trees with 3 nodes.
*		A: To find that there are 5 different binary trees with 3 nodes, we must devise
*			a recursive algorithm. Below is code that employs this algorithm to ouput
*			how many possible binary trees exist for n nodes. The way that this algorithm
*			works is by multiplying the count of possible pairs by recursivley iterating 
*			through left and right nodes. Then we add these together and result in the 
*			final number of possible binary trees.
*			
*  Q: How many different binary trees with 4 nodes are there ? Justify your answer.
*		14 using algorithm described above.
* 



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