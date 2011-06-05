/*
 * FilePreviewColumnDefinition.h
 *
 *  Created on: 2011-6-5
 *      Author: tinyms
 */

#ifndef FILEPREVIEWCOLUMNDEFINITION_H_
#define FILEPREVIEWCOLUMNDEFINITION_H_
#include <gtkmm.h>
class FilePreviewColumnDefinition : public Gtk::TreeModel::ColumnRecord{
public:
	Gtk::TreeModelColumn<Glib::ustring> m_file_full_path;
public:
	FilePreviewColumnDefinition();
	virtual ~FilePreviewColumnDefinition();
};

#endif /* FILEPREVIEWCOLUMNDEFINITION_H_ */
