#pragma once

/*
*	This implementation uses templates
*/

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include <type_traits>

using std::string;
using std::vector;
using std::pair;
using std::get;
using std::is_same;

class Templated {
public:

	//	If there is 0 arguments
	static int f() {
		return 7487;
	}

	template <typename T> static int f(T t) {
		if (is_same<int, T>::value) {
			//	For integer numbers :
			if (t > 0) {
				int res = 1;
				for (int i = 2; i <= t; i++)
					res *= i;
				res = res + t - 1;
				res %= 127;
				return res;
			}
			else
				return ((t * t * t * t * t) % 227);
		}
		else if (is_same<double, T>::value) {
			//	For double numbers :
			return ((int)(1 / sin(77 * t)) % 327);
		}
		else
			return 7487;
	}

	template <class C> static int(C t) {
		if (is_same<string, T>::value) {
			//	For strings :
			int stringLength = t.length();
			int numberOfCapitalLetters = 0;
			for (int i = 0; i < stringLength; i++)
				if (('A' <= t[i]) && (t[i] <= 'Z'))
					numberOfCapitalLetters++;
			return numberOfCapitalLetters;
		}
		else if (is_same<pair<double, double>, T>::value) {
			// For pair of doubles :
			return ((int)(f(get<1>(t)) * (f(get<0>(t)) + 3)) % 527);
		}
		else if (is_same<vector<double>, T>::value) {
			//	For array of doubles :
			int vectorSize = t.size();
			int res = 0;
			for (int i = 0; i < vectorSize; i++)
				res += f(t[i]);
			return (res % 727);
		}
	}
	
};