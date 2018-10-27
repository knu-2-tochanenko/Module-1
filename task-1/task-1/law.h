#pragma once

#include "deputy.h"
#include "consignment.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

using std::string;
using std::vector;
using std::map;
using std::pair;

/*
*	Laws are can't be changed once they are created!
*/

class Law {
protected:
	string name;						//	Law name
	double complexity;					/*	Law complexity. [complexity] + 1 = number of days
											which are needed to process current law */
	double neededVotes;					//	Part of notes which are needed to process current law [0.1 - 1]
	enum LawType { STANDART, ELECTIONS_LAW, WORKING_PROCESS_LAW };

	static int MaxID;
	int ID;
public:
	Law(string name, double complexity, double neededVotes) {
		this->name = name;
		this->complexity = complexity;
		this->neededVotes = neededVotes;

		this->ID = MaxID;
		MaxID++;
	}
	
	//	Getters
	LawType getType() { return STANDART; }
	string getName() { return name; }
	double getComplexity() { return complexity; }
	double getNeededVotes() { return neededVotes; }
	int getID() { return ID; }
	string getIDString() {
		string res = "";
		if (ID < 10)
			res += "00";
		else if (ID < 100)
			res += "0";
		res += std::to_string(ID);
		return res;
	}

};

int Law::MaxID = 0;

class ElectionsLaw : protected Law {
private:
	int daysBetweenElections;			//	Days between each elections of main party
	int deputiesFromMainConsignment;	/*	Number of deputies from main consignment,
											higher than from another consignments */
	int deputiesFromConsignments;		//	Number of deputies from non-main consignment
	Consignment *mainConsignment;		//	Main consignment 
	map<Consignment, bool> preferredConsignments;	//	Preferred consignments for this law

public:
	//	Constructor. Only consignmentList is needed for GENERATING preferredConsignments
	ElectionsLaw(string name, double complexity, double neededVotes, int daysBetweenElections,
		int deputiesFromMainConsignment, int deputiesFromConsignments, Consignment *mainParty,
		vector<Consignment> &consignmentList) : Law(name, complexity, neededVotes) {

		this->daysBetweenElections = daysBetweenElections;
		this->deputiesFromMainConsignment = deputiesFromMainConsignment;
		this->deputiesFromConsignments = deputiesFromConsignments;
		this->mainConsignment = mainConsignment;

		//	randomly support consignments
		int numberOfConsignments = consignmentList.size();
		for (int i = 0; i < numberOfConsignments; i++)
			if (((rand() % 3) != 0) || (this->mainConsignment->getName() == consignmentList[i].getName()))
				preferredConsignments.insert(pair<Consignment, bool>(consignmentList[i], true));
			else
				preferredConsignments.insert(pair<Consignment, bool>(consignmentList[i], true));
	}
	
	//	More getters
	LawType getType() { return ELECTIONS_LAW; }
	int getDaysBetweenElections() { return daysBetweenElections; }
	int getDeputiesFromMainConsignment() { return deputiesFromMainConsignment; }
	int getDeputiesFromConsignment() { return deputiesFromConsignments; }
	Consignment* getMainConsignment() { return mainConsignment; }

	//	Check whether specific Consignment is preferred for this law
	bool isPreferred(Consignment *consignment) {
		return preferredConsignments[*consignment];
	}
};

class WorkingProcessLaw : protected Law {
private:
	double newComplexityFactor;			//	A number from [0.1 - 5] which defines days for each law to be processed
	double newNeededVotesFactor;		//	A number from [0.1 - 5] which defines number of 
public:

	WorkingProcessLaw(string name, double complexity, double neededVotes,
		double newComplexityFactor, double newNeededVotesFactor) : Law(name, complexity, neededVotes) {
		this->newComplexityFactor = newComplexityFactor;
		this->newNeededVotesFactor = newNeededVotesFactor;
	}

	//	Even more getters!
	LawType getType() { return WORKING_PROCESS_LAW; }
	double getNewComplexityFactor() { return newComplexityFactor; }
	double getnewNeededVotesFactor() { return newNeededVotesFactor; }
};