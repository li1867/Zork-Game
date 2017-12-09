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
#include "Attack.hpp"

using namespace std;
using namespace rapidxml;

class Creature{						//: public Object{
public:
	string name;
	vector<string> vulnerability;
	string status;
	string description;

	vector<Trigger*> trigger;
	bool hasTrigger = false;
	Attack * attack = NULL;
	//Trigger * trigger = NULL;


	Creature(xml_node<> *node)//:Object(node)
	{
		cpy_creature(node);
	}

	void cpy_creature(xml_node<> *node)
	{
		for(xml_node<> *current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(strcmp(current -> name(), "name") == 0)
			{
				name = current -> value();
			}
			if(strcmp(current -> name(), "vulnerability") == 0)
			{
				vulnerability.push_back(current -> value());
			}
			if(strcmp(current -> name(), "attack") == 0)
			{
				attack = new Attack(current);
			}
			if(strcmp(current -> name(), "trigger") == 0)
			{
				trigger.push_back(new Trigger(current));
				hasTrigger = true;
				//trigger = new Trigger(current);
			}
		}

	}


private:

};
