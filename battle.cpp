#include <iomanip>
#include <cmath>
#include <conio.h>
#include "battle.h"
#include "main_menu.h"
#include "selection_manipulation.h"
#include "create_waza.h"
#include "text_display.h"
#include <memory>

void engage_battle_loop(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, const int& battle_type) {
	bool show_battlers = true;
	std::string sel{};
	bool player_all_defeated = false;
	bool enemy_all_defeated = false;
	bool nigeru = false;
	int nigeru_attempts{ 0 };
	// pointers and actual pokemon in trainer's party were being treated as different things, so try using a reference instead
		//std::unique_ptr<Pokemon> player_active_pokemon = std::make_unique<Pokemon>(tnr.get_lead_pokemon());
		//std::unique_ptr<Pokemon> enemy_active_pokemon = std::make_unique<Pokemon>(enemy_tnr->get_lead_pokemon());
	int player_active_pok_index = tnr.get_lead_pokemon_index();
	int enemy_active_pok_index = enemy_tnr->get_lead_pokemon_index();

	// Pokemon &player_active_pokemon = tnr.get_current_pokemon(player_active_pok_index); // these need to become pointers so they can be reseatable
	// Pokemon &enemy_active_pokemon = enemy_tnr->get_current_pokemon(enemy_active_pok_index);
	// std::shared_ptr<Pokemon> player_active_pokemon = tnr.get_current_pokemon_shared_ptr(player_active_pok_index);
	// std::shared_ptr<Pokemon> enemy_active_pokemon = enemy_tnr->get_current_pokemon_shared_ptr(enemy_active_pok_index);


	int player_waza_index = -1;
	int enemy_waza_index = -1;

	display_battle_opening(tnr, enemy_tnr, battle_type);
	// player_active_pokemon->reset_stats_battle();
	// enemy_active_pokemon->reset_stats_battle();
	
	do {
		if (show_battlers) {
			display_battlers(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index));
			show_battlers = false;
		}

		std::cin >> sel;
		if (sel == "1" || sel == "�P") {
			player_waza_index = select_waza_player(tnr.get_current_pokemon(player_active_pok_index));
			if (player_waza_index == -1) {
				show_battlers = true;
			}
			else {
				enemy_waza_index = select_waza_enemy(enemy_tnr->get_current_pokemon(enemy_active_pok_index));
//				std::cout << "index: " << enemy_waza_index << std::endl;
				do_battle(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index), player_waza_index, enemy_waza_index);
				show_battlers = true;
			}
		}
		else if (sel == "3" || sel == "�R") {
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
		else if (sel == "4" || sel == "�S") {
			player_waza_index = -4;
			nigeru = try_escape(tnr.get_current_pokemon(player_active_pok_index), enemy_tnr->get_current_pokemon(enemy_active_pok_index), nigeru_attempts);
			if (nigeru) {
				text_escape_success();
			}
			else {
				text_escape_failure();
				enemy_waza_index = select_waza_enemy(enemy_tnr->get_current_pokemon(enemy_active_pok_index));
				use_waza(enemy_tnr->get_current_pokemon(enemy_active_pok_index), tnr.get_current_pokemon(player_active_pok_index), enemy_waza_index, player_waza_index);
				show_battlers = true;
			}
		}

		player_all_defeated = tnr.check_if_party_is_all_defeated();
		enemy_all_defeated = enemy_tnr->check_if_party_is_all_defeated(); // needs consideration on how to check

	} while (!player_all_defeated && !enemy_all_defeated && !nigeru);
}


void display_battle_opening(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, const int& battle_type) {
	if (battle_type == 1) {
		text_enemy_sendout_pokemon(enemy_tnr->get_trainer_name(), enemy_tnr->get_lead_pokemon().get_pokedex_name(), battle_type);
	}

	std::cout << "�䂯���I�@" << tnr.get_lead_pokemon().get_nickname() << "�I" << std::endl;
	_getch();
}


void display_withdraw_pokemon(Pokemon& pok) {
	std::cout << pok.get_nickname() << "�A�߂�I" << std::endl;
} 


void display_sendout_pokemon(Pokemon& pok, Pokemon& enemy_pok) {
	std::cout << "����΂�A" << pok.get_nickname() << "!" << std::endl;
}


void display_battlers(Pokemon& pok, Pokemon& enemy_pok) {
//	std::cout << "123456789012345678901234567890" << std::endl;
	std::cout << std::endl;
	std::cout << "==============================" << std::endl;
	display_battler_basics(enemy_pok);
	display_battler_hp(enemy_pok);
	std::cout << "==============================" << std::endl;

	std::cout << std::setw(22) << std::left << "1�j��������"
		<< "==============================" << std::endl;
	std::cout << std::setw(22) << std::left << "2�j�ǂ���";
	display_battler_basics(pok);
	std::cout << std::setw(22) << std::left << "3�j�|�P����";
	display_battler_hp(pok);
	std::cout << std::setw(22) << std::left << "4�j������" << "==============================" << std::endl;
	std::cout << std::endl;
	std::cout << pok.get_nickname() << "�͂ǂ�����H ";

}


void display_battler_basics(Pokemon& pok) {
	std::cout << "= " << std::setw(10) << std::left << pok.get_pokedex_name()
		<< " " << std::setw(2) << pok.display_gender() << " "
		<< std::setw(6) << "" << "Lv "
		<< std::setw(3) << std::right << pok.get_level_exp().at(0)
		<< " =" << std::endl;
}


void display_battler_hp(Pokemon& pok) {
	std::cout << "=" << std::setw(12) << std::left << "" << "HP"
		<< std::setw(4) << ""
		<< std::setw(3) << std::right << pok.get_stats_battle().at(0) << " / "
		<< std::setw(3) << std::right << pok.get_stats_main().at(0)
		<< " =" << std::endl;
}


int select_waza_player(Pokemon& pok) {
	int i{ 0 };
	std::string sel{};
	int waza_size{ pok.get_waza_current_size() + 1 }; // +1 to account for "�߂�"
	int el{ -1 };
	bool loop_sel = true;

	std::cout << std::endl;
	for (auto w : pok.get_waza_current()) {
		//if (w.get_waza_name() != "-----") {
			i++;
			std::cout << "�@" << i << "�j" << std::setw(20) << std::left << w.get_waza_name()
				<< "�@" << std::setw(2) << std::right << w.get_pp_current() << "/"
				<< std::setw(2) << w.get_pp_max() << std::endl;
		//}
	}

	std::cout << std::endl;
	std::cout << "�@" << i+1 << "�j�߂�" << std::endl;
	std::cout << std::endl;
	std::cout << "�ǂ̂킴���g���H ";

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


int select_waza_enemy(Pokemon& pok) {
	int waza_count{ 0 };
	for (auto w : pok.get_waza_current()) {
		if (w.get_waza_name() != "-----")
			waza_count++;
	}

	if (waza_count > 0)
		return rand() % waza_count;
}


void do_battle(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
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
			std::cout << enemy_pok.get_nickname() << "���|�ꂽ�I" << std::endl;
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


bool determine_player_order(const int& player_priority, const int& enemy_priority, const int& pok_speed, const int& enemy_pok_speed) {
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


void use_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
	std::cout << std::endl;
	std::cout << pok.get_nickname() << "�́@" << pok.get_waza_current().at(p_waza).get_waza_name() << "���g�����I" << " ��";
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
				std::cout << "�@" << damage << "�_���[�W��^�����I" << " ��";
				enemy_pok.deal_damage(damage);
				_getch();
			}
		}
		else {
			std::cout << "�@" << "�������A�U�����O�ꂽ�I" << " ��";
			_getch();
		}
	}
}


bool check_hit_or_miss(const int &acc) {
	int rn = rand() % 100;
	if (rn < acc)
		return true;
	else
		return false;
}


int calc_damage(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
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


void status_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza) {
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


int display_trainer_pokemon(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, int &index) {
	bool tojiru = false;
	bool show_menu = true;
	std::string sel{};
	bool show_irekaeru = false;
	int party_size = tnr.get_current_party().size();

	do {
		if (show_menu) {
			std::cout << std::endl;
			std::cout << " " << tnr.get_trainer_name() << "�̃|�P����" << std::endl;
			tnr.display_party_current();
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << " " << enemy_tnr->get_trainer_name() << "�̃|�P����" << std::endl;
			enemy_tnr->display_party_current(7);
			std::cout << std::endl;
			if (party_size > 1) {
				show_irekaeru = true;
				std::cout << " I�j����ւ���" << std::endl;
			}
			std::cout << " B�j�Ƃ���" << std::endl;
			std::cout << std::endl;
			show_menu = false;
		}

		std::cin >> sel;
		std::transform(sel.begin(), sel.end(), sel.begin(), ::toupper);
		if (sel == "��" || sel == "B") {
			tojiru = true;
		}
		else if ((sel == "i" || sel == "I") && show_irekaeru) {
			std::string first{};
			std::cout << "����ւ���|�P�����̔ԍ�����͂��Ă�������" << "�i1�`" << party_size << "�j" << std::endl;
			std::cout << "�@�퓬�ɏo���|�P�����̔ԍ��F";
			std::cin >> first;
			int first_el = selection_to_element(first, party_size);

			if (first_el == -1) {
				std::cout << "����ւ��邱�Ƃ��ł��܂���ł����B" << std::endl;
				show_menu = true;
			}
			else if (first_el == index) {
				std::cout << "���̃|�P�����͊��ɐ퓬�ɏo�Ă��܂��B" << std::endl;
				show_menu = true;
			}
			else {
				return first_el;
			}
		}
		else {
			int element = -1;
			if (sel == "�P" || sel == "1")
				element = 0;
			else if (sel == "�Q" || sel == "2")
				element = 1;
			else if (sel == "�R" || sel == "3")
				element = 2;
			else if (sel == "�S" || sel == "4")
				element = 3;
			else if (sel == "�T" || sel == "5")
				element = 4;
			else if (sel == "�U" || sel == "6")
				element = 5;
			else if (sel == "�V" || sel == "7")
				element = 6;
			else if (sel == "�W" || sel == "8")
				element = 7;
			else if (sel == "�X" || sel == "9")
				element = 8;
			else if (sel == "�P�O" || sel == "10")
				element = 9;
			else if (sel == "�P�P" || sel == "11")
				element = 10;
			else if (sel == "�P�Q" || sel == "12")
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


bool check_party_all_defeated(Trainer &tnr) {
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


bool try_escape(Pokemon& pok, Pokemon& enemy_pok, int& attempts) {
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