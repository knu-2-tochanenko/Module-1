#pragma once


#include <iostream>
#include <string>
#include <list>
#include <queue>

#include <random>
#include <time.h>

using std::string;
using std::vector;
using std::queue;
using std::cout;
using std::endl;
using std::pair;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	int singlePartyDeputies;		/*	Number of deputies from main party,
											higher than from another parties */
	int mainPartyDeputies;		//	Number of deputies from non-main party
	int mainPartyID;				//	Main party 
	bool *preferredParty;		//	Preferred parties for this law

public:
	//	Constructor. Only partyList is needed for GENERATING preferredParties
	ElectionsLaw(int complexity, double neededVotes, int daysBetweenElections,
		int mainPartyDeputies, int singlePartyDeputies, int mainPartyID,
		Party *partyList) {

		this->complexity = complexity;
		this->neededVotes = neededVotes;

		this->ID = MaxID;
		MaxID++;

		this->electionTerm = daysBetweenElections;
		this->singlePartyDeputies = singlePartyDeputies;
		this->mainPartyDeputies = mainPartyDeputies;
		this->mainPartyID = mainPartyID;

		int numberOfParties = 5;
		preferredParty = new bool[numberOfParties];
		//	randomly support parties
		srand(clock());
		for (int i = 0; i < numberOfParties; i++)
			if (((rand() % 3) != 0) || (this->mainPartyID == partyList[i].getID()))
				preferredParty[i] = true;
			else
				preferredParty[i] = false;
	}

	//	More getters
	int getElectionTerm() { return electionTerm; }
	int getMainPartyDeputies() { return singlePartyDeputies; }
	int getSinglePartyDeputies() { return mainPartyDeputies; }
	int getMainParty() { return mainPartyID; }
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
	bool isPartyPreferred(int ID) {
		return (preferredParty[ID]);
	}

	//	Check whether specific Party is preferred for this law
	bool isPreferred(Party party) {
		return preferredParty[party.getID()];
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr double SUPPORT_COEFF = 0.33;

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
	bool voteForParty(ElectionsLaw law, int lawsSize, int electSize, int workSize, Party *allParties) {
		int mainParty = law.getMainParty();

		double totalNumberOfSameLaws = 0.0;

		for (int i = 0; i < lawsSize; i++)
			if ((lawCoef[i])
				&& (allParties[mainParty].standardLawVote(i)))
				totalNumberOfSameLaws += 1.0;
		for (int i = 0; i < electSize; i++)
			if ((lawCoef[i])
				&& (allParties[mainParty].electLawVote(i)))
				totalNumberOfSameLaws += 1.0;
		for (int i = 0; i < workSize; i++)
			if ((lawCoef[i])
				&& (allParties[mainParty].workLawVote(i)))
				totalNumberOfSameLaws += 1.0;

		return (((double)lawsSize / totalNumberOfSameLaws) >= SUPPORT_COEFF);
	}

	bool standardLawVote(int lawID) { return lawCoef[lawID]; }
	bool electLawVote(int lawID) { return electCoef[lawID]; }
	bool workLawVote(int lawID) { return workCoef[lawID]; }

};

int Deputy::MaxID = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr int MAX_COEFFICIENT = 5;

class Party {
private:

	string name;					//	Name of the party
	string motto;					//	Motto of current party
	string parliamentName;	//	Preferred name of the Parliament

	int ID;
	static int MaxID;

	vector<Deputy> deputiesList;				//	List of deputies
	bool *lawCoef;		// true - law is preferred, if else - is not
	bool *electCoef;	// true - law is preferred, if else - is not
	bool *workCoef;		// true - law is preferred, if else - is not

public:
	Party() {};
	Party(string name, string moto, string preferredParliamentName) {
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
	int electVotesNumber(ElectionsLaw law, int lawsSize, int electSize, int workSize, Party *allParties) {
		int res = 0;
		int deputiesSize = deputiesList.size();
		for (int i = 0; i < deputiesSize; i++)
			if (deputiesList[i].voteForParty(law, lawsSize, electSize, workSize, allParties))
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

int Party::MaxID = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const int LAWS = 32;			//	Max number of standard laws
const int ELECTIONS = 5;		//	Max number of election laws
const int WORKING = 5;			//	Max number of working laws

const int DEPUTIES = 10;		//	Max number of deputies from each party
const int PENDING_LAWS = 5;		//	Max number of pending laws

const int MAX_DAYS = 5;			//	
const int DAYS = 256;

class Parliament {
private:

	double complexityFactor;
	double neededVotesFactor;

	int electionTerm;
	int mainPartyDeputies;
	int singlePartyDeputies;

	string parliamentName;						//	Name of current Parliament (may change with elected party)
	int mainPartyID;							//	Main party in Parliament
	Party partyList[5];		//	List of parties
	bool partyAvi[5];
	vector<Law> lawList;						//	List of all laws. Can't be changed
	bool lawStAvi[LAWS];
	vector<ElectionsLaw> electionLawList;		//	List of all election laws
	bool electionLawAvi[ELECTIONS];
	vector<WorkingProcessLaw> workingLawList;	//	List of all working laws
	bool workingLawAvi[WORKING];
	
	struct PartyInit {
		string moto;
		string name;
		string parliamentName;

		void set(string moto, string name, string parliamentName) {
			this->moto = moto;
			this->name = name;
			this->parliamentName = parliamentName;
		}

	};

	//	There are 5 different parties
	bool generateParties() {

		PartyInit strings[5];

		strings[0].set("For our country!", "R.E.D.", "The Central Committee");
		strings[1].set("For the Queen!", "W.H.I.T.E.", "The White Castle");
		strings[2].set("In Dog we trust!", "The Dog-gists", "Bob's house");
		strings[3].set("Pray for iKakashki!", "Applies", "An innovative place to live");
		strings[4].set("HTML is not a programming language!", "ANTI-HTML", "VIM");

		for (int i = 0; i < 5; i++) {
			Party newParty(strings[i].name, strings[i].moto, strings[i].parliamentName);
			partyList[i] = newParty;
			partyAvi[i] = true;
		}
		return true;
	}

	bool generateLaws(int numberOfLaws) {
		srand(clock());
		int randomValue, complexity, daysBetweenElections, newMainPartyDeputies,
			newSinglePartyDeputies, newMainPartyID, newTerm;
		double neededVotes, newComplexityFactor, newNeededVotesFactor;

		for (int i = 0; i < LAWS; i++) {
			//	Generate standard law
			complexity = (rand() % MAX_DAYS);
			neededVotes = (double)(rand() % 10 + 1) / 10.0;
			Law newLaw(complexity, neededVotes);
			lawList.push_back(newLaw);

			lawStAvi[i] = true;
		}
		for (int i = 0; i  < ELECTIONS; i++) {
			//	Generate elections law
			complexity = (rand() % MAX_DAYS);
			neededVotes = (double)(rand() % 10 + 1) / 10.0;

			newTerm = (rand() % (DAYS / 2)) + 1;

			newMainPartyDeputies = (rand() % (DEPUTIES / 2)) + (DEPUTIES / 2);
			newSinglePartyDeputies = newMainPartyDeputies - (rand() % (DEPUTIES / 2));
			newMainPartyID = rand() % 5;

			ElectionsLaw newLaw(complexity, neededVotes, newMainPartyDeputies, newTerm,
				newSinglePartyDeputies, newMainPartyID, partyList);
			electionLawList.push_back(newLaw);

			electionLawAvi[i] = true;
		}
		for (int i = 0; i < WORKING; i++) {
			//	Generate working process law
			complexity = (rand() % MAX_DAYS);
			neededVotes = (double)(rand() % 10 + 1) / 10.0;

			newComplexityFactor = (double)(rand() % 20 + 1) / 10.0;
			newNeededVotesFactor = (double)(rand() % 10 + 1) / 10.0;
			WorkingProcessLaw newLaw(complexity, neededVotes, newComplexityFactor, newNeededVotesFactor);
			workingLawList.push_back(newLaw);

			workingLawAvi[i] = true;
		}
	}

	bool generateDeputies(int mainParty, int maxNumberOfDeputies) {
		srand(clock());
		for (int i = 0; i < 5; i++) {
			if (i == mainPartyID)
				partyList[i].generateDeputies(DEPUTIES, lawList.size(), electionLawList.size(), workingLawList.size());
			else
				partyList[i].generateDeputies(maxNumberOfDeputies, lawList.size(), electionLawList.size(), workingLawList.size());
		}
	}

public:
	Parliament() {
		complexityFactor = 1.0;
		neededVotesFactor = 1.0;

		electionTerm = 8;
		int maxNumberOfDeputies = (rand() % (DEPUTIES / 2)) + (DEPUTIES / 2);
		singlePartyDeputies = maxNumberOfDeputies;
		mainPartyDeputies = 10;

		mainPartyID = rand() % 5;
		parliamentName = partyList[mainPartyID].getParliamentName();

		generateParties();
		generateLaws(LAWS);
		generateDeputies(mainPartyDeputies, singlePartyDeputies);
	}

	bool workDay() {
		srand(clock());
		vector< pair<int,int> > pendingSt;			//	<Law ID, number of processed days>
		vector< pair<int, int> > pendingWorking;	//	<Law ID, number of processed days>

		int pendingLaws = 0;
		
		int daysSinceLastElection = 0;
		for (int day = 0; day < DAYS; day++) {
			//	If it's time to make an election!
			if (daysSinceLastElection == (electionTerm - 1)) {
				electNewParty();
			}

			// If there is less then PENDING_LAWS laws are being processed
			if (pendingLaws < PENDING_LAWS) {
				//	Decide what type of law to process
				int type = rand() % 2;
				if (type == 0) {	//	Standard type
					for (int i = 0; i < LAWS; i++)
						if (lawStAvi[i]) {
							pendingSt.push_back(pair<int, int>(i, 0));
							pendingLaws++;
							lawStAvi[i] = false;
						}
				}
				else {				//	Working type
					for (int i = 0; i < WORKING; i++)
						if (workingLawAvi[i]) {
							pendingWorking.push_back(pair<int, int>(i, 0));
							pendingLaws++;
							workingLawAvi[i] = false;
						}
				}
			}

			//	Check if some of laws have been fully processed
			int pendingStSize = pendingSt.size();
			int pendingWorkSize = pendingWorking.size();
			if (pendingStSize != 0)
				for (int i = 0; i < pendingStSize; i++) {
					//	The law is fully processed
					if (pendingSt[i].second >= (lawList[pendingSt[i].first].getComplexity() * complexityFactor)) {

						//	OUTPUT
						cout << lawList[pendingSt[i].first].getIDString << " law is processed and it has been ";

						//	Check for success
						int totalVotes = 0, totalParties = 5;
						for (int j = 0; j < 5; j++)
							if (partyAvi[i]) {
								if (partyList[i].standardLawVote(pendingSt[i].first))
									totalVotes++;
							}
							else
								totalParties--;

						if (((double)totalVotes / totalParties) >= lawList[pendingSt[i].first].getNeededVotes())
							cout << "approved!\n";	//	OUTPUT
						else
							cout << "denied!\n";	//	OUTPUT

						// Delete law from pending list
						pendingSt.erase(pendingSt.begin() + i);
						pendingStSize--;
						i--;
					}
				}

			if (pendingWorkSize != 0)
				for (int i = 0; i < pendingWorkSize; i++) {
					//	The law is fully processed
					if (pendingWorking[i].second >= (workingLawList[pendingWorking[i].first].getComplexity() * complexityFactor)) {

						//	OUTPUT
						cout << workingLawList[pendingWorking[i].first].getIDString << " law is processed and it has been ";

						//	Check for success
						int totalVotes = 0, totalParties = 5;
						for (int j = 0; j < 5; j++)
							if (partyAvi[i]) {
								if (partyList[i].standardLawVote(pendingWorking[i].first))
									totalVotes++;
							}
							else
								totalParties--;

						if (((double)totalVotes / totalParties) >= workingLawList[pendingWorking[i].first].getNeededVotes()) {
							cout << "approved!\n";	//	OUTPUT

							complexityFactor = workingLawList[pendingWorking[i].first].getNewComplexityFactor();
							neededVotesFactor = workingLawList[pendingWorking[i].first].getNewNeededVotesFactor();

						}
						else
							cout << "denied!\n";	//	OUTPUT

						// Delete law from pending list
						pendingWorking.erase(pendingWorking.begin() + i);
						pendingWorkSize--;
						i--;
					}
				}

			//	Add one day to all pending laws
			if (pendingStSize != 0)
				for (int i = 0; i < pendingStSize; i++)
					pendingSt[i].second++;
			if (pendingWorkSize != 0)
				for (int i = 0; i < pendingWorkSize; i++)
					pendingWorking[i].second++;
		}
	}

	
	//	Picks random election law
	bool electNewParty() {
		int electSize = electionLawList.size();
		srand(clock());

		int numberOfLeftLaws = electSize;
		for (int i = 0; i < electSize; i++)
			if (!electionLawAvi[i])
				numberOfLeftLaws--;

		//	If all of the election law have been processed
		if (numberOfLeftLaws == 0)
			return false;

		bool gotLaw = false;
		int electLaw;
		while (!gotLaw) {
			electLaw = rand() % electSize;
			if (electionLawAvi[electLaw])
				gotLaw = true;
		}
		

		int totalVotes = 0;
		int partySize = 5;
		for (int i = 0; i < partySize; i++) {
			totalVotes += partyList[i].electVotesNumber(electionLawList[electLaw], lawList.size(),
				electSize, workingLawList.size(), partyList);
		}
		
		int deputiesSize = mainPartyDeputies + singlePartyDeputies * 4;
		if (((double)totalVotes / deputiesSize) >= electionLawList[electLaw].getNeededVotes()) {

			mainPartyID = electionLawList[electLaw].getMainParty();
			parliamentName = partyList[mainPartyID].getParliamentName();

			electionTerm = electionLawList[electLaw].getElectionTerm();
			//	New number of deputies from main party
			int newMainPartyDeputies = electionLawList[electLaw].getMainPartyDeputies();
			if (newMainPartyDeputies > mainPartyDeputies)
				for (int i = 0; i < newMainPartyDeputies - mainPartyDeputies; i++)
					partyList[mainPartyID].addDeputy(lawList.size(), electionLawList.size(), workingLawList.size());
			else if (newMainPartyDeputies < mainPartyDeputies)
				for (int i = 0; i < mainPartyDeputies - newMainPartyDeputies; i++)
					partyList[mainPartyID].removeDeputy(lawList.size(), electionLawList.size(), workingLawList.size());
			mainPartyDeputies = newMainPartyDeputies;

			//	New number of deputies from other parties
			int newSinglePartyDeputies = electionLawList[electLaw].getSinglePartyDeputies();
			for (int j = 0; j < 5; j++)
				if (j != mainPartyID) {
					if (newSinglePartyDeputies > singlePartyDeputies)
						for (int i = 0; i < newSinglePartyDeputies - mainPartyDeputies; i++)
							partyList[j].addDeputy(lawList.size(), electionLawList.size(), workingLawList.size());
					else if (newSinglePartyDeputies < singlePartyDeputies)
						for (int i = 0; i < mainPartyDeputies - newSinglePartyDeputies; i++)
							partyList[j].removeDeputy(lawList.size(), electionLawList.size(), workingLawList.size());
				}
			singlePartyDeputies = newSinglePartyDeputies;

			//	Get all supported parties
			for (int i = 0; i < 5; i++)
				partyAvi[i] = electionLawList[electLaw].isPartyPreferred(i);
			return true;
		}
		else
			return false;
	}
};
