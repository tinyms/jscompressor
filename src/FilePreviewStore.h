/*
 * FilePreviewStore.h
 *
 *  Created on: 2011-6-17
 *      Author: tinyms
 */

#ifndef FILEPREVIEWSTORE_H_
#define FILEPREVIEWSTORE_H_
#include <iostream>
#include <gtkmm.h>
#include "FilePreviewColumnDefinition.h"
using namespace std;
namespace tinyms {
class FilePreviewStore: public Gtk::ListStore {

public:
	static Glib::RefPtr<FilePreviewStore> create();
	FilePreviewColumnDefinition m_colsDef;
	virtual ~FilePreviewStore();
protected:
	FilePreviewStore();
	virtual void evt_reordered(const TreeModel::Path& path, const TreeModel::iterator& iter, int* new_order);
};
}
#endif /* FILEPREVIEWSTORE_H_ */
