#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int data = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	unsigned char height;
};

class AVL {
	Node* root;
public:
	AVL() {
		root = new Node;
		root->height = 1;
	}
	AVL(int x) {
		root = new Node;
		root->data = x;
		root->height = 1;
	}
	~AVL() {
		delete_tree(root);
	}
	void delete_tree(Node* root) {
		if (root->left) delete_tree(root->left);
		if (root->right) delete_tree(root->right);
		delete root;
	}
	unsigned char height(Node* p){
		return p ? p->height : 0;
	}
	int bfactor(Node* p){
		return height(p->right) - height(p->left);
	}
	void fixheight(Node* p){
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	Node* rotateright(Node* p) {
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}
	Node* rotateleft(Node* q) {
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}
	Node* balance(Node* p) {
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}
	bool dfs(Node* t, int x) {
		if (t->data == x) return 1;
		if ((t->left) && (dfs(t->left, x))) return 1;
		if ((t->right) && (dfs(t->right, x))) return 1;
		return 0;
	}
	void search(int x) {
		Node* temp = root;
		if (dfs(temp, x)) std::cout << x << " is in this tree " << std::endl;
		else std::cout << x << " isn't in this tree " << std::endl;
	}
	Node* down(Node* t, int x) {
		Node* temp = t;
		while (((temp->left) && (temp->right)) && (temp->data != x)) {
			if ((temp->left) && (temp->data > x)) temp = temp->left;
			else if ((temp->right) && (temp->data < x)) temp = temp->right;
		}
		if ((temp->left) && (temp->data > x)) temp = down(temp->left, x);
		else if ((temp->right) && (temp->data < x)) temp = down(temp->right, x);
		if ((!temp->left) && (temp->data > x)) return temp;
		else if ((!temp->right) && (temp->data < x)) return temp;

	}
	void push(int x) {
		if (!root->data) root->data = x;
		else {
			Node* temp = root;
			temp = down(temp, x);
			if (temp->data > x) { temp->left = new Node;  temp->left->data = x; }
			else if (temp->data < x) { temp->right = new Node; temp->right->data = x; }
		}
		root=balance(root);
	}
	void print() {
		Node* temp = root;
		print_t(temp);
		std::cout << endl;
	}
	void print_t(Node* temp) {
		if (temp->left) print_t(temp->left);
		std::cout << temp->data << ' ';
		if (temp->right) print_t(temp->right);
	}
	void bfs(Node* root) {
		queue<Node*>A;
		A.push(root);
		int i = 0;
		while (!A.empty()) {
			Node* temp = A.front();
			A.pop();
			std::cout << temp->data << " ";
			if (temp->left) A.push(temp->left);
			if (temp->right) A.push(temp->right);
			if (i % 2 == 0) std::cout << std::endl;
			i++;
		}
	}
	void print_tree() {
		bfs(root);
	}
};
int main() {
	AVL A;
	A.push(5);
	A.push(3);
	A.push(4);
	A.push(6);
	A.push(7);
	A.push(8);
	A.push(9);
	A.print();
	A.print_tree();
}
