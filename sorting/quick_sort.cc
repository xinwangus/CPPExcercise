#include <iostream>

using namespace std;

void swap (int a[], int i, int j)
{
	if (i == j) return;
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp; 
}

int partition (int a[], int b, int e)
{
	int p = a[e];

	int i = b;
	int j = e;

	while (1) {
		while (a[i] < p) {
			i++;
		}
		while (a[j] >= p) {
			j--;
			if (j == b) break; // this is important!
		}
		if (i >= j) break;
		swap(a, i, j);
	}
	swap(a, i, e); // this is important too.
	return i;
}

void quickSort (int a[], int b, int e)
{
	if (e <= b) return;
	int i = partition(a, b, e);	
	quickSort(a, b, i-1);
	quickSort(a, i+1, e);
}

void print_array(int a[], int n)
{
	int i = 0;
	while (i < n) {
		cout << a[i] << " ";
		i++;
	}
	cout << endl;
}


int main()
{
	int a[] = {1};
	int b[] = {3, 5};
	int bb[] = {5, 3};
	int c[] = {5, 2, 7};
	int d[] = {9, 5, 2, 7};

	print_array(a, sizeof(a)/sizeof(int));
	quickSort(a, 0, sizeof(a)/sizeof(int) - 1);
	print_array(a, sizeof(a)/sizeof(int));

	print_array(b, sizeof(b)/sizeof(int));
	quickSort(b, 0, sizeof(b)/sizeof(int) - 1);
	print_array(b, sizeof(b)/sizeof(int));

	print_array(bb, sizeof(bb)/sizeof(int));
	quickSort(bb, 0, sizeof(bb)/sizeof(int) - 1);
	print_array(bb, sizeof(bb)/sizeof(int));

	print_array(c, sizeof(c)/sizeof(int));
	quickSort(c, 0, sizeof(c)/sizeof(int) - 1);
	print_array(c, sizeof(c)/sizeof(int));

	print_array(d, sizeof(d)/sizeof(int));
	quickSort(d, 0, sizeof(d)/sizeof(int) - 1);
	print_array(d, sizeof(d)/sizeof(int));
}
