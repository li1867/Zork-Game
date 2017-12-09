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


using namespace std;
using namespace rapidxml;

class Attack{
public:
	string print;
	vector<string> action;
	struct condition {
		string object;
		string status;
	}cond;
	bool hasAction = false;
	bool hasPrint = false;
	bool hasCondition = false;

	Attack(){};

	Attack(xml_node<> *node)
	{
		//xml_node<>* temp = node;
		cpy_Attack(node);
	}

	void cpy_Attack(xml_node<> *node)
	{
		for(xml_node<> *current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(string(current -> name()) == (string)"print")
			{
				hasPrint = true;
				print = current -> value();
			}
			if(string(current -> name()) == (string)"condition")
			{
				hasCondition = true;
				xml_node<>* child = current -> first_node();
				while(child != NULL)
				{
					if(string(child -> name()) == (string)"object")
					{
						cond.object = child-> value();
					}
					if(string(child -> name()) == (string)"status")
					{
						cond.status = child-> value();
					}
					child = child -> next_sibling();
				}
			}
			if(string(current -> name()) == (string)"action")
			{
				hasAction = true;
				string temp = current -> value();
				action.push_back(temp);
			}
		}
	}

};




