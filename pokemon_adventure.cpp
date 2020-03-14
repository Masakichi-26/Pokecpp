#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <ctime>
#include <memory>

#include "create_pokemon.h"
#include "create_waza.h"
#include "create_location.h"
#include "Location.h"
#include "Trainer.h"
#include "Pokemon.h"
#include "Waza.h"
#include "waza_list_levelUp.h"
#include "moving_on_world_map.h"

// g++ -Wall -std=c++14 Pokemon.cpp Trainer.cpp Waza.cpp create_pokemon.cpp create_waza.cpp waza_list_levelUp.cpp Location.cpp pokemon_adventure.cpp -o pokemon_adventure


int main(){
	srand(time(nullptr));
	Pokemon p1 {1, 6};
	
	std::cout << "お名前は何ですか？" << std::endl;
	std::string trainer_name{};
	getline(std::cin, trainer_name);
	Trainer t1 {trainer_name};
	std::cout << "お名前は　" << t1.get_trainer_name() << "ですね。" << std::endl;
	std::cout << "ポケモンをあげます。かわいがってくださいね。" << std::endl;
	t1.add_pokemon_to_party({1, 50});
	t1.add_pokemon_to_party({ 4, 19 });
	t1.add_pokemon_to_party({ 7, 11 });
	t1.display_party_current();
//	t1.display_trainer_location();
	std::cout << t1.get_location_info().get_location_name() << std::endl;
	std::cout << t1.get_location_info().get_length() << std::endl;
	std::cout << t1.get_location_info().get_wild_encounters() << std::endl;
	std::cout << t1.get_location_info().get_trainer_encounters() << std::endl;

	int i = 0;
	for (auto o : t1.get_location_info().get_options_info()) {
		i++;
		std::cout << i << "）" << o << std::endl;
	}


	
	std::cout << p1.get_pokedex_name() << std::endl;
	std::cout << p1.get_nickname() << std::endl;

	std::cout << p1.get_level_exp().at(0) << std::endl;
	std::cout << p1.get_level_exp().at(1) << std::endl;
	std::cout << p1.get_level_exp().at(2) << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < 6; i++)
		std::cout << p1.get_info_constants().at(i) << std::endl;
	std::cout << std::endl;
	

	
	for(int i = 0; i < 3; i++)
		std::cout << p1.get_info_non_constants().at(i) << std::endl;
	std::cout << std::endl;
	

	
	std::cout << "Gender: " << p1.display_gender() << std::endl;
	std::cout << "Nature: " << p1.display_nature() << std::endl;
	for(int i = 0; i < 6; i++)
		std::cout << p1.get_stats_base().at(i) << std::endl;
	std::cout << std::endl;

	std::cout << "IVs" << std::endl;
	for(int i = 0; i < 6; i++)
		std::cout << p1.get_stats_indiv_values().at(i) << std::endl;


	std::cout << "Main Stats" << std::endl;
	for(int i = 0; i < 6; i++)
		std::cout << p1.get_stats_main().at(i) << std::endl;

	
	

	
	
	
	std::cout << std::endl;
	for(int i = 0; i < p1.get_waza_current_size(); i++){
		std::cout << std::setw(20) << std::left << p1.get_waza_current().at(i).get_waza_name() 
		<< "威力：" << std::setw(3) << std::right << p1.get_waza_current().at(i).get_waza_power() 
		<< "命中率：" << std::setw(3) << p1.get_waza_current().at(i).get_waza_accuracy() << std::endl;
	}
	
	/*
//	int enemy_level {};
	std::cout << "Exp to give: ";
	int exp_gain {};
	std::cin >> exp_gain;
	//int exp_gain = calc_exp_gained(65, enemy_level, 1);
	std::cout << "Exp gain: " << exp_gain << std::endl;
	p1.add_exp(exp_gain);
	std::cout << "Total exp is now: " << p1.get_level_exp().at(1) << std::endl;
	std::cout << "Exp for next is: " << p1.get_level_exp().at(2) << std::endl;
	*/
	
	/*
	std::cout << std::endl;
	Waza w1 {"・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ"};
	std::cout << "・ｽ墲ｴ・ｽ・ｽ: " << w1.get_waza_name() << std::endl;
	std::cout << "・ｽﾐ力　: " << w1.get_waza_power() << std::endl;
	std::cout << "・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ: " << w1.get_waza_accuracy() << std::endl;
	*/
	
//	Waza w1 = p1.get_waza_current().at(0);
	
	
	std::cout << std::endl;
	for(int i = 0; i < p1.get_waza_current_size(); i++){
		std::cout << std::setw(20) << std::left << p1.get_waza_current().at(i).get_waza_name() 
		<< "威力：" << std::setw(3) << std::right << p1.get_waza_current().at(i).get_waza_power() 
		<< "命中率：" << std::setw(3) << p1.get_waza_current().at(i).get_waza_accuracy() << std::endl;
	}
	
	move_location_on_world_map(t1);
	
	return 0;
}