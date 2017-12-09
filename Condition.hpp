/*#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <string.h>
#include <list>
#include "Trigger.hpp"

class Condition : public Trigger{

public:

	Condition(xml_node<> * node, conditionstruct * temp)
	{
		//conditionstruct temp;
		xml_node<> * childNode = node -> first_node();
		while(childNode != NULL)
		{
			if(string(childNode -> name()) == (string)"object")
			{
				setOwner(node -> first_node(),temp);
			}
			if(string(childNode -> name()) == (string)"status")
			{
				setStatus(node -> first_node(),temp);
			}
		}
		childNode = childNode -> next_sibling();

		return;
	}


	void setStatus(xml_node<> *node, conditionstruct * cond)
	{
		cond->hasStatus = true;
		cond->hasOwner = false;
		while(node != NULL)
		{
			if(string(node -> name()) == (string)"object")
			{
				cond->condition_object = node -> value();
			}
			if(string(node -> name()) == (string)"status")
			{
				cond->status = node -> value();
			}
			node = node -> next_sibling();
		}
		cond->owner = "";
	}
	void setOwner(xml_node<> *node, conditionstruct * cond)
	{
		cond->hasStatus = false;
		cond->hasOwner = true;
		while(node != NULL)
		{
			if(string(node -> name()) == (string)"has")
			{
				cond->has = node -> value();
			}
			if(string(node -> name()) == (string)"object")
			{
				cond->condition_object = node -> value();
			}
			if(string(node -> name()) == (string)"owner")
			{
				cond->owner = node -> value();
			}
			node = node -> next_sibling();
		}
		cond->status = "";
	}
};*/
