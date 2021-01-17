#include <iostream>
#include <list>

using namespace std;

void print_list(const list<int>& ll)
{
	for (auto& item : ll) {
		cout << item << " ";
	}
	cout << endl;
}

int main()
{
	int arr1[] = { 2, 3, 1, 4 };
	int arr2[] = { 12, 13, 11, 24 };

	list<int> list1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	list<int> list2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));

	print_list(list1);
	print_list(list2);

	// TEST, this is to demo splice, joining two lists together.
	list1.splice(list1.end(), list2);

	print_list(list1);
	print_list(list2); // list2 is now empty

	return 0;
}
