// File: StringHelpers.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 16-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP

// Public
#include <string>
#include <vector>
#include <tuple>

// Private

namespace mj2 {

	std::vector<std::string> split(std::string input, std::string delimiter);
	std::tuple<std::string, std::string> chopLeft(std::string input, std::string delimiter);
	std::tuple<std::string, std::string> chopRight(std::string input, std::string delimiter);

	bool endsWith(std::string input, std::string suffix);
	bool beginsWith(std::string input, std::string prefix);
	bool contains(std::string input, std::string query);

	std::string trim(std::string input);
	std::string trimLeft(std::string input);
	std::string trimRight(std::string input);

	std::string tos(int p);
	std::string tos(float p);
	int stoi(std::string p);
	float stof(std::string p);
	long stol(std::string p);

}

#endif
