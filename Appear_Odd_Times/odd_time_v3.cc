#include <iostream> 
#include <unordered_set>  // we do not even need to use an unordered_map

using namespace std;

int
appear_odd_times (unsigned int* arr, unsigned int len) 
{
	int ret = -1;
	if ((arr == NULL) || (len == 0)) {
		return ret;
	}

	typedef unordered_set<unsigned int> Counter_set;
	Counter_set my_set;
	Counter_set::iterator itr;

	for (int i = 0; i < len; i++) {
		itr = my_set.find(arr[i]);
		if (itr == my_set.end()) {
			// apeared odd times
			my_set.insert(arr[i]);
		} else {
			// apeared even times
			my_set.erase(itr);
		}
	}

	for (itr = my_set.begin(); itr != my_set.end(); itr++) {
			if (ret == -1) {
				ret = *itr; // this is how you access the set member.
				cout <<"First answer: " << *itr << endl;
			} else {
				cout <<"More answer: " << *itr << endl;
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
