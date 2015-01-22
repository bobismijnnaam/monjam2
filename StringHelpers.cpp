// File: StringHelpers.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <vector>
#include <string>
#include <sstream>

// Private
#include "StringHelpers.hpp"

namespace mj2 {

	std::vector<std::string> split(std::string input, std::string delimiter) {
		std::vector<std::string> result;
		if (input.find(delimiter) == std::string::npos) return {input};
		result.push_back("");

		for (char c : input) {
			std::string s(1, c);
			if (s == delimiter) {
				result.push_back("");
			} else {
				result[result.size() - 1] = result.back() + s;
			}
		}

		return result;
	}

	std::tuple<std::string, std::string> chopLeft(std::string input, std::string delimiter) {
		size_t const pos = input.find(delimiter);
		if (pos == std::string::npos) return std::make_tuple(input, "");

		std::string left = input.substr(0, pos);
		std::string right = input.substr(pos + 1, input.size());
		
		return std::make_tuple(left, right);
	}

	std::tuple<std::string, std::string> chopRight(std::string input, std::string delimiter) {
		size_t const pos = input.rfind(delimiter);
		if (pos == std::string::npos) return std::make_tuple("", input);

		std::string left = input.substr(0, pos);
		std::string right = input.substr(pos + 1, input.size());
		
		return std::make_tuple(left, right);
	}

	bool endsWith(std::string input, std::string suffix) {
		if (suffix.size() > input.size()) {
			return false;
		}
		
		if (suffix.empty() && input.empty()) {
			return true;
		}

		if (suffix.empty() || input.empty()) {
			return false;
		}
		
		int j = input.size() - 1;
		for (int i = suffix.size() - 1; i >= 0; --i) {
			if (suffix[i] != input[j])
				return false;

			j--;
		}

		return true;
	}

	bool beginsWith(std::string input, std::string prefix) {
		if (prefix.size() > input.size()) {
			return false;
		}

		if (prefix.empty() && input.empty()) {
			return true;
		}

		if (prefix.empty() || input.empty()) {
			return false;
		}

		for (size_t i = 0; i < prefix.size(); ++i) {
			if (prefix[i] != input[i]) {
				return false;
			}
		}

		return true;
	}

	bool contains(std::string input, std::string query) {
		return input.find(query, 0) != std::string::npos;
	}

	std::string trim(std::string input) {
		return trimLeft(trimRight(input));
	}

	std::string trimLeft(std::string input) {
		size_t const left = input.find_first_not_of(" \n\r\t");

		if (left == std::string::npos) {
			return "";
		}

		return input.substr(left, input.size());
	}

	std::string trimRight(std::string input) {
		size_t const right = input.find_last_not_of(" \n\r\t");
		
		if (right == std::string::npos) {
			return "";
		}

		return input.substr(0, right + 1);
	}

	std::string tos(int p) {
		std::stringstream ss;
		ss << p;
		return ss.str();
	}

	std::string tos(float p) {
		std::stringstream ss;
		ss << p;
		return ss.str();
	}

	int stoi(std::string p) {
		std::stringstream ss;
		ss << p;
		int i;
		ss >> i;
		return i;
	}

	float stof(std::string p) {
		std::stringstream ss;
		ss << p;
		float f;
		ss >> f;
		return f;
	}

	long stol(std::string p) {
		std::stringstream ss;
		ss << p;
		long l;
		ss >> l;
		return l;
	}

}
