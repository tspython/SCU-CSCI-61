
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>

using namespace std;

class tree_node {
	public:
		string data;
		tree_node* left, * right;
		
		tree_node(string d) {
			data = d;
			left = nullptr;
			right = nullptr;
		}
};

class stack_node {
	public:
		tree_node* tn;
		stack_node* sn;
		stack_node(tree_node* tnp) {
			tn = tnp;
			sn = nullptr;
		}
};

class ExpressionTree {
	public:
		ExpressionTree() {
			top = nullptr;
		}

		//helper
		bool is_operator(string op)
		{
			return op == "+" || op == "-" || op == "*" || op == "/";
		}

		void push(tree_node *t) {
			if (top == nullptr)
				top = new stack_node(t);
			else {
				stack_node* nsn = new stack_node(t);
				nsn->sn = top;
				top = nsn;
			}
		}

		tree_node* pop() {
			if (top == nullptr) 
				cout << "TREE UNDERFLOW ERROR" << endl;
			else {
				tree_node* tmp = top->tn;
				top = top->sn;
				return tmp;
			}
		}

		tree_node* peek() {
			return top->tn;
		}

		void insert(string n) {
			if (is_operator(n)) {
				tree_node *tmp = new tree_node(n);
				tmp->left = pop();
				tmp->right = pop();
				push(tmp);
			}
			else {
				tree_node* tmp = new tree_node(n);
				push(tmp);
			}
		}

		void build_tree(string prefix[], int l) {
			for (int i = l - 1; i >= 0; i--)
				insert(prefix[i]);
		}

		void pre_order(tree_node* t, int depth) {
			if (t != nullptr) {

				pre_order(t->left, depth + 1);
				cout << setw(4 * depth) << ""; // Indent 4*depth spaces.
				cout << t->data << endl;
				pre_order(t->right, depth + 1);
			}
		}

		void prefix_to_binary_tree(int depth) {
			pre_order(peek(), depth);
		}


	private:
		stack_node* top;
};

int main() {
	//will add a proper user interface 
	string expression[7] = { "*", "+", "6", "99", "-", "21", "33" };
	ExpressionTree exp;
	exp.build_tree(expression, 7);
	cout << "Prefix Tree: " << endl;
	exp.prefix_to_binary_tree(3);
	cout << endl;
	return 0;
}
