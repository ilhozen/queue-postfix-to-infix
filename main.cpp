#include <iostream>
#include <cctype>
#include <cstring>
#include <queue>
using namespace std;
const int MAX_SIZE = 10000; // Maximum size of the stack

template<typename T>//template<class T> could also be used.
class Stack {
private:
	T arr[MAX_SIZE];
	int topIndex; // Index of the top element in the stack
	int stackSize; // Size of the stack
public:
	// Constructor
	Stack(int sz = 100) : topIndex(-1), stackSize(sz) {
		if (sz > MAX_SIZE) {
			cout << "System Error: Size cannot be greater than " << MAX_SIZE << endl;
			exit(EXIT_FAILURE);
		}
	}

	// Pushes an element onto the stack
	void push(const T& value) {
		if (topIndex >= stackSize - 1) {
			cout << "Error: Stack overflow. Cannot push.";
			exit(EXIT_FAILURE);
		}
		arr[++topIndex] = value;
	}

	// Removes and returns the top element from the stack
	T pop() {
		if (isEmpty()) {
			cout << "Error: Stack is empty. Cannot pop.";
			exit(EXIT_FAILURE);
		}
		return arr[topIndex--];
	}

	// Returns the top element from the stack without removing it
	T top() const {
		if (isEmpty()) {
			cout << "Error: Stack is empty. No top element.";
			exit(EXIT_FAILURE);
		}
		return arr[topIndex];
	}

	// Checks if the stack is empty
	bool isEmpty() const {
		return topIndex == -1;
	}
};

bool isOperand(char op) {
	return '0' <= op && '9' >= op;
}
bool isOperator(char op) {
	switch (op) {
	case '+':
	case '-':
	case '*':
	case '/': return true;
	}
	return false;
}

double calc(double op1, double op2, char op) {
	switch (op) {
	case '+': return op1 + op2;
	case '-':return op1 - op2;
	case '*':return op1 * op2;
	case '/': return  op1 / op2;
	}

}
int evalPosftix(queue<char> postFix) {
	Stack<double> s;
	while (!postFix.empty()) {
		char symb = postFix.front();
		if (isOperand(symb))
			s.push(symb - '0'); //since symb is single digit char: we can obtain its decimal equivalent by subtracting '0'
		else if (isOperator(symb)) {
			if (s.isEmpty()) {
				cout << "\n1. Error in expression (at least one operand is missing";
				exit(0);
			}
			double op2 = s.pop();
			if (s.isEmpty()) {
				cout << "\n2. Error in expression (at least one operand is missing";
				exit(0);
			}
			double op1 = s.pop();
			double res = calc(op1, op2, symb);
			s.push(res);
		}
		else if (!isspace(symb)) {
			cout << "Undefined symbol:" << symb << endl;
			exit(0);
		}
		postFix.pop();

	}//end of while
	if (s.isEmpty()) {
		cout << "\n3. Error in expression (at least one operator is missing";
		exit(0);
	}
	double potentialRes = s.pop();
	if (!s.isEmpty()) {
		cout << "\n4. Error in expression (at least one operator is missing";
		exit(0);
	}
	return potentialRes;
}

char* myStrcpy(char* t, const char* src) {
	int i = 0;
	while (*src != '\0')
		t[i++] = *(src++);
	t[i] = '\0';
	return t;
}
void postFixToInfix(queue<char> postFix, char* infix) {
	Stack<string> s;
	while (!postFix.empty()) {
		char symb = postFix.front();
		if (isOperand(symb)) {
			string s1(" ");
			s1[0] = symb;
			s.push(s1); //since symb is single digit char: we can obtain its decimal equivalent by subtracting '0'
		}
		else if (isOperator(symb)) {
			if (s.isEmpty()) {
				cout << "\n1. Error in expression (at least one operand is missing";
				exit(0);
			}
			string op2 = s.pop();
			if (s.isEmpty()) {
				cout << "\n2. Error in expression (at least one operand is missing";
				exit(0);
			}
			string oprt(" ");
			oprt[0] = symb;
			string op1 = s.pop();
			string subExp = "(" + op1 + oprt + op2 + ")";
			s.push(subExp);
		}
		else if (!isspace(symb)) {
			cout << "Undefined symbol:" << symb << endl;
			exit(0);
		}
		postFix.pop();

	}//end of while
	if (s.isEmpty()) {
		cout << "\n3. Error in expression (at least one operator is missing";
		exit(0);
	}
	string potentialInfix = s.pop();
	if (!s.isEmpty()) {
		cout << "\n4. Error in expression (at least one operator is missing";
		exit(0);
	}
	myStrcpy(infix, potentialInfix.c_str());
}

void printPostFix(queue<char> postFix) {
	while (!postFix.empty()) {
		cout << postFix.front() << " ";
		postFix.pop();
	}
}

int main() {
	queue<char> postFix;
	postFix.push('4');
	postFix.push(' ');
	postFix.push('5');
	postFix.push(' ');
	postFix.push('7');
	postFix.push(' ');
	postFix.push('2');
	postFix.push(' ');
	postFix.push('+');
	postFix.push(' ');
	postFix.push('-');
	postFix.push(' ');
	postFix.push('*');
	
	printPostFix(postFix);
	cout << " evaluates to: " << evalPosftix(postFix) << endl;
	char infix[500];
	postFixToInfix(postFix, infix);
	printPostFix(postFix);
	cout << " is Equivalent to:  " << infix << endl;

	return 0;
}