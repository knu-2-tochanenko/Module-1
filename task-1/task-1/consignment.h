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
	string parliamentName;	//	Preferred name of the Parliament

	int ID;
	static int MaxID;

	vector<Deputy> deputiesList;				//	List of deputies
	bool *lawCoef;		// true - law is preferred, if else - is not
	bool *electCoef;	// true - law is preferred, if else - is not
	bool *workCoef;		// true - law is preferred, if else - is not

public:
	Consignment(string name, string moto, string preferredParliamentName) {
		this->name = name;
		this->motto = moto;
		this->parliamentName = preferredParliamentName;

		this->ID = MaxID;
		MaxID++;
	}

	//	The second stage of initialization
	void generateCoefficients(int lawsSize, int electSize, int workSize) {
		srand(clock());

		lawCoef = new bool[lawsSize];
		electCoef = new bool[electSize];
		workCoef = new bool[workSize];

		for (int i = 0; i < lawsSize; i++)
			lawCoef[i] = rand() % 2;
		for (int i = 0; i < electSize; i++)
			electCoef[i] = rand() % 2;
		for (int i = 0; i < workSize; i++)
			workCoef[i] = rand() % 2;
	}

	//	The third stage of initialization
	void generateDeputies(int maxNumber, int lawsSize, int electSize, int workSize) {
		for (int i = 0; i < maxNumber; i++) {
			Deputy newDeputy(lawsSize, electSize, workSize);
			deputiesList.push_back(newDeputy);
		}
	}

	int getID() { return ID; }

	string getName() { return name; }
	string getMotto() { return motto; }
	string getParliamentName() { return parliamentName; }

	bool standardLawVote(int lawID) { return lawCoef[lawID]; }
	bool electLawVote(int lawID) { return electCoef[lawID]; }
	bool workLawVote(int lawID) { return workCoef[lawID]; }

	//	get how many deputies have 
	int electVotesNumber(ElectionsLaw law, int lawsSize, int electSize, int workSize, vector<Consignment> allConsignments) {
		int res = 0;
		int deputiesSize = deputiesList.size();
		for (int i = 0; i < deputiesSize; i++)
			if (deputiesList[i].voteForConsignment(law, lawsSize, electSize, workSize, allConsignments))
				res++;
		return res;
	}

	int getDeputiesSize() {
		return deputiesList.size();
	}

	//	Adds another randomly generated deputy
	bool addDeputy(int lawsSize, int electSize, int workSize) {
		Deputy newDeputy(lawsSize, electSize, workSize);
		deputiesList.push_back(newDeputy);
	}

	//	Removes least favorite deputy
	bool removeDeputy(int lawsSize, int electSize, int workSize) {
		//	If deputies list is empty
		if (deputiesList.size() == 0)
			return false;

		int deputySize = deputiesList.size();
		int *similarCoef;
		similarCoef = new int[deputySize];
		for (int i = 0; i < deputySize; i++)
			similarCoef[i] = 0;

		//	Check for every deputy for similar votes
		for (int i = 0; i < deputySize; i++) {
			for (int j = 0; j < lawsSize; j++)
				if (deputiesList[i].standardLawVote(j) && lawCoef[j])
					similarCoef[i]++;
			for (int j = 0; j < electSize; j++)
				if (deputiesList[i].electLawVote(j) && electCoef[j])
					similarCoef[i]++;
			for (int j = 0; j < workSize; j++)
				if (deputiesList[i].workLawVote(j) && workCoef[j])
					similarCoef[i]++;
		}

		//	Find the least suitable deputy
		int lowestNum = 0;
		for (int i = 1; i < deputySize; i++)
			if (similarCoef[lowestNum] > similarCoef[i])
				lowestNum = i;

		//	Delete it!
		deputiesList.erase(deputiesList.begin() + lowestNum);
		return true;
	}

};

int Consignment::MaxID = 0;