#include <iomanip>
#include <fstream>
#include <conio.h>
#include "Pokemon.h"
#include "create_pokemon.h"
#include "create_waza.h"
#include "waza_list_levelUp.h"
#include "text_display.h"

Pokemon::Pokemon(){};

// constructor
Pokemon::Pokemon(std::string pokedex_name, int level)
	: pokedex_name {pokedex_name}, nickname {pokedex_name}, level_exp {level} {
	set_baseStats_infoConstants();
	info_non_constants.at(0) = set_gender(info_constants.at(4));
	info_non_constants.at(1) = set_nature();
	stats_indiv_values = set_stats_indiv_values();
	set_stats_main();
	stats_battle = stats_main;
	level_exp.at(1) = set_exp(level_exp.at(0), info_constants.at(3));
	level_exp.at(2) = set_exp(level_exp.at(0) + 1, info_constants.at(3));
//	waza_current = check_waza();
	check_waza(pokedex_number, level_exp.at(0), 0, waza_current);
}


Pokemon::Pokemon(int number, int level)
	: pokedex_number{number}, level_exp {level} {
	set_name();
	set_baseStats_infoConstants();
	info_non_constants.at(0) = set_gender(info_constants.at(4));
	info_non_constants.at(1) = set_nature();
	stats_indiv_values = set_stats_indiv_values();
	set_stats_main();
	stats_battle = stats_main;
	level_exp.at(1) = set_exp(level_exp.at(0), info_constants.at(3));
	level_exp.at(2) = set_exp(level_exp.at(0) + 1, info_constants.at(3));
//	waza_current = check_waza(pokedex_number, level_exp.at(0), 0, waza_current);
	check_waza(pokedex_number, level_exp.at(0), 0, waza_current);
}

/*
// copy constructor
Pokemon::Pokemon(const Pokemon &source) 
	: Pokemon{source.pokedex_name, source.level_exp.at(0)}  {
	std::cout << "-----Copy Constructor being called-----" << std::endl;
}


// move constructor
Pokemon::Pokemon(Pokemon &&source) 
	: Pokemon{ source.pokedex_name, source.level_exp.at(0) } {
	std::cout << "-----Move Constructor being called-----" << std::endl;
}


~Pokemon::Pokemon() {
	std::cout << "-----Destructor being called-----" << std::endl;
}
*/

std::string Pokemon::get_nickname(){
	return nickname;
}


std::string Pokemon::get_pokedex_name(){
	return pokedex_name;
}


std::array<int, 3> Pokemon::get_level_exp(){
	return level_exp;
}


std::array<int, 6> Pokemon::get_stats_main(){
	return stats_main;
}


std::array<int, 6> Pokemon::get_stats_battle(){
	return stats_battle;
}


std::array<int, 8> Pokemon::get_stats_battles_stages() {
	return stats_battle_stages;
}


std::array<int, 6> Pokemon::get_stats_indiv_values(){
	return stats_indiv_values;
}


std::array<int, 6> Pokemon::get_stats_base(){
	return stats_base;
}


std::array<int, 6> Pokemon::get_info_constants(){
	return info_constants;
}


std::array<int, 3> Pokemon::get_info_non_constants(){
	return info_non_constants;
}


void Pokemon::set_name(){	
	pokedex_name = init_pokedex_name(pokedex_number);
	if(nickname == "")
		nickname = pokedex_name;
}


std::string Pokemon::display_gender(){
	if(info_non_constants.at(0) == 3)
		return "@"; // genderless
	else if(info_non_constants.at(0) == 1)
		return "‰"; // male
	else if(info_non_constants.at(0) == 2)
		return "Š"; // female
	else
		return "H"; // 0 ‚Ìê‡
}


std::string Pokemon::display_nature(){
	if(info_non_constants.at(1) == 0)
		return "‚ª‚ñ‚Î‚è‚â";	// Hardy
	else if(info_non_constants.at(1) == 1)
		return "‚³‚İ‚µ‚ª‚è";	// Lonely
	else if(info_non_constants.at(1) == 2)
		return "‚ä‚¤‚©‚ñ";		// Brave
	else if(info_non_constants.at(1) == 3)
		return "‚¢‚¶‚Á‚Ï‚è";	// Adamant
	else if(info_non_constants.at(1) == 4)
		return "‚â‚ñ‚¿‚á";		// Naughty
	else if(info_non_constants.at(1) == 5)
		return "‚¸‚Ô‚Æ‚¢";		// Bold
	else if(info_non_constants.at(1) == 6)
		return "‚·‚È‚¨";		// Docile
	else if(info_non_constants.at(1) == 7)
		return "‚Ì‚ñ‚«";		// Relaxed
	else if(info_non_constants.at(1) == 8)
		return "‚í‚ñ‚Ï‚­";		// Impish
	else if(info_non_constants.at(1) == 9)
		return "‚Ì‚¤‚Ä‚ñ‚«";	// Lax
	else if(info_non_constants.at(1) == 10)
		return "‚¨‚­‚Ñ‚å‚¤";	// Timid
	else if(info_non_constants.at(1) == 11)
		return "‚¹‚Á‚©‚¿";		// Hasty
	else if(info_non_constants.at(1) == 12)
		return "‚Ü‚¶‚ß";		// Serious
	else if(info_non_constants.at(1) == 13)
		return "‚æ‚¤‚«";		// Jolly
	else if(info_non_constants.at(1) == 14)
		return "‚Ş‚¶‚á‚«";		// Naive
	else if(info_non_constants.at(1) == 15)
		return "‚Ğ‚©‚¦‚ß";		// Modest
	else if(info_non_constants.at(1) == 16)
		return "‚¨‚Á‚Æ‚è";		// Mild
	else if(info_non_constants.at(1) == 17)
		return "‚ê‚¢‚¹‚¢";		// Quiet
	else if(info_non_constants.at(1) == 18)
		return "‚Ä‚ê‚â";		// Bashful
	else if(info_non_constants.at(1) == 19)
		return "‚¤‚Á‚©‚è‚â";	// Rash
	else if(info_non_constants.at(1) == 20)
		return "‚¨‚¾‚â‚©";		// Calm
	else if(info_non_constants.at(1) == 21)
		return "‚¨‚Æ‚È‚µ‚¢";	// Gentle
	else if(info_non_constants.at(1) == 22)
		return "‚È‚Ü‚¢‚«";		// Sassy
	else if(info_non_constants.at(1) == 23)
		return "‚µ‚ñ‚¿‚å‚¤";	// Careful
	else if(info_non_constants.at(1) == 24)
		return "‚«‚Ü‚®‚ê";		// Quirky
	else
		return "“–ŠY‚È‚µ";
}




void Pokemon::set_baseStats_infoConstants(){
	std::array<int, 12> indiv_constants_arr = get_basic_data(pokedex_number);
	for(size_t i {0}; i < 6; i++)
		stats_base.at(i) = indiv_constants_arr.at(i);
	
	for(size_t j{0}; j < 6; j++)
		info_constants.at(j) = indiv_constants_arr.at(j+6);

}


void Pokemon::set_stats_main(){
	std::array<int, 5> nature_modifier = get_nature_modifiers(info_non_constants.at(1));
	
	int hp_constant {10};
	int other_stats_constant {5};
	double hp_double {};
	double other_double {};
	
	hp_double = (((2 * stats_base.at(0) + stats_indiv_values.at(0) + (stats_effort_values.at(0) / 4.0)) * level_exp.at(0)) / 100.0) + level_exp.at(0) + hp_constant;
	stats_main.at(0) = std::floor(hp_double);
	for(size_t i{1}; i <= 5; i++){
		other_double = ((((2 * stats_base.at(i) + stats_indiv_values.at(i) + (stats_effort_values.at(i) / 4.0)) * level_exp.at(0)) / 100.0) + other_stats_constant);
		other_double = std::floor(other_double) * (nature_modifier.at(i-1) / 100.0);
		stats_main.at(i) =  std::floor(other_double);
//		std::cout << stats_main.at(i) << " ";
	}
	std::cout << std::endl;
}


void Pokemon::reset_stats_battle() {
	for (size_t i{ 1 }; i < stats_battle.size(); i++)
		stats_battle.at(i) = stats_main.at(i);
}


void Pokemon::reset_stats_battle_stages() {
	stats_battle_stages = { 0, 0, 0, 0, 0, 0, 0, 0 };
}


void Pokemon::change_stats_battle_stages(std::array<int, 2> &index_change) {
	if (stats_battle_stages.at(index_change.at(0)) + index_change.at(1) >= 7) {
		text_stat_at_max(nickname, index_change.at(0));
	}
	else if (stats_battle_stages.at(index_change.at(0)) + index_change.at(1) <= -7) {
		text_stat_at_min(nickname, index_change.at(0));
	}
	else {
		stats_battle_stages.at(index_change.at(0)) += index_change.at(1);
		text_stat_change(nickname, index_change.at(0), index_change.at(1));
	}

	update_battle_stats();
}


void Pokemon::update_battle_stats() {
	// skip HP and start at ATTACK
	for (size_t i{ 1 }; i < stats_battle.size(); i++) {
		int stage = stats_battle_stages.at(i);
		double stat = stats_battle.at(i);
		std::cout << stat << std::endl;
		switch (stage) {
			case 6: stat *= 4.0; break;
			case 5: stat *= 3.5; break;
			case 4: stat *= 3.0; break;
			case 3: stat *= 2.5; break;
			case 2: stat *= 2.0; break;
			case 1: stat *= 1.5; break;
			case 0: stat *= 1.0; break;
			case -1: stat *= (2.0 / 3); break;
			case -2: stat *= (2.0 / 4); break;
			case -3: stat *= (2.0 / 5); break;
			case -4: stat *= (2.0 / 6); break;
			case -5: stat *= (2.0 / 7); break;
			case -6: stat *= (2.0 / 8); break;
		}
		std::cout << stat << std::endl;
		stats_battle.at(i) = std::floor(stat);
	}
}


void Pokemon::add_exp(const int &exp){
	level_exp.at(1) += exp;
	while(level_exp.at(1) >= level_exp.at(2)){
		level_exp.at(0)++;
		level_exp.at(2) = set_exp(level_exp.at(0) + 1, info_constants.at(3));
		display_level_up();
		check_waza(pokedex_number, level_exp.at(0), 1, waza_current);
		_getch();
	}
}


void Pokemon::deal_damage(const int &damage) {
	stats_battle.at(0) -= damage;
	if (stats_battle.at(0) < 0)
		stats_battle.at(0) = 0;
}


void Pokemon::display_level_up(){
	std::array<int, 6> previous = stats_main;
	std::array<int, 6> difference {};
	std::array<std::string, 6> stats_names {"HP", "UŒ‚", "–hŒä", "“ÁU", "“Á–h", "‘f‘‚³"};
	set_stats_main();
	for(size_t i{0}; i < 6; i++)
		difference.at(i) = stats_main.at(i) - previous.at(i);
	
	std::cout << std::setw(16) << std::left << nickname 
		<< std::setw(5) << "Lv "
		<< std::setw(3) << std::right << level_exp.at(0) << std::endl;
	for(size_t j{0}; j < 6; j++){
		std::cout << std::setw(10) << std::left << stats_names.at(j)
			<< std::setw(3) << std::right << previous.at(j) << " + "
		<< std::setw(2) << difference.at(j) << " = "
		<< std::setw(3) << stats_main.at(j) << std::endl;
	}
}


std::vector<Waza> Pokemon::get_waza_current(){
	return waza_current;
}


int Pokemon::get_waza_current_size() {
	return waza_current.size();
}


void Pokemon::display_status_menu() {
	std::array<std::string, 6> stats_names{ "HP", "UŒ‚", "–hŒä", "“ÁU", "“Á–h", "‘f‘‚³" };
	int i{ 0 };
//	std::cout << "1234567890123456789012345678901234567890123456789012345678901234567890" << std::endl;

	std::cout << "}ŠÓ No. " << std::setw(3) << std::right << std::setfill('0') << info_constants.at(0) << std::setfill(' ') << "@" << std::setw(10) << std::left << pokedex_name << std::endl;
	std::cout << std::endl;

	std::cout << "@" << std::setw(10) << std::left << nickname << "  " << display_gender() << "  Lv " 
		<< std::setw(3) << std::right << level_exp.at(0) 
		<< std::setw(24) << std::left << "" << "í“¬’l" 
		<< std::setw(4) << "" << "”\—Í’l"
		<< std::setw(4) << "" << "ŒÂ‘Ì’l"
		<< std::setw(4) << "" << "“w—Í’l"
		<< std::endl;

	// HP
	std::cout
		<< std::setw(40) << std::left << "" << std::setw(6) << stats_names.at(i) 
		// << std::setw(3) << std::right << stats_battle.at(i) << " / " 
		<< std::setw(3) << ""
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i) 
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

	// UŒ‚
	i++;
	std::cout << "@ƒ^ƒCƒvF@" << std::setw(12) << std::left << display_type(info_constants.at(1)) 
		<< std::setw(12) << display_type(info_constants.at(2)) 
		<< std::setw(4) << ""
		<< std::setw(9) << stats_names.at(i)
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i)
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

	// –hŒä
	i++;
	std::cout << "@«Ši@F@" << std::setw(12) << std::left << display_nature() 
		<< std::setw(16) << ""
		<< std::setw(9) << stats_names.at(i)
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i)
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

	// “ÁU
	i++;
	std::cout 
		<< std::setw(40) << ""
		<< std::setw(9) << std::left << stats_names.at(i)
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i)
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

	// “Á–h
	i++;
	std::cout << "@Œ»İ‚ÌŒoŒ±’l@@F@" 
		<< std::setw(10) << std::right << level_exp.at(1) 
		<< std::setw(8) << ""
		<< std::setw(9) << std::left << stats_names.at(i)
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i)
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

	// ‘f‘‚³
	i++;
	std::cout << "@Ÿ‚ÌƒŒƒxƒ‹‚Ü‚Å@F@" 
		<< std::setw(10) << std::right << level_exp.at(2) - level_exp.at(1) 
		<< std::setw(8) << ""
		<< std::setw(9) << std::left << stats_names.at(i)
		<< std::setw(3) << std::right << stats_battle.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_main.at(i)
		<< std::setw(8) << ""
		<< std::setw(2) << stats_indiv_values.at(i)
		<< std::setw(7) << ""
		<< std::setw(3) << stats_effort_values.at(i)
		<< std::endl;

}