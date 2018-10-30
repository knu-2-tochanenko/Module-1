#pragma once

#include "law.h"
#include "deputy.h"
#include "consignment.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

#include <random>
#include <time.h>

using std::string;
using std::vector;
using std::queue;

constexpr int NUMBER_OF_LAWS = 32;
constexpr int MAX_NUMBER_OF_DEPUTIES = 10;

constexpr int MAX_DAYS = 5;
constexpr int DAYS = 256;

class Parliament {
private:

	double complexityFactor;
	double neededVotesFactor;

	int daysBetweenElections;
	int deputiesFromMainConsignment;
	int deputiesFromConsignments;

	string parliamentName;					//	Name of current Parliament (may change with elected consignment)
	int mainConsignmentID;					//	Main consignment in Parliament
	vector<Consignment> consignmentList;	//	List of consignments
	vector<Law> lawList;					//	List of all laws. Can't be changed
	//	TODO change to pointers
	struct ConsignmentInit {
		string moto;
		string name;
		string parliamentName;

		void set(string moto, string name, string parliamentName) {
			this->moto = moto;
			this->name = name;
			this->parliamentName = parliamentName;
		}

	};

	//	There are 5 different consignments
	bool generateConsignments() {

		ConsignmentInit strings[5];

		strings[0].set("For our country!", "R.E.D.", "The Central Committee");
		strings[1].set("For the Queen!", "W.H.I.T.E.", "The White Castle");
		strings[2].set("In Dog we trust!", "The Dog-gists", "Bob's house");
		strings[3].set("Let the fun begin!", "Funnies", "A Fun place to live");
		strings[4].set("HTML is not a programming language!", "ANTI-HTML", "VIM");

		for (int i = 0; i < 5; i++) {
			Consignment newConsignment(strings[i].name, strings[i].moto, strings[i].parliamentName);
			consignmentList.push_back(newConsignment);
		}
		return true;
	}

	bool generateLaws(int numberOfLaws) {
		srand(clock());
		int randomValue, complexity, daysBetweenElections, newDeputiesFromMainConsignment,
			newDeputiesFromConsignments, newMainConsignmentID, newDaysBetweenElections;
		double neededVotes, newComplexityFactor, newNeededVotesFactor;

		for (int i = 0; i < NUMBER_OF_LAWS; i++) {
			randomValue = rand() % 10;
			if (randomValue > 5) {
				//	Generate standard law
				complexity = (rand() % MAX_DAYS);
				neededVotes = (double)(rand() % 10 + 1) / 10.0;
				Law newLaw(complexity, neededVotes);
				lawList.push_back(newLaw);
			}
			else if (randomValue > 1) {
				//	Generate working process law
				complexity = (rand() % MAX_DAYS);
				neededVotes = (double)(rand() % 10 + 1) / 10.0;

				newComplexityFactor = (double)(rand() % 20 + 1) / 10.0;
				newNeededVotesFactor = (double)(rand() % 10 + 1) / 10.0;

				WorkingProcessLaw newLaw(complexity, neededVotes, newComplexityFactor, newNeededVotesFactor);
				lawList.push_back(newLaw);
			}
			else {
				//	Generate elections law
				complexity = (rand() % MAX_DAYS);
				neededVotes = (double)(rand() % 10 + 1) / 10.0;

				newDaysBetweenElections = (rand() % (DAYS / 2)) + 1;

				newDeputiesFromMainConsignment = (rand() % (MAX_NUMBER_OF_DEPUTIES / 2)) + (MAX_NUMBER_OF_DEPUTIES / 2);
				newDeputiesFromConsignments = newDeputiesFromMainConsignment - (rand() % (MAX_NUMBER_OF_DEPUTIES / 2));
				newMainConsignmentID = rand() % 5;

				ElectionsLaw newLaw(complexity, neededVotes, newDeputiesFromMainConsignment, newDaysBetweenElections,
					newDeputiesFromConsignments, newMainConsignmentID, consignmentList);
				lawList.push_back(newLaw);
			}
		}

	}

	bool generateDeputies(int mainConsignment, int maxNumberOfDeputies) {
		srand(clock());
		for (int i = 0; i < 5; i++) {
			if (i == mainConsignmentID)
				consignmentList[i].generateDeputies(MAX_NUMBER_OF_DEPUTIES, lawList.size());
			else
				consignmentList[i].generateDeputies(maxNumberOfDeputies, lawList.size());
		}
	}

public:
	Parliament() {
		complexityFactor = 1.0;
		neededVotesFactor = 1.0;

		daysBetweenElections = 8;
		int maxNumberOfDeputies = (rand() % (MAX_NUMBER_OF_DEPUTIES / 2)) + (MAX_NUMBER_OF_DEPUTIES / 2);
		deputiesFromConsignments = maxNumberOfDeputies;
		deputiesFromMainConsignment = 10;

		mainConsignmentID = rand() % 5;
		parliamentName = consignmentList[mainConsignmentID].getPreferredParliamentName();

		generateConsignments();
		generateLaws(NUMBER_OF_LAWS);
		generateDeputies(deputiesFromMainConsignment, deputiesFromConsignments);
	}

	bool workDay() {
		int daysSinceLastElection = 0;
		for (int day = 0; day < DAYS; day++) {
			if (daysSinceLastElection == (daysBetweenElections - 1)) {
				electNewConsignment();
			}
		}
	}

	

	bool electNewConsignment() {
		int lawsSize = lawList.size();
		vector<Law> electionLaws;
		for (int i = 0; i < lawsSize; i++) {
			if (lawList[i].getType() == 1)
				electionLaws.push_back(lawList[i]);
		}

		int electionSize = electionLaws.size();
		int pick = rand() % electionSize;

		int numberOfVotes = 0;
		for (int i = 0; i < 5; i++) {
			numberOfVotes += consignmentList[i].getVotedElectionsNumber(electionLaws[pick], lawList.size(), consignmentList);
		}

		if ((double)numberOfVotes / (deputiesFromMainConsignment + deputiesFromConsignments * 4)
			>= (electionLaws[pick].getComplexity * complexityFactor)) {

			daysBetweenElections = electionLaws[pick].getDaysBetweenElections();

		}

	}

};
