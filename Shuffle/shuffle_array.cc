#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void swap (int* ar, int l, int r)
{
	if (l == r) {
		return;
	}
	int tmp = ar[l];
	ar[l] = ar[r];
	ar[r] = tmp;
	return;
}

void shuffle(int* ar, unsigned int len)
{
	for (unsigned int i = 0; i < len; ++i) {
		srand(time(NULL));
		swap(ar, i, rand()%len);
	} 
}

void print_array(int* arr, unsigned int len)
{
	for (unsigned int i = 0; i < len; ++i) {
	        std::cout << arr[i] << " ";
	} 
	std::cout << endl;
}

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};

	print_array(arr, sizeof(arr)/sizeof(int));
	shuffle(arr, sizeof(arr)/sizeof(int));
	print_array(arr, sizeof(arr)/sizeof(int));

	return 0;
}

