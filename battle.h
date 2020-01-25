#ifndef _BATTLE_H_
#define _BATTLE_H_
#include <iostream>
#include <array>
#include <string>
#include "Trainer.h"

void engage_battle_loop(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, const int& battle_type);

void display_battle_opening(Trainer& tnr, std::shared_ptr<Trainer>& enemy_tnr, const int& battle_type);
void display_battlers(Pokemon& pok, Pokemon& enemy_pok);
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

#endif