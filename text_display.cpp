#include <iostream>
#include <conio.h>
#include "text_display.h"



void text_enemy_sendout_pokemon(std::string &&trainer_name, std::string &&pok_name, const int &battle_type) {
	std::string battle_type_text{};
	if (battle_type == 1)
		battle_type_text = "����яo���Ă����I";
	else
		battle_type_text = "���������������Ă����I";

	std::cout << trainer_name << "��" << pok_name << battle_type_text << std::endl;
}


void text_escape_failure() {
	std::cout << "�������Ȃ������I" << " ��" << std::endl;
	_getch();
}


void text_escape_success() {
	std::cout << "���܂������؂ꂽ�I" << " ��" << std::endl;
	_getch();
}


std::string text_get_stat_name(int &index) {
	if (index == 0)
		return "HP";
	else if (index == 1)
		return "�U��";
	else if (index == 2)
		return "�h��";
	else if (index == 3)
		return "���U";
	else if (index == 4)
		return "���h";
	else if (index == 5)
		return "�f����";
	else if (index == 6)
		return "���";
	else if (index == 7)
		return "������";
}


void text_stat_at_max(std::string &name, int &stat) {
	std::cout << name << "��" << text_get_stat_name(stat) << "�́@����ȏ�@������Ȃ��I" << text_press_any_button() << std::endl;
	_getch();
}


void text_stat_at_min(std::string &name, int &stat) {
	std::cout << name << "��" << text_get_stat_name(stat) << "�́@����ȏ�@������Ȃ��I" << text_press_any_button() << std::endl;
	_getch();
}


void text_stat_change(std::string &name, int &stat, int &stage) {
	std::string change{};
	std::string potency{};

	if (stage > 0)
		change = "��������";
	else
		change = "��������";

	if (stage >= 2 || stage <= -2)
		potency = "��������";


	std::cout << name << "��" << text_get_stat_name(stat) << "���@" << potency << change << text_press_any_button() << std::endl;
	_getch();
}


std::string text_press_any_button() {
	return " ��";
}