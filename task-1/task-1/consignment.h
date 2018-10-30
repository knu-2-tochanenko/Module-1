#pragma once

#include "law.h"
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

constexpr int MAX_COEFFICIENT = 5;

class Consignment {
private:

	string name;					//	Name of the consignment
	string motto;					//	Motto of current consignment
	string preferredParliamentName;	//	Preferred name of the Parliament

	int ID;
	static int MaxID;

	vector<Deputy> deputiesList;				//	List of deputies
	bool *preferredLawCoefficient;	// If <int> is > 0 then current consignment prefers this law

public:
	Consignment(string name, string moto, string preferredParliamentName) {
		this->name = name;
		this->motto = moto;
		this->preferredParliamentName = preferredParliamentName;

		this->ID = MaxID;
		MaxID++;
	}

	//	The second stage of initialization
	void generateCoefficients(vector<Law> allLaws) {
		int lawsSize = allLaws.size();
		srand(clock());

		preferredLawCoefficient = new bool[lawsSize];

		for (int i = 0; i < lawsSize; i++)
			preferredLawCoefficient[i] = rand() % 2;
	}

	//	The third stage of initialization
	void generateDeputies(int maxNumber, int lawsSize) {
		for (int i = 0; i < maxNumber; i++) {
			Deputy newDeputy(lawsSize);
			deputiesList.push_back(newDeputy);
		}
	}

	int getID() { return ID; }

	string getName() { return name; }
	string getMotto() { return motto; }
	string getPreferredParliamentName() { return preferredParliamentName; }

	bool voteForLaw(int lawID) {
		return (preferredLawCoefficient[lawID]);
	}

	//	get how many deputies have 
	int getVotedElectionsNumber(ElectionsLaw law, int lawsSize, vector<Consignment> allConsignments) {
		int res = 0;
		int deputiesSize = deputiesList.size();
		for (int i = 0; i < deputiesSize; i++)
			if (deputiesList[i].voteForConsignment(law, lawsSize, allConsignments))
				res++;
		return res;
	}

};

int Consignment::MaxID = 0;