/*
 * FileUtils.h
 *
 *  Created on: 2011-6-14
 *      Author: tinyms
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_
#include <glibmm/regex.h>
#include <glibmm/ustring.h>
#include <giomm/file.h>
namespace tinyms {

class FileUtils {
public:
	FileUtils();
	virtual ~FileUtils();
public:
	static Glib::ustring escapeBlank(Glib::ustring path);
	static Glib::ustring read(Glib::ustring fileFullPath);
	static void write(const char* fileFullPath,const char* content);
};

}

#endif /* FILEUTILS_H_ */
