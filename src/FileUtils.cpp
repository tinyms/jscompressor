/*
 * FileUtils.cpp
 *
 *  Created on: 2011-6-14
 *      Author: tinyms
 */
#include <stdlib.h>
#include <iostream>
#include "FileUtils.h"
using namespace std;
namespace tinyms {

FileUtils::FileUtils() {
	// TODO Auto-generated constructor stub

}
Glib::ustring FileUtils::escapeBlank(Glib::ustring path) {
	Glib::ustring winPath("");
	Glib::RefPtr<Glib::Regex> rpl = Glib::Regex::create(" ");
	std::vector<Glib::ustring> arr = rpl->split(path);
	for (size_t k = 0; k < arr.size(); k++) {
		if (k != 0) {
			winPath.append("\\ ");
		}
		winPath.append(arr[k]);
	}
	return winPath;
	//Glib::ustring result = rpl->replace(path.c_str(),path.size(),0,rplStr);
	//std::cout<<result<<std::endl;
}
Glib::ustring FileUtils::read(Glib::ustring fileFullPath) {
	Glib::RefPtr<Gio::File> txtfile = Gio::File::create_for_path(fileFullPath);
	char* content;
	gsize length;
	txtfile->load_contents(content, length);
	Glib::ustring txtcontent(content);
	return txtcontent;
}
void FileUtils::write(const char* fileFullPath, const char* content) {
	Glib::RefPtr<Gio::File> txtfile = Gio::File::create_for_path(fileFullPath);
	if (!txtfile->query_exists()) {
		txtfile->create_file()->write(content);
	} else {
		txtfile->remove();
		txtfile->create_file()->write(content);
	}
}
void FileUtils::config_read(std::map<std::string, std::string>& config) {
	std::string config_path = __APSPATH__ + "/_config_";
	cJSON *json = cJSON_Parse(read(config_path).c_str());
	if(!json)return;
	if (json->type == cJSON_Object) {
		cJSON* selectedPath = cJSON_GetObjectItem(json,"preSelectedPath");
		config["preSelectedPath"] = selectedPath->valuestring;
		//std::cout<<config["preSelectedPath"]<<std::endl;
	}
}
void FileUtils::config_write(std::map<std::string, std::string>& config) {
	cJSON *root;
	char* json;
	root = cJSON_CreateObject();
	std::map<std::string, std::string>::iterator it;
	for (it = config.begin(); it != config.end(); it++) {
		std::string key = (*it).first;
		std::string value = (*it).second;
		cJSON_AddStringToObject(root,key.c_str(),value.c_str());
	}
	json = cJSON_Print(root);
	std::string config_path = __APSPATH__ + "/_config_";
	write(config_path.c_str(), json);
	free(json);
}
std::string FileUtils::__APSPATH__ = "";

Glib::RefPtr<Gio::File> FileUtils::parent(const char* fileFullPath) {
	return Gio::File::create_for_path(fileFullPath)->get_parent();
}

Glib::RefPtr<Gio::File> FileUtils::touch(const char* fileFullPath) {
	return Gio::File::create_for_path(fileFullPath);
}
void FileUtils::walkFiles(std::string currentDir, std::string include,
		std::string exclude, std::vector<std::string>& files) {
	Glib::Dir dir(currentDir);
	Glib::PatternSpec regx(include);
	Glib::PatternSpec regx1(exclude);
	for (Glib::DirIterator it = dir.begin(); it != dir.end(); ++it) {
		std::string file = *it;
		std::string fullPath = currentDir + "/" + file;
		if (regx.match(file) && !regx1.match(file)) {
			files.push_back(fullPath);
		}
		Glib::RefPtr<Gio::File> dirOrFile =
				Gio::File::create_for_path(fullPath);
		if (dirOrFile->query_file_type() == Gio::FILE_TYPE_DIRECTORY) {
			walkFiles(fullPath, include, exclude, files);
		}
	}
	dir.close();
}
FileUtils::~FileUtils() {
	// TODO Auto-generated destructor stub
}

}
