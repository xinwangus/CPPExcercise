/*
 * Given a number n, find the smallest number that has same
 * set of digits as n and is greater than n. If n is the
 * greatest possible number with its set of digits,
 * then print “not possible”.
 * https://www.geeksforgeeks.org/find-next-greater-number-set-digits/
 */

#include <deque>
#include <set>
#include <iostream>

using namespace std;

bool smallest_greater(unsigned int a, unsigned int& out)
{
	deque<int> dq;
	multiset<int> ms;

	// put all digits into deque in order.
	while (a) {
		dq.push_front(a%10);
		a /= 10;
	}

	// Smallest greater comes from re-organize the
	// lower digits.
	// move digits from deque to multiset, use
	// multiset to keep them sorted.
	int maxv = -1;
	while (!dq.empty()) {
		int v = dq.back();
		dq.pop_back();
		if (v >= maxv) {
			// we need to continue move forward
			if (v > maxv) maxv = v;
			ms.insert(v);
		} else {
			// find our spot, we can stop as we have
			// found the value we can replace with,
			// and move such from multiset to deque.
			auto itr = ms.lower_bound(v);		
			dq.push_back(*itr);
			ms.erase(itr);

			ms.insert(v);
			break;
		}
	}

	// If nothing left in deque, that means
	// an answer is not possible.
	if (dq.empty()) {
		return false;
	}

	// Now combination of the two structures
	// should be our answer.
	out = 0;
	while (!dq.empty()) {
		out *= 10;
		out += dq.front();
		dq.pop_front();
	}
	for (auto& item : ms) {
		out *= 10;
		out += item;
	}
	return true;
}

int main()
{
	while (1) {
		unsigned int a;
		unsigned int a_out;
		cout << "Input an unsigned int:" << endl;
		cin >> a;
		cout << a << endl;
		if (smallest_greater(a, a_out)) {
			cout << "smallest_greater is: " << a_out << endl;
		} else {
			cout << "not possible!" << endl;
		}
	}
	return 0;
}
