#pragma once

#include "law.h"
#include "deputy.h"
#include <iostream>
#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

class Consignment {
private:

	string name;					//	Name of the consignment
	string motto;					//	Motto of current consignment
	string preferredParliamentName;	//	Preferred name of the Parliament

	list<Deputy> deputiesList;				//	List of deputies
	map<Law, int> preferredLawCoefficient;	// If <int> is > 0 then current consignment prefers this law

public:
	Consignment(string name, string moto, string preferredParliamentName) {
		this->name = name;
		this->motto = moto;
		this->preferredParliamentName = preferredParliamentName;
	}

	string getName() { return name; }

};

