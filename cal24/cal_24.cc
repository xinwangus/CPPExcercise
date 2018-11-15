/*
 * A test program to test Git and Github.
 * 
 * Given 4 int's in the range of 1-24, 
 * decide if they can produce 24 with +|-|*|\|
 * operations.
 */
#include <iostream>
using namespace std;
const int FINAL_V = 24;

void
print_result(int v1,
	     int v2,
	     int op,
	     int result)
{
	int big = (v1 >= v2)? v1:v2;
	int small = (v1 >= v2)? v2:v1;

	cout << "( ";
	cout << big;
        switch (op)
        {
        case 0:
                cout << " + ";
                break;
        case 1:
                cout << " - ";
                break;
        case 2:
                cout << " * ";
                break;
        case 3:
                cout << " / ";
                break;
        default:
                break;
        }

	cout << small;
	cout << " ) = ";
	if (result == FINAL_V) {
		cout << "<" << result <<">";
	} else {
		cout << result;
	} 
	cout << endl;
}

void
do_math(int v1,
	 int v2,
	 int* p_v,
	 int* m_v,
	 int* t_v,
	 int* d_v)
{
	*p_v = *m_v = *t_v = *d_v = -1;
	if ((v1 <= 0) ||
	    (v2 <= 0)) {
		return;
	}
	*p_v = v1 + v2;
	*t_v = v1 * v2;
	int big = (v1 >= v2)? v1:v2;
	int small = (v1 >= v2)? v2:v1;

	*m_v = big - small;

	if ((big % small) == 0) {
		*d_v = big/small;
	}
}

int
can_make_it (int v1, int v2, int target) 
{
        // cout << "< " << v1 << " " << v2 << " " << target << endl;
	if ((v1 <= 0) ||
	    (v2 <= 0) ||
	    (target <= 0)) {
		return -1;
	}
	int a[4] = {0};
	do_math (v1, v2,
		 &a[0], &a[1], &a[2], &a[3]);

	for (int i = 0; i < 4; i++) {
		if (a[i] == target) {
			return i;
		}
	}
	return -1;
}

static bool
_method_two_two_internal (int v1, int v2, int v3, int v4, int target)
{
	int i, j, k;
	int a[4] = {0};
	int b[4] = {0};

	do_math (v1, v2, 
		&a[0], &a[1], &a[2], &a[3]);
	do_math (v3, v4, 
		&b[0], &b[1], &b[2], &b[3]);

	for (i = 0; i < 4; i++) {
	    for (j = 0; j < 4; j++) {
		k = can_make_it(a[i], b[j], target);
		if (k >= 0) {
			/* need to print */
			print_result(v1, v2, i, a[i]);
			print_result(v3, v4, j, b[j]);
			print_result(a[i], b[j], k, target);
			return true;
		}
	    }
	}
	return false;
}

static bool
_method_two_one_one_internal (int v1, int v2, int v3, int v4, int target)
{
	int i, j, k;
	int a[4] = {0};
	int b[4] = {0};

	do_math (v1, v2, 
		&a[0], &a[1], &a[2], &a[3]);
	for (i = 0; i < 4; i++) {
            memset(b, 0, 4);
	    do_math (a[i], v3, 
		&b[0], &b[1], &b[2], &b[3]);
	    for (j = 0; j < 4; j++) {
		k = can_make_it(b[j], v4, target);
		if (k >= 0) {
			/* need to print */
			print_result(v1, v2, i, a[i]);
			print_result(a[i], v3, j, b[j]);
			print_result(b[j], v4, k, target);
			return true;
		}
	    }
	}
	return false;
}

bool
method_two_two (int v1, int v2, int v3, int v4, int target)
{
	if (_method_two_two_internal(v1, v2, v3, v4, target) ||
	    _method_two_two_internal(v1, v3, v2, v4, target) ||
	    _method_two_two_internal(v1, v4, v2, v3, target)) {
		return true;
	}
	return false;
}

bool
method_two_one_one (int v1, int v2, int v3, int v4, int target)
{
	if (_method_two_one_one_internal(v1, v2, v3, v4, target) ||
	    _method_two_one_one_internal(v1, v2, v4, v3, target) ||
	    _method_two_one_one_internal(v1, v3, v2, v4, target) ||
	    _method_two_one_one_internal(v1, v3, v4, v2, target) ||
	    _method_two_one_one_internal(v1, v4, v2, v3, target) ||
	    _method_two_one_one_internal(v1, v4, v3, v2, target) ||
	    _method_two_one_one_internal(v2, v3, v1, v4, target) ||
	    _method_two_one_one_internal(v2, v3, v4, v1, target) ||
	    _method_two_one_one_internal(v2, v4, v1, v3, target) ||
	    _method_two_one_one_internal(v2, v4, v3, v1, target) ||
	    _method_two_one_one_internal(v3, v4, v1, v2, target) ||
	    _method_two_one_one_internal(v3, v4, v2, v1, target)) {
		return true;
	}
	return false;
}

int
main()
{
	int input[4] = {0};
	int i = 0;
	while (1) {
	    i = 0;
	    cout << "\n\n New Game:" << endl;
            cout << "Provide 4 positive int " << endl;
	    while (i < 4) {
            cin >> input[i];
            i++;
	    }

	    cout << "\n" <<"Working on them .....\n";

	    if (method_two_two(input[0], input[1], input[2], input[3], FINAL_V)) {
		goto next;
	    }

	    if (method_two_one_one (input[1], input[2], input[3], input[0], FINAL_V)) {
		goto next;
	    }
	    cout << "can not make 24!" << endl;
	    continue;
next:
	    cout << "can make 24!" << endl;
	}
	return 0;
}

