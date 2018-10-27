#pragma once

#include "law.h"
#include "deputy.h"
#include "consignment.h"
#include <iostream>
#include <string>
#include <list>

using std::string;
using std::list;

class Parliament {
private:

	int complexityFactor;

	string parliamentName;					//	Name of current Parliament (may change with elected consignment)
	list<Consignment> consignmentList;		//	List of consignments
	Consignment* mainConsignment;			//	Main consignment in Parliament

	bool generateLaws(int numberOfLaws) {

	}

public:
	Parliament() {
		
	}

	bool workDay() {

	}

	bool election() {

	}

};
