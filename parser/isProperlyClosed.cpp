/*
 * Check a string, if contains [], {}, (), having
 * them properly closed and no interlace.
 * 
 * Can be enhanced to produce a conatent parsing tree if
 * [], {}, () are the only seperators.
 */

#include <iostream>
#include <stack>
#include <string>

using namespace std;

typedef enum sepType 
{
	NONE,
	P,  // ()
	SB, // []
	B,  // {}
} sepType_t;

struct Entry 
{
	sepType_t t;
	int c;
};

bool isProperlyClosed (const string& s)
{
	// Top of the stack records what is the next type 
	// to close, and how many of this type are currently
	// open in this record.
	stack<Entry> myStack;

	for (int i = 0; i < s.length(); ++i) {
		switch (s[i]) 
		{
		  case '(':
			if (myStack.empty() || myStack.top().t != P) {
				Entry* ne = new Entry();
				ne->t = P;
				ne->c = 1;
				myStack.push(*ne);	
				delete ne;
			} else {
				myStack.top().c++;
			}
			break;
		  case '[':
			if (myStack.empty() || myStack.top().t != SB) {
				Entry* ne = new Entry();
				ne->t = SB;
				ne->c = 1;
				myStack.push(*ne);	
				delete ne;
			} else {
				myStack.top().c++;
			}
			break;
		  case '{':
			if (myStack.empty() || myStack.top().t != B) {
				Entry* ne = new Entry();
				ne->t = B;
				ne->c = 1;
				myStack.push(*ne);	
				delete ne;
			} else {
				myStack.top().c++;
			}
			break;
		  case ')':
			if (myStack.empty() || myStack.top().t != P) { 
				return false; 
			} else {
				myStack.top().c--;
				if (myStack.top().c == 0) {
					myStack.pop();
				}
			}
			break;
		  case ']':
			if (myStack.empty() || myStack.top().t != SB) { 
				return false; 
			} else {
				myStack.top().c--;
				if (myStack.top().c == 0) {
					myStack.pop();
				}
			}
			break;
		  case '}':
			if (myStack.empty() || myStack.top().t != B) { 
				return false; 
			} else {
				myStack.top().c--;
				if (myStack.top().c == 0) {
					myStack.pop();
				}
			}
			break;
		  default:
			break;
		}
	}

	if (myStack.empty()) {
		return true;
	} else {
		return false;;
	}
}


int main ()
{
	string s1 = "{{{{[[[[(({{{}}}))]]]]}}}}";
	string s2 = "{{{[[[[(({{{}}}))]]]]}}}}";
	string s3 = "{{{[[[[(({{{0000)}}})]]]]}}}}";
	cout << s1
             << (isProperlyClosed(s1)? " is " : " is NOT ")
             << "properly closed."
             << endl;
	cout << s2
             << (isProperlyClosed(s2)? " is " : " is NOT ")
             << "properly closed."
             << endl;
	cout << s3
             << (isProperlyClosed(s3)? " is " : " is NOT ")
             << "properly closed."
             << endl;

	string test;
	while (true) {
		cout << "Input a string: ";
		cin >> test;
		cout << test
             		<< (isProperlyClosed(test)? " is " : " is NOT ")
             		<< "properly closed."
             		<< endl;
	}

	return 0;
}



