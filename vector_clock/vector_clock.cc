/* 
 * A C++ class to implement "vector clock"
 * notes please see https://www.cs.rutgers.edu/~pxk/417/notes/logical-clocks.html
 */
#include <iostream>
#include <map>
#include <string>

using namespace std;

class VC {
public:
	VC(string n);
	virtual ~VC() {};

	// tracking events
	void local();
	void remote(const VC& r);

	void printMe();

	string name;
	map<string, unsigned int> vc_map;
};

VC::VC(string n)
	: name(n), vc_map()
{
	vc_map[n] = 0;
}

void
VC::local()
{
	vc_map[name]++;
}

void
VC::remote(const VC& r)
{
	local();
	for (auto& r_elem: r.vc_map) { // good C++11 syntex
		map<string, unsigned int>::iterator it  
			= vc_map.find(r_elem.first);
		if (it != vc_map.end()) {
			if (it->second < r_elem.second) {
				it->second = r_elem.second;
			}
		} else {
			vc_map[r_elem.first] = r_elem.second;
		}
	}
}

void
VC::printMe()
{
	cout << "My Process is " << name << endl;
	map<string, unsigned int>::iterator it;
	for (it = vc_map.begin(); it != vc_map.end(); it++) {
		cout << it->first << " clock # " << it->second << endl;
	}
	cout << endl;
}


int main()
{
	// Example is from:
	// https://www.cs.rutgers.edu/~pxk/417/notes/logical-clocks.html
	VC p0("P0");
	VC p1("P1");
	VC p2("P2");
	
	p0.local();
	p0.local();

	p1.local();	

	VC tmp_p1("P1");
	tmp_p1 = p1;	

	p1.remote(p0);
	p0.remote(tmp_p1);

	p0.local();

	p2.local();	
	p2.local();	

	VC tmp_p2("P2");
	tmp_p2 = p2;	

	p2.remote(p0);
	p0.remote(tmp_p2);

	p0.local();
	p1.remote(p0);

	p0.local();

	p0.printMe();
	p1.printMe();
	p2.printMe();
}
