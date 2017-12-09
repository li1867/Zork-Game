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

#include "Turnon.hpp"
#include "Trigger.hpp"

using namespace std;
using namespace rapidxml;

class Item{
public:
	string writing;
	string name;
	string status;
	vector<Trigger*> trigger;
	Turnon* turnon = NULL;
	bool hasTrigger = false;
	//Trigger * trigger = NULL;

	Item(xml_node<> *node)
	{
		cpy_item(node);
	}

	void cpy_item(xml_node <>* node)
	{
		for(xml_node<>* current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(strcmp(current -> name(), "writing") == 0)
			{
				writing = current -> value();
			}
			if(strcmp(current -> name(), "name") == 0)
			{
				name = current -> value();
			}
			if(strcmp(current -> name(), "status") == 0)
			{
				status = current -> value();
			}
			if(strcmp(current -> name(), "turnon") == 0)
			{
				turnon = new Turnon(current);
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
