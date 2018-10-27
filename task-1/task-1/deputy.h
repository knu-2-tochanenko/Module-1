#pragma once

#include "law.h"
#include <iostream>
#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

class Deputy {
private:
	string name;	//	Deputy's name
	string surname;	//	Deputy's surname
	static int id;	//	Deputy's ID which is unique for each deputy

	map<Law, int> supportCoefficient; // If <int> is > 0 then current deputy supports this law

public:

};