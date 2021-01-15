#include <iostream>
#include <vector>
#include <deque>

using namespace std;
int main()
{
	deque<int> dq;
	vector<int> ret;
	int n, p, t;
	int c = 0;
	cout << "Number of Players:" << endl;
	cin >> n;
	cout << "Number of Piles:" << endl;
	cin >> p;
	cout << "Values of Piles:" << endl;
	// TODO, check n and p
	while (c < p && cin >> t) {
		c++;
		dq.push_back(t); 
	} 
	ret.resize(n);
	int i = 0;
	while (!dq.empty()) {
		if (dq.front() > dq.back()) {
			ret[i] += dq.front();
			dq.pop_front();
		} else {
			ret[i] += dq.back();
			dq.pop_back();
		}
		i++;
		i = i % n;
	}

	cout << "Result:" << endl;
	for (auto& item : ret) {
		cout << item << " ";
	} 
	cout << endl;
}
