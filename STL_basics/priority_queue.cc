#include <queue>
#include <iostream>

using namespace std;


struct Obj {
	Obj(int i):a(i) {};
	~Obj() = default;
	// reverse to define a MIN heap.
	bool operator< (const Obj& rh) const {
		return (a > rh.a);
	}
	int a;
};

int main()
{
	// Test 1, demo pri_queue operations.
	// by default, it is a MAX heap!
	priority_queue<int> qu;

	for (auto i = 9; i >= 0; i--) {
		qu.push(i);
	}

	// Test 2, iterate through using iterator is not valid, use top(), pop()
#if 0
	for (auto itr = qu.begin(); itr != qu.end(); ++itr) {
		cout << *itr << " ";
	}
	cout << endl;
#endif
	while (!qu.empty()) {
		cout << qu.top() << " ";
		qu.pop();
	}
	cout << endl;

	// Demo a MIN heap
	priority_queue<Obj> qu2;

	for (auto i = 0; i < 10; i++) {
		qu2.emplace(i); // cerate and push the object in one shot
	}
	while (!qu2.empty()) {
		cout << qu2.top().a << " ";
		qu2.pop();
	}
	cout << endl;
}
