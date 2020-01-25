#include "waza_list_levelUp.h"

// status: 0 = initialize wild pokemon moveset, 1 = check for learn new moves
void check_waza(const int &num, const int &lev, const int &status, std::vector<Waza> &current_moveset){
	std::multimap<int, std::string> moveset {};
	if(num == 1){
		moveset = {{
			{ 1, "����������"},
			{ 3, "�Ȃ�����"},
			{ 7, "��ǂ肬�̃^�l"},
			{10, "��̂ނ�"},
			{13, "�ǂ��̂���"},
			{13, "�˂ނ育��"}
			
		}};
	}
	else if(num == 4){
		moveset = {{
			{ 1, "�Ђ�����"},
			{ 3, "�Ȃ�����"},
			{ 7, "�Ђ̂�"},
			{10, "����܂�"},
			{16, "��イ�̂�����"},
			{19, "���킢����"}
		}};
	}
	else if (num == 16) {
		moveset = { {
			{ 1, "����������"},
			{ 5, "���Ȃ���"},
			{ 9, "����������"}
		} };
	}
	else if (num == 19) {
		moveset = { {
			{ 1, "����������"},
			{ 1, "�����ۂ��ӂ�"},
			{ 4, "�ł񂱂�������"},
			{ 7, "����������"}
		} };
	}
	
	
	auto it = moveset.find(lev);
	int count = moveset.count(lev);
	
	if(status == 0){
		current_moveset = init_waza(moveset, lev);
		
	}
	else if (status == 1){
		bool done = false;
		while (!done) {
			if (it != moveset.end()) {
				if (it->first == lev) {
					learn_new_waza(moveset, it->second, lev, current_moveset); // replace moveset with the move name
					it++;
				}
				else
					done = true;
			}
			else
				done = true;
		}
	}
	
}


// initialize moveset for wild pokemon
std::vector<Waza> init_waza(std::multimap<int, std::string> &moveset, const int &lev){
	std::vector<Waza> constructed_moveset{};
	auto it = moveset.find(lev+1);
	if(it != moveset.end())
		moveset.erase(it);
	
	moveset.insert(std::make_pair(lev+1, "��"));
	it = moveset.find(lev+1);
	
	size_t counter{0};
	while(it != moveset.end() && counter < 4){
//		std::cout << "it->second: " << it->second << std::endl;
		it--;
		counter++;
	}
	
	if(it == moveset.end())
		it = moveset.begin();
	
	
	if(it->second == "��"){
		for(size_t j{0}; j < counter; j++){
			it--;
		}
	}
	
	
	size_t i{0};
	while(it != moveset.end() && counter > 0 && it->second != "��" && constructed_moveset.size() < 4){
//		constructed_moveset.at(i) = it->second;
		constructed_moveset.emplace_back(it->second);
		it++;
		i++;
		counter--;
	}
	
//	while(i < 4){
//		constructed_moveset.at(i) = {"-----"};
//		i++;
//	}
	
	return constructed_moveset;
}


void learn_new_waza(std::multimap<int, std::string> &moveset, std::string &new_move, const int &lev, std::vector<Waza> &current_moveset){
	auto it = moveset.find(lev);
	if(it != moveset.end()){
		std::cout << "Found new waza" << std::endl;
		bool waza_already_have = false;
		size_t i {0};
		int first_no_move_location {-1};
//		std::string new_move = it->second;

		for(auto w : current_moveset){
			if(w.get_waza_name() == new_move){
				waza_already_have = true;
			}
//			else if(w.get_waza_name() == "-----" && first_no_move_location == -1){
//				first_no_move_location = i;
//				std::cout << "first no move found at " << first_no_move_location << std::endl;
//			}
			i++;
		}

		if (current_moveset.size() < 4 && i < 4) {
			first_no_move_location = i;
			std::cout << "first no move found at " << first_no_move_location << std::endl;
		}
		
		if(!waza_already_have){
			if(first_no_move_location >= 0 && first_no_move_location <= 3){
//				current_moveset.at(first_no_move_location) = new_move;
				current_moveset.emplace_back(new_move);
				std::cout << "�����炵���@" << new_move << "�@�����ڂ����I" << std::endl;
			}
			else{
				bool done = false;
				std::string selection{};
				while(!done){
					std::cout << new_move << " �����ڂ��悤�Ƃ��Ă���B" << std::endl;
					std::cout << "�������A4�̂킴���@���łɂ��ڂ��Ă���B" << std::endl;
					std::cout << "�킴���@�킷�ꂳ���܂����H" << std::endl;
					std::cout << "�@�P�j�킷�ꂳ����" << std::endl;
					std::cout << "�@�Q�j���ڂ���̂�������߂�" << std::endl;
					getline(std::cin, selection);
					while(selection != "�P" && selection != "1" && selection != "�Q" && selection != "2"){
						getline(std::cin, selection);
					}
					
					if(selection == "�P" || selection == "1"){
						std::cout << "�킷�ꂳ����킴���@�����ł��������B" << std::endl;
						std::cout << "�@�P�j" << current_moveset.at(0).get_waza_name() << std::endl;
						std::cout << "�@�Q�j" << current_moveset.at(1).get_waza_name() << std::endl;
						std::cout << "�@�R�j" << current_moveset.at(2).get_waza_name() << std::endl;
						std::cout << "�@�S�j" << current_moveset.at(3).get_waza_name() << std::endl;
						std::cout << std::endl;
						std::cout << "�@�T�j�����炵���킴�F�@" << new_move << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "�P" && selection != "1" && selection != "�Q" && selection != "2" && selection != "�R" && selection != "3" && selection != "�S" && selection != "4" && selection != "�T" && selection != "5"){
							getline(std::cin, selection);
						}
						
						int location {};
						if(selection == "�P" || selection == "1")
							location = 0;
						else if(selection == "�Q" || selection == "2")
							location = 1;
						else if(selection == "�R" || selection == "3")
							location = 2;
						else if(selection == "�S" || selection == "4")
							location = 3;
						
						if(selection == "�T" || selection == "5"){
							std::cout << new_move << "�@�����ڂ���̂��@������߂܂����H" << std::endl;
							std::cout << "�@�P�j�͂�" << std::endl;
							std::cout << "�@�Q�j������" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "�P" && selection != "1" && selection != "�Q" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "�P" || selection == "1"){
								std::cout << new_move << "�@�����ڂ����ɂ�������B" << std::endl;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
						else{
							std::cout << current_moveset.at(location).get_waza_name() << "�@���킷��܂����A��낵���ł����H" << std::endl;
							std::cout << "�@�P�j�͂�" << std::endl;
							std::cout << "�@�Q�j������" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "�P" && selection != "1" && selection != "�Q" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "�P" || selection == "1"){
								std::cout << "�P�A�Q�c�|�J���I" << std::endl;
								std::cout << current_moveset.at(location).get_waza_name() << "�@����������킷��܂����B" << std::endl;
								std::cout << "�����āA�����炵���@" << new_move << "�����ڂ��܂����I" << std::endl;
								current_moveset.at(location) = new_move;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
					}
					else{
						std::cout << new_move << "�@�����ڂ���̂��@������߂܂����H" << std::endl;
						std::cout << "�@�P�j�͂�" << std::endl;
						std::cout << "�@�Q�j������" << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "�P" && selection != "1" && selection != "�Q" && selection != "2"){
							getline(std::cin, selection);
						}
						if(selection == "�P" || selection == "1"){
							std::cout << new_move << "�@�����ڂ����ɂ�������B" << std::endl;
							done = true;
						}
						else{
							done = false; // ask again
						}
					}
				}
			}
		}
	}
}
