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

void swap (int* arr, int l, int r)
{
	if (l == r) return;
	int tmp = arr[l];
	arr[l] = arr[r];
	arr[r] = tmp;
}

// answer is list of lists
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
		 * this solution not only print combination,
	 	 * but also ordering.
	 	 */
		for (int i = 0; i < s; i++) {
			swap(arr, 0 , i);
			work(&arr[1], s-1, r-1, ll);
			for (auto& item : ll) {
				if (item.size() < r) {
					item.push_front(arr[0]);
				}
			}
			// backtrack
			swap(arr, 0 , i);
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

