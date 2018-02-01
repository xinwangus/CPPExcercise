/*
 * A test program to decode tire types
 * follow the instruction at 
 * https://www.goodyearautoservice.com/en-US/tire-basics/tire-size
 *
 * The following samples give valid inputs:
 *         P215/65R15/95H
 *         255/55R18/109W
 *         P225/60R18/100H
 */
#include <iostream>
#include <sstream>
#include <regex> // C++11

using namespace std;

struct load_index_entry {
	unsigned int index;
	unsigned int load;
};

load_index_entry loadIndexTable[] = {
	{75, 852},
	{76, 882},
	{77, 908},
	{78, 937},
	{79, 963},
	{80, 992},
	{81, 1019},
	{82, 1047},
	{83, 1074},
	{84, 1102},
	{85, 1135},
	{86, 1168},
	{87, 1201},
	{88, 1235},
	{89, 1279},
	{90, 1323},
	{91, 1356},
	{92, 1389},
	{93, 1433},
	{94, 1477},
	{95, 1521},
	{96, 1565},
	{97, 1609},
	{98, 1653},
	{99, 1709},
	{100, 1764},
	{101, 1819},
	{102, 1874},
	{103, 1929},
	{104, 1984},
	{105, 2039},
	{106, 2094},
	{107, 2149},
	{108, 2205},
	{109, 2271},
	{110, 2337},
	{111, 2403},
	{112, 2469},
	{113, 2535},
	{114, 2601},
	{115, 2679},
	{116, 2756},
	{117, 2833},
	{118, 2910},
	{119, 2998},
	{120, 3086},
};

void decodeWidth(const string& w, string& o)
{
	stringstream ss;
	ss << "\tTire Width is: " << w << " millimeters;" << endl;
	o = ss.str();
	return;
}

void decodeAspect(const string& a, string& o)
{
	stringstream ss;
	ss << "\tTire Aspect Ratio is: " << a << " %;" << endl;
	o = ss.str();
	return;
}

void decodeDiameter(const string& d, string& o)
{
	stringstream ss;
	ss << "\tWheel Diameter is: " << d << " inches;" << endl;
	o = ss.str();
	return;
}

void decodeLoad(const string& l, string& o)
{
	stringstream ss;
	ss << "\tTire Load Index is: " << l << ";" << endl;
	o = ss.str();
	return;
}

bool getMaxCarWeight (const string& load, unsigned int& w)
{
	unsigned int l = stoi(load);
	for (int i = 0; 
                 i < sizeof(loadIndexTable)/sizeof(load_index_entry); 
                 i++) {
		if (loadIndexTable[i].index == l) {
			w = (loadIndexTable[i].load) * 4; // 4 wheels
			return true;
		}
	}
	return false;
}

void decodeCarWeight(const unsigned int & we, string& o)
{
	stringstream ss;
	ss << "\t\tCar Weight cannot exceed  " << we << " pounds;" << endl;
	o = ss.str();
	return;
}

/* the entry point function */
bool decodeTireType(const string& tire, string& o)
{
	string tireFields[10];
	string tire1 = tire;
	smatch sm;
	string partialOutput;

	regex tireNumber("[1-9][0-9]+");
	int i = 0;
	while(regex_search(tire1, sm, tireNumber)) {
		if (i == 10) { break; } // just be safe.
		tireFields[i++] = sm.str();
		// cout << sm.str() << endl;
		tire1 = sm.suffix(); // search what is left.
	}

	if (i != 4) {
		return false; // decode failed.
	}

	decodeWidth(tireFields[0], partialOutput);
	o += partialOutput;

	decodeAspect(tireFields[1], partialOutput);
	o += partialOutput;
	
	decodeDiameter(tireFields[2], partialOutput);
	o += partialOutput;
	
	decodeLoad(tireFields[3], partialOutput);
	o += partialOutput;

	unsigned int carWeight = 0;
	if (getMaxCarWeight(tireFields[3], carWeight)) {
		decodeCarWeight(carWeight, partialOutput);
		o += partialOutput;
	}
	
	return true; // decode ok.
}


int
main ()
{
	while (true) {
		string tire;
		string output;
		cout << "Please input your tire type info: ";
		cin >> tire;
		if (!decodeTireType(tire, output)) {
			cout << "decode failed" << endl;
		} else {
			cout << output << endl;
		}
	}
}

