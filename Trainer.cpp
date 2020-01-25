#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <utility>
#include "Trainer.h"

// constructor
Trainer::Trainer(const std::string &name)
	: trainer_name {name} {
	set_trainer_id();
}


Trainer::Trainer(const std::vector<Pokemon> & party)
	: party_current{ party } {

}

/*
// Move constructor
Trainer::Trainer(Trainer &&source)
	: trainer_name{ source.trainer_name }, trainer_id{ source.trainer_id }, trainer_funds{ source.trainer_funds }, party_current{ source.party_current }, trainer_location{ source.trainer_location }, previous_location{ source.previous_location } {
	source
}*/


Trainer::Trainer(const std::string& name, const std::vector<Pokemon> & party)
	: trainer_name{ name }, party_current{ party } {

}


void Trainer::set_trainer_id(){
	srand(time(nullptr));
	std::stringstream ss;
	int rn {};
	std::string id;
	for(int i = 0; i < 5; i++){
		rn = rand() % 10;
		ss << rn;
	}
	trainer_id = ss.str();
}



std::string Trainer::get_trainer_name(){
	return trainer_name;
}


std::string Trainer::get_trainer_id(){
	return trainer_id;
}


Location Trainer::get_location_info() {
	return trainer_location;
}


Location Trainer::get_previous_location_info() {
	return previous_location;
}


void Trainer::set_current_location(std::string& loc) {
	trainer_location = loc;
}


void Trainer::set_previous_location(std::string& loc) {
	previous_location = loc;
}


void Trainer::display_trainer_location() {
	std::cout << trainer_location << std::endl;
}


bool Trainer::check_if_party_is_empty() {
	return party_current.empty();
}


std::vector<Pokemon> Trainer::get_current_party() {
	return party_current;
}


void Trainer::switch_pokemon(int &first_el, int &second_el) {
	std::swap(party_current.at(first_el), party_current.at(second_el));
}


/*
void Trainer::change_trainer_location(world::locations &wl){
	trainer_location = wl;
}
*/

void Trainer::add_pokemon_to_party(Pokemon &&poke){
	bool done = false;
//	std::cout << poke.get_pokedex_name() << "が　なかまになった！　" << std::endl;
	if (party_current.size() < 6) {
		party_current.emplace_back(poke);
	}
	else {
		party_in_pc.at(0).emplace_back(poke);
	}

	/*
	for(size_t i{0}; i < 6; i++){
		if(party_current.at(i).get_pokedex_name() == "" && !done){
			party_current.at(i) = poke;
//			std::cout << poke.get_pokedex_name() << "が　なかまになった！　" << i << std::endl;
			done = true;
		}
	}
	*/
}


void Trainer::display_party_current(int &&i){
	std::cout << std::endl;
	//int i{1};
	for(auto &p: party_current){
//		if(p.get_nickname() != "" && p.get_pokedex_name() != ""){
			if (i < 10)
				std::cout << " ";
			std::cout << i++ << "）" << std::setw(12) << std::left << p.get_nickname() 
				<< "Lv " << std::setw(3) << std::right << p.get_level_exp().at(0)
				<< "　" << p.display_gender() << "　HP　"
				<< std::setw(3) << std::right << p.get_stats_battle().at(0) 
				<< " / " << std::setw(3) << p.get_stats_main().at(0) << std::endl;
//		}
	}
}


Pokemon& Trainer::get_lead_pokemon() {
	size_t i{ 0 };
	for (auto &p : party_current) {
		int cur_hp = p.get_stats_battle().at(i);
		if (cur_hp != 0)
			return p;
	}
}


int& Trainer::get_lead_pokemon_index() {
	size_t i{ 0 };
	int index{ 0 };
	for (auto &p : party_current) {
		int cur_hp = p.get_stats_battle().at(i);
		if (cur_hp != 0)
			return index;
		index++;
	}
}


Pokemon& Trainer::get_current_pokemon(const int &element) {
	return party_current.at(element);
}


std::shared_ptr<Pokemon> Trainer::get_current_pokemon_shared_ptr(const int &element) {
	return std::shared_ptr<Pokemon>(&(party_current.at(element)));
}


bool Trainer::check_if_party_is_all_defeated() {
	int count{ 0 };
	int defeated_pok{ 0 };
	for (auto &p : party_current) {
//		if (p.get_info_constants().at(0) != 0) {
			if(p.get_stats_battle().at(0) == 0)
				defeated_pok++;
			count++;
//		}
	}

	return defeated_pok == count ? true : false;
}