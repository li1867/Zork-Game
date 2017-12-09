#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <list>

#include "Game_map.hpp"
#include "Game.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

int main(int argc, char *argv[]) {
	file<> xml(argv[1]);
	xml_document<> doc;
	doc.parse<0>(xml.data());
	xml_node<> * node = doc.first_node();
	xml_node<> * top = node;
	Map *map = new Map(top);
	Game *game = new Game(map);
	string input;
	string empty = "";

	//cout<<"1"<<endl;
	cout << game->room->description << endl;
	//cout<<"1"<<endl;
	//int x = 0;
	bool trigger_check = false;
	//bool trigger_check2 = false;
	while (true) {
		if(game->game_over == true)
		{
			break;
		}
		//cout<<"001"<<endl;
		trigger_check = game->check_trigger(empty);

		//cout<<"002"<<endl;
		if (trigger_check == true) {
			//x++;
			//if(x>5){break;}
			continue;
		}

		//cout<<"003"<<endl;
		getline(cin, input);
		trigger_check = game->check_trigger(input);

		//cout<<"004"<<endl;
		if (trigger_check == true) {
			continue;
		}
		game->input_check(input);

	}
	return 0;
}

