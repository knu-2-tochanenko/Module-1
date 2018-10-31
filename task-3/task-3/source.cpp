#include <iostream>
#include <memory>
#include <vector>

using namespace std;

double S;

enum type { BASE, BASE1, BASE2, ALPHA, BETA, GAMMA, DELTA };

class Base {
public:
	virtual type getType() { return BASE; }
};

class Base2 : public Base {
private:
	int N;
	static int MaxN;

public:
	Base2() {
		N = MaxN;
		MaxN++;
	}
	~Base2() {
		S = S / 2 - N;
	}
	virtual type getType() { return BASE2; }
	virtual void foo() = 0;
};
int Base2::MaxN = 1;

class Gamma : public Base2 {
private:
	int N;
	static int MaxN;
public:
	Gamma() {
		N = MaxN;
		MaxN++;
	}
	~Gamma() {
		S = S - N;
	}
	virtual type getType() { return GAMMA; }
	void foo() override {
		cout << "wow";
	}
};
int Gamma::MaxN = 1;

class Delta : public Base2 {
private:
	int N;
	static int MaxN;
public:
	Delta() {
		N = MaxN;
		MaxN++;
	}
	~Delta() {
		S = S + 3 * N - 27;
	}
	virtual type getType() { return DELTA; }
	void foo() override {
		cout << "wow";
	}
};
int Delta::MaxN = 1;

class Base1 : public Base {
private:
	int N;
	static int MaxN;

	Base1* base1;
	Base2* base2_1;
	Base2* base2_2;

public:
	Base1() {
		N = MaxN;
		MaxN++;
	}
	~Base1() {
		S = 3*S + N + 27;
	}
	virtual type getType() { return BASE1; }
	virtual void foo() = 0;

	void setBase1(Base1 *base1) {
		this->base1 = base1;
	}

	void setBase2_1(Base2* base2_1) {
		this->base2_1 = base2_1;
	}

	void setBase2_2(Base2* base2_2) {
		this->base2_2 = base2_2;
	}

};
int Base1::MaxN = 1;

class Alpha : public Base1 {
private:
	int N;
	static int MaxN;

	Base1* base1;
	Base2* base2_1;
	Base2* base2_2;

public:
	Alpha() {
		N = MaxN;
		MaxN++;
	}

	~Alpha() {
		S = S - 2 * N + 5;
	}
	virtual type getType() { return ALPHA; }
	void foo() override {
		cout << "wow";
	}
};
int Alpha::MaxN = 1;

class Beta : public Base1 {
private:
	int N;
	static int MaxN;

	Base1* base1;
	Base2* base2_1;
	Base2* base2_2;

public:
	Beta() {
		N = MaxN;
		MaxN++;
	}

	~Beta() {
		S = S - N;
	}
	virtual type getType() { return BETA; }
	void foo() override {
		cout << "wow";
	}
};
int Beta::MaxN = 1;

double predictValue(vector<Base*> vec) {
	double res = 0.0;
	int numberOfElements[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int vecSize = vec.size();

	for (int i = 0; i < vecSize; i++) {
		switch (vec[i]->getType()) {
		case BASE1:
			numberOfElements[BASE1]++;
			break;
		case BASE2:
			numberOfElements[BASE2]++;
			break;
		case ALPHA:
			numberOfElements[ALPHA]++;
			numberOfElements[BASE1]++;
			break;
		case BETA:
			numberOfElements[BETA]++;
			numberOfElements[BASE1]++;
			break;
		case GAMMA:
			numberOfElements[GAMMA]++;
			numberOfElements[BASE2]++;
			break;
		case DELTA:
			numberOfElements[DELTA]++;
			numberOfElements[BASE2]++;
			break;
		default:
			break;
	}
	}

	for (int i = 0; i < vecSize; i++) {
		switch (vec[i]->getType()) {
		case BASE1:
			res = 3 * res + numberOfElements[BASE1] + 27;
			numberOfElements[BASE1]--;
			break;
		case BASE2:
			res = res / 2 - numberOfElements[BASE2];
			numberOfElements[BASE2]--;
			break;
		case ALPHA:
			res = res - 2 * numberOfElements[ALPHA] + 5;
			numberOfElements[ALPHA]--;
			res = 3 * res + numberOfElements[BASE1] + 27;
			numberOfElements[BASE1]--;
			break;
		case BETA:
			res = res - numberOfElements[BETA];
			numberOfElements[BETA]--;
			res = 3 * res + numberOfElements[BASE1] + 27;
			numberOfElements[BASE1]--;
			break;
		case GAMMA:
			res = res - numberOfElements[GAMMA];
			numberOfElements[GAMMA]--;
			res = res / 2 - numberOfElements[BASE2];
			numberOfElements[BASE2];
			break;
		case DELTA:
			res = res + 3 * numberOfElements[DELTA] - 27;
			numberOfElements[DELTA]--;
			res = res / 2 - numberOfElements[BASE2];
			numberOfElements[BASE2]--;
			break;
		default:
			break;
		}
	}
	return res;
}

int main() {
	S = 0.0;
	{
		vector<Base*> vec;
		shared_ptr<Base1> p1 = make_shared<Alpha>();
		shared_ptr<Base1> p2 = make_shared<Beta>();

		shared_ptr<Base2> p3 = make_shared<Gamma>();
		shared_ptr<Base2> p4 = make_shared<Delta>();

		p2->setBase1(p1.get());
		p2->setBase2_1(p3.get());
		p2->setBase2_2(p4.get());

		vec.push_back(p4.get());
		vec.push_back(p3.get());
		vec.push_back(p2.get());
		vec.push_back(p1.get());

		cout << predictValue(vec) << " EXPECTED!\n";
	}

	cout << S << " GOT!\n";
	system("pause");
	return 0;
}