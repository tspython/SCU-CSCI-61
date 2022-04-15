/*
* FILE: hw01.cpp
* Author: Tushar Shrivastav
* Class: CSCI 61 
*/

#include <stack>
#include <iostream>
#include <string>
using namespace std;

//FUNCTION PROTOTYPES
string prefixToInfix(string input);
//Precondition: takes an prefix expression
//Postcondition: outputs equivilent infix expression 

string infixToPrefix(string input);
//Precondition: takes in an infix expression
//Postcondition: outputs equivalent Prefix expression

int operator_precedence(char op);
//Precondition: takes in an operator character
//Postcondition: returns its precedence

string infixtoPrefixReverse(string postfix);
//Precondition: takes in a infix expression
//Postcondition: returns a reversed infix with brackets replaced

int main() {
	string input;
	string exp_name;
	int choice = 0;
	cout << "Input 1 for Infix to Prefix Conversion or Input 2 for Prefix to Infix Conversion: ";
	cin >> choice;
	if (choice == 1)
		exp_name = "Infix";
	else
		exp_name = "Prefix(with spaces in between operators/operands)";
	cout << endl;
	cout << "Enter " + exp_name + " expression: ";
	
	cin.ignore();
	getline(cin, input);	

	if (choice == 1) 
		input = infixToPrefix(input);
	else 
		input = prefixToInfix(input);

	cout << input << endl;
	
	return 0;
}

//HELPER FUNCTIONS
int operator_precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	if(op == '*' || op == '/')
		return 2;
	return 0;
}

string infixtoPrefixReverse(string postfix) {

	reverse(postfix.begin(), postfix.end());

	//fix the brackets if needed
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i] == '(') {
			postfix[i] = ')';
			i++;
		}
		else if(postfix[i] == ')') {
			postfix[i] = '(';
			i++;
		}
	}

	return postfix;
}
//END OF HELPER FUNCTIONS

string prefixToInfix(string input) {
	stack<string> operands;
	string current_operand;

	int i = input.size() - 1;
	while (i >= 0) {
		if (isalpha(input[i]) || isdigit(input[i])) {
			while (isalpha(input[i]) || isdigit(input[i])) {
				current_operand += input[i];
				i--;
			}
			reverse(current_operand.begin(), current_operand.end());
			operands.push(current_operand);
			current_operand = "";
		}
		else if (input[i] != ' ') { //when we reach an operator
			string operand_one = operands.top();
			operands.pop();

			string operand_two = operands.top();
			operands.pop();

			operands.push('(' + operand_one + input[i] + operand_two + ')');
		}
		i--;
	}

	return operands.top();
}

string infixToPrefix(string input) {
	stack<char> operators;
	string output;
	
	//reverse infix
	input = infixtoPrefixReverse(input);
	
	//convert to postfix
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '(') 
			operators.push(input[i]);
	
		else if (isalpha(input[i]) || isdigit(input[i])){
			output += input[i];
		}
		else if (strchr("+-*/", input[i]) != NULL) {
			while (!operators.empty() &&  !(input[i] == '(') &&
					(operator_precedence(operators.top()) >= operator_precedence(input[i]))) {
				output += operators.top();
				operators.pop();
			}
			output += " "; //add space between numbers
			operators.push(input[i]);
		}
		else {
			while (operators.top() != '(') {
				output += operators.top();
				operators.pop();
			}
			operators.pop();
		}
	}
		
	while (!operators.empty()){
		if(operators.top() != '(')
			output += operators.top();
		operators.pop();
	}

	//reverse string function
	reverse(output.begin(), output.end());

	return output;
}