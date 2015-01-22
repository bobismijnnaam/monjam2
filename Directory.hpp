// File: Directory.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: sa 16-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

// Public
#include <string>
#include <vector>

// Private

namespace mj2 {

	std::vector<std::string> getFiles(std::string tgtDir, std::string suffix = ""); 
	bool exists(std::string path);
	std::string folderFromPath(std::string path);
	std::string fileFromPath(std::string path);

}

#endif
