/* 
 * An encoding method to save space for 4 byte int, if it is less than 32768 (2^15)
 * first 3 bits in the first byte is to save the size. 
 *       5 bits in each byte is used to save the data.
 */
#include <iostream>

using namespace std;

typedef char uint8;
typedef unsigned int uint32;

#define TOP 0xE0
#define BOTTOM 0x1F

void encode(const uint32* in, uint8* out)
{
	int size = 0;
	if (*in == 0) {
		*out = 0;
		out[0] |= 1 << 5;
		return;
	}
	uint32 tmp = *in;
	while (tmp) {
		size++;
		tmp = tmp >> 5;
	}
	tmp = *in;
	for (int i = size; i > 0; i--) {
		out[i-1] = tmp & BOTTOM;
		tmp = tmp >> 5;
	}
	out[0] |= size << 5;
}

void decode(uint32* out, const uint8* in)
{
	*out = 0;
	int size = (in[0] & TOP) >> 5;
	for (int i = 0; i < size; i++) {
		*out |= (in[i] & BOTTOM) << ((size - i - 1)*5);
	}
}

int main()
{
	uint32 t;
	uint32 t_out = 0;
	uint8 en[7] = {0};
	int size = 0;

	while (cin >> t) {
		encode(&t, en);
		size = (en[0] & TOP) >> 5;
		decode(&t_out, en);
		cout << "t = " << t << endl;
		cout << "encoded size = " << size << endl;
		cout << "encoded bytes: " << endl;
		for (int i = 0; i < size; i++) {
			cout << (en[i] & BOTTOM) << " ";
		}
		cout << endl;
		cout << endl;
		assert(t == t_out);
	}
}
