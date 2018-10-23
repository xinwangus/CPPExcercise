/*
 * Check a string, if contains [], {}, (), having
 * them properly closed and no interlace.
 *
 * This is a better implementation than version 1.
 */
#include <iostream>
#include <stack>

using namespace std;

bool isProperlyClosed(const string& s)
{
	stack<char> sc;
	for (int i = 0 ; i < s.length(); ++i) {

		// Skip all others we do not care.
		if (s[i] != '{' && s[i] != '}' && 
		    s[i] != '[' && s[i] != ']' && 
                    s[i] != '(' && s[i] != ')') {
			continue;
		}

		// First take care of closure,
		// if not closed, just push to
		// the stack.
		if (!sc.empty() &&
			s[i] == '}' &&
			sc.top() == '{') {
			sc.pop();
		} else if (!sc.empty() &&
                        s[i] == ']' &&
                        sc.top() == '[') {
                        sc.pop();
		} else if (!sc.empty() &&
                        s[i] == ')' &&
                        sc.top() == '(') {
                        sc.pop();
		} else {
			sc.push(s[i]);
		}
	}

	return (sc.empty());
}

int main()
{
	string test;
	while (true) {
		cout << "String to test: ";
		cin >> test; // spaces are treated as seperators from cin
		cout << test << endl;
		cout << (isProperlyClosed(test)? "is": "is NOT")
	     		<< " properly closed." << endl;
	}
	return 0;
}

