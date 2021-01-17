#include <queue>
#include <iostream>

using namespace std;

int main()
{
	// Test 1, demo queue operations.
	queue<int> qu;

	for (auto i = 0; i < 10; ++i) {
		qu.push(i);
	}

	cout << "Front is: " << qu.front() << endl;
	cout << "Back is: " << qu.back() << endl;

	// Test 2, iterate through using iterator is not valid, use front(), pop()
#if 0
	for (auto itr = qu.begin(); itr != qu.end(); ++itr) {
		cout << *itr << " ";
	}
	cout << endl;
#endif
	while (!qu.empty()) {
		cout << qu.front() << " ";
		qu.pop();
	}
	cout << endl;
}
