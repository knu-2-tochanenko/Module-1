#include "customassert.h"
#include <iostream>
#include <vector>

using namespace std;

class X{}x;

//	Make it true, if you want to see which functions are being used
bool DEBUG_ENABLED = false;

//	For integer numbers :
int f(int n) {
	if (DEBUG_ENABLED) cout << "Integer\n";
	if (n > 0) {
		int res = 1;
		for (int i = 2; i <= n; i++)
			res *= i;
		res = res + n - 1;
		res %= 127;
		return res;
	}
	else
		return ((n * n * n * n * n) % 227);
}

//	For double numbers :
int f(double d) {
	if (DEBUG_ENABLED) cout << "Double\n";
	return ((int)(1 / sin(77 * d)) % 327);
}

//	For strings :
int f(string s) {
	if (DEBUG_ENABLED) cout << "String\n";
	int stringLength = s.length();
	int numberOfCapitalLetters = 0;
	for (int i = 0; i < stringLength; i++)
		if (('A' <= s[i]) && (s[i] <= 'Z'))
			numberOfCapitalLetters++;
	return numberOfCapitalLetters;
}

// For pair of doubles :
template <typename T, typename F> int f(pair<T, F> p) {
	if (DEBUG_ENABLED) cout << "Pair\n";
	return ((int)(f(p.first) * (f(p.second) + 3)) % 527);
}

//	For array of doubles :
template <typename T> int f(vector<T> v) {
	if (DEBUG_ENABLED) cout << "Vector\n";
	int vectorSize = v.size();
	int res = 0;
	for (int i = 0; i < vectorSize; i++)
		res += f(v[i]);
	return (res % 727);
}

//	For any other arguments :
template <typename T> int f(T t) {
	if (DEBUG_ENABLED) cout << "Other\n";
	return 7487;
}

int f() {
	if (DEBUG_ENABLED) cout << "Empty\n";
	return 7487;
}

void testFunction() {
	cout << "\nEmpty function f() :\n";
	if (assertTestSoft(f() == 7487, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nInteger function f(7) :\n";
	if (assertTestSoft(f(7) == 93, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nNegative integer function f(-15) :\n";
	if (assertTestSoft(f(-15) == -60, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nDouble function f(3.14) :\n";
	if (assertTestSoft(f(3.14) == 8, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nString function f(str) :\n";
	string str = "That WaS uNexPectEd";
	if (assertTestSoft(f(str) == 6, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nPair function f(p) :\n";
	pair<double, int> p(3.14, 4);
	if (assertTestSoft(f(p) == 240, "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nList (vector) function f(v) :\n";
	vector <double> v{ 2.14, 3, 3.14, 3.22, 6.4 };
	if (assertTestSoft(f(v), "Wrong value!"))
		cout << "Passed!\n";

	cout << "\nOther function f(x) :\n";
	if (assertTestSoft(f(x), "Wrong value!"))
		cout << "Passed!\n";
}

int main() {
	cout << "You will get tests for all of\ndifferent kinds of functions.\n\n";
	testFunction();

	system("pause");
	return 0;
}