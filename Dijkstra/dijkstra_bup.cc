/* 
 * My own implementation of Dijkstra's algorithm
 * to find the shortest path in Graph.
 */
//#include <priority_queue> -- error, <queue> header covers everything.
#include <queue>
#include <string> // -- error, C++ need this header
#include <iostream>
#include <stdio.h>

using namespace std; // -- error, need name space.

class AdjNode; // --err, this breaks the dependency.

class Node 
{
public:
	Node(string s);
	virtual ~Node() {};

	string id;
	AdjNode* adj;

	int pd; // shortest distance
	string prev;
	bool visited;

	bool operator< (const Node& r);
	void addPeer(Node* n, int d);
};

Node::Node(string s)
: id(s), adj(0), pd(0xFFFFFF), prev(s), visited(false)
{
}

bool
Node::operator< (const Node& r)
{
	return (pd < r.pd);
}

class AdjNode
{
public:
	AdjNode(Node* node, int dis);
	~AdjNode() {};
	Node* n;
	int d;
	AdjNode* next;
}; // -- error, never miss this

AdjNode::AdjNode(Node* node, int dis)
:n(node), d(dis), next(0)
{
}

void Node::addPeer(Node* n, int d)
{
	AdjNode* tmp = adj;
	AdjNode* new_node = new AdjNode(n, d);
	adj = new_node;
	new_node->next = tmp;
}

void shortest_path(Node* a)
{
	if (a == 0) return;
	priority_queue<Node*> queue;
	queue.push(a);
	a->pd = 0;
	while (!queue.empty()) { // -- error, just empty()
		Node* c = queue.top();
		queue.pop();
		cout << "pop: " << c->id << endl;
		c->visited = true;
		AdjNode* adj = c->adj;
		while (adj != 0) {
			if (adj->n->visited) {
				adj = adj->next;
				continue;
			}
			// if Node in the queue, better to take it out
			// but do not HAVE to
			if ((adj->d + c->pd) < (adj->n->pd)) {
				adj->n->pd = (adj->d + c->pd);
				adj->n->prev = c->id;
			}
			queue.push(adj->n);
			cout << "push: " << adj->n->id << endl;
			adj = adj->next;
		}
	}
	
}

void print_shortest (Node* n)
{
	cout << "Node: " << n->id 
             << " shortest distnace to A is: " << n->pd 
             << " Prev is " << n->prev << endl;
}

int main()
{
	Node* a = new Node("A");
	Node* b = new Node("B");
	Node* c = new Node("C");
	Node* d = new Node("D");
	Node* e = new Node("E");

	a->addPeer(b, 6);
	b->addPeer(a, 6);

	a->addPeer(d, 1);
	d->addPeer(a, 1);

	b->addPeer(d, 2);
	d->addPeer(b, 2);

	b->addPeer(e, 2);
	e->addPeer(b, 2);

	d->addPeer(e, 1);
	e->addPeer(d, 1);

	c->addPeer(e, 5);
	e->addPeer(c, 5);

	b->addPeer(c, 5);
	c->addPeer(b, 5);

	shortest_path(a);

	print_shortest(a);
	print_shortest(b);
	print_shortest(c);
	print_shortest(d);
	print_shortest(e);

	return 0;
}

