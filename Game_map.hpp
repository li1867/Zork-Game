#pragma once
#include "rapidxml_print.hpp"
#include <stdio.h>
#include <map>
#include <list>
#include <string>

#include "Room.hpp"
#include "Container.hpp"
#include "Item.hpp"

using namespace std;
using namespace rapidxml;

class Map
{
public:
	map<string,Room*> room_list;
	vector<Container*> container_list;
	vector<Item*> item_list;
	vector<Creature*> creature_list;

	int item_ct = 0;

	Map(xml_node<>* root)
	{
		xml_node<> * node = root->first_node();
		int i = 0;

		while(node != NULL)
		{
			string nodeName(node->name());
			if(nodeName.compare("room") == 0)
			{
				Room* room = new Room(node);
				room_list[room->name] = room;
				i++;
			}

			if(nodeName.compare("container") == 0)
			{
				container_list.push_back(new Container(node));
			}

			if(nodeName.compare("item") == 0)
			{
				item_list.push_back(new Item(node));
				item_ct++;
			}
			if(nodeName.compare("creature") == 0)
			{
				creature_list.push_back(new Creature(node));
			}


			node = node -> next_sibling();
		}
	}
};
