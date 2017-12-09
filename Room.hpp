#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <string.h>
#include <list>
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

#include "Border.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "Trigger.hpp"

using namespace std;
using namespace rapidxml;

class Room {
public:

	string type;
	string description;
	string status;
	string name;
	string direction;
	string room_name;
	int item_count = 0;  //count how many item in each room, this variable will be use in list item
	int container_count = 0;
	vector<Border*> border;
	vector<string> item;
	//vector<Item*> itemsvec;
	//vector<Container*> container;
	vector<string> container_name;
	vector<string> creature_name;
	//vector<Creature*> creature;
	//Trigger * trigger = NULL;
	vector<Trigger*> trigger;
	bool hasTrigger = false;
	int creaturecnt = 0;



	Room(xml_node<> *node)
	{
		cpy_room(node);
	}

	virtual ~Room()
	{
	}

	void cpy_room(xml_node<> *node)
	{
		//int x = 1000;
		for(xml_node<> *current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(strcmp(current -> name(), "description") == 0)
			{
				description = current -> value();
			}
			else if(strcmp(current -> name(), "name") == 0)
			{
				name = current -> value();
			}
			else if(strcmp(current -> name(), "statue") == 0)
			{
				status = current -> value();
			}
			else if(string(current -> name()) == (string)"type")
			{
				type = current -> value();
			}
			if(strcmp(current -> name(), "border") == 0)
			{
				int i = 0;
				for(xml_node<>* border_temp = current -> first_node(); border_temp != NULL; border_temp = border_temp -> next_sibling())
				{

					if(strcmp(border_temp -> name(), "name") == 0)
					{
						room_name = border_temp -> value();
					}
					if(strcmp(border_temp -> name(), "direction") == 0)
					{
						if((string)(border_temp -> value()) == "north")
						{
							direction = "n";
						}
						if((string)(border_temp -> value())  == "south")
						{
							direction = "s";
						}
						if((string)(border_temp -> value())  == "west")
						{
							direction = "w";
						}
						if((string)(border_temp -> value())  == "east")
						{
							direction = "e";
						}
					}
					i++;
				}
				border.push_back(new Border(direction, room_name));
			}
			if(strcmp(current -> name(), "item") == 0)
			{
				item_count++;
				item.push_back(current -> value());
				//cout<<name<<current->value()<<endl;
				//itemsvec.push_back(new Item(current));
			}
			if(strcmp(current -> name(), "container") == 0)
			{
				//container.push_back(new Container(node));
				//cout<< container[0]->name<<endl;
				container_name.push_back(current->value());
				container_count++;
			}
			if(strcmp(current -> name(), "creature") == 0)
			{
				//creature.push_back(new Creature(node));
				creature_name.push_back(current->value());
				creaturecnt++;
			}
			if(strcmp(current -> name(), "trigger") == 0)
			{
				//trigger = new Trigger(current);
				hasTrigger = true;
				trigger.push_back(new Trigger(current));
			}
		}
	}
};
