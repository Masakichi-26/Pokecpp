#ifndef _BATTLE_H_
#define _BATTLE_H_
#include <iostream>
#include <array>
#include <string>
#include "Trainer.h"
#include "BattleAction.h"

class Battle {
private:
	Trainer player;
	std::shared_ptr<Trainer> enemy;
	std::vector<int> active_player_pokemon_index;
	std::vector<int> active_enemy_pokemon_index;

	int pokemon_count = 2;
	bool trainer_battle = false;
	bool can_use_items_gain_exp = true;

	bool escape = false;
	int escape_attempts{ 0 };

	bool player_all_defeated = false;
	bool enemy_all_defeated = false;


public:
	Battle();
	Battle(Trainer& player, std::shared_ptr<Trainer>& enemy);
	Battle(Trainer& player, std::shared_ptr<Trainer>& enemy, bool is_trainer);

	void engage_battle_loop();

	void battle_initialization();
	void initialize_stats();


	void display_battlers();
	void display_team(std::vector<int>& index, std::vector<Pokemon>&& party);
	void display_battler_basics(Pokemon& pok);
	void display_battler_hp(Pokemon& pok);
	void display_withdraw_pokemon(Pokemon& pok);
	void display_sendout_pokemon(Pokemon& pok, Pokemon& enemy_pok);
	int display_trainer_pokemon(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, int &index);

	int select_waza_player(Pokemon& pok);
	int select_waza_enemy(Pokemon& pok);

	void do_battle(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza);
	bool determine_player_order(const int& player_priority, const int& enemy_priority, const int& pok_speed, const int& enemy_pok_speed);
	void use_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza);
	bool check_hit_or_miss(const int& acc);
	int calc_damage(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza);
	void status_waza(Pokemon& pok, Pokemon& enemy_pok, const int& p_waza, const int& e_waza);

	bool check_party_all_defeated(Trainer &tnr);
	bool try_escape(Pokemon& pok, Pokemon& enemy_pok, int& attempts);
};

#endif