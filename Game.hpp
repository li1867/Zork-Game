#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <string>
#include <list>
#include <algorithm>
#include "Room.hpp"
#include "Item.hpp"
#include "Container.hpp"

using namespace std;
using namespace rapidxml;

class Game {
public:
	Map* map;
	Room* room;
	bool game_over;
	string took;

	vector<string> inventory;

	Game(Map* input_map) {
		map = input_map;
		room = map->room_list["Entrance"];
		game_over = false;
	}

	void input_check(string input) {

		if (input == "n" || input == "w" || input == "e" || input == "s") {
			next_room(input);
			return;
		} else if (input == "look") {
			check_room();
		} else if (input == "i") {
			getInventory();
		} else if (input == "take") {
			take_item(input);
		} else if (input.find("take") != string::npos) {

			take_item(input.erase(0, 5));
		} else if (input == "open") {
			open_container(input);
		} else if (input.find("open") != string::npos) {
			open_container(input.erase(0, 5));
		} else if (input.find("drop") != string::npos) {
			drop(input.erase(0, 5));
		} else if (input.find("read") != string::npos) {
			read(input.erase(0, 5));
		} else if (input.find("turn on") != string::npos) {
			turnon(input.erase(0, 8));
		} else if (input.find("put") != string::npos) {
			string target;  //item need to put to
			string source;  //item need to put
			input = input.erase(0, 4);
			int target_count = input.find(" ");
			source = input.substr(0, target_count);
			input.erase(0, target_count + 4);
			target = input;
			put(target, source);
		} else if (input.find("attack") != string::npos) {
			input.erase(0, 7);
			int i = input.find(" ");
			string creature_name = input.substr(0, i);
			input.erase(0, i + 6);
			string weapon = input;
			attack(creature_name, weapon);
		} else {
			cout << "Error!" << endl;
		}

	}

	void turnon(string input) {
		int inventory_size = inventory.size();
		for (int i = 0; i < inventory_size; i++) {
			if (inventory[i] == input) {
				for (int j = 0; j < (int) map->item_list.size(); j++) {
					if (input == map->item_list[j]->name) {
						Item* item = map->item_list[j];
						if (item->turnon != NULL) {
							cout << "You activate the " << item->name << "."
									<< endl;
							cout << item->turnon->print << endl;
							//bool check_trigger1 = check_trigger(item->name);
							//		if(check_trigger == true)
							string action = item->turnon->action;
							if (action.find("Add") != string::npos) {
								add(action.erase(0, 4));
							} else if (action.find("Delete") != string::npos) {
								del(action.erase(0, 7));
							} else if (action.find("Update") != string::npos) {
								update(action.erase(0, 7));
							} else if (action.find("Game Over")) {
								Gameover();
							}
							return;
						} else {
							cout << item->name << " can not be turned on"
									<< endl;
						}
					}
				}
			}
		}
		cout << "Error" << endl;
		return;
	}

	void Gameover() {
		game_over = true;
		cout << "Victory" << endl;
	}

	void update(string in) {
		string obj;
		string status;
		int i = in.find(" to ");
		obj = in.substr(0, i);
		status = in.substr(i + 4);

		string type = determine_type(obj);

		if (type == "item") {
			for (int j = 0; j < (int) map->item_list.size(); j++) {
				if (obj == map->item_list[j]->name) {
					map->item_list[j]->status = status;
					return;
				}
			}
		} else if (type == "creature") {
			for (int k = 0; k < (int) map->creature_list.size(); k++) {
				if (obj == map->creature_list[k]->name) {
					map->creature_list[k]->status = status;
					return;
				}
			}
		} else if (type == "container") {
			for (int l = 0; l < (int) map->container_list.size(); l++) {
				if (obj == map->container_list[l]->name) {
					map->container_list[l]->status = status;
					//cout<<map->container_list[l]->status<<endl;
					return;
				}
			}
		}
		cout << obj << " can not be updated" << endl;
	}

	void del(string obj) {
		string type = determine_type(obj);
		if (type == "item") {
			std::map<string, Room*>::iterator it;
			for (it = map->room_list.begin(); it != map->room_list.end();
					++it) {
				for (int i = 0; i < (int) it->second->item.size(); i++) {
					if (it->second->item[i] == obj) {
						map->room_list[it->first]->item.erase(
								map->room_list[it->first]->item.begin() + i);
						return;
					}
				}
			}
		}

		if (type == "Container") {
			std::map<string, Room*>::iterator it;
			for (it = map->room_list.begin(); it != map->room_list.end();
					++it) {
				for (int i = 0; i < (int) it->second->container_name.size();
						i++) {
					if (it->second->container_name[i] == obj) {
						map->room_list[it->first]->container_name.erase(
								map->room_list[it->first]->container_name.begin()
										+ i);
						return;
					}
				}
			}
		}

		if (type == "Creature") {
			std::map<string, Room*>::iterator it;
			for (it = map->room_list.begin(); it != map->room_list.end();
					++it) {
				for (int i = 0; i < (int) it->second->creature_name.size();
						i++) {
					if (it->second->creature_name[i] == obj) {
						map->room_list[it->first]->creature_name.erase(
								map->room_list[it->first]->creature_name.begin()
										+ i);
						return;
					}

				}
			}
		}
		if (type == "Room") {
			std::map<string, Room*>::iterator it;
			for (it = map->room_list.begin(); it != map->room_list.end();
					++it) {
				for (int i = 0; i < (int) it->second->border.size(); i++) {
					if (it->second->border[i]->name == obj) {
						it->second->border.erase(
								it->second->border.begin() + i);
						return;
					}

				}

			}
		}
	}

	string determine_type(string obj) {
		string type;
		for (int i = 0; i < (int) map->container_list.size(); i++) {
			if (obj == map->container_list[i]->name) {
				type = "container";
				return type;
			}
		}

		for (int j = 0; j < (int) map->creature_list.size(); j++) {
			if (obj == map->creature_list[j]->name) {
				type = "creature";
				return type;
			}
		}

		for (int k = 0; k < (int) map->item_list.size(); k++) {
			if (obj == map->item_list[k]->name) {
				type = "item";
				return type;
			}
		}

		if (map->room_list[obj]) {
			type = "room";
			return type;
		}
		return type;
	}

	void add(string in) {
		string obj;
		string des;
		int i = in.find(" to ");
		obj = in.substr(0, i);
		des = in.substr(i + 4);
		string type = determine_type(obj);
		//cout<<des<<endl;
		//cout<<obj<<endl;
		if (type == "item") {
			if (map->room_list[des]) {
				map->room_list[des]->item.push_back(obj);
				map->room_list[des]->item_count++;
				return;
			}
			for (int i = 0; i < (int) map->container_list.size(); i++) {
				if (des == map->container_list[i]->name) {
					map->container_list[i]->item.push_back(obj);
					return;
				}
			}
		} else if (type == "creature") {
			map->room_list[des]->creature_name.push_back(obj);
			return;
		} else if (obj == "container") {
			if (map->room_list[des]) {
				map->room_list[des]->container_name.push_back(obj);
				return;
			}
		}
	}

	void drop(string input) {
		int inventory_size = inventory.size();
		for (int i = 0; i < inventory_size; i++) {
			if (inventory[i] == input) {
				room->item.push_back(input);
				room->item_count++;
				inventory.erase(inventory.begin() + i);
				cout << input << " dropped." << endl;
				return;
			}
		}
		cout << input << " not in inventory" << endl;
	}

	void read(string in) {
		int inventory_size = inventory.size();
		for (int i = 0; i < inventory_size; i++) {
			if (inventory[i] == in) {
				for (int i = 0; i < (int) map->item_list.size(); i++) {
					if (in == map->item_list[i]->name) {
						Item * item = map->item_list[i];
						if ((int) item->writing.size() == 0) {
							cout << "Error" << endl;
						} else {
							cout << item->writing << endl;
						}
						return;
					}
				}
			}
		}
		cout << "Error" << endl;
	}

	void put(string target, string source) {
		if (find(inventory.begin(), inventory.end(), source)
				== inventory.end()) {
			cout << source << " not in inventory" << endl;
			return;
		}

		int container_count = map->container_list.size();
		int check1 = 0;

		for (int x = 0; x < container_count; x++) {
			//cout<<room->container[x]->name<<endl;
			if ((string) (room->container_name[x]) == (string) target) {
				check1++;
			}
		}

		if (check1 == 0) {
			cout << target << " is not in the current room." << endl;
			return;
		}
		//cout << "1" << endl;
		int inventory_size = inventory.size();
		for (int i = 0; i < inventory_size; i++)
		{
		//	cout << "2" << endl;
			if (source == inventory[i])
			{
		//		cout << "3" << endl;
				for (int j = 0; j < container_count; j++)
				{
		//			cout << "4" << endl;
					if (find(room->container_name.begin(), room->container_name.end(), target) != room->container_name.end())
					{
						for (int k = 0; k < (int) map->container_list.size(); k++)
						{
							if (target == map->container_list[k]->name)
							{
		//						cout << "5" << endl;
								int accept_size = (map->container_list[k]->accept).size();

								if (accept_size > 0)
								{
									bool check_accept = false;
									for (int i = 0; i < (int) map->container_list[k]->accept.size();i++)
									{
										if (map->container_list[k]->accept[i]== source)
										{
											check_accept = true;
										}
									}
									if (check_accept == false)
									{
										cout << source<< " can not be placed in "	<< target << endl;
										return;
									}
									else
									{
										if (map->container_list[j]->status== "locked")
										{
											cout << target << " is locked"<< endl;

											return;
										}
										else
										{
											inventory.erase(inventory.begin() + i);
											map->container_list[k]->item.push_back(source);
											map->container_list[k]->item_count++;
											//cout<< map->container_list[j]->name<< " wasefasdawd " << endl;
											cout << "Item " << source << " added to " << target << endl;
											//check_trigger(target);
											map->container_list[j]->acceptance= true;
											return;
										}
									}
								}
								if(accept_size == 0)
								{
									if(map->container_list[k]->status == "closed")
									{
										cout<< target << " is closed." << endl;
										return;
									}
									if(map->container_list[k]->status == "locked")
									{
										cout<< target << " is locked." << endl;
										return;
									}
									inventory.erase(inventory.begin() + i);
									map->container_list[k]->item.push_back(source);
									map->container_list[k]->item_count++;
									//cout<< map->container_list[j]->name<< " wasefasdawd " << endl;
									cout << "Item " << source << " added to " << target << endl;
									//check_trigger(target);
									map->container_list[j]->acceptance= true;
									return;
								}
							}
						}
					}
				}
			}
		}
		return;
	}

	void take_item(string input) {
		while (input == "take") {
			cout << "What do you want to take?" << endl;
			getline(cin, input);
			if (input == "take") {
				continue;
			}
			if (input.find("take") != string::npos) {
				input.erase(0, 5);
			}
		}
		for (int x = 0; x < (int) map->container_list.size(); x++) {
			if (find(room->container_name.begin(), room->container_name.end(),
							map->container_list[x]->name)
					!= room->container_name.end()) {
				if (map->container_list[x]->status != "closed"
						&& map->container_list[x]->status != "locked") {
					for (int y = 0; y < map->container_list[x]->item_count;
							y++) {
						if (map->container_list[x]->item[y] == input) {
							inventory.push_back(
									map->container_list[x]->item[y]);
							cout << "Item " << map->container_list[x]->item[y]
							<< " was added to inventory." << endl;
							map->container_list[x]->item.erase(
									map->container_list[x]->item.begin() + y);
							map->container_list[x]->item_count--;
							return;
						}
					}
				}
			}
		}

		if (find(room->item.begin(), room->item.end(), input)
				!= room->item.end()) {
			for (int x = 0; x < room->item_count; x++) {
				if (room->item[x] == input) {
					inventory.push_back(input);
					room->item.erase(room->item.begin() + x);
					room->item_count--;
					cout << "Item " << input << " was added to inventory."
					<< endl;

					return;
				}
			}
		}
		cout << "Error, item not available" << endl;
		return;
	}

	void check_room() {
		int i;
		cout << room->description << "\n";
		if (room->item_count != 0) {
			cout << "You see something on the ground." << endl;
			cout << "It looks like there's a ";
			for (i = 0; i < room->item_count; i++) {
				if (room->item_count > 1 && i < (room->item_count - 1)) {
					cout << " and a ";
				}
			}
			cout << endl;
		}

		if (room->container_count != 0) {
			cout << "\nThere's something here" << endl;
			cout << "It looks like a ";
			for (i = 0; i < room->container_count; i++) {
				cout << room->container_name[i];
				if (room->container_count > 1
						&& i < (room->container_count - 1)) {
					cout << " and a ";
				}
			}
			cout << endl;
		}
	}

	void open_container(string input) {
		if (input == "exit") {
			if (string(room->type) == "exit") {
				cout << "Game Over" << endl;
				game_over = true;
				return;
			} else {
				cout << "You are not allowed to exit" << endl;
				return;
			}
		}
		while (input == "open") {
			cout << "What do you want to open?" << endl;
			getline(cin, input);
			if (input == "open") {
				continue;
			}
			if (input.find("open") != string::npos) {
				input.erase(0, 5);
			}
		}
		for (int i = 0; i < (int) map->container_list.size(); i++) {
			if ((string) input == (string) (map->container_list[i]->name)) {
				if (map->container_list[i]->status == "closed") {
					map->container_list[i]->status = "open";
				}
				for (int j = 0; j < map->container_list[i]->item_count; j++) {
					if (j == 0) {
						cout << input << " contains: ";
					}
					if (map->container_list[i]->item_count > 1 && j > 0) {
						cout << ", ";
					}
					cout << map->container_list[i]->item[j];
				}
				if (map->container_list[i]->item_count == 0) {
					cout << input << " is empty";
				}
				cout << "." << endl;
				return;
			}
		}
		cout << input << " not found." << endl;
		return;
	}

	void next_room(string input) {
		int border_ct = (int) room->border.size();
		int i = 0;

		while (i < border_ct) {
			if (input == room->border[i]->dir) {
				room = map->room_list[room->border[i]->name];
				//cout<<room->name<<"\n";
				cout << room->description << "\n";
				return;
			}
			i++;
		}
		if (i == border_ct) {
			cout << "Can't go that way!" << "\n";
		}
		return;
	}

	void getInventory() {
		int i = inventory.size();
		if (i == 0) {
			cout << "Inventory: empty" << endl;
			return;
		}

		cout << "Inventory: ";
		for (int x = 0; x < i; x++) {
			if (i > 1 && x > 0) {
				cout << ", ";
			}
			cout << inventory[x];
		}
		cout << endl;
		return;
	}

	void attack(string creaturename, string weapon) {
		if (find(room->creature_name.begin(), room->creature_name.end(),
						creaturename) == room->creature_name.end()) {
			cout << "Error" << endl;
			return;
		}
		//cout<<"100"<<endl;
		if (find(inventory.begin(), inventory.end(), weapon)
				== inventory.end()) {
			cout << "Error" << endl;
			return;
		}

		//cout<<"200"<<endl;
		bool condition = false;
		for (int i = 0; i < (int) map->creature_list.size(); i++)
		{
			if (creaturename == map->creature_list[i]->name)
			{
				//cout<<"300"<<endl;
				Creature * creature = map->creature_list[i];
				for (int x = 0; x < (int) creature->vulnerability.size(); x++)
				{
					//cout<<"times"<<creature->vulnerability[x]<<"   " << weapon<<endl;
					//cout<<x<<" "<<creature->vulnerability.size()<<endl;
					if (creature->vulnerability[x] == weapon)
					{
						cout << "You assault the " << creaturename << " with the " << weapon << endl;
						//cout<<"400"<<endl;
						if(creature->attack != NULL)
						{
							if (creature->attack->hasCondition == true)
							{
								//cout<<"500"<<endl;
								string object = creature->attack->cond.object;
								string status = creature->attack->cond.status;

								if (map->room_list.find(object)
										!= map->room_list.end())
								{
									if (map->room_list.find(object)
											!= map->room_list.end())
									{
										if (map->room_list[object]->status
												== status) {
											condition = true;
										}
									}
								}
								//cout<<"600"<<endl;
								for (int i = 0; i < map->item_ct; i++)
								{
									if (object == map->item_list[i]->name)
									{
										if (status == map->item_list[i]->status)
										{
											condition = true;
										}
									}
								}
								//cout<<"700"<<endl;
								for (int i = 0;i < (int) map->container_list.size(); i++)
								{
									if (object == map->container_list[i]->name)
									{
										if (status
												== map->container_list[i]->status)
										{
											condition = true;
										}
									}
								}
								//cout<<"800"<<endl;
								for (int i = 0; i < (int) map->creature_list.size(); i++)
								{
									if (object == map->creature_list[i]->name)
									{
										if (status == map->creature_list[i]->status)
										{
											condition = true;
										}
									}
								}
								//cout<<"900"<<endl;
								if (condition == false) {
									cout << "Error" << endl;
									return;
								}
								//cout << "You assault the " << creaturename << " with the " << weapon << endl;
							}

							//cout<<"1000"<<endl;
							if (creature->attack->hasPrint == true) {
								//cout<<"2000"<<endl;
								cout << creature->attack->print << endl;
							}
							if (creature->attack->hasAction == true) {
								//cout<<"3000"<<endl;
								for (int j = 0; j < (int) creature->attack->action.size(); j++) {
									check_action(creature->attack->action[j]);
								}
							}
						}
						return;
					}
				}
				cout<<"Error, "<< creaturename << " was not affected by " << weapon <<endl;
				return;
			}
		}
	}

	void check_action(string action) {
		if (action.find("Add") != string::npos) {
			add(action.erase(0, 4));
			return;
		}
		if (action.find("Delete") != string::npos) {
			//del(action.erase(0,7));
			return;
		}
		if (action.find("Update") != string::npos) {
			update(action.erase(0, 7));
			return;
		}
		if (action == "Game Over") {
			Gameover();
			return;
		}
		input_check(action);
	}

	void execute_trigger(Trigger* t) {
		for (int i = 0; i < (int) t->print.size(); i++) {
			cout << t->print[i] << endl;
		}
		for (int i = 0; i < (int) t->action.size(); i++) {
			check_action(t->action[i]);
		}
	}



	bool check_owner(Trigger* tri) {
		string owner = tri->owner; //owner_node->value();
		string object = tri->object;
		string has = tri->has;

		if (owner == "inventory") {
			//if (owner == "inventory") {

			for (int i = 0; i < (int) inventory.size(); i++)
			{
				if (inventory[i] == object)
				{
					if (has == "yes")
					{
						execute_trigger(tri);
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			if (has == "no")
			{
				execute_trigger(tri);
				return true;
			}
			else
			{
				return false;
			}
		}

		string ownertype = determine_type(owner);
		string objecttype = determine_type(object);


		if (ownertype == "room")
		{
			std::map<string, Room*>::iterator it_room;
			for (it_room = map->room_list.begin();
					it_room != map->room_list.end(); it_room++)
			{
				if (it_room->first == owner)
				{
					if (objecttype == "item")
					{
							for (int j = 0; j < (int) it_room->second->item.size();j++)
							{
								if (it_room->second->item[j] == object)
								{
									if (has == "yes")
									{
										execute_trigger(tri);
										return true;
									}
									else
									{
										return false;
									}
								}
							}
							if (has == "no")
							{
								execute_trigger(tri);
								return true;
							}
							else
							{
								return false;
							}
					}
					else if (objecttype == "container")
					{
						for (int j = 0; j< (int) it_room->second->container_name.size(); j++)
						{
							if(it_room->second->container_name[j] == object)
							{
								if (has == "yes")
								{
									execute_trigger(tri);
									return true;
								}
								else
								{
									return false;
								}
							}
						}
						if (has == "no")
						{
							execute_trigger(tri);
							return true;
						}
						else
						{
							return false;
						}
					} else if (objecttype == "creature")
					{
						if (has == "yes")
						{
							for (int j = 0; j < (int) it_room->second->creature_name.size();j++)
							{
								if (it_room->second->creature_name[j] == object)
								{
									execute_trigger(tri);
									return true;
								}
							}
							return false;
						}
						if (has == "no")
						{
							execute_trigger(tri);
							return true;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
		else if (ownertype == "container")
		{
			for (int i = 0; i < (int) map->container_list.size(); i++)
			{
				if(map->container_list[i]->name == owner)
				{
					if(objecttype == "item")
					{
						for (int x = 0; x < (int) map->container_list[i]->item.size(); x++)
						{
							//cout<<map->container_list[i]->name<<"  andasdasd       "<<object<<endl;
							if (map->container_list[i]->item[x] == object)
							{
								if (has == "yes")
								{
									//cout<<map->container_list[i]->name<<"  andasdasd       "<<object<<endl;
									execute_trigger(tri);
									return true;
								}
								else
								{
									return false;
								}
							}
						}
						if (has == "no")
						{
							//cout<<map->container_list[i]->name<<"andasdasd"<<owner<<endl;
							execute_trigger(tri);
							return true;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
		return false;
	}

	bool check_status(Trigger * t) {
		string object = t->object;
		string status = t->status;
		//cout<<object<<endl;
		string object_type = determine_type(object);

		//cout<< object_type<< endl;
		if (object_type == "room")
		{
			std::map<string, Room*>::iterator it_room;
			for (it_room = map->room_list.begin(); it_room != map->room_list.end(); ++it_room)
			{
				if (it_room->first == object)
				{
					if (it_room->second->status == status)
					{
						//cout<<"room"<<endl;
						//cout<<it_room->second->status<<endl;
						execute_trigger(t);
						//t->single = false;
						return true;
					}
				}
			}
		}
		else if (object_type == "item")
		{
			for (int j = 0; j < (int) map->item_list.size(); j++)
			{
				if (map->item_list[j]->name == object)
				{
					if (map->item_list[j]->status == status)
					{
						//cout<<"item"<<endl;
						execute_trigger(t);
						//t->single = false;
						return true;
					}
				}
			}
		}
		else if (object_type == "container")
		{
			//cout<< object<< status << endl;
			for (int k = 0; k < (int) map->container_list.size(); k++)
			{
				if (map->container_list[k]->name == object)
				{
					//cout<<map->container_list[k]->status << "   w     "<< status<< endl;
					if (map->container_list[k]->status == status)
					{
					//if(map->container_list[k]->acceptance == true)
						//cout<<"container"<<endl;
						execute_trigger(t);
						//t->single = false;
						return true;
					}
				}
			}
		} else if (object_type == "creature")
		{
			for (int a = 0; a < (int) map->creature_list.size(); a++)
			{
				if (map->creature_list[a]->name == object)
				{
					if (map->creature_list[a]->status == status)
					{
						//cout<<"creature"<<endl;
						execute_trigger(t);
						//t->single = false;
						return true;
					}
				}
			}
		}
		return false;
	}

	bool check_trigger(string input) {
		bool room_result = false;
		bool item_result = false;
		bool container_result = false;
		bool creature_result = false;

		Trigger * t;

		//cout<<"1"<<endl;
		for (int i = 0; i < (int) room->trigger.size(); i++)
		{
			t = room->trigger[i];
			if (((int) t->command.size() != 0 && input == t->command) || ((int) t->command.size() == 0 && input.size() == 0))
			{
				if (t->type == "permanent"|| (t->single))
				{

					//cout<<"1"<<endl;
					if (t->hasOwner == true)
					{
						//cout<<"4"<<endl;
						room_result = check_owner(t);
					}
					if (t->hasStatus == true)
					{
						//cout<< room_result<<t->status<<endl;
						room_result = check_status(t);
						//cout<< room_result<<endl;
						//t->count++;
						//t->single = false;
					}
					if(room_result)
					{
						t->single = false;
						//t->count++;
					}

				}
			}/*
			else
			{
				room_result = true;
			}*/
		}

		//cout<<"2"<<endl;
		for (int i = 0; i < (int) room->item.size(); i++)
		{
			for (int k = 0; k < (int) map->item_list.size(); k++)
			{
				if (map->item_list[k]->name == room->item[i]) {
					Item* item = map->item_list[i];
					for (int j = 0; j < int(item->trigger.size()); j++)
					{
						t = item->trigger[j];
						if (((int) t->command.size() != 0 && input == t->command) || ((int) t->command.size() == 0 && input.size() == 0))
						{
							//cout<<"222"<<endl;
							if (t->type == "permanent" || (t->single))
							{
								if (t->hasOwner == true)
								{
									item_result = check_owner(t);
									//t->count++;
									//t->single = false;
								}
								if (t->hasStatus == true)
								{
									item_result = check_status(t);
									//t->count++;
									//t->single = false;
								}
								if(item_result)
								{
									t->single = false;
									//t->count++;
								}
								//t->single = false;
							}/*
							else
							{
								item_result = true;
							}*/
						}
					}
				}
			}

		}

		//cout<<"3"<<endl;
		for (int i = 0; i < int(room->container_name.size()); i++)
		{
			for (int a = 0; a < (int) map->container_list.size(); a++)
			{
				if (map->container_list[a]->name == room->container_name[i])
				{
					Container* container = map->container_list[a];
					for (int j = 0; j < (int) (container->trigger.size()); j++)
					{
						t = container->trigger[j];
						if (( t->command.size() > 0 && input == t->command) || ( t->command.size() == 0 && input.size() == 0))
						{
							//cout<<"1"<<endl;
							//cout<<"3"<<endl;
							if (t->type == "permanent"|| (t->single))
							{
								//cout<<"7"<<endl;
								if (t->hasOwner == true)
								{
									//cout<<"9"<<endl;
									container_result = check_owner(t);
									//t->count++;
									//t->single = false;
								}
								else if (t->hasStatus == true)
								{
									//cout<<"8"<<endl;
									//cout<<t->status<<"   awdasd"<<endl;
									container_result = check_status(t);
									//t->count++;
									//t->single = false;
								}
								if(container_result)
								{
									t->single = false;
									//t->count++;
								}
							}/*
							else
							{
								container_result = true;
							}*/
						}
					}
				}
			}
		}

		//cout<<"4"<<endl;
		for (int i = 0; i < int(room->creature_name.size()); i++)
		{
			for (int a = 0; a < (int) map->creature_list.size(); a++)
			{
				if (map->creature_list[a]->name == room->creature_name[i])
				{
					Creature* creature = map->creature_list[a];
					for (int j = 0; j < (int) (creature->trigger.size()); j++)
					{
						t = creature->trigger[j];
						if (((int) t->command.size() != 0 && input == t->command) || ((int) t->command.size() == 0 && input.size() == 0))
						{
							//cout<<"4"<<endl;
							if (t->type == "permanent" || (t->single))
							{
								if (t->hasOwner == true) {
									creature_result = check_owner(t);
									//t->count++;
									//t->single = false;
								}
								else if (t->hasStatus == true)
								{
									creature_result = check_status(t);
								}
								if(creature_result)
								{
									t->single = false;
									//t->count++;
								}
							}/*
							else
							{
								creature_result = true;
							}
							*/
						}
					}
				}
			}
		}

		return room_result || item_result || container_result || creature_result;

	}

}
;
