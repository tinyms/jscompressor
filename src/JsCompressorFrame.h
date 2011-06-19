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
#include <gdk/gdkkeysyms-compat.h>
#include <giomm/filemonitor.h>

#include "FileUtils.h"
#include "FilePreviewColumnDefinition.h"
#include "FilePreviewStore.h"
using namespace tinyms;

class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	/**
	 * layouts
	 */
	Gtk::VBox m_main_vbox,m_toolbar4treeview_vbox;
	Gtk::HBox m_top_hbox, m_center_head_hbox, m_center_foot_hbox, m_bottom_hbox;
	/**
	 * text view
	 */
	Gtk::Entry m_root_path_entry;
	Gtk::ScrolledWindow m_scrolledWindow4ConsoleWin;
	Gtk::TextView m_consoleWin;
	Gtk::Label m_selected_path_label;
	Gtk::Label m_tipConsoleWin;
	Gtk::CheckButton m_jsOrCssChkbox;
	Gtk::Button m_select_folder_btn, m_compress_btn;
	Gtk::Label m_home_label;
	Gtk::EventBox m_home_eventbox;
	// toolbuttons
	Gtk::ToolButton m_up_toolbtn,m_down_toolbtn,m_remove_toolbtn;
	Gtk::Image m_up_image,m_down_image,m_remove_image;
	/**
	 * toolbar
	 */
	Gtk::ToolPalette m_filepreview_toolpalette;
	/**
	 * grid
	 */
	Glib::RefPtr<tinyms::FilePreviewStore> m_filePreviewStore;
	Gtk::TreeView m_filePreviewGrid;
	Gtk::ScrolledWindow m_ScrolledWindow4FilePreview;
	//
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
	virtual bool evt_key_release(GdkEventKey* event);
	virtual bool evt_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time);
	//
	void scan_files();
	void init_logfile();
	void read_logfile();
	void clear_log();
	//toolbutton bind events
	virtual void evt_uptoolbtn_clicked();
	virtual void evt_downtoolbtn_clicked();
	virtual void evt_removetoolbtn_clicked();
	void bind_toolbutton4treeview_events();
};

#endif /* JSCOMPRESSORFRAME_H_ */
