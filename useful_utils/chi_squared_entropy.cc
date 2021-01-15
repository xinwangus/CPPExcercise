/*
 * An util to calculate a file's chi-squared entropy
 */

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Please give a file name!\n";
		return -1;
	}
	if (argc > 2) {
		cout << "Too many arguments!\n";
		return -1;
	}
	char* file = argv[1];		
	ifstream in(file);
	if (!in.is_open()) {
		cout << "File does not exist!\n";
		return -1;
	}

	char c;
	unsigned int counts[256] = {0};
	unsigned int total = 0;
	while (in.get(c)) {
		total++;
		counts[(int)c]++;
	}
	if (total == 0) {
		cout << "Empty file!\n";
		return -1;
	}

	float expect = (float)total/256;
	cout << "Total = " << total << " Expect = " << expect << "\n";
	float chi_squ = 0;
	for (int i = 0; i < 256; i++) {
#if 0
		if (counts[i] != 0) {
			cout << "'" << (char)i << "'" << " count = " << counts[i] << "\n";
		}
#endif
		chi_squ += pow((counts[i] - expect), 2);
	}
	chi_squ /= expect;
	cout << "File's chi-squared value is " << chi_squ << endl;
	in.close();
	return 0;
}

