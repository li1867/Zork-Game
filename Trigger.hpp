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
#include "Status.hpp"
#include "Owner.hpp"


using namespace std;
using namespace rapidxml;


class Trigger{

public:
	/*

	struct conditionstruct {
		string condition_object;
		string status;
		string owner;
		string has;
		bool hasStatus;
		bool hasOwner;
	}Cond;
	string type;
	string print;
	string command;
	bool hasCommand = false;
	bool hasAction = false;
	bool single = false;
	int condition_count = 0;
	vector<conditionstruct*> conditionlist;
	vector<string> action;

	Trigger(){};

	Trigger(xml_node<> *node)
	{
		cpy_trigger(node);
	}
	virtual ~Trigger(){};

private:

	void cpy_trigger(xml_node<> *node)
	{
		for(xml_node<> *current = node -> first_node(); current != NULL; current = current -> next_sibling())
		{
			if(string(current -> name()) == (string)"type")
			{
				type = current -> value();
				if(type == "single")
				{
					single = true;
				}
			}
			if(string(current -> name()) == (string)"print")
			{
				print = current -> value();

			}
			if(string(current -> name()) == (string)"command")
			{
				command = current -> value();
				hasCommand = true;
			}
			if(string(current -> name()) == (string)"action")
			{
				hasAction = true;
				string temp = current -> value();
				action.push_back(temp);
			}
			if(string(current -> name()) == (string)"condition")
			{
				conditionstruct *temp;
				Condition(current);
				conditionlist.push_back(temp);
			}
		}
		return;
	}



	void Condition(xml_node<> * node)//, conditionstruct * temp)
	{
		//conditionstruct temp;
		//int x = 300;

		xml_node<> * childNode = node -> first_node();
		while(childNode != NULL)
		{
			//cout<<x << childNode -> name() <<"\n";
			if(string(childNode -> name()) == (string)"object")
			{
				//condition_count++;
				//cout<<"pls maybe?\n";
				setOwner(node -> first_node());//,temp);
				return;
			}
			if(string(childNode -> name()) == (string)"status")
			{
				//condition_cou
				//cout<<"why not maybe?\n";
				setStatus(node -> first_node());//,temp);
				return;
			}
			childNode = childNode -> next_sibling();
			//x++;
		}
		return;
	}


	void setStatus(xml_node<> *node)//, conditionstruct * cond)
	{
		//int x = 400;
		Cond.hasStatus = true;
		//cout<<"notmaybe?\n";
		Cond.hasOwner = false;
		//cout<<"maybe?\n";
		while(node != NULL)
		{
			//cout<<x<<"\n";
			if(string(node -> name()) == (string)"object")
			{
				//cout<<"hwere\n";
				Cond.condition_object = node -> value();
			}
			if(string(node -> name()) == (string)"status")
			{
				//cout<<"nothere\n";
				Cond.status = node -> value();
			}
			node = node -> next_sibling();
			//x++;
		}
		Cond.owner = "";
		return;
	}
	void setOwner(xml_node<> *node)//, conditionstruct * cond)
	{
		//int x = 500;
		Cond.hasStatus = false;
		Cond.hasOwner = true;
		while(node != NULL)
		{
			//cout<<x<<"\n";
			if(string(node -> name()) == (string)"has")
			{
				Cond.has = node -> value();
			}
			if(string(node -> name()) == (string)"object")
			{
				Cond.condition_object = node -> value();
			}
			if(string(node -> name()) == (string)"owner")
			{
				Cond.owner = node -> value();
			}
			node = node -> next_sibling();
			//x++;
		}
		Cond.status = "";
		return;
	}
*/

	string type;// = "single";// = "permanent";
	string command;
	vector<string> print;
	vector<string> action;
	string has;
	string object;
	string status;
	string owner;
	bool single = true;
	bool hasOwner = false;
	bool hasStatus = false;

	Trigger(xml_node<> *node)
	{
		cpy_trigger(node);
	}

	void cpy_trigger(xml_node<>* node)
	{
		//type = "single";
		for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling())
		{
					if (string(curr->name()) == "type") {
						type = curr->value();
						/*
						if(type == "single")
						{
							single = true;
						}*/
					}
					if (string(curr->name()) == "command") {
						command = curr->value();
					}
					if (string(curr->name()) == "action") {
						action.push_back(curr->value());
					}
					if (string(curr->name()) == "print") {
						print.push_back(curr->value());
					}
					if (string(curr->name()) == "condition")
					{
						for(xml_node<>* temp = curr->first_node();temp; temp = temp->next_sibling())
						{
						if(strcmp(temp->name(), "has") == 0)
						{
							has = temp->value();
						}
						if(strcmp(temp->name(), "object") == 0)
						{
								object = temp->value();
						}
						if(strcmp(temp->name(), "status") == 0)
						{
							status = temp->value();
							hasStatus = true;
						}
						if(strcmp(temp->name(), "owner") == 0)
						{
							owner = temp->value();
							hasOwner = true;
						}
						}

					}



			}
	}
/*
	int next_sibling_count(xml_node<>* node)
	{
		int count = 0;
		for(xml_node<>* cur = node->first_node(); cur != NULL; cur = cur->next_sibling())
		{
			count++;
		}
		return count;
	}*/

};


