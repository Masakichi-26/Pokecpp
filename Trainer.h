#ifndef _TRAINER_H_
#define _TRAINER_H_

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Location.h"
#include "Pokemon.h"

//enum world_locations { Exit, Masara, Route_1, Tokiwa };

class Trainer {
private:
	std::string trainer_name = "";
	std::string trainer_id = "     ";
	int trainer_funds = 0;
	std::vector<Pokemon> party_current;
	std::vector<std::vector<Pokemon>> party_in_pc;
	std::vector<int> lead_fightable_pokemon;
//	world_locations trainer_location = Masara;
//	std::string trainer_location = "マサラタウン";
	Location trainer_location  {"マサラタウン"};
	Location previous_location{};
public:
	Trainer();
	Trainer(const std::string& name);
	Trainer(const std::vector<Pokemon> & party);
	Trainer(const std::string& name, const std::vector<Pokemon> & party);
//	Trainer(Trainer&& source);

	void set_trainer_id();
	std::string get_trainer_name();
	std::string get_trainer_id();

	Pokemon& get_lead_pokemon();
	int& get_lead_pokemon_index();
	std::vector<int>& get_fightable_pokemon(const size_t pokemon_count);
	void add_pokemon_to_party(Pokemon&& poke);
	Pokemon& get_current_pokemon(const int& element);
	std::shared_ptr<Pokemon> get_current_pokemon_shared_ptr(const int &element);
	void display_party_current(int &&i = 1);

	Location get_location_info();
	Location get_previous_location_info();
	void display_trainer_location();
	std::vector<Pokemon> get_current_party();
	void switch_pokemon(int &first_el, int &second_el);
	bool check_if_party_is_empty();
	bool check_if_party_is_all_defeated();

	void reset_party_battle_stats();

	void set_current_location(std::string& loc);
	void set_previous_location(std::string& loc);

//	friend void change_trainer_location(world::locations &wl);

	/*
	void location_loop();
	std::string get_location_name();
	void display_location_and_surrounding_areas();
	bool display_route_prediction(int& pok_count, int& tnr_count);
	void change_trainer_location(char& sel);
	*/
};


#endif