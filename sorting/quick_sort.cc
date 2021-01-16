//
// Re-do the version 1 of quick sort code
// two pointers converge in the middle is always more error
// prone, try to use two pointers both moving from left to right.
//
#include <iostream>
#include <vector>

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
	assert(b < e);

	int p = a[e];
	int i = b;

	// top of all smaller ones.
	int j = b - 1;

	while (i < e) {
		if (a[i] < p) {
			j++;
			swap(a, i, j);
		}
		i++;
	}
	swap(a, (j + 1), e); // this is important too.
	return (j + 1);
}

void quickSort (int a[], int b, int e)
{
	if (e <= b) return;
	int i = partition(a, b, e);	
	quickSort(a, b, i-1);
	quickSort(a, i+1, e);
}

// use STL to sort, cheating
// also memory cost!
void cheatSort (int a[], int s)
{
	if (s <= 1) return;

	// give start and one over of the array
	// I guess maps to end()?
	vector<int> v(a, a+s);

	// can do stable sort as well.
	sort(v.begin(), v.end());

	int i = 0;
	for (auto& item: v) {
		a[i++] = item;
	}
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
	int dd[] = {9, 5, 2, 7};

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

	cout << "Cheat Sort" << endl;
	print_array(dd, sizeof(dd)/sizeof(int));
	cheatSort(dd, sizeof(dd)/sizeof(int));
	print_array(dd, sizeof(dd)/sizeof(int));
}
