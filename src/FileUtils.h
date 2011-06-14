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
namespace tinyms {

class FileUtils {
public:
	FileUtils();
	virtual ~FileUtils();
public:
	Glib::ustring escapeBlank(Glib::ustring& path);
};

}

#endif /* FILEUTILS_H_ */
