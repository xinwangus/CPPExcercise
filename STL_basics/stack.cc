#include <stack>
#include <iostream>

using namespace std;

int main()
{
	// Test 1, demo stack operations.
	stack<int> stk;

	for (auto i = 0; i < 10; ++i) {
		stk.push(i);
	}

	// Test 2, iterate through using iterator is not valid, top/pop
	while (!stk.empty()) {
		cout << stk.top() << " ";
		stk.pop();
	}
	cout << endl;
}
