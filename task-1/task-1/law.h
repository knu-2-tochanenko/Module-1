#pragma once

#include "deputy.h"
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

	static int MaxID;
	int ID;
public:
	Law(int complexity, double neededVotes) {
		this->complexity = complexity;
		this->neededVotes = neededVotes;

		this->ID = MaxID;
		MaxID++;
	}
	
	//	Getters
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

class ElectionsLaw {
private:

	int complexity;
	double neededVotes;
	static int MaxID;
	int ID;

	int electionTerm;	//	Days between each elections of main party
	int singleConsDeputies;		/*	Number of deputies from main consignment,
											higher than from another consignments */
	int mainConsDeputies;		//	Number of deputies from non-main consignment
	int mainConsID;				//	Main consignment 
	bool *preferredCons;		//	Preferred consignments for this law

public:
	//	Constructor. Only consignmentList is needed for GENERATING preferredConsignments
	ElectionsLaw(int complexity, double neededVotes, int daysBetweenElections,
		int mainConsDeputies, int singleConsDeputies, int mainConsID,
		vector<Consignment> consignmentList) {

		this->complexity = complexity;
		this->neededVotes = neededVotes;

		this->ID = MaxID;
		MaxID++;

		this->electionTerm = daysBetweenElections;
		this->singleConsDeputies = singleConsDeputies;
		this->mainConsDeputies = mainConsDeputies;
		this->mainConsID = mainConsID;

		int numberOfConsignments = consignmentList.size();
		preferredCons = new bool[numberOfConsignments];
		//	randomly support consignments
		srand(clock());
		for (int i = 0; i < numberOfConsignments; i++)
			if (((rand() % 3) != 0) || (this->mainConsID == consignmentList[i].getID()))
				preferredCons[i] = true;
			else
				preferredCons[i] = false;
	}
	
	//	More getters
	int getElectionTerm() { return electionTerm; }
	int getMainConsDeputies() { return singleConsDeputies; }
	int getSingleConsDeputies() { return mainConsDeputies; }
	int getMainConsignment() { return mainConsID; }
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
	bool isConsPreferred(int ID) {
		return (preferredCons[ID]);
	}

	//	Check whether specific Consignment is preferred for this law
	bool isPreferred(Consignment consignment) {
		return preferredCons[consignment.getID()];
	}
};



class WorkingProcessLaw {
private:

	int complexity;
	double neededVotes;
	static int MaxID;
	int ID;

	double newComplexityFactor;			//	A number from [0.1 - 2] which defines days for each law to be processed
	double newNeededVotesFactor;		//	A number from [0.1 - 0.9] which defines number of votes which are needed
public:

	WorkingProcessLaw(int complexity, double neededVotes,
		double newComplexityFactor, double newNeededVotesFactor) {

		this->complexity = complexity;
		this->neededVotes = neededVotes;

		this->ID = MaxID;
		MaxID++;

		this->newComplexityFactor = newComplexityFactor;
		this->newNeededVotesFactor = newNeededVotesFactor;
	}

	//	Even more getters!
	double getNewComplexityFactor() { return newComplexityFactor; }
	double getNewNeededVotesFactor() { return newNeededVotesFactor; }

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

int WorkingProcessLaw::MaxID = 0;