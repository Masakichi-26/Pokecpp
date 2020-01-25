#ifndef _LOCATION_H_
#define _LOCATION_H_
#include <string>
#include <vector>
#include <iostream>

class Location {
	friend std::ostream& operator<<(std::ostream& os, const Location& loc);
private:
	std::string location_name = "";
	int length = 0;
	int wild_encounters = 0;
	int trainer_encounters = 0;
	std::vector<std::string> options;
public:
	Location();
	Location(std::string);

	std::string get_location_name();
	int get_length();
	int get_wild_encounters();
	int get_trainer_encounters();
	std::vector<std::string> get_options_info();

	
};

#endif