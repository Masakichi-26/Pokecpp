#include <string>
#include <cctype>
#include "moving_on_world_map.h"
#include "create_opponent.h"
#include "battle.h"
#include "main_menu.h"


void move_location_on_world_map(Trainer& tnr) {
	std::string sel{};
	std::string cur_loc{};
	std::string prev_loc{};
	int length{};
	bool loop_reset = false;

	do {
		if (cur_loc != tnr.get_location_info().get_location_name()) {
			cur_loc = tnr.get_location_info().get_location_name();
			prev_loc = tnr.get_previous_location_info().get_location_name();
			length = tnr.get_location_info().get_length();
		}

		std::cout << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << "現在地：　" << cur_loc;
		if (length > 0)
			std::cout << " (あと" << length << "回)";
		std::cout << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << std::endl;

		display_current_location_options(tnr);
		
		loop_reset = false;
		while (!loop_reset && sel != "q" && sel != "Q") {
			//sel.clear();
			std::cin >> sel;
			if (sel != "q" && sel != "Q") {
				if (sel == "x" || sel == "X" || sel == "ｘ") {
					call_main_menu(tnr);
					loop_reset = true;
				}
				else {
					//determine_new_location(tnr, sel, length);
					determine_new_location(tnr, sel, length, loop_reset);
				}
			}
		}
	} while (sel != "q" && sel != "Q");
}


void display_current_location_options(Trainer& tnr) {
	int i = 1;
	std::string prev_loc = tnr.get_previous_location_info().get_location_name();
	for (auto v : tnr.get_location_info().get_options_info()) {
		size_t position = v.find("pr");
		if(position != std::string::npos)
			v.replace(position, position + 2, prev_loc);
		std::cout << i << " ）" << v << std::endl;
		i++;
	}
}


void determine_new_location(Trainer &tnr, std::string& sel, int &len, bool &loop_reset) {
	std::string new_loc{};
	std::string cur_loc = tnr.get_location_info().get_location_name();
	std::string prev_loc = tnr.get_previous_location_info().get_location_name();
	loop_reset = true;

	if (cur_loc == "マサラタウン") {
		if (sel == "1" || sel == "１") {
			new_loc = "１番道路";
		}
		else {
			loop_reset = false;
		}
	}
	else if (cur_loc == "１番道路") {
		if (sel == "1" || sel == "１") {
			if (len > 1)
				len--;
			else if (len == 1) {
				if(prev_loc == "マサラタウン")
					new_loc = "トキワシティ";
				else if(prev_loc == "トキワシティ")
					new_loc = "マサラタウン";
			}
		}
		else if ((sel == "2" || sel == "２")) {
			new_loc = prev_loc;
		}
		else {
			loop_reset = false;
		}
	}
	else if (cur_loc == "トキワシティ") {
		if (sel == "1" || sel == "１") {
			new_loc = "１番道路";
		}
		else {
			loop_reset = false;
		}
	}

	

	if (len > 0 && (new_loc != prev_loc) && loop_reset == true) {
		int wild_enc = tnr.get_location_info().get_wild_encounters();
		int tnr_enc = tnr.get_location_info().get_trainer_encounters();
		std::shared_ptr<Trainer> enemy_tnr = determine_battle_opponent(cur_loc, wild_enc, tnr_enc);
		if (!enemy_tnr->check_if_party_is_empty()) {
			engage_battle_loop(tnr, enemy_tnr, 1);
		}
	}

	if (new_loc != "") {
		tnr.set_current_location(new_loc);
		tnr.set_previous_location(cur_loc);
	}

}