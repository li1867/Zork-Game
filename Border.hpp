#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class Border{
public:
	string dir;
	string name;

	Border(string direction, string input_name)
	{
		dir = direction;
		name = input_name;
	}
	virtual ~Border(){

	}
};
