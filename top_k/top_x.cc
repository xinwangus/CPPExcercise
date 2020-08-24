#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class Count
{
public:
	Count(int v, unsigned int c);
	virtual ~Count();
	// *** note: this is tricky, because we want a min-heap.
	bool operator< (const Count& c2) const {
		return count > c2.count;
	}
	int value;
	unsigned int count;	
};

Count::Count(int v, unsigned int c)
{
	value = v;
	count = c;
}

Count::~Count()
{
}


bool top_x (const int* in, const unsigned int in_size, const unsigned int x, int* out, const unsigned int  out_size) 
{
	if ((in == NULL) || (out == NULL) || (in_size == 0) || (in_size > out_size) || (x > out_size)) {
		return false;
	}

	/*
	 * Step 1: going through the array and build a hashTable (int -> Count)
	 * O(N)
	 */
	typedef unordered_map<int, Count> mapType;
	mapType my_map;
	for (int i = 0; i < in_size; ++i) {
		mapType::iterator f = my_map.find(in[i]);
		if (f == my_map.end()) {
			Count* ct = new Count(in[i], 1);
			my_map.insert(make_pair(in[i], *ct));
		} else {
			f->second.count++;
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

	for (mapType::iterator f = my_map.begin(); f != my_map.end(); f++) {
		if (my_pq.size() < x) {
			my_pq.push(f->second);
		} else {
			Count top = my_pq.top();
			if (top.count < f->second.count) {
				my_pq.pop();
				my_pq.push(f->second);
			}
		}
	}

        /*
         * Step 3: pop the min heap one by one to get the sorted list of top X.	
	 * O(X*logX)
	 */
	int j = my_pq.size();
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

