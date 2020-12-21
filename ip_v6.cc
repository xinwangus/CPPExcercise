/*
 * Code to print out an IP v6 address in its most compact
 * format
 */
#include <stdio.h>

typedef unsigned char uint8_t;

void print_short(unsigned short d)
{
	printf ("%x", d);
}

void print_ipv6 (uint8_t ip[])
{
	bool is_v4 = false;

	unsigned short word[8] = {0};

	// combine to hexdecimal
	for (int i = 0; i < 16; ++i) {
		if ((i % 2) == 0) {
			word[i/2] |= (unsigned short)(ip[i] << 8);
		} else {
			word[i/2] |= (unsigned short)ip[i];
		}
	}

	if (word[5] == 0xFFFF) { is_v4 = true; }

	if (is_v4) {
		printf ("\n%hu.%hu.%hu.%hu\n", 
		        (uint8_t)ip[12],
			(uint8_t)ip[13],
		        (uint8_t)ip[14],
			(uint8_t)ip[15]);
	} else {
		// ip v6
		// find the largest all 0 range in word
		int start, b_start = -1;
		int len, b_len = 0;
		for (int j = 0; j < 8; ++j) {
/*
			print_short(word[j]);
			if (j != 7) { printf(":"); }
*/
			if (word[j] == 0) {
				if (start == -1) {
					start = j;
					len = 1;
				} else {
					len++;
				}
			} else {
				if (len > b_len) {
					b_start = start;
					b_len = len;
				}
				start = -1;
				len = 0;
			}
		}

		/*
		printf("\nb_start = %u\n", b_start);
		printf("b_len = %u\n", b_len);
		 */
		printf("\n");

		for (int j = 0; j < 8; ++j) {
			if ((j < b_start) ||
                            (j > (b_start + b_len - 1))) {
				print_short(word[j]);
				if ((j != 7) &&
				    (j + 1 != b_start)) { printf(":"); }
			} else if (j == b_start) {
				printf("::");
			}
		}
		printf("\n");
	}
}

int main () 
{
	uint8_t myip1[16] = { 254, 125, 0, 0, 
			     0, 0, 7, 7,
			     0, 0, 100, 100,
			     3, 3, 3, 3 };
	print_ipv6(myip1);

	uint8_t myip2[16] = {0, 0, 7, 7,
			     0, 0, 100, 100,
			     3, 3, 3, 3,
			     254, 125, 0 ,0 };
	print_ipv6(myip2);
 
	uint8_t myip3[16] = {0, 0, 7, 7,
			     0, 0, 100, 100,
			     3, 3, 255, 255,
			     254, 125, 0 ,0 };
	print_ipv6(myip3);
}
