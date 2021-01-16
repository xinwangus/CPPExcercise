#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


/* 
 * This is a simple interview C question.
 * Implement your own memmove() function in C.
 */


/*
 * The trick is that, src and dst may overlap, given s.
 */
void
my_memmove(void* dst, const void* src, size_t s)
{
	size_t i = 0;
	char* dc = (char*)dst;
	char* sc = (char*)src;
	if (dc == sc) {
		return;
	}
	if (dc < sc) {
		while (i++ < s) {
			*dc++ = *sc++;
		}
	} else {
		dc += s;
		sc += s;
		while (i++ < s) {
			*dc-- = *sc--;
		}
	}
}

int main ()
{
	char str1[] = "memmove can be very useful......";
	char str2[] = "memmove can be very useful......";
	memmove(str1+15,str1+20,11);
	cout << str1 << endl;
	my_memmove(str2+15,str2+20,11);
	cout << str2 << endl;
	return 0;
}
