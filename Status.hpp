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

class Status{
public:
	string object;
	string status;
	Status(string object_input, string status_input)
	{
		object = object_input;
		status = status_input;
	}
};
