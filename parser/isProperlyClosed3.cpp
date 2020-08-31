/*
 * Check a string, if contains [], {}, (), having
 * them properly closed and no interlace.
 *
 * This is a better implementation than version 2
 */
#include <iostream>
#include <stack>

using namespace std;

bool match(char l, char r)
{
	if ((l == '[' && r == ']') ||
            (l == '{' && r == '}') ||
            (l == '(' && r == ')')) {
		return true;
	} else {
		return false;
	}
}

bool isLeft(char l)
{
	if ((l == '[') ||
            (l == '{') ||
            (l == '(')) {
		return true;
	} else {
		return false;
	}
}

bool isRight(char r)
{
	if ((r == ']') ||
            (r == '}') ||
            (r == ')')) {
		return true;
	} else {
		return false;
	}
}

bool isProperlyClosed(const string& s)
{
	stack<char> sc;
	for (int i = 0 ; i < s.length(); ++i) {
		// Skip all others we do not care.
		if (!isLeft(s[i]) && !isRight(s[i])) {
			continue;
		} else if (isLeft(s[i])) {
			sc.push(s[i]);
		} else { // isRight()
			if (sc.empty() || !match(sc.top(), s[i])) {
				return false;
			}
			// match()
			sc.pop();
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

