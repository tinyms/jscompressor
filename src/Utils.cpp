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

std::string Utils::getFileName(const char* fileFullPath) {
	return Gio::File::create_for_path(fileFullPath)->get_basename();
}
void Utils::walkFiles(std::string currentDir,std::string spec, std::vector<std::string>& files) {
	Glib::Dir dir(currentDir);
	Glib::PatternSpec regx(spec);
	for (Glib::DirIterator it = dir.begin(); it != dir.end(); ++it) {
		std::string file = *it;
		std::string fullPath = currentDir+"/"+file;
		if(regx.match(file)){
			files.push_back(fullPath);
		}
		Glib::RefPtr<Gio::File> dirOrFile = Gio::File::create_for_path(fullPath);
		if(dirOrFile->query_file_type()==Gio::FILE_TYPE_DIRECTORY){
			walkFiles(fullPath,spec,files);
		}
	}
	dir.close();
}
Utils::~Utils() {
	// TODO Auto-generated destructor stub
}
