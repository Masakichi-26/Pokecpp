#include <iostream>
#include <conio.h>
#include "text_display.h"



void text_enemy_sendout_pokemon(std::string &&trainer_name, std::string &&pok_name, const int &battle_type) {
	std::string battle_type_text{};
	if (battle_type == 1)
		battle_type_text = "が飛び出してきた！";
	else
		battle_type_text = "が勝負をしかけてきた！";

	std::cout << trainer_name << "の" << pok_name << battle_type_text << std::endl;
}


void text_escape_failure() {
	std::cout << "逃げられなかった！" << " ▽" << std::endl;
	_getch();
}


void text_escape_success() {
	std::cout << "うまく逃げ切れた！" << " ▽" << std::endl;
	_getch();
}


std::string text_get_stat_name(int &index) {
	if (index == 0)
		return "HP";
	else if (index == 1)
		return "攻撃";
	else if (index == 2)
		return "防御";
	else if (index == 3)
		return "特攻";
	else if (index == 4)
		return "特防";
	else if (index == 5)
		return "素早さ";
	else if (index == 6)
		return "回避率";
	else if (index == 7)
		return "命中率";
}


void text_stat_at_max(std::string &name, int &stat) {
	std::cout << name << "の" << text_get_stat_name(stat) << "は　これ以上　あがらない！" << text_press_any_button() << std::endl;
	_getch();
}


void text_stat_at_min(std::string &name, int &stat) {
	std::cout << name << "の" << text_get_stat_name(stat) << "は　これ以上　さがらない！" << text_press_any_button() << std::endl;
	_getch();
}


void text_stat_change(std::string &name, int &stat, int &stage) {
	std::string change{};
	std::string potency{};

	if (stage > 0)
		change = "あがった";
	else
		change = "さがった";

	if (stage >= 2 || stage <= -2)
		potency = "がくっと";


	std::cout << name << "の" << text_get_stat_name(stat) << "が　" << potency << change << text_press_any_button() << std::endl;
	_getch();
}


std::string text_press_any_button() {
	return " ▽";
}