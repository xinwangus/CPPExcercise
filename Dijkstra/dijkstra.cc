/* 
 * My own implementation of Dijkstra's algorithm
 * to find the shortest path in a Graph.
 */
#include <queue>
#include <string> 
#include <iostream>
#include <stdio.h>

using namespace std;

class AdjNode; // forward declaration

class Node 
{
public:
	Node(string s);
	virtual ~Node() {};

	string id;

	AdjNode* adj; // adjacent list

	int pd; // shortest distance to root
	string prev; // prev Node in the shortest route

	bool visited; // done with it

	// used by STL priority queue
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
	int d; // distance between neighbors
	AdjNode* next; // linked list
}; // never miss this

AdjNode::AdjNode(Node* node, int dis)
:n(node), d(dis), next(0)
{
}

void Node::addPeer(Node* n, int d)
{
	if ( n == 0 ) return;
	AdjNode* tmp = adj;
	while (tmp) {
		// already added. stop
		if (tmp->n == n) {
			return;
		}
		tmp = tmp->next;
	}
	tmp = adj;
	AdjNode* new_node = new AdjNode(n, d);
	adj = new_node;
	new_node->next = tmp;
	// to connect both ends
	n->addPeer(this, d);
}

void shortest_path(Node* a)
{
	if (a == 0) return;

	priority_queue<Node*> queue; // Most important part of the algorithm <<<
	queue.push(a);
	a->pd = 0;

	while (!queue.empty()) { // just empty(), not is_empty()
		Node* c = queue.top();
		queue.pop();

		if (c->visited) continue;
		c->visited = true;

		AdjNode* adj = c->adj;
		while (adj != 0) {
			if (adj->n->visited) {
				adj = adj->next;
				continue;
			}

			// if Node in the queue, better to take it out
			// but do not HAVE to

			// Most important part of the algorithm <<<
			if ((adj->d + c->pd) < (adj->n->pd)) {
				adj->n->pd = (adj->d + c->pd);
				adj->n->prev = c->id;
			}
			queue.push(adj->n);

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

	// example is from
	// https://www.youtube.com/watch?v=pVfj6mxhdMw&ab_channel=ComputerScience
	a->addPeer(b, 6);
	a->addPeer(d, 1);
	b->addPeer(d, 2);
	b->addPeer(e, 2);
	d->addPeer(e, 1);
	c->addPeer(e, 5);
	b->addPeer(c, 5);

	shortest_path(a);

	print_shortest(a);
	print_shortest(b);
	print_shortest(c);
	print_shortest(d);
	print_shortest(e);

	return 0;
}

