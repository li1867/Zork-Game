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

class Turnon{
public:

	string print;
	string action;

	Turnon(xml_node<> *node)
	{
		cpy_turnon(node);
	}

	void cpy_turnon(xml_node <>* node)
	{
		for(xml_node<>* current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(strcmp(current -> name(), "print") == 0)
			{
				print = current -> value();
			}
			if(strcmp(current -> name(), "action") == 0)
			{
				action = current -> value();
			}
		}
	}
};



