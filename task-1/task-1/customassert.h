#pragma once

/*
*	These 'assert' functions would allow to see all errors
*	without crashing the program, if user wants so
*/

#include <iostream>
#include <string>

//	Function that displays message and closes the program when value if false
bool assertTestHard(bool value, std::string errorMessage) {
	if (!value) {
		std::cout << "Error : " << errorMessage << std::endl;
		system("pause");
		exit(1);
	}
	return true;
}

//	Function that displays message when value if false
bool assertTestSoft(bool value, std::string errorMessage) {
	if (!value) {
		std::cout << "Error : " << errorMessage << std::endl;
		return false;
	}
	return true;
}
