/*
 * Breadth First walk of a binary tree (not necessarily search tree)
 */

#include <iostream>
#include <queue>
// we should use push() and pop()

using namespace std;

class Node
{
public:
	Node(int val);
	virtual ~Node() {};
	void setLeft(Node* l);
	void setRight(Node* r);
	void bfPrint();

	Node* left;
	Node* right;
	int v;
	unsigned int level;
};


Node::Node(int val)
:left(0), right(0), level(0)
{
	v = val;
}

void
Node::setLeft(Node* l)
{
	this->left = l;
	if (l) {
		l->level = this->level + 1;
	}
}

void
Node::setRight(Node* r)
{
	this->right = r;
	if (r) {
		r->level = this->level + 1;
	}
}

void
Node::bfPrint()
{
	queue<Node*> bf_queue;
	bf_queue.push(this);
	while (!bf_queue.empty()) {
		Node* c = bf_queue.front();
		if (c->left) { bf_queue.push(c->left); }
		if (c->right) { bf_queue.push(c->right); }
		cout << c->v << " ";
		bf_queue.pop();
		// anytime use front(), check !empty()
		if (!bf_queue.empty() &&
		    (bf_queue.front()->level != c->level)) {
			assert(bf_queue.front()->level > c->level);
			cout << endl;
		}
	}
	cout << endl;
}

int main()
{
	Node* a = new Node(1);
	Node* b = new Node(2);
	Node* c = new Node(3);
	Node* d = new Node(4);
	Node* e = new Node(5);
	Node* f = new Node(6);
	Node* g = new Node(7);

	a->setLeft(b);
	a->setRight(c);
	b->setLeft(d);
	b->setRight(e);
	c->setLeft(f);
	c->setRight(g);

	a->bfPrint();
	b->bfPrint();
	c->bfPrint();
}
