#include "waza_list_levelUp.h"

// status: 0 = initialize wild pokemon moveset, 1 = check for learn new moves
void check_waza(const int &num, const int &lev, const int &status, std::vector<Waza> &current_moveset){
	std::multimap<int, std::string> moveset {};
	if(num == 1){
		moveset = {{
			{ 1, "‚½‚¢‚ ‚½‚è"},
			{ 3, "‚È‚«‚²‚¦"},
			{ 7, "‚â‚Ç‚è‚¬‚Ìƒ^ƒl"},
			{10, "‚Â‚é‚Ì‚Þ‚¿"},
			{13, "‚Ç‚­‚Ì‚±‚È"},
			{13, "‚Ë‚Þ‚è‚²‚È"}
			
		}};
	}
	else if(num == 4){
		moveset = {{
			{ 1, "‚Ð‚Á‚©‚­"},
			{ 3, "‚È‚«‚²‚¦"},
			{ 7, "‚Ð‚Ì‚±"},
			{10, "‚¦‚ñ‚Ü‚­"},
			{16, "‚è‚ã‚¤‚Ì‚¢‚©‚è"},
			{19, "‚±‚í‚¢‚©‚¨"}
		}};
	}
	else if (num == 16) {
		moveset = { {
			{ 1, "‚½‚¢‚ ‚½‚è"},
			{ 5, "‚·‚È‚©‚¯"},
			{ 9, "‚©‚º‚¨‚±‚µ"}
		} };
	}
	else if (num == 19) {
		moveset = { {
			{ 1, "‚½‚¢‚ ‚½‚è"},
			{ 1, "‚µ‚Á‚Û‚ð‚Ó‚é"},
			{ 4, "‚Å‚ñ‚±‚¤‚¹‚Á‚©"},
			{ 7, "‚«‚ ‚¢‚¾‚ß"}
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
	
	moveset.insert(std::make_pair(lev+1, "‚ð"));
	it = moveset.find(lev+1);
	
	size_t counter{0};
	while(it != moveset.end() && counter < 4){
//		std::cout << "it->second: " << it->second << std::endl;
		it--;
		counter++;
	}
	
	if(it == moveset.end())
		it = moveset.begin();
	
	
	if(it->second == "‚ð"){
		for(size_t j{0}; j < counter; j++){
			it--;
		}
	}
	
	
	size_t i{0};
	while(it != moveset.end() && counter > 0 && it->second != "‚ð" && constructed_moveset.size() < 4){
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
				std::cout << "‚ ‚½‚ç‚µ‚­@" << new_move << "@‚ð‚¨‚Ú‚¦‚½I" << std::endl;
			}
			else{
				bool done = false;
				std::string selection{};
				while(!done){
					std::cout << new_move << " ‚ð‚¨‚Ú‚¦‚æ‚¤‚Æ‚µ‚Ä‚¢‚éB" << std::endl;
					std::cout << "‚µ‚©‚µA4‚Â‚Ì‚í‚´‚ð@‚·‚Å‚É‚¨‚Ú‚¦‚Ä‚¢‚éB" << std::endl;
					std::cout << "‚í‚´‚ð@‚í‚·‚ê‚³‚¹‚Ü‚·‚©H" << std::endl;
					std::cout << "@‚Pj‚í‚·‚ê‚³‚¹‚é" << std::endl;
					std::cout << "@‚Qj‚¨‚Ú‚¦‚é‚Ì‚ð‚ ‚«‚ç‚ß‚é" << std::endl;
					getline(std::cin, selection);
					while(selection != "‚P" && selection != "1" && selection != "‚Q" && selection != "2"){
						getline(std::cin, selection);
					}
					
					if(selection == "‚P" || selection == "1"){
						std::cout << "‚í‚·‚ê‚³‚¹‚é‚í‚´‚ð@‚¦‚ç‚ñ‚Å‚­‚¾‚³‚¢B" << std::endl;
						std::cout << "@‚Pj" << current_moveset.at(0).get_waza_name() << std::endl;
						std::cout << "@‚Qj" << current_moveset.at(1).get_waza_name() << std::endl;
						std::cout << "@‚Rj" << current_moveset.at(2).get_waza_name() << std::endl;
						std::cout << "@‚Sj" << current_moveset.at(3).get_waza_name() << std::endl;
						std::cout << std::endl;
						std::cout << "@‚Tj‚ ‚½‚ç‚µ‚¢‚í‚´F@" << new_move << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "‚P" && selection != "1" && selection != "‚Q" && selection != "2" && selection != "‚R" && selection != "3" && selection != "‚S" && selection != "4" && selection != "‚T" && selection != "5"){
							getline(std::cin, selection);
						}
						
						int location {};
						if(selection == "‚P" || selection == "1")
							location = 0;
						else if(selection == "‚Q" || selection == "2")
							location = 1;
						else if(selection == "‚R" || selection == "3")
							location = 2;
						else if(selection == "‚S" || selection == "4")
							location = 3;
						
						if(selection == "‚T" || selection == "5"){
							std::cout << new_move << "@‚ð‚¨‚Ú‚¦‚é‚Ì‚ð@‚ ‚«‚ç‚ß‚Ü‚·‚©H" << std::endl;
							std::cout << "@‚Pj‚Í‚¢" << std::endl;
							std::cout << "@‚Qj‚¢‚¢‚¦" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "‚P" && selection != "1" && selection != "‚Q" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "‚P" || selection == "1"){
								std::cout << new_move << "@‚ð‚¨‚Ú‚¦‚¸‚É‚¨‚í‚Á‚½B" << std::endl;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
						else{
							std::cout << current_moveset.at(location).get_waza_name() << "@‚ð‚í‚·‚ê‚Ü‚·‚ªA‚æ‚ë‚µ‚¢‚Å‚·‚©H" << std::endl;
							std::cout << "@‚Pj‚Í‚¢" << std::endl;
							std::cout << "@‚Qj‚¢‚¢‚¦" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "‚P" && selection != "1" && selection != "‚Q" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "‚P" || selection == "1"){
								std::cout << "‚PA‚Qcƒ|ƒJƒ“I" << std::endl;
								std::cout << current_moveset.at(location).get_waza_name() << "@‚ð‚·‚Á‚©‚è‚í‚·‚ê‚Ü‚µ‚½B" << std::endl;
								std::cout << "‚»‚µ‚ÄA‚ ‚½‚ç‚µ‚­@" << new_move << "‚ð‚¨‚Ú‚¦‚Ü‚µ‚½I" << std::endl;
								current_moveset.at(location) = new_move;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
					}
					else{
						std::cout << new_move << "@‚ð‚¨‚Ú‚¦‚é‚Ì‚ð@‚ ‚«‚ç‚ß‚Ü‚·‚©H" << std::endl;
						std::cout << "@‚Pj‚Í‚¢" << std::endl;
						std::cout << "@‚Qj‚¢‚¢‚¦" << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "‚P" && selection != "1" && selection != "‚Q" && selection != "2"){
							getline(std::cin, selection);
						}
						if(selection == "‚P" || selection == "1"){
							std::cout << new_move << "@‚ð‚¨‚Ú‚¦‚¸‚É‚¨‚í‚Á‚½B" << std::endl;
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
