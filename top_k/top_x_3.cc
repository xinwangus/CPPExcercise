#include <iostream>
#include <set> // just <set>
#include <unordered_map>

using namespace std;

struct frequency
{
	frequency (int value, int f): v(value), count(f) {}
	bool operator< (const frequency& rh) const { // position of 2 const!
		return count > rh.count;
	}
	int v;
	int count;
};

void top_work(int arr[], int s, int k) // [] position
{
	// array to hashtable
	unordered_map<int, int> ht;
	for (int i = 0; i < s; i++) {
		ht[arr[i]]++;
	}

	// hash table to multi-set (sorting)
	multiset<frequency> myset;
	for (auto& item: ht) {
		frequency* f = new frequency(item.first, item.second); // use item
		myset.insert(*f);
	}
	
	// print out result
	int j = 0;
	for (auto& item: myset) {
		cout << "(" << j+1 << ")" << " Value: " << item.v 
                     << " appeared " << item.count <<" times" << endl;
		j++;
		if (j == k) break;
	}
}

int main ()
{
	int arr[] = {1, 2, 4, 5, 2, 3, 5, 5, 6, 3, 1, 1, 1, 7};
	top_work(arr, sizeof(arr)/sizeof(arr[0]), 10);
	return 0;
}
