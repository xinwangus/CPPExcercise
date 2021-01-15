/*
 * Top X out of N
 * Problem: input: Array of int, with duplicates, 
 * output: Top X of ints, in sorted order, with the max number of appearance.
 * Hint: do it in O(N*logX). 
 */
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class Count
{
public:
	Count();
	Count(int v, unsigned int c);
	virtual ~Count();
	// *** note: this is tricky, because we want a min-heap.
	bool operator< (const Count& c2) const {
		return count > c2.count;
	}
	int value;
	unsigned int count;	
};

Count::Count()
	:value(0), count(0)
{
}

Count::Count(int v, unsigned int c)
	:value(v), count(c)
{
}

Count::~Count()
{
}

bool top_x (const int* in, const unsigned int in_size,
            const unsigned int x,
            int* out, const unsigned int  out_size) 
{
	if ((in == NULL) || (out == NULL) || (in_size == 0) || (in_size > out_size) || (x > out_size)) {
		return false;
	}

	/*
	 * Step 1: going through the array and build a hashTable (int -> Count)
	 * O(N)
	 */
	typedef unordered_map<int, Count> mapType;
	mapType ht;
	for (int i = 0; i < in_size; ++i) {
		if (ht[in[i]].count == 0) {
			ht[in[i]].value = in[i];
			ht[in[i]].count = 1;
		} else {
			ht[in[i]].count++;
		}
	}
	
	/*
         * Step 2: put the object into min heap of X one by one. if heap is less than X size, always push, otherwise compare the
         *       top() with incoming, if top() is less, pop out the top() and put the new one in. Otherwise, skip the 
         *       new one.
	 * O(N*logX)
         */

	typedef priority_queue<Count> pqType;
	pqType my_pq;

	for (auto& item : ht) {
		if (my_pq.size() < x) {
			my_pq.push(item.second);
		} else {
			Count top = my_pq.top();
			if (top.count < item.second.count) {
				my_pq.pop();
				my_pq.push(item.second);
			}
		}
	}

        /*
         * Step 3: pop the min heap one by one to get the sorted list of top X.	
	 * O(X*logX)
	 */
	while (!my_pq.empty()) {
		out[my_pq.size()-1] = my_pq.top().value;
		my_pq.pop();
	}	
	return true;
}

int main ()
{
	int input[] = { 1, 3, 5, -1, 5, 5, 1, 6, 1, 6, 1, 7 };
	int output[12] = {};
	int x = 4;
	if (top_x(input, sizeof(input)/sizeof(int), x, output, sizeof(output)/sizeof(int))) {
		for (int k = 0; k < x; k++) {
			cout << output[k] << " ";
		}
		cout << endl;
	}
}

