/*
 * FilePreviewStore.cpp
 *
 *  Created on: 2011-6-17
 *      Author: tinyms
 */

#include "FilePreviewStore.h"

namespace tinyms {
FilePreviewStore::FilePreviewStore() {
	// TODO Auto-generated constructor stub
	set_column_types(m_colsDef);
	this->signal_rows_reordered().connect(sigc::mem_fun(*this, &FilePreviewStore::evt_reordered));
}
Glib::RefPtr<FilePreviewStore> FilePreviewStore::create() {
	return Glib::RefPtr<FilePreviewStore>(new FilePreviewStore());
}
void FilePreviewStore::evt_reordered(const TreeModel::Path& path, const TreeModel::iterator& iter, int* new_order){
	return;
}
FilePreviewStore::~FilePreviewStore() {
	// TODO Auto-generated destructor stub
}
}
