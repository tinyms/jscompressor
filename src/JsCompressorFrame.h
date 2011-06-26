/*
 * JsCompressorFrame.h
 *  gdk_keyval_name(event->keyval)<-keyboard mapping
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#ifndef JSCOMPRESSORFRAME_H_
#define JSCOMPRESSORFRAME_H_

#ifndef JSCOMPRESSOR_VERSION
#define JSCOMPRESSOR_VERSION "3.0"
#endif

#ifndef OS_IS_WINDOWS
#define OS_IS_WINDOWS true
#endif

#include <iostream>
using namespace std;
#include <gtkmm.h>
#include <gdkmm/cursor.h>

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
	Gtk::ToolButton m_up_toolbtn,m_down_toolbtn,m_remove_toolbtn,m_refresh_toolbtn;
	Gtk::Image m_up_image,m_down_image,m_remove_image,m_refresh_image;
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
	Gtk::Expander m_optionpanel_expander;
	Gtk::HBox m_optionpanel_hbox;
	Gtk::CheckButton m_option_isallinone;
	Gtk::CheckButton m_option_iscompress;

	//
	std::vector<Glib::ustring> files;
	Glib::RefPtr<Gtk::TextBuffer> m_logBuffer;
	std::string seletedPath;
	Gtk::TreeModel::iterator current;
protected:
	virtual bool evt_gohome_enter(GdkEventCrossing* eb);
	virtual bool evt_gohome_clicked(GdkEventButton* eb);
	virtual void evt_jsOrCssChkbox_clicked();
	virtual void evt_selectFolderBtn_clicked();
	virtual void evt_executeBtn_clicked();
	//
	void init();
	void scan_files(std::string path);
	void init_logfile();
	void read_logfile();
	void clear_log();
	void iter_filelist();
	//toolbutton bind events
	virtual void evt_uptoolbtn_clicked();
	virtual void evt_downtoolbtn_clicked();
	virtual void evt_removetoolbtn_clicked();
	virtual void evt_refreshtoolbtn_clicked();
	//
	void bind_toolbutton4treeview_events();
	//create option panel
	void create_option_panel_expander();
};

#endif /* JSCOMPRESSORFRAME_H_ */
