/*
 * Utils.h
 *
 *  Created on: 2011-5-21
 *      Author: tinyms
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <giomm/file.h>
#include <glibmm/ustring.h>

class Utils {
public:
	static std::string __APSPATH__;
public:
	Utils();
	virtual ~Utils();
public:
	std::string getParentPath(const char*);
	std::string getFileName(const char*);
};

#endif /* UTILS_H_ */
