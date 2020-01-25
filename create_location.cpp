#include <map>
#include "create_location.h"


std::array<int, 3> init_location_info(std::string & name) {
	std::map<std::string, std::array<int, 3>> location_list{ {
		{"�}�T���^�E��",		{  0,  0,  0}},
		{"�P�ԓ��H",			{  3,  3,  0}},
		{"�g�L���V�e�B",		{  0,  0,  0}},
	} };

	auto it = location_list.find(name);
	if (it != location_list.end())
		return it->second;
	else
		return { 0, 0, 0 };
}


std::vector<std::string> init_options_info(std::string& name) {
	std::map<std::string, std::vector<std::string>> options_list{ {
		{"�}�T���^�E��",		{{"�P�ԓ��H�Ɉړ�����"}}},
		{"�P�ԓ��H",			{{"�O�֐i��"},
								{"pr�֖߂�"}}},
		{"�g�L���V�e�B",		{{"�P�ԓ��H�Ɉړ�����"}}}
	} };

	auto it = options_list.find(name);
	if (it != options_list.end())
		return it->second;
	else
		return {"�����ł��Ȃ�"};
}
