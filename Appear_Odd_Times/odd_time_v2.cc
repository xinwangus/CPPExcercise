#include <iostream> // << typo
#include <unordered_map> // << not <map>

using namespace std;

int
appear_odd_times (unsigned int* arr, unsigned int len) 
{
	int ret = -1;
	if ((arr == NULL) || (len == 0)) {
		return ret;
	}

	typedef unordered_map<unsigned int, unsigned int> Counter_map;
	Counter_map my_map;
	Counter_map::iterator itr;

	for (int i = 0; i < len; i++) {
		itr = my_map.find(arr[i]);
		if (itr == my_map.end()) {
			// <<< make_pair is a template func
			// my_map.insert(make_pair<unsigned int, unsigned int>(arr[i], 1));
			my_map[arr[i]] = 1;
		} else {
			my_map.erase(itr); // this is more memory efficient, but a little
					   // more cpu expensive
		}
	}

	for (itr = my_map.begin(); itr != my_map.end(); itr++) {
			if (ret == -1) {
				ret = itr->first;
				cout <<"First answer: " << itr->first << endl;
			} else {
				cout <<"More answer: " << itr->first << endl;
			}
	}
	return ret;
}

int main ()
{
	unsigned int test[] = {1, 1, 3, 4, 4, 0, 0, 0, 0, 6, 9, 7, 7}; 
	cout << "Odd appearance: " 
	     << appear_odd_times(test, sizeof(test)/sizeof(unsigned int))
             << endl;

	// to test:
	// empty; without answer; with more than one answer.
}
