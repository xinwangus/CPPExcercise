/*
 * This is to show the trick of doing "unsigned int" comparison taking
 * wrap into considerations.
 * The trick is to cast to (int), do arithmetic calculation, then compare with 0.
 */
#include <stdio.h>
#include <assert.h>

int main ()
{
	unsigned int v1 = 0;
	unsigned int v2 = 0xFFFFFFFF;
	unsigned int v3 = 0x7FFFFFFF;
	unsigned int v4 = 0x80000000;

	printf("\nv1 = 0\n");
	printf("v1 as unsigned =%u, as signed =%d\n", v1, v1);
	printf("v2 = 0xFFFFFFFF\n");
	printf("v2 as unsigned =%u, as signed =%d\n", v2, v2);
	
	(v1 < v2)? printf("as unsigned, v1 is less than v2\n"):
        ((v1 > v2)? printf("as unsigned, v1 is more than v2\n"):           
		    printf("as unsigned, v1 == v2\n"));

	(((int)v1 - (int)v2) < 0)? (void)printf("calc as signed consider wrapping, v1 is less than v2\n"):
        ((((int)v1 - (int)v2) > 0)? (void)printf("calc as signed consider wrapping, v1 is more than v2\n"):           
		    assert(0));

	((long int)v1 < (long int)v2)? (void)printf("cast as long signed, v1 is less than v2\n"):
        (((long int)v1 > (long int)v2)? (void)printf("cast as long signed, v1 is more than v2\n"):           
		    assert(0));

	(((long int)v1 - (long int)v2) < 0)? (void)printf("calc as long signed, v1 is less than v2\n\n"):
        ((((long int)v1 - (long int)v2) > 0)? (void)printf("calc as long signed, v1 is more than v2\n\n"):           
		    assert(0));

	printf("\nv3 = 0x7FFFFFFF\n");
	printf("v3 as unsigned =%u, as signed =%d\n", v3, v3);
	printf("v4 = 0x80000000\n");
	printf("v4 as unsigned =%u, as signed =%d\n", v4, v4);

	(v3 < v4)? printf("as unsigned, v3 is less than v4\n"):
        ((v3 > v4)? printf("as unsigned, v3 is more than v4\n"):           
		    printf("as unsigned, v3 == v4\n"));

	(((int)v3 - (int)v4) < 0)? (void)printf("calc as signed consider wrapping, v3 is still less than v4\n"):
        ((((int)v3 - (int)v4) > 0)? (void)printf("calc as signed consider wrapping, v3 is more than v4\n"):           
		    assert(0));

	((long int)v3 < (long int)v4)? (void)printf("cast as long signed, v3 is still less than v4\n"):
        (((long int)v3 > (long int)v4)? (void)printf("cast as long signed, v3 is more than v4\n"):           
		    assert(0));

	(((long int)v3 - (long int)v4) < 0)? (void)printf("calc as long signed, v3 is still less than v4\n\n"):
        ((((long int)v3 - (long int)v4) > 0)? (void)printf("calc as long signed, v3 is more than v4\n\n"):           
		    assert(0));
	return 0;
}
