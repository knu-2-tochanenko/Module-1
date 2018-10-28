#pragma once

/*
*	This implementation doesn't use template (almost)
*/

#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;
using std::pair;
using std::get;

class NonTemplated {
public:
	//	For integer numbers :
	static int f(int n) {
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
	static int f(double d) {
		return ((int)(1 / sin(77 * d)) % 327);
	}

	//	For strings :
	static int f(string s) {
		int stringLength = s.length();
		int numberOfCapitalLetters = 0;
		for (int i = 0; i < stringLength; i++)
			if (('A' <= s[i]) && (s[i] <= 'Z'))
				numberOfCapitalLetters++;
		return numberOfCapitalLetters;
	}

	// For pair of doubles :
	static int f(pair<double, double> p) {
		return ((int)(f(get<1>(p)) * (f(get<0>(p)) + 3)) % 527);
	}

	//	For array of doubles :
	static int f(vector<double> v) {
		int vectorSize = v.size();
		int res = 0;
		for (int i = 0; i < vectorSize; i++)
			res += f(v[i]);
		return (res % 727);
	}

	//	For any other arguments :
	template <typename T> static  int f(T t) {
		return 7487;
	}
	static int f() {
		return 7487;
	}
};