#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"


using namespace std;
using namespace rapidxml;

class Object{
public:
	xml_node<> * name;
	Object * owner;
	string status;

	Object(xml_node<> * root)
	{

		name = NULL;
		status = string();
		owner = NULL;
		xml_node<> * node = root->first_node();
		while(node !=NULL)
		{
			string nodeName(node->name());
			if(nodeName.compare("name") == 0)
			{
				name = node;
			}
			if(nodeName.compare("status") == 0)
			{
				status = string(node -> value());
			}
			node = node->next_sibling();
		}
	}

	virtual ~Object()
	{
	}
};
