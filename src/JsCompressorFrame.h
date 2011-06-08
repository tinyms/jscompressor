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
#include <giomm/filemonitor.h>
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
	Gtk::HBox topLayout, centerLayout, center2Layout, buttomLayout;
	/**
	 * text view
	 */
	Gtk::Entry topPath;
	Gtk::ScrolledWindow m_scrolledWindow4ConsoleWin;
	Gtk::TextView m_consoleWin;
	Gtk::Label tipSelectFile;
	Gtk::Label m_tipConsoleWin;
	Gtk::CheckButton m_jsOrCssChkbox;
	Gtk::Button selectFolderBtn, executeBtn;
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
	//
	Utils util;
	std::vector<std::string> files;
	//Glib::RefPtr<Gio::FileMonitor> logmonitor;
	Glib::RefPtr<Gtk::TextBuffer> m_logBuffer;
	std::string seletedPath;
protected:
	virtual void evt_jsOrCssChkbox_clicked();
	virtual void evt_selectFolderBtn_clicked();
	virtual void evt_executeBtn_clicked();
	virtual void evt_logfile_changed(const Glib::RefPtr<Gio::File>& file,
			const Glib::RefPtr<Gio::File>& other_file,
			Gio::FileMonitorEvent event_type);
	void scan_files();
	void listen_java_program();
	void read_logfile();
	void clear_log();
};

#endif /* JSCOMPRESSORFRAME_H_ */
