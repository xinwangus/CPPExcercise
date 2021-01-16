/*
 * 1. Notice, this only returns one solution.
 *    if Out being vector of strings, we can come up with all solutions.
 * 2. Use greedy approach, always check the whole word and going down
 *    backwards maybe be faster to find one answer.
 */

#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

bool lookup(const string &in)
{
	unordered_set<string> dict;
	dict.insert("Hello");	
	dict.insert("World");	

	if (dict.find(in) != dict.end()) {
		return true;
	} else {
		return false;
	}
}

// recursive

bool break_up(const string& in, string &out)
{
	if (in.size() == 0) return false;

	// Greedy: always check the whole string first
	if (lookup(in)) {
		out = in;
		return true;
	}

	// must have stop point!
	if (in.size() == 1) {
		return false;
        }	

	for (int i = 0; i < in.size(); i++) {
		// the 2nd is length, not end position!
		if (lookup(in.substr(0, i+1)) &&
		    break_up(in.substr(i+1, in.size()-1-i), out)) {
			out.insert(0, in.substr(0, i+1) + " ");
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
