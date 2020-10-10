// https://techdevguide.withgoogle.com/resources/compress-decompression/#code-challenge
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>

using namespace std;

string decomp (const string& s)
{
	string ret;
	if (s.empty()) return s;

	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i])) { // <<<<<
			int l = s.find("[", i); // <<< substr, pos
			int r = l;

			// <<< need to use a stack to find the closing "]"
			stack<char> stk;
			stk.push('[');
			for (int m = l+1; m < s.size(); m++) {
				if (s[m] == '[') {
					stk.push('[');
				}
				if (s[m] == ']') {
					stk.pop();
					if (stk.empty()) {
						r = m;
						break;
					}
				}
			}

			int len = stoi(s.substr(i, (l-i))); // <<<<
			if ((r-l) > 1) { // skip empty[]
				string inner = decomp(s.substr(l+1, (r-l-1))); // <<<< recursive
				while (len > 0) {
					len--;
					ret += inner;
				}
			}
			i = r; // <<<< important
		} else { // letters, just copy
			ret += s[i];
		}
	}	
	return ret; // basic stuff.
}


int main ()
{
	cout << decomp("5[]abc10[tl]0[skip]efg2[xin3[kj]]zzz") << endl;
	return 0;
}

