/*
 * To demo some tricky points of C++ STL map.
 */

#include <iostream>
#include <map>
#include <string>

using namespace std;

void print_map(map<int, string>& m)
{
	cout << "\nMap contents:" << endl;
	for (auto& item : m) {
		cout << item.first << "==>" << item.second << endl;
	}
}

int main()
{
	// given a map of <int, string>

	map<int, string> mymap;
	mymap[1] = "test";
	mymap[2] = "another test";
	mymap.insert(make_pair(5, "hello")); // std::make_pair
	mymap[7] = "test 89";
	mymap.insert(make_pair(10, "world"));
	mymap[11] = "test 11";

	print_map(mymap);

	// idea is to delete all entries whose string payload length is 5.
	// this is to demo to maintain the valid of iterator
#if 0
	for (auto itr = mymap.begin(); itr != mymap.end(); itr++) {
		if (itr->second.size() == 5) {
			mymap.erase(itr); // WRONG! because erase would make itr invalid
		}
	}
	print_map(mymap);
#endif

	for (auto itr = mymap.begin(); itr != mymap.end();) {
		if (itr->second.size() == 5) {
			/* this is correct, because:
			 * 1. itr current value is given to erase.
			 * 2. then itr is incremented.
			 * 3. then erase() is called with the previous value.
			 */	
			mymap.erase(itr++);
		} else {
			itr++;
		}
	}
	print_map(mymap);

	return 0;
}
