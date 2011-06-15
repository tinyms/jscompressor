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
void FileUtils::write(const char* fileFullPath,const char* content){
	Glib::RefPtr<Gio::File> txtfile = Gio::File::create_for_path(fileFullPath);
	if(!txtfile->query_exists()){
		txtfile->create_file()->write(content);
	}else{
		txtfile->remove();
		txtfile->create_file()->write(content);
	}
}
FileUtils::~FileUtils() {
	// TODO Auto-generated destructor stub
}

}
