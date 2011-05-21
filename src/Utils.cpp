/*
 * Utils.cpp
 *
 *  Created on: 2011-5-21
 *      Author: tinyms
 */

#include "Utils.h"

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

std::string Utils::__APSPATH__ = "";

std::string Utils::getParentPath(const char* fileFullPath) {
	return Gio::File::create_for_path(fileFullPath)->get_parent()->get_path();
}

std::string Utils::getFileName(const char* fileFullPath){
	return Gio::File::create_for_path(fileFullPath)->get_basename();
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}
