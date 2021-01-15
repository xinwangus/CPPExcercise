/* 
 * Given an array of size n, generate and print all
 * possible combinations of r elements in array.
 * For example, if input array is {1, 2, 3, 4} 
 * and r is 2, then output should be {1, 2}, {1, 3}, 
 * {1, 4}, {2, 3}, {2, 4} and {3, 4}.
 */

#include <list>
#include <iostream>

using namespace std;

void work(int* arr, size_t s, size_t r, list<list<int> >& ll)
{
	if (arr == 0 || s == 0 || r == 0 || s < r) return;
	
	/* if asking for 1, then just add answers */
	if (r == 1) {
		for (int i = 0; i < s; i++) {
			list<int> l;
			l.push_back(arr[i]);
			ll.push_back(l);
		}
	} else {
	/*
	 * Otherwise, recurively call the rest of
         * array, with r-1, then push one elem to
	 * the front.
	 */
		for (int i = 0; i+1 < s; i++) {
			if ((s-i-1) > 0) {
				work(&arr[i+1], s-i-1, r-1, ll);
				for (auto& item : ll) {
					if (item.size() < r) {
						item.push_front(arr[i]);
					}
				}
			}
		}
	}
}


int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	list<list<int> > ll;

	for (auto j = 0; j <= sizeof(arr)/sizeof(arr[0]); j++) {
		cout << " Pick: " <<  j << endl;
		work(arr, sizeof(arr)/sizeof(arr[0]), j, ll);
		for (auto& item : ll) {
			for (auto& val : item) {
				cout << val << " ";
			}
			cout << endl;
		}
		ll.clear();
	}
	return 0;
}

