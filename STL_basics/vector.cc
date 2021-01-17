#include <vector>
#include <iostream>

using namespace std;

void print_vector(const vector<int>& v)
{
	cout << "Index way:" << endl;
	for (auto i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "Iterater way:" << endl;
	for (auto itr = v.begin(); itr != v.end(); ++itr) {
		cout << *itr << " ";
	}
	cout << endl;
	cout << "C++11 Looping way:" << endl;
	for (auto& item : v) {
		cout << item << " ";
	}
	cout << endl;
}

int main()
{
	// Test 1: demo can not use [] to add.
	cout << "<Test 1>" << endl;
	std::vector<int> v1; // do not forget it is <>, STL!

	for (int i = 0; i < 10; ++i) {
		// v1[i] = i; // WRONG! unlike map, this is wrong, seg fault.
		v1.push_back(i);
	}
	print_vector(v1);

	// Test 2: demo remove elements
	cout << "\n<Test 2>" << endl;
	v1.pop_back(); // remove 9
	v1.erase(v1.end() - 1); // remove 8, can not remove v1.end() as it is one off limit.
	v1.erase(v1.end() - 3); // remove 5
	print_vector(v1);

	// Test 3: demo construct vector from an array
	cout << "\n<Test 3>" << endl;
	int arr[] = {11, 12, 13, 14};
	vector<int> v2(arr, arr + sizeof(arr)/sizeof(arr[0])); // Note! start and end (one over) of the array.
	print_vector(v2);

	return 0;
}

