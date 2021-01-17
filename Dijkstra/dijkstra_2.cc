/* 
 * My own implementation of Dijkstra's algorithm
 * to find the shortest path in a Graph.
 */
#include <set>
#include <string> 
#include <iostream>
#include <stdio.h>

using namespace std;

class Connection; // forward declaration

template<class T> struct ptr_less {
    bool operator()(T* lhs, T* rhs) {
        return *lhs < *rhs;
    }
};


class Node 
{
public:
	Node(string s);
	virtual ~Node() {};

	string id;

	Connection* adj; // adjacent list

	// I put all these in the Node itself to make
	// the code simpler.
	// But if we want to keep the Node code pure,
	// we should have a seperated structure, such
	// as a HashTable.	
	int pd; // shortest distance to root
	string prev; // prev Node in the shortest route
	bool visited; // done with it (shortest has decided)

	bool operator<(Node& rhs);	

	void addPeer(Node* n, int d);
};

Node::Node(string s)
: id(s), adj(0), pd(0xFFFFFF), prev(s), visited(false)
{
}

bool
Node::operator< (Node& r)
{
	return (pd < r.pd);
}

class Connection
{
public:
	Connection(Node* node, int dis);
	~Connection() {};
	Node* n;
	int d; // distance between neighbors
	Connection* next; // for linked list
}; // never miss this

Connection::Connection(Node* node, int dis)
:n(node), d(dis), next(0)
{
}

void Node::addPeer(Node* n, int d)
{
	if ( n == 0 ) return;
	Connection* tmp = adj;
	// This session of code is to
	// avoid looping by the last
	// line of code of this function.
	while (tmp) {
		// already added. stop
		if (tmp->n == n) {
			return;
		}
		tmp = tmp->next;
	}
	tmp = adj;
	Connection* new_node = new Connection(n, d);
	adj = new_node;
	new_node->next = tmp;
	// to connect both ends
	n->addPeer(this, d);
}

void shortest_path(Node* a)
{
	if (a == 0) return;

	// THIS is important! How to provide a customised comparator
	// class for using pointer as key in the set!
	set<Node*, ptr_less<Node> > mset; // Most important part of the algorithm <<<
	mset.insert(a);
	a->pd = 0;

	while (!mset.empty()) { // just empty(), not is_empty()
		auto itr = mset.begin();
		Node* c = *itr;
		mset.erase(itr);

		if (c->visited) continue;
		c->visited = true;

		Connection* adj = c->adj;
		while (adj != 0) {
			if (adj->n->visited) {
				adj = adj->next;
				continue;
			}

			// take out the old entry if any
			itr = mset.find(adj->n);
			if (itr != mset.end()) {
				mset.erase(itr);
			}
			// Most important part of the algorithm
			if ((adj->d + c->pd) < (adj->n->pd)) {
				adj->n->pd = (adj->d + c->pd);
				adj->n->prev = c->id;
			}
			// put the peer into the sorted set
			// at the correct position.
			mset.insert(adj->n);

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

