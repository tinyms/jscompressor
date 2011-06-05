/*
 * JsCompressorFrame.h
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#ifndef JSCOMPRESSORFRAME_H_
#define JSCOMPRESSORFRAME_H_

#include <iostream>
using namespace std;
#include <gtkmm.h>
#include <glibmm/slisthandle.h>
#include "Utils.h"
#include "FilePreviewColumnDefinition.h"
class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	/**
	 * layouts
	 */
	Gtk::VBox mainLayout;
	Gtk::HBox topLayout,centerLayout,buttomLayout;
	/**
	 * text view
	 */
	Gtk::Entry topPath;
	Gtk::Label tipSelectFile;
	Gtk::FileChooserButton fileChooserBtn;
	Gtk::Button selectFolderBtn,executeBtn;
	/**
	 * dialogs
	 */
	/**
	 * grid
	 */
	FilePreviewColumnDefinition m_column_def;
	Glib::RefPtr<Gtk::ListStore> m_filePreviewStore;
	Gtk::TreeView m_filePreviewGrid;
	Gtk::ScrolledWindow m_ScrolledWindow4FilePreview;
protected:
	virtual void evt_selectFolderBtn_clicked();
	virtual void evt_executeBtn_clicked();
};

#endif /* JSCOMPRESSORFRAME_H_ */
