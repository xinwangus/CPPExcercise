#include <list>
#include <iostream>

using namespace std;

/* 
 * Solution for Game of Tower of Hanoi
 */

class motion {
public:
	motion(char f, char t):from(f), to(t) {};
	~motion() = default;
	char from;
	char to;
};

void play(char* at, size_t s, char f, char t, unsigned int disk, std::list<motion>& l)
{
	if (disk == 0) return;
	if (disk == 1) {
		l.push_back(*(new motion(f, t)));
		return;
	}
	int i = 0;
	for (i = 0 ; i < s; i++) {
		if ((at[i] != f) && (at[i] != t)) {
			break;
		}
	}
	// If is 2 or above, solve with 3 steps:
	// 1. move all (disk - 1) to the 3rd party.
	// 2. move the bottom one to "t".
	// 3. move all (disk - 1) from 3rd party to "t".
	// Trick: recursive and dynamic programming
	play(at, s, f, at[i], (disk - 1), l);
	l.push_back(*(new motion(f, t)));
	play(at, s, at[i], t, (disk - 1), l);

}

void print_list(const list<motion>& ll)
{
	for (auto& item : ll) {
		cout << item.from << "->" << item.to << endl;
	}
}

int main()
{
	char t[] = {'a', 'b', 'c'}; // Towers
	unsigned int d = 5; // num of disks, all on 'a' as starter.

	list<motion> ll; // could also use a vector
	play(t, sizeof(t)/sizeof(t[0]), 'a', 'b', d, ll);

	print_list(ll);
	return 0;
}
