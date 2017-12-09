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

class Owner{
public:
	string object;
	string has;
	string owner;

	Owner(string object_input, string owner_input, string has_input)
	{
		object = object_input;
		has = has_input;
		owner = owner_input;
	}
};
