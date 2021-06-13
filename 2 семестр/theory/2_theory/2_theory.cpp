#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct Node {
	T data;
	Node* next = NULL;
};
template <typename T>
class Stack {
	Node<T>* head;
public:
	Stack(int i) {
		head = new Node<T>;
		head->data = i;
	}
	Stack() {
		head = new Node<T>;
	}
	~Stack() {
		while (head) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void push(int x) {
		Node<T>* temp = new Node<T>;
		temp->next = head;
		temp->data = x;
		head = temp;
	}
	T pop() {
		if (!head) {
			cerr << "stack is empty !";
			return 0;
		}
		Node<T>* temp = head;
		head = head->next;
		T res = temp->data;
		delete temp;
		return res;
	}
	T top()const {
		if (!head) {
			cerr << "stack is empty !";
			return 0;
		}
		return head->data;
	}
	T EOS() {
		Node<T>* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return temp->data;
	}
	friend class C2Ppn;
};
class C2Ppn {
	char curc;
	string str_in, str_out;   
	size_t iin;

	char nextChar() {
		if (iin < str_in.length()) {
			return curc = str_in[iin++];
		}
		else return curc = '\0';
	}
	bool isDigit(char c) {
		return (c >= '0' && c <= '9');
	}
	int prior(char c) {
		switch (c) {
		case '(': return 1;
		case '+': case '-': return 2;
		case '*': case '/': return 3;
		default: return 0;
		}
	}
public:
	void convert(string str) {
		int was_op = 0, np = 0;
		iin = 0;
		Stack<char> op_stack;
		str_in = str;
		if ((!isDigit(str_in[0])) && str_in[0] != '(')
			throw (string)"Syntax error";
		while (nextChar() != '\0') {
			if (isDigit(curc)) {
				str_out += curc;
				was_op = 0;
				continue;
			}
			else str_out += ' ';
			switch (curc) {
			case '(':
				op_stack.push(curc);
				++np;
				was_op = 0;
				break;
			case '*': case '/': case '+': case '-':
				if (iin == str_in.length())
					throw (string)"Syntax error";
				if (!was_op) {
					was_op = 1;
					while (prior(curc) <= prior(op_stack.top())) {
						str_out += op_stack.pop();
					}
					if (prior(curc) > prior(op_stack.top())) {
						op_stack.push(curc);
					}
					break;
				}
				else throw (string)"Syntax error";

			case ')':
				if (was_op)
					throw (string)"Syntax error";
				else
					while ((curc = op_stack.pop()) != '(' && np > 0) {
						str_out += curc;
					}
				--np;
				break;
			default: {
				throw (string)"Error: invalid symbol in the string";
			}
			}
		}
		while (op_stack.top() != op_stack.EOS())
			str_out += op_stack.pop();
		if (np)
			throw (string)"Error: wrong number of brackets";
	}
	string get_str_out()const {
		return str_out;
	}
};
int main() {
	string S;
	std::cin >> S;
	C2Ppn A;
	A.convert(S);
	std::cout << A.get_str_out();
}