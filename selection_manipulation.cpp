#include "selection_manipulation.h"

int selection_to_element(std::string &s, int &max) {
	if ((s == "1" || s == "‚P") && max > 0)
		return 0;
	else if ((s == "2" || s == "‚Q") && max > 1)
		return 1;
	else if ((s == "3" || s == "‚R") && max > 2)
		return 2;
	else if ((s == "4" || s == "‚S") && max > 3)
		return 3;
	else if ((s == "5" || s == "‚T") && max > 4)
		return 4;
	else if ((s == "6" || s == "‚U") && max > 5)
		return 5;
	else
		return -1;
}