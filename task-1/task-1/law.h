#pragma once

#include "deputy.h"
#include "consignment.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <time.h>

using std::string;
using std::vector;
using std::map;
using std::pair;

/*
*	Laws are can't be changed once they are created!
*/

class Law {
protected:
	int complexity;						/*	Law complexity. [complexity] + 1 = number of days
											which are needed to process current law */
	double neededVotes;					//	Part of notes which are needed to process current law [0.1 - 1]
	enum LawType { STANDART = 0, ELECTIONS_LAW = 1, WORKING_PROCESS_LAW = 2 } lawType;

	static int MaxID;
	int ID;
public:
	Law(int complexity, double neededVotes) {
		this->complexity = complexity;
		this->neededVotes = neededVotes;
		lawType = STANDART;

		this->ID = MaxID;
		MaxID++;
	}
	
	//	Getters
	LawType getType() { return STANDART; }
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

class ElectionsLaw : public Law {
private:
	int daysBetweenElections;			//	Days between each elections of main party
	int deputiesFromMainConsignment;	/*	Number of deputies from main consignment,
											higher than from another consignments */
	int deputiesFromConsignments;		//	Number of deputies from non-main consignment
	int mainConsignmentID;				//	Main consignment 
	bool *preferredConsignments;		//	Preferred consignments for this law

public:
	//	Constructor. Only consignmentList is needed for GENERATING preferredConsignments
	ElectionsLaw(int complexity, double neededVotes, int daysBetweenElections,
		int deputiesFromMainConsignment, int deputiesFromConsignments, int mainConsignmentID,
		vector<Consignment> consignmentList) : Law(complexity, neededVotes) {

		this->daysBetweenElections = daysBetweenElections;
		this->deputiesFromMainConsignment = deputiesFromMainConsignment;
		this->deputiesFromConsignments = deputiesFromConsignments;
		this->mainConsignmentID = mainConsignmentID;

		lawType = ELECTIONS_LAW;

		int numberOfConsignments = consignmentList.size();
		preferredConsignments = new bool[numberOfConsignments];
		//	randomly support consignments
		srand(clock());
		for (int i = 0; i < numberOfConsignments; i++)
			if (((rand() % 3) != 0) || (this->mainConsignmentID == consignmentList[i].getID()))
				preferredConsignments[i] = true;
			else
				preferredConsignments[i] = false;
	}
	
	//	More getters
	LawType getType() { return ELECTIONS_LAW; }
	int getDaysBetweenElections() { return daysBetweenElections; }
	int getDeputiesFromMainConsignment() { return deputiesFromMainConsignment; }
	int getDeputiesFromConsignment() { return deputiesFromConsignments; }
	int getMainConsignment() { return mainConsignmentID; }

	//	Check whether specific Consignment is preferred for this law
	bool isPreferred(Consignment consignment) {
		return preferredConsignments[consignment.getID()];
	}
};

class WorkingProcessLaw : public Law {
private:
	double newComplexityFactor;			//	A number from [0.1 - 2] which defines days for each law to be processed
	double newNeededVotesFactor;		//	A number from [0.1 - 0.9] which defines number of votes which are needed
public:

	WorkingProcessLaw(int complexity, double neededVotes,
		double newComplexityFactor, double newNeededVotesFactor) : Law(complexity, neededVotes) {
		this->newComplexityFactor = newComplexityFactor;
		this->newNeededVotesFactor = newNeededVotesFactor;

		lawType = WORKING_PROCESS_LAW;

	}

	//	Even more getters!
	LawType getType() { return WORKING_PROCESS_LAW; }
	double getNewComplexityFactor() { return newComplexityFactor; }
	double getnewNeededVotesFactor() { return newNeededVotesFactor; }
};