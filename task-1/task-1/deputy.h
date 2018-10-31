#pragma once

#include "law.h"
#include "consignment.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <time.h>

constexpr double SUPPORT_COEFF = 0.33;

using std::string;
using std::vector;
using std::map;

class Deputy {
private:
	int id;	//	Deputy's ID which is unique for each deputy
	static int MaxID;

	bool *lawCoef;		// true - law is preferred, if else - is not
	bool *electCoef;	// true - law is preferred, if else - is not
	bool *workCoef;		// true - law is preferred, if else - is not

public:

	Deputy(int lawsSize, int electSize, int workSize) {
		this->id = MaxID;
		MaxID++;

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

	/*
	*	Checks if current Deputy wants to vote for law, which is
	*	elections type. His decision is made based of the same
	*	number of supported laws.
	*/
	bool voteForConsignment(ElectionsLaw law, int lawsSize, int electSize, int workSize, vector<Consignment> allConsignments) {
		int mainConsignment = law.getMainConsignment();

		double totalNumberOfSameLaws = 0.0;

		for (int i = 0; i < lawsSize; i++)
			if ((lawCoef[i])
				&& (allConsignments[mainConsignment].standardLawVote(i)))
				totalNumberOfSameLaws += 1.0;
		for (int i = 0; i < electSize; i++)
			if ((lawCoef[i])
				&& (allConsignments[mainConsignment].electLawVote(i)))
				totalNumberOfSameLaws += 1.0;
		for (int i = 0; i < workSize; i++)
			if ((lawCoef[i])
				&& (allConsignments[mainConsignment].workLawVote(i)))
				totalNumberOfSameLaws += 1.0;

		return (((double)lawsSize / totalNumberOfSameLaws) >= SUPPORT_COEFF);
	}

	bool standardLawVote(int lawID) { return lawCoef[lawID]; }
	bool electLawVote(int lawID) { return electCoef[lawID]; }
	bool workLawVote(int lawID) { return workCoef[lawID]; }

};

int Deputy::MaxID = 0;