#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_

#include <string>

void text_player_sendout_pokemon(std::string&& pok_name);
void text_enemy_sendout_pokemon(std::string&& trainer_name, std::string&& pok_name, const bool& trainer_battle);
void text_player_withdraw_pokemon(std::string&& pok_name);

void text_escape_failure();
void text_escape_success();

std::string text_get_stat_name(int &index);
void text_stat_at_max(std::string &name, int &stat);
void text_stat_at_min(std::string &name, int &stat);
void text_stat_change(std::string &name, int &stat, int &stage);

std::string text_press_any_button();

#endif