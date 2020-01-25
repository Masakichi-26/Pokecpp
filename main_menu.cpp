#include<string>
#include <conio.h>
#include "main_menu.h"
#include "selection_manipulation.h"


void call_main_menu(Trainer& tnr) {
	bool tojiru = false;
	bool show_menu = true;
	std::string sel{};
	do {
		if (show_menu) {
			std::cout << std::endl;
			std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
			std::cout << "| ���C�����j���[ |" << std::endl;
			std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
			std::cout << std::endl;

			std::cout << "�@1�j������" << std::endl;
			std::cout << "�@2�j�|�P����" << std::endl;
			std::cout << "�@3�j�o�b�O" << std::endl;
			std::cout << "�@4�j�g���[�i" << std::endl;
			std::cout << "�@5�j�ݒ�" << std::endl;
			std::cout << "�@6�j���|�[�g" << std::endl;
			std::cout << "�@7�j�Ƃ���" << std::endl;
			std::cout << std::endl;
			show_menu = false;
		}

		std::cin >> sel;
		std::transform(sel.begin(), sel.end(), sel.begin(), ::toupper);
		if (sel == "��" || sel == "B" || sel == "7") {
			tojiru = true;
		}
		else if (sel == "��" || sel == "P" || sel == "2") {
			call_pokemon_menu(tnr);
			show_menu = true;
		}

	} while (!tojiru);

}


void call_pokemon_menu(Trainer& tnr) {
	bool tojiru = false;
	bool show_menu = true;
	bool show_irekaeru = false;
	std::string sel{};
	int party_size = tnr.get_current_party().size();

	do {
		if (show_menu){
			std::cout << std::endl;
			std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
			std::cout << "|  �|�P�����ꗗ  |" << std::endl;
			std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
			tnr.display_party_current();
			std::cout << std::endl;
			if (party_size > 1) {
				std::cout << "I�j����ւ���" << std::endl;
				show_irekaeru = true;
			}
			std::cout << "B�j�Ƃ���" << std::endl;
			show_menu = false;
		}


		std::cin >> sel;
		std::transform(sel.begin(), sel.end(), sel.begin(), ::toupper);
		if (sel == "��" || sel == "B") {
			tojiru = true;
		}
		else if (show_irekaeru && (sel == "i" || sel == "I")) {
			std::string first{};
			std::string second{};

			std::cout << "����ւ���|�P�����̔ԍ�����͂��Ă�������" << "�i1�`" << party_size << "�j" << std::endl;
			std::cout << "�@1�Ԗڂ̔ԍ��F";
			std::cin >> first;
			std::cout << "�@2�Ԗڂ̔ԍ��F";
			std::cin >> second;

			int first_el = selection_to_element(first, party_size);
			int second_el = selection_to_element(second, party_size);

			if (first_el != -1 && second_el != -1 && first_el != second_el) {
				tnr.switch_pokemon(first_el, second_el);
			}
			else
				std::cout << "����ւ��邱�Ƃ��ł��܂���ł����B" << std::endl;
			
			show_menu = true;
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

			if(element != -1 && tnr.get_current_pokemon(element).get_info_constants().at(0) != 0){
				call_pokemon_status_menu(tnr.get_current_pokemon(element));
				show_menu = true;
			}

		}

	} while (!tojiru);
}


void call_pokemon_status_menu(Pokemon& pok) {
	std::cout << std::endl;
	std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
	std::cout << "|  �|�P�����\��  |" << std::endl;
	std::cout << "�\�\�\�\�\�\�\�\�\" << std::endl;
	std::cout << std::endl;
	pok.display_status_menu();
	std::cout << std::endl;
	std::cout << "1�j�Ƃ��� (B)" << std::endl;
	std::cout << std::endl;

	_getch();
}