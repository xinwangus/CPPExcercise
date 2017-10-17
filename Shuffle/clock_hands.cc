//
// A simple program to calculate the angle of two clock
// hands (hour/min) at any time.
//

#include <stdio.h> /* scanf() */
#include <iostream>

using namespace std;

bool
get_angle(const unsigned int hour, 
	  const unsigned int min,
	  unsigned int& angle)
{
	if ((hour >= 24) || (min >= 60)) {
		return false;
	}

	// convert to 12 hour format.
	unsigned int h = hour % 12;

	// Minute hand moves 360/60 degrees every min
	unsigned int min_hand_angle = (min*6);

	// Hour hand moves 360/12 = 30 degrees every hour
	// plus the minute portion (min/60)*30.
	unsigned int hour_hand_angle = 
		(h*30) + 
                (unsigned int)(min/2); /* could be off by .5 */

	// could also use abs()
	angle = (min_hand_angle >= hour_hand_angle) ?
		(min_hand_angle - hour_hand_angle) :
		(hour_hand_angle - min_hand_angle);

	// only return the smaller angle
	if (angle > 180) {
		angle = (360 - angle);
	}

	return true;
}

int main ()
{
	unsigned int angle;
	unsigned int h;
	unsigned int m;
	
	while(1) {
		cout << "Input a time in the format of hh:mm:";
		scanf("%u:%u", &h, &m); 
		if (get_angle(h, m, angle)) {
			cout << "Angle is " << angle << endl;
		} else {
			cout << "Invalid Time!" << endl;
		}
	}
}
