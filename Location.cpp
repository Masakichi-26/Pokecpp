#include <array>
#include "Location.h"
#include "create_location.h"

// Constructors
Location::Location()
	: Location{ "" } {

}


Location::Location(std::string n)
	: location_name{ n } {
	std::array<int, 3> temp = init_location_info(location_name);
	length = temp.at(0);
	wild_encounters = temp.at(1);
	trainer_encounters = temp.at(2);

//	std::vector<std::string> temp_vec = init_options_info(location_name);
	options = init_options_info(location_name);
}


std::string Location::get_location_name() {
	return location_name;
}


int Location::get_length() {
	return length;
}


int Location::get_wild_encounters() {
	return wild_encounters;
}


int Location::get_trainer_encounters() {
	return trainer_encounters;
}


std::vector<std::string> Location::get_options_info() {
	return options;
}



std::ostream& operator<<(std::ostream& os, const Location& loc) {
	os << loc.location_name << std::endl;
	return os;
}