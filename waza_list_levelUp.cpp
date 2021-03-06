#include "waza_list_levelUp.h"

// status: 0 = initialize wild pokemon moveset, 1 = check for learn new moves
void check_waza(const int &num, const int &lev, const int &status, std::vector<Waza> &current_moveset){
	std::multimap<int, std::string> moveset {};
	if(num == 1){
		moveset = {{
			{ 1, "たいあたり"},
			{ 3, "なきごえ"},
			{ 7, "やどりぎのタネ"},
			{10, "つるのむち"},
			{13, "どくのこな"},
			{13, "ねむりごな"}
			
		}};
	}
	else if(num == 4){
		moveset = {{
			{ 1, "ひっかく"},
			{ 3, "なきごえ"},
			{ 7, "ひのこ"},
			{10, "えんまく"},
			{16, "りゅうのいかり"},
			{19, "こわいかお"}
		}};
	}
	else if (num == 16) {
		moveset = { {
			{ 1, "たいあたり"},
			{ 5, "すなかけ"},
			{ 9, "かぜおこし"}
		} };
	}
	else if (num == 19) {
		moveset = { {
			{ 1, "たいあたり"},
			{ 1, "しっぽをふる"},
			{ 4, "でんこうせっか"},
			{ 7, "きあいだめ"}
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
	
	moveset.insert(std::make_pair(lev+1, "を"));
	it = moveset.find(lev+1);
	
	size_t counter{0};
	while(it != moveset.end() && counter < 4){
//		std::cout << "it->second: " << it->second << std::endl;
		it--;
		counter++;
	}
	
	if(it == moveset.end())
		it = moveset.begin();
	
	
	if(it->second == "を"){
		for(size_t j{0}; j < counter; j++){
			it--;
		}
	}
	
	
	size_t i{0};
	while(it != moveset.end() && counter > 0 && it->second != "を" && constructed_moveset.size() < 4){
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
				std::cout << "あたらしく　" << new_move << "　をおぼえた！" << std::endl;
			}
			else{
				bool done = false;
				std::string selection{};
				while(!done){
					std::cout << new_move << " をおぼえようとしている。" << std::endl;
					std::cout << "しかし、4つのわざを　すでにおぼえている。" << std::endl;
					std::cout << "わざを　わすれさせますか？" << std::endl;
					std::cout << "　１）わすれさせる" << std::endl;
					std::cout << "　２）おぼえるのをあきらめる" << std::endl;
					getline(std::cin, selection);
					while(selection != "１" && selection != "1" && selection != "２" && selection != "2"){
						getline(std::cin, selection);
					}
					
					if(selection == "１" || selection == "1"){
						std::cout << "わすれさせるわざを　えらんでください。" << std::endl;
						std::cout << "　１）" << current_moveset.at(0).get_waza_name() << std::endl;
						std::cout << "　２）" << current_moveset.at(1).get_waza_name() << std::endl;
						std::cout << "　３）" << current_moveset.at(2).get_waza_name() << std::endl;
						std::cout << "　４）" << current_moveset.at(3).get_waza_name() << std::endl;
						std::cout << std::endl;
						std::cout << "　５）あたらしいわざ：　" << new_move << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "１" && selection != "1" && selection != "２" && selection != "2" && selection != "３" && selection != "3" && selection != "４" && selection != "4" && selection != "５" && selection != "5"){
							getline(std::cin, selection);
						}
						
						int location {};
						if(selection == "１" || selection == "1")
							location = 0;
						else if(selection == "２" || selection == "2")
							location = 1;
						else if(selection == "３" || selection == "3")
							location = 2;
						else if(selection == "４" || selection == "4")
							location = 3;
						
						if(selection == "５" || selection == "5"){
							std::cout << new_move << "　をおぼえるのを　あきらめますか？" << std::endl;
							std::cout << "　１）はい" << std::endl;
							std::cout << "　２）いいえ" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "１" && selection != "1" && selection != "２" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "１" || selection == "1"){
								std::cout << new_move << "　をおぼえずにおわった。" << std::endl;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
						else{
							std::cout << current_moveset.at(location).get_waza_name() << "　をわすれますが、よろしいですか？" << std::endl;
							std::cout << "　１）はい" << std::endl;
							std::cout << "　２）いいえ" << std::endl;
							selection = "";
							getline(std::cin, selection);
							while(selection != "１" && selection != "1" && selection != "２" && selection != "2"){
								getline(std::cin, selection);
							}
							if(selection == "１" || selection == "1"){
								std::cout << "１、２…ポカン！" << std::endl;
								std::cout << current_moveset.at(location).get_waza_name() << "　をすっかりわすれました。" << std::endl;
								std::cout << "そして、あたらしく　" << new_move << "をおぼえました！" << std::endl;
								current_moveset.at(location) = new_move;
								done = true;
							}
							else{
								done = false; // ask again
							}
						}
					}
					else{
						std::cout << new_move << "　をおぼえるのを　あきらめますか？" << std::endl;
						std::cout << "　１）はい" << std::endl;
						std::cout << "　２）いいえ" << std::endl;
						selection = "";
						getline(std::cin, selection);
						while(selection != "１" && selection != "1" && selection != "２" && selection != "2"){
							getline(std::cin, selection);
						}
						if(selection == "１" || selection == "1"){
							std::cout << new_move << "　をおぼえずにおわった。" << std::endl;
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
