#include <iomanip>
#include <cmath>
#include <conio.h>
#include "battle.h"
#include "main_menu.h"
#include "selection_manipulation.h"
#include "create_waza.h"
#include "text_display.h"
//#include <memory> needed for visual studio code

// constructor
Battle::Battle() {};

Battle::Battle(Trainer& player, std::shared_ptr<Trainer>& enemy)
	: player{ player }, enemy{ enemy } {
	
	//player.get_current_pokemon(0).deal_damage(999);

	active_player_pokemon_index = player.get_fightable_pokemon(pokemon_count);
	active_enemy_pokemon_index = enemy->get_fightable_pokemon(pokemon_count);
};

Battle::Battle(Trainer& player, std::shared_ptr<Trainer>& enemy, bool is_trainer)
	: Battle(player, enemy) {
	trainer_battle = is_trainer;
};

void Battle::engage_battle_loop() {
	bool show_battlers = true;
	std::string sel{};

	//int player_waza_index = -1;
	//int enemy_waza_index = -1;

	battle_initialization();
	// player_active_pokemon->reset_stats_battle();
	// enemy_active_pokemon->reset_stats_battle();
	
	do {
		if (show_battlers) {
			display_battlers();
			show_battlers = false;
		}

		std::cin >> sel;
		sel = parse_selection(sel);

		if (sel == "1") {
			player_waza_index = select_waza_player(tnr.get_current_pokemon(player_active_pok_index));
			if (player_waza_index == -1) {
				show_battlers = true;
			}
			else {
				enemy_waza_index = select_waza_enemy(enemy_tnr->get_current_pokemon(enemy_active_pok_index));
				std::cout << "index: " << enemy_waza_index << std::endl;
				do_battle(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index), player_waza_index, enemy_waza_index);
				show_battlers = true;
			}
		}
		else if (sel == "3" || sel == "３") {
			int choice = display_trainer_pokemon(tnr, enemy_tnr, player_active_pok_index);
			if(choice == -1)
				show_battlers = true;
			else if (choice >= 0 && choice <= 5) {
				display_withdraw_pokemon(tnr.get_current_pokemon(player_active_pok_index));
				player_active_pok_index = choice;
				display_sendout_pokemon(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index));

				enemy_waza_index = select_waza_enemy(enemy_tnr->get_current_pokemon(enemy_active_pok_index));
				use_waza(enemy_tnr->get_current_pokemon(enemy_active_pok_index), tnr.get_current_pokemon(player_active_pok_index), enemy_waza_index, player_waza_index);
				show_battlers = true;
			}
		}
		else if (sel == "4" || sel == "４") {
			player_waza_index = -4;
			escape = try_escape(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index), escape_attempts);
			if (escape) {
				text_escape_success();
			}
			else {
				text_escape_failure();
				enemy_waza_index = select_waza_enemy(enemy_tnr->get_current_pokemon(enemy_active_pok_index));
				use_waza(enemy_tnr->get_current_pokemon(enemy_active_pok_index), tnr.get_current_pokemon(player_active_pok_index), enemy_waza_index, player_waza_index);
				show_battlers = true;
			}
		}

		player_all_defeated = player.check_if_party_is_all_defeated();
		enemy_all_defeated = enemy->check_if_party_is_all_defeated(); // needs consideration on how to check
		player_all_defeated = true;

	} while (!player_all_defeated && !enemy_all_defeated && !escape);
}


void Battle::battle_initialization() {
	text_enemy_sendout_pokemon(enemy->get_trainer_name(), enemy->get_lead_pokemon().get_pokedex_name(), trainer_battle);
	text_player_sendout_pokemon(player.get_lead_pokemon().get_nickname());
	initialize_stats();
}


void Battle::initialize_stats() {
	player.reset_party_battle_stats();
	enemy->reset_party_battle_stats();
}


void Battle::display_withdraw_pokemon(Pokemon& pok) {
	text_player_withdraw_pokemon(pok.get_nickname());
} 


void Battle::display_sendout_pokemon(Pokemon& pok, Pokemon& enemy_pok) {
	std::cout << "がんばれ！　" << pok.get_nickname() << "!" << std::endl;
}


void Battle::display_battlers() {
	display_team(active_enemy_pokemon_index, enemy->get_current_party());
	text_action_options();
	display_team(active_player_pokemon_index, player.get_current_party());
}


void Battle::display_team(std::vector<int>& index, std::vector<Pokemon>&& party) {
	//	std::cout << "123456789012345678901234567890" << std::endl;
	for (auto& i : index) {
		std::cout << text_separator() << text_single_half_space();
	}
	text_single_empty_line();

	for (auto& i : index) {
		display_battler_basics(party.at(i));
		std::cout << text_single_half_space();
	}
	text_single_empty_line();

	for (auto& i : index) {
		display_battler_hp(party.at(i));
		std::cout << text_single_half_space();
	}
	text_single_empty_line();

	for (auto& i : index) {
		std::cout << text_separator() << text_single_half_space();
	}
	text_single_empty_line();
}


void Battle::display_battler_basics(Pokemon& pok) {
	std::cout << "= " << std::setw(10) << std::left << pok.get_pokedex_name()
		<< " " << std::setw(2) << pok.display_gender() << " "
		<< std::setw(6) << "" << "Lv "
		<< std::setw(3) << std::right << pok.get_level_exp().at(0)
		<< " =";
}


void Battle::display_battler_hp(Pokemon& pok) {
	std::cout << "=" << std::setw(12) << std::left << "" << "HP"
		<< std::setw(4) << ""
		<< std::setw(3) << std::right << pok.get_stats_battle().at(0) << " / "
		<< std::setw(3) << std::right << pok.get_stats_main().at(0)
		<< " =";
}


int Battle::select_waza_player(Pokemon& pok) {
	int i{ 0 };
	std::string sel{};
	int waza_size{ pok.get_waza_current_size() + 1 }; // +1 to account for "・ｽﾟゑｿｽ"
	int el{ -1 };
	bool loop_sel = true;

	std::cout << std::endl;
	for (auto w : pok.get_waza_current()) {
		//if (w.get_waza_name() != "-----") {
			i++;
			std::cout << "　" << i << "）" << std::setw(20) << std::left << w.get_waza_name()
				<< "　" << std::setw(2) << std::right << w.get_pp_current() << "/"
				<< std::setw(2) << w.get_pp_max() << std::endl;
		//}
	}

	std::cout << std::endl;
	std::cout << "　" << i+1 << "戻る" << std::endl;
	std::cout << std::endl;
	std::cout << "どのわざを使う？　";

	do {
		std::cin >> sel;
		el = selection_to_element(sel, waza_size);

		if (el == i) {
			loop_sel = false;
			return -1;
		}
		else if ((el >= 0 && el <= 3) && el < i) {
			loop_sel = false;
			return el;
		}
	} while (loop_sel);
	
}


int Battle::select_waza_enemy(Pokemon& pok) {
	int waza_count{ 0 };
	for (auto w : pok.get_waza_current()) {
		if (w.get_waza_name() != "-----")
			waza_count++;
	}

	if (waza_count > 0)
		return rand() % waza_count;
}


void Battle::do_battle(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
	int player_priority = pok.get_waza_current().at(p_waza).get_priority();
	int enemy_priority = enemy_pok.get_waza_current().at(e_waza).get_priority();
	int pok_speed = pok.get_stats_battle().at(5);
	int enemy_pok_speed = enemy_pok.get_stats_battle().at(5);
	bool player_first = determine_player_order(player_priority, enemy_priority, pok_speed, enemy_pok_speed);

	if (player_first) {
		use_waza(pok, enemy_pok, p_waza, e_waza);
		if (enemy_pok.get_stats_battle().at(0) > 0) {
			use_waza(enemy_pok, pok, e_waza, p_waza);
		}
		else {
			std::cout << std::endl;
			std::cout << enemy_pok.get_nickname() << "が倒れた！" << std::endl;
			_getch();
		}
	}
	else{
		use_waza(enemy_pok, pok, e_waza, p_waza);
		if (enemy_pok.get_stats_battle().at(0) > 0) {
			use_waza(pok, enemy_pok, p_waza, e_waza);
		}
		else {

		}
	}
}


bool Battle::determine_player_order(const int& player_priority, const int& enemy_priority, const int& pok_speed, const int& enemy_pok_speed) {
	if (player_priority > enemy_priority) {
		return true;
	}
	else if (player_priority < enemy_priority) {
		return false;
	}
	else {
		if (pok_speed > enemy_pok_speed) {
			return true;
		}
		else if (pok_speed < enemy_pok_speed) {
			return false;
		}
		else {
			int rn = rand() % 2;
			if (rn == 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}


void Battle::use_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
	std::cout << std::endl;
	std::cout << pok.get_nickname() << "は　" << pok.get_waza_current().at(p_waza).get_waza_name() << "を使った！";
	std::cout << std::endl;

	if (pok.get_waza_current().at(p_waza).get_scope() == 0) {

	}
	else if (pok.get_waza_current().at(p_waza).get_scope() == 1) {
		int acc = pok.get_waza_current().at(p_waza).get_waza_accuracy();
		bool waza_hits = check_hit_or_miss(acc);

		if (waza_hits) {
			int damage{ };

			if (pok.get_waza_current().at(p_waza).get_characteristic() == 0) {
				status_waza(pok, enemy_pok, p_waza, e_waza);
			}
			else if (pok.get_waza_current().at(p_waza).get_characteristic() == 1 || pok.get_waza_current().at(p_waza).get_characteristic() == 2) {
				damage = calc_damage(pok, enemy_pok, p_waza, e_waza);
				std::cout << "　" << damage << "　ダメージを与えた！" << text_press_any_button();
				enemy_pok.deal_damage(damage);
				_getch();
			}
		}
		else {
			std::cout << "　" << "しかし攻撃が外れた！" << text_press_any_button();
			_getch();
		}
	}
}


bool Battle::check_hit_or_miss(const int &acc) {
	int rn = rand() % 100;
	if (rn < acc)
		return true;
	else
		return false;
}


int Battle::calc_damage(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
	int level = pok.get_level_exp().at(0);
	double power = pok.get_waza_current().at(p_waza).get_waza_power();
	double attack{ 0 };
	double defense{ 0 };
	double modifier{ 1.0 };
	double stab{ 1.0 };
	double random{ 85.0 };

	if (pok.get_waza_current().at(p_waza).get_characteristic() == 1) {
		attack = pok.get_stats_battle().at(1);
		defense = enemy_pok.get_stats_battle().at(2);
	}
	else {
		attack = pok.get_stats_battle().at(3);
		defense = enemy_pok.get_stats_battle().at(4);
	}

	if (pok.get_info_constants().at(1) == pok.get_waza_current().at(p_waza).get_type() || pok.get_info_constants().at(2) == pok.get_waza_current().at(p_waza).get_type()) {
		stab = 1.5;
	}

	int rn = rand() % 16;
	random += rn;
	random /= 100;

	modifier *= stab * random;

	double damage_double = ((((((2.0*level) / 5) + 2)*power*(attack / defense)) / 50) + 2)*modifier;
	int damage = std::floor(damage_double);

	if (damage < 1)
		damage = 1;

	return damage;

}


void Battle::status_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
	if (check_if_waza_is_stat_changing(pok.get_waza_current().at(p_waza))) {
		std::vector<std::array<int, 2>> effect = determine_stat_changes(pok.get_waza_current().at(p_waza));

		for (std::array<int, 2> &v : effect) {
			// move targets self
			if (pok.get_waza_current().at(p_waza).get_scope() == 0) {
				pok.change_stats_battle_stages(v);
			}
			// move targets other pokemon
			else if (pok.get_waza_current().at(p_waza).get_scope() == 1) {
				enemy_pok.change_stats_battle_stages(v);
			}
		}
	}
}


int Battle::display_trainer_pokemon(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, int &index) {
	bool tojiru = false;
	bool show_menu = true;
	std::string sel{};
	bool show_irekaeru = false;
	int party_size = tnr.get_current_party().size();

	do {
		if (show_menu) {
			std::cout << std::endl;
			std::cout << " " << tnr.get_trainer_name() << "のポケモン" << std::endl;
			tnr.display_party_current();
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << " " << enemy_tnr->get_trainer_name() << "のポケモン" << std::endl;
			enemy_tnr->display_party_current(7);
			std::cout << std::endl;
			if (party_size > 1) {
				show_irekaeru = true;
				std::cout << "I）入れ替える" << std::endl;
			}
			std::cout << "B）とじる" << std::endl;
			std::cout << std::endl;
			show_menu = false;
		}

		std::cin >> sel;
		std::transform(sel.begin(), sel.end(), sel.begin(), ::toupper);
		if (sel == "ｂ" || sel == "B") {
			tojiru = true;
		}
		else if ((sel == "i" || sel == "I") && show_irekaeru) {
			std::string first{};
			std::cout << "入れ替えるポケモンの番号を入力してください" << "（1〜" << party_size << "）" << std::endl;
			std::cout << "戦闘に出すポケモンの番号：";
			std::cin >> first;
			int first_el = selection_to_element(first, party_size);

			if (first_el == -1) {
				std::cout << "入れ替えることができませんでした。" << std::endl;
				show_menu = true;
			}
			else if (first_el == index) {
				std::cout << "そのポケモンはすでに戦闘に出ています。" << std::endl;
				show_menu = true;
			}
			else {
				return first_el;
			}
		}
		else {
			int element = -1;
			if (sel == "１" || sel == "1")
				element = 0;
			else if (sel == "２" || sel == "2")
				element = 1;
			else if (sel == "３" || sel == "3")
				element = 2;
			else if (sel == "４" || sel == "4")
				element = 3;
			else if (sel == "５" || sel == "5")
				element = 4;
			else if (sel == "６" || sel == "6")
				element = 5;
			else if (sel == "７" || sel == "7")
				element = 6;
			else if (sel == "８" || sel == "8")
				element = 7;
			else if (sel == "９" || sel == "9")
				element = 8;
			else if (sel == "１０" || sel == "10")
				element = 9;
			else if (sel == "１１" || sel == "11")
				element = 10;
			else if (sel == "１２" || sel == "12")
				element = 11;

			
			if (element != -1 && element <= 5) {
				if (tnr.get_current_pokemon(element).get_info_constants().at(0) != 0) {
					call_pokemon_status_menu(tnr.get_current_pokemon(element));
					show_menu = true;
				}
			}
			else if (element != 1 && element >= 6) {
				element -= 6;
				if (enemy_tnr->get_current_pokemon(element).get_info_constants().at(0) != 0) {
					call_pokemon_status_menu(enemy_tnr->get_current_pokemon(element));
					show_menu = true;
				}
			}

		}

	} while (!tojiru);

	return -1;
}


bool Battle::check_party_all_defeated(Trainer &tnr) {
	int count{ 0 };
	int defeated{ 0 };
	for (auto p : tnr.get_current_party()) {
		if (p.get_info_constants().at(0) != 0) {
			if (p.get_stats_battle().at(0) == 0)
				defeated++;
			count++;
		}
	}

	return defeated == count ? true : false;
}


bool Battle::try_escape(Pokemon& pok, Pokemon& enemy_pok, int& attempts) {
	attempts++;
	int pok_speed = pok.get_stats_main().at(5);
	int enemy_pok_speed = enemy_pok.get_stats_main().at(5);

	if (pok_speed > enemy_pok_speed)
		return true;

	if (enemy_pok_speed <= 0)
		enemy_pok_speed = 1;

	int escape_rate = ((pok_speed * 28) / enemy_pok_speed) + (30 * attempts);
	int rn = rand() % 256;
	// std::cout << "escape rn: " << rn << std::endl;
	// std::cout << "escape rate: " << escape_rate << std::endl;

	if (rn < escape_rate)
		return true;

	return false;
}