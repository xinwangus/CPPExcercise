#include <stdio.h>
#include <string.h>


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
		while (i < s) {
			*dc = *sc;
			dc++;
			sc++;
			i++;
		}
	} else {
		dc = dc + s;
		sc = sc + s;
		while (i < s) {
			*dc = *sc;
			dc--;
			sc--;
			i++;
		}
	}
}

int main ()
{
	char str1[] = "memmove can be very useful......";
	char str2[] = "memmove can be very useful......";
	memmove(str1+20,str1+15,11);
	puts(str1);
	my_memmove(str2+20,str2+15,11);
	puts(str2);
	return 0;
}
