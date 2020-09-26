/*
 * This is a similar idea of using recusrive.
 */
#include <iostream>

using namespace std;

class Node {
public:
	Node(int i);
	virtual ~Node();
	Node* next;
	int v;
};

Node::Node(int i)
	:v(i), next(0)
{
}

Node::~Node()
{
}

void print_in_order(Node *n)
{
	while (n != 0) {
		cout << n->v << endl;
		n = n->next;
	}
}

void print_reverse(Node *n)
{
	if (n == 0) { return; }
	if (n->next == 0) {
		cout << n->v << endl;
		return;
	}
	print_reverse(n->next);
	cout << n->v << endl;
	return;
}

int main()
{
	Node* root = new Node(0);
	Node* n = root;
	for (int i = 1; i < 10; ++i) {
		Node* node = new Node(i);
		n->next = node;
		n = node;
	}
	cout << "In order: " << endl;
	print_in_order(root);
	cout << "Reverse order: " << endl;
	print_reverse(root);
}
