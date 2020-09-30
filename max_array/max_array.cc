#include <iostream>

using namespace std;

#define MAX(a, b) (((a) > (b))? (a) : (b))

void
find_overlap(int* a, int sa, int* b, int sb, int*c, int sc, int*out, int*out_len)
{
	// check 0 for all pointers.
	int* ae = a + sa; // **** typo
	int* be = b + sb;
	int* ce = c + sc;
        *out_len = 0;
	while (a < ae && b < be && c < ce) {
		int max = MAX (*a, MAX(*b, *c));
		if ((*a == *b) && (*a == *c)) {
			*out = *a;
			out++;
                        (*out_len)++; // ****()
			a++;
			b++;
			c++;
			continue;
		}
		while (a < ae && *a < max) a++;
		while (b < be && *b < max) b++;
		while (c < ce && *c < max) c++;
	}
}

int main()
{
	int a[] = {2, 6, 7, 7, 9,11, 13, 17};
	int b[] = {3, 6, 7, 7, 7, 10, 13, 18};
        int c[] = {4, 5, 6, 7, 7, 7, 7, 9, 11, 13};
        int* out = (int*)malloc(MAX(MAX(sizeof(a), sizeof(b)), sizeof(c))); // **** cast !
        int out_len = 0;
        find_overlap(a, sizeof(a)/sizeof(int),
        	     b, sizeof(b)/sizeof(int),
        	     c, sizeof(c)/sizeof(int),
        	     out, &out_len);
	for (int i = 0; i < out_len; ++i) {
		cout << out[i] << endl;
	}
}

