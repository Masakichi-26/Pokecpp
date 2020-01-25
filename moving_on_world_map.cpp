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
		std::cout << "���ݒn�F�@" << cur_loc;
		if (length > 0)
			std::cout << " (����" << length << "��)";
		std::cout << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << std::endl;

		display_current_location_options(tnr);
		
		loop_reset = false;
		while (!loop_reset && sel != "q" && sel != "Q") {
			//sel.clear();
			std::cin >> sel;
			if (sel != "q" && sel != "Q") {
				if (sel == "x" || sel == "X" || sel == "��") {
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
		std::cout << i << " �j" << v << std::endl;
		i++;
	}
}


void determine_new_location(Trainer &tnr, std::string& sel, int &len, bool &loop_reset) {
	std::string new_loc{};
	std::string cur_loc = tnr.get_location_info().get_location_name();
	std::string prev_loc = tnr.get_previous_location_info().get_location_name();
	loop_reset = true;

	if (cur_loc == "�}�T���^�E��") {
		if (sel == "1" || sel == "�P") {
			new_loc = "�P�ԓ��H";
		}
		else {
			loop_reset = false;
		}
	}
	else if (cur_loc == "�P�ԓ��H") {
		if (sel == "1" || sel == "�P") {
			if (len > 1)
				len--;
			else if (len == 1) {
				if(prev_loc == "�}�T���^�E��")
					new_loc = "�g�L���V�e�B";
				else if(prev_loc == "�g�L���V�e�B")
					new_loc = "�}�T���^�E��";
			}
		}
		else if ((sel == "2" || sel == "�Q")) {
			new_loc = prev_loc;
		}
		else {
			loop_reset = false;
		}
	}
	else if (cur_loc == "�g�L���V�e�B") {
		if (sel == "1" || sel == "�P") {
			new_loc = "�P�ԓ��H";
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