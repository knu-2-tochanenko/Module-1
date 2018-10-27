#pragma once

/*
*	This implementation doesn't use template (almost)
*/

#include <iostream>
#include <string>
#include <algorithm>

using std::string;

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
	static int f(double a, double b) {
		return ((int)(f(b) * (f(a) + 3)) % 527);
	}

	//	For array of doubles :
	static int f(int numberOfElements, double *v) {
		int res = 0;
		for (int i = 0; i < numberOfElements; i++)
			res += f(v[i]);
		return (res % 727);
	}

	//	For any other arguments :
	template <typename T> static  int f(T t) {
		return 7487;
	}
};