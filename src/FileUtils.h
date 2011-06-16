/*
 * FileUtils.h
 *
 *  Created on: 2011-6-14
 *      Author: tinyms
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_
#include <stdlib.h>
#include <glibmm/regex.h>
#include <glibmm/ustring.h>
#include <giomm/file.h>
#include "cJSON/cJSON.h"
using namespace std;
namespace tinyms {

class FileUtils {
public:
	FileUtils();
	virtual ~FileUtils();
public:
	static std::string __APSPATH__;
public:
	static Glib::ustring escapeBlank(Glib::ustring path);
	static Glib::ustring read(Glib::ustring fileFullPath);
	static void write(const char* fileFullPath,const char* content);
	static void config_read(std::map<std::string,std::string>& config);
	static void config_write(std::map<std::string,std::string>& config);

	static Glib::RefPtr<Gio::File> parent(const char* fileFullPath);
	static Glib::RefPtr<Gio::File> touch(const char* fileFullPath);
	static void walkFiles(std::string currentDir,std::string include,std::string exclude,std::vector<std::string>& files);
};

}

#endif /* FILEUTILS_H_ */
