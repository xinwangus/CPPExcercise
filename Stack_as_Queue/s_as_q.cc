/*
 * This is an typical interview question:
 *   To implement a Queue with Stack.
 *   Problem is no practical usefulness.
 */

// Basically we want to achieve FIFO with a FILO
// data structure.
// Idea 1 is to use two Stacks
// Idea 2 is to use recursive programming.
//  this implements Idea 2
//  this Solution while looks clean, is not necessily
//  practical either. -- function calling stack can overflow.

#include <iostream>
#include <stack>

using namespace std;

// Could be a template to make it more generic.
class MyQueue
{
public:
	MyQueue();
	virtual ~MyQueue();
	void enqueue(int input);
	int dequeue();
	unsigned int size();
private:
	stack<int> _st;
};

MyQueue::MyQueue():_st()
{
}

MyQueue::~MyQueue()
{
}

void
MyQueue::enqueue(int input)
{
	_st.push(input);
}

int
MyQueue::dequeue()
{
	// STL can just check empty()
	if (_st.empty()) {
		return 0;
	} else if (_st.size() == 1) {
		int ret = _st.top();
		_st.pop();
		return ret;
	} else {
		int tmp = _st.top();
		_st.pop();
		int ret = this->dequeue();
		_st.push(tmp);
		return ret;
	}
}

unsigned int
MyQueue::size()
{
	return _st.size();
}	

int main()
{
	MyQueue mq;
	for (int i = 1; i < 10; ++i) {
		mq.enqueue(i);
	}
	while (mq.size() != 0) {
		cout << mq.dequeue() << " ";
	}
	cout << endl;
}
