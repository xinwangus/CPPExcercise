#include <vector>
#include <iostream>

using namespace std;

bool isPal(unsigned int a)
{
	vector<unsigned int> v;
	if (a == 0) return true;
	while (a) {
		v.push_back(a % 10);
		a /= 10;
	}
	int s = v.size();
	for (auto i = 0; i < s/2; i++) {
		if (v[i] != v[s-1-i]) return false;
	}
	return true;
}

int main()
{
	unsigned int i1 = 0;
	cout << i1 << " is Palindrome: " << isPal(i1) << endl;
	unsigned int i2 = 9;
	cout << i2 << " is Palindrome: " << isPal(i2) << endl;
	unsigned int i3 = 12;
	cout << i3 << " is Palindrome: " << isPal(i3) << endl;
	unsigned int i4 = 123;
	cout << i4 << " is Palindrome: " << isPal(i4) << endl;
	unsigned int i5 = 12321;
	cout << i5 << " is Palindrome: " << isPal(i5) << endl;
	return 0;
}
