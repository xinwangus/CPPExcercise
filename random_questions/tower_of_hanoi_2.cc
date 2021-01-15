#include <list>
#include <iostream>

using namespace std;

/* 
 * Solution for Game of Tower of Hanoi
 */

class motion {
public:
	motion(char f, char t):from(f), to(t) {};
	virtual ~motion() = default;
	char from;
	char to;
};

void play(char f, char t, char s, unsigned int disk, std::list<motion>& l)
{
	if (disk == 0) return;
	if (disk == 1) {
		l.push_back(*(new motion(f, t)));
		return;
	}
	// If disk is 2 or above, solve with 3 steps:
	// 1. move all (disk - 1) to the 3rd party.
	// 2. move the bottom one to "t".
	// 3. move all (disk - 1) from 3rd party to "t".
	// Trick: recursive and dynamic programming
	play(f, s, t, (disk - 1), l);
	l.push_back(*(new motion(f, t)));
	play(s, t, f, (disk - 1), l);
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
	while (1) {
		cout << "Play Game! num of disks: " << endl;
		unsigned int d;
		cin >> d;
		d = min(d, (unsigned int)10);
		list<motion> ll; // could also use a vector
		play('a', 'b', 'c', d, ll);
		print_list(ll);
		ll.clear();
	}
	return 0;
}
