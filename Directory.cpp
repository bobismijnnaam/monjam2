// File: Directory.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: su 17-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <string>
#include <dirent.h>
#include <vector>
#include <iostream>

// Private
#include "Directory.hpp"
#include "StringHelpers.hpp"

namespace mj2 {

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix) {
		DIR *dir;
		struct dirent *ent;
		std::vector<std::string> dirs;

		if ((dir = opendir(tgtDir.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				std::string dirStr{ent->d_name};
				if (mj2::endsWith(dirStr, suffix) || suffix.empty())  {
					dirs.push_back(dirStr);
				}
			}
			closedir(dir);
			return dirs;
		} else {
			std::cout << "Error opening directory: \"" << tgtDir << "\"";
			return {};
		}
	}

	bool exists(std::string path) {
		auto folder = folderFromPath(path);
		auto file = fileFromPath(path);
		auto files = getFiles(folder);
		
		for (auto f : files) {
			if (f == file) {
				return true;
			}
		}

		return false;
	}

	std::string folderFromPath(std::string path) {
		std::tuple<std::string, std::string> result;
			
		if (mj2::contains(path, "\\")) {
			result = mj2::chopRight(path, "\\");
		} else if (mj2::contains(path, "/")) {
			result = mj2::chopRight(path, "/");
		} else {
			return "";
		}

		return std::get<0>(result);
	}

	std::string fileFromPath(std::string path) {
		std::vector<std::string> result;

		if (mj2::contains(path, "\\")) {
			result = mj2::split(path, "\\");
		} else if (mj2::contains(path, "/")) {
			result = mj2::split(path, "/");
		} else {
			return "";
		}

		if (result.size() > 0) {
			return result[result.size() - 1];
		} else {
			return "";
		}
	}

}
