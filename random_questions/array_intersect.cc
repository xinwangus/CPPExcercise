#include <iostream>
#include <unordered_map>

using namespace std;

void overlap(int* arr1, int s1, int* arr2, int s2)
{
	int s3 = (s1 < s2)? s2: s1;
	int* ret = new int[s3];
	int s4 = 0;

	unordered_map<int, int> ht;
	// step 1, build the loopup hash table
	// using one array.
	for (int i = 0; i < s1; i++) {
		ht[arr1[i]]++;
	}
	// step 2., go through the 2nd array,
	// check hash table each time,
	// if found, use 1 instance of it,
	// and add into result.
	for (int i = 0; i < s2; i++) {
		if (ht[arr2[i]] > 0) {
			ht[arr2[i]]--;
			ret[s4++] = arr2[i];
		}
	}

	for (int i = 0; i < s4; i++) {
		cout << ret[i] << " ";
	}
	cout << endl;
	delete [] ret;
}

int main()
{
	int a1[] = {1, 2, 4, 3, 3, 3, 5, 7};
	int a2[] = {2, 4, 3, 3, 7, 9, 10};
	overlap(a1, sizeof(a1)/sizeof(a1[0]),
		a2, sizeof(a2)/sizeof(a2[0]));
	return 0;
}
