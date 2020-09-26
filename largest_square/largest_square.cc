// do not type unsigned
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define MAX(a, b) ((a > b)? a : b)
#define MIN(a, b) ((a > b)? b : a)

const unsigned int D = 5;

// This show dynamic allocation and free.
unsigned int** allocate_matrix(unsigned int s)
{
	unsigned int** rows = (unsigned int**)malloc(sizeof(unsigned int*)*s);
	for (int i = 0; i < s; i++) {
		// use calloc is better.
		rows[i] = (unsigned int*)calloc(s, sizeof(unsigned int));
	}
	return rows;
}

void free_matrix(unsigned int** r, unsigned int s)
{
	for (int i = 0; i < s; i++) {
		free(r[i]);
	}
	free(r);
}

// this shows how to pass an multi-demension array to a function.
unsigned int max_square(unsigned int m[D][D])
{
	unsigned int** r = allocate_matrix(D);	
	unsigned int ret = 0;
	unsigned int p_i, p_j = 0;

	for (int i = 0; i < D; ++i) {
		for (int j = 0; j < D; ++j) {
			if (m[i][j] == 0) {
				r[i][j] = 0;
			} else if ((i == 0) || (j == 0)) {
				r[i][j] = m[i][j];
			} else {
				unsigned int tmp = MIN(r[i-1][j], r[i][j-1]);
				tmp = MIN(tmp, r[i-1][j-1]);
				r[i][j] = tmp + m[i][j];
			}
			if (r[i][j] > ret) {
				ret = r[i][j];
				p_i = i;
				p_j = j;
			}
		}
	}

	free_matrix(r, D);

	cout << "max square up, left: (" << (p_i - ret + 1) << " , " 
             << (p_j - ret + 1) << ")" << endl;
	cout << "bottom, right: (" << (p_i) << " , " 
             << (p_j) << ")" << endl;
	return ret;
}
 
int main()
{
	unsigned int matrix[D][D] = {{1, 1, 0, 1, 0},
                                     {0, 1, 1, 1, 0},
                                     {0, 1, 1, 1, 0},
                                     {1, 1, 1, 1, 0},
                                     {0, 0, 1, 0, 0}};
	cout << max_square(matrix) << endl;
}
