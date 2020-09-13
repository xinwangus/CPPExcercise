// The best idea is that if there is one, and only one number that appears
// odd times, then XOR operations will give the answer.
// because any X ^ X == 0

#include <iostream> 

using namespace std;

int
appear_odd_times (unsigned int* arr, unsigned int len) 
{
	int ret = -1;
	if ((arr == NULL) || (len == 0)) {
		return ret;
	}

	ret = arr[0];

	for (int i = 1; i < len; i++) {
		ret = ret ^ arr[i];
	}

	return ret;
}

int main ()
{
	unsigned int test[] = {1, 1, 3, 4, 4, 0, 0, 0, 0, 7, 7}; 
	cout << "Odd appearance: " 
	     << appear_odd_times(test, sizeof(test)/sizeof(unsigned int))
             << endl;

	// to test:
	// empty; only one element; more elements
}
