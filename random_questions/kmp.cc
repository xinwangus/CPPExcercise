// KMP algorithm
// 
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

void print_result(const vector<int>& v)
{
	for (auto& item : v) {
		cout << item << " ";
	}
	cout << endl;
}

// C++ way, not sure about complexity of C++ STL implementation.....
// looks like it is O(N*M)
void find_within_1 (const string& b, const string& s, vector<int>& po)
{
	int p = 0;
	// Notice using find_first_of() here is wrong!
	p = b.find(s, p); // what to search, then position
	while (p != string::npos) {
		po.push_back(p);
		p += 1;
		p = b.find(s, p);
	}
}

// Naive C way, ~O(N*M)
void find_within_2 (const char* b, const char* s, vector<int>& po)
{
	int bl = strlen(b);
	int sl = strlen(s);
	if (bl < sl) return;
	int k = 0;
	while (k <= (bl - sl)) {
		if (strncmp(&b[k], s, sl) == 0) {
			po.push_back(k);
		}
		k++;
	}
}

// KMP algorithm can do O(N) at the worst.
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void find_within_kmp (const char* s, const char* w, vector<int>& po)
{
	// Step 1, build a kmp table
	vector<int> T;
	T.push_back(-1);

	int wl = strlen(w);
	int pos = 1;
	int cnd = 0;

	while (pos < wl) {
		if (w[pos] == w[cnd]) {
			T.push_back(T[cnd]);
		} else {
			T.push_back(cnd);
			while ((cnd >= 0) && (w[pos] != w[cnd])) {
				cnd = T[cnd];
			}
		}
		pos++;
		cnd++;
	}
	T.push_back(cnd);

	print_result(T);

	// Step 2, actually do the search of w in s
	int wp = 0;
	int sp = 0;
	int sl = strlen(s);

	while (sp < sl) {
		if (s[sp] == w[wp]) {
			sp++;
			wp++;
			if (wp == wl) {
				// matched everything
				po.push_back(sp - wp);
				wp = T[wp];
				assert(wp >= 0);
			}
		} else {
			wp = T[wp];
			if (wp < 0) {
				sp++;
				wp++;
			}
		}
	}
}

int main()
{
	string s1("ABCDEAABCD");
	string s2("AB");

	vector<int> v;
	find_within_1(s1, s2, v);
	print_result(v);
	v.clear();

	find_within_2(s1.c_str(), s2.c_str(), v);
	print_result(v);
	v.clear();

	find_within_kmp(s1.c_str(), s2.c_str(), v);
	print_result(v);
	v.clear();
	return 0;
}
