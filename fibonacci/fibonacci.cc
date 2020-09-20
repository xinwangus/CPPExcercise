/*
 * fibonacci number at a given position 
 */

#include <iostream>

using namespace std;

const unsigned int fib_0 = 0;
const unsigned int fib_1 = 1;

unsigned int fib_recursive(unsigned int p)
{
	if (p == 0) { return fib_0; }
	if (p == 1) { return fib_1; }
	return (fib_recursive(p - 1) + fib_recursive(p - 2));
}

unsigned int fib_iterative(unsigned int p)
{
	if (p == 0) { return fib_0; }
	if (p == 1) { return fib_1; }
	
	unsigned int v1 = fib_0;
	unsigned int v2 = fib_1;
	unsigned int pp = 1;
	unsigned int ret = 0;

	while (pp < p) {
		ret = v1 + v2;
		v1 = v2;
		v2 = ret;
		pp++;
	}
	return ret;
}

int main()
{
	for (unsigned int i = 2; i < 10; ++i) {
		cout << fib_recursive(i) << endl; 
		cout << fib_iterative(i) << endl; 
	}
}


