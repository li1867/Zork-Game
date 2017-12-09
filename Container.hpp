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

#include "Trigger.hpp"


using namespace std;
using namespace rapidxml;

class Container{
public:
	string name;
	string status = "closed";
	vector<string> accept;
	vector<string> item;
	//vector<Item*> vecitem;
	vector<Trigger*> trigger;
	int item_count = 0;
	bool hasTrigger = false;
	bool acceptance = false;

	//Trigger * trigger = NULL;

	Container(xml_node<> *node)
	{
		cpy_container(node);
	}

	void cpy_container(xml_node<>* node)
	{
		for(xml_node<>* current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(strcmp(current -> name(), "name") == 0)
			{
				name = current -> value();
				//cout<< name<< endl;
			}
			if(strcmp(current -> name(), "status") == 0)
			{
				status = current -> value();
				//cout<< status<<endl;
			}
			if(strcmp(current -> name(), "accept") == 0)
			{
				accept.push_back(current->value());
			}
			if(strcmp(current -> name(), "item") == 0)
			{
				item.push_back(current->value());
				//vecitem.push_back(new Item(current));
				item_count++;
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
