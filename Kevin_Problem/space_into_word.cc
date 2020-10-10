/*
 * 1. Notice, this only returns one solution.
 *    if Out being vector of strings, we can come up with all solutions.
 * 2. Use greedy approach, always check the whole word and going down
 *    backwards maybe be faster to find one answer.
 */

#include <string>
#include <iostream>

using namespace std;

bool lookup(const string &in)
{
	// todo use dictionary API
	return true;
}

// recursive

bool break_up(const string& in, string &out)
{
	if (in.size() == 0) return false;

	// must have stop point!
	if (in.size() == 1) {
		if (lookup(in)) {
			out = in;
			return true;
		} else {
			return false;
		}
        }	

	string out_r;
	for (int i = 0; i < in.size(); i++) {
		// the 2nd is length, not end position!
		if (lookup(in.substr(0, i+1)) &&
		    break_up(in.substr(i+1, in.size()-1-i), out_r)) {
			out = in.substr(0, i+1) + " " + out_r;
			return true;
		}
	}
	return false;
}

int main()
{
	string out;
	if (break_up("HelloWorld", out)) {
		cout << out << endl;
	}
	return 0;
}
