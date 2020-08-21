#include "Waza.h"
#include "create_waza.h"


// constructor
Waza::Waza()
	: name {"-----"}{
}


//constructor
Waza::Waza(std::string name)
	: name {name} {
	std::array<int, 9> temp = init_waza_info(name);
	
	type = temp.at(0);
	power = temp.at(1);
	accuracy = temp.at(2);
	power_points_max = temp.at(3);
	power_points_current = power_points_max;
	characteristic = temp.at(4);
	scope = temp.at(5);
	priority = temp.at(6);
	text_type = temp.at(7);
	additional_effect_percentage = temp.at(8);
}

//constructor
Waza::Waza(int id)
	: id { id } {


}


std::string Waza::get_waza_name(){
	return name;
}


int Waza::get_waza_power(){
	return power;
}


int Waza::get_waza_accuracy(){
	return accuracy;
}


int Waza::get_pp_max() {
	return power_points_max;
}


int Waza::get_pp_current() {
	return power_points_current;
}


int Waza::get_priority() {
	return priority;
}


int Waza::get_scope() {
	return scope;
}


int Waza::get_characteristic() {
	return characteristic;
}


int Waza::get_type() {
	return type;
}