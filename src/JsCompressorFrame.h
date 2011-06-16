/*
 * JsCompressorFrame.h
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#ifndef JSCOMPRESSORFRAME_H_
#define JSCOMPRESSORFRAME_H_

#ifndef JSCOMPRESSOR_VERSION
#define JSCOMPRESSOR_VERSION "3.0"
#endif

#ifndef WITH_JRE
#define WITH_JRE true
#endif

#include <iostream>
using namespace std;
#include <gtkmm.h>
#include <gdkmm/cursor.h>
#include <glibmm/slisthandle.h>
#include <giomm/filemonitor.h>

#include "Utils.h"
#include "FileUtils.h"
#include "FilePreviewColumnDefinition.h"

using namespace tinyms;

class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	/**
	 * layouts
	 */
	Gtk::VBox m_main_vbox;
	Gtk::HBox m_top_hbox, centerLayout, center2Layout, m_bottom_hbox;
	/**
	 * text view
	 */
	Gtk::Entry m_root_path_entry;
	Gtk::ScrolledWindow m_scrolledWindow4ConsoleWin;
	Gtk::TextView m_consoleWin;
	Gtk::Label tipSelectFile;
	Gtk::Label m_tipConsoleWin;
	Gtk::CheckButton m_jsOrCssChkbox;
	Gtk::Button selectFolderBtn, executeBtn;
	Gtk::Label m_home_label;
	Gtk::EventBox m_home_eventbox;
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
	virtual bool evt_gohome_enter(GdkEventCrossing* eb);
	virtual bool evt_gohome_clicked(GdkEventButton* eb);
	virtual void evt_jsOrCssChkbox_clicked();
	virtual void evt_selectFolderBtn_clicked();
	virtual void evt_executeBtn_clicked();
	virtual void evt_logfile_changed(const Glib::RefPtr<Gio::File>& file,
			const Glib::RefPtr<Gio::File>& other_file,
			Gio::FileMonitorEvent event_type);
	void scan_files();
	void init_logfile();
	void read_logfile();
	void clear_log();
};

#endif /* JSCOMPRESSORFRAME_H_ */
