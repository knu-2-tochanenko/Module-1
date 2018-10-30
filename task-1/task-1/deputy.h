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

	bool *supportCoefficient; // If it is > 0 then current deputy supports this law 

public:

	Deputy(int lawsSize) {
		this->id = MaxID;
		MaxID++;

		supportCoefficient = new bool[lawsSize];

		srand(clock());
		for (int i = 0; i < lawsSize; i++)
			supportCoefficient[i] = rand() % 2;
	}

	/*
	*	Checks if current Deputy wants to vote for law, which is
	*	elections type. His decision is made based of the same
	*	number of supported laws.
	*/
	bool voteForConsignment(ElectionsLaw law, int lawsSize, vector<Consignment> allConsignments) {
		int mainConsignment = law.getMainConsignment();

		double totalNumberOfSameLaws = 0.0;

		for (int i = 0; i < lawsSize; i++)
			if ((supportCoefficient[i])
				&& (allConsignments[mainConsignment].voteForLaw(i)))
				totalNumberOfSameLaws += 1.0;

		return (((double)lawsSize / totalNumberOfSameLaws) >= SUPPORT_COEFF);
	}

};

int Deputy::MaxID = 0;