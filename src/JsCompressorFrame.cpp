/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	m_main_vbox(false, 0), m_toolbar4treeview_vbox(false, 0),
			m_top_hbox(false, 0), m_center_head_hbox(false, 0),
			m_center_foot_hbox(false, 0), m_bottom_hbox(false, 0),
			m_selected_path_label("文件夹(不含中文和空格):"),
			m_tipConsoleWin("控制台 (如果有`WARNING`,可以忽略,但建议排除再压缩,直到控制台无任何提示)"),
			m_jsOrCssChkbox("CSS(默认过滤JS)"), m_select_folder_btn(" 浏览.. "),
			m_compress_btn(" 压缩&混淆 (DOS窗口消失则压缩完毕) ") {

	//for main window
	Glib::ustring m_appTitle("JsCompressor v");
	m_appTitle.append(JSCOMPRESSOR_VERSION);
	this->set_title(m_appTitle);
	Gtk::Image m_appIcon("compress.png");
	this->set_icon(m_appIcon.get_pixbuf());
	this->set_position(Gtk::WIN_POS_CENTER);

	//begin top panel
	this->m_top_hbox.pack_start(this->m_selected_path_label, false, false, 0);
	this->m_top_hbox.pack_start(this->m_root_path_entry, true, true, 5);
	this->m_select_folder_btn.signal_clicked().connect(
			sigc::mem_fun(*this,
					&JsCompressorFrame::evt_selectFolderBtn_clicked));
	this->m_top_hbox.pack_start(this->m_select_folder_btn, false, false, 0);
	this->m_jsOrCssChkbox.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_jsOrCssChkbox_clicked));
	this->m_top_hbox.pack_start(this->m_jsOrCssChkbox, false, false, 5);
	//end

	//begin center panel
	this->m_filePreviewStore = tinyms::FilePreviewStore::create();
	this->m_filePreviewGrid.set_model(this->m_filePreviewStore);
	this->m_filePreviewGrid.set_rules_hint();
	this->m_filePreviewGrid.append_column("文件名",
			this->m_filePreviewStore->m_colsDef.m_file_full_path);
	this->m_filePreviewGrid.set_reorderable();
	//evt for grid
	this->m_filePreviewGrid.signal_drag_motion().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_drag_motion));
	this->m_filePreviewGrid.signal_key_release_event().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_key_release));
	this->m_ScrolledWindow4FilePreview.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_ScrolledWindow4FilePreview.set_policy(Gtk::POLICY_NEVER,
			Gtk::POLICY_AUTOMATIC);
	this->m_ScrolledWindow4FilePreview.add(this->m_filePreviewGrid);

	this->m_center_head_hbox.pack_start(this->m_ScrolledWindow4FilePreview,
			true, true, 0);

	this->bind_toolbutton4treeview_events();

	this->m_toolbar4treeview_vbox.set_size_request(24, -1);
	this->m_center_head_hbox.pack_start(this->m_toolbar4treeview_vbox, false,
			false, 2);
	//console window
	this->m_center_foot_hbox.pack_start(this->m_tipConsoleWin, false, false, 0);
	this->m_consoleWin.set_size_request(-1, 150);
	this->m_consoleWin.set_editable(false);
	this->m_scrolledWindow4ConsoleWin.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_scrolledWindow4ConsoleWin.set_policy(Gtk::POLICY_NEVER,
			Gtk::POLICY_AUTOMATIC);
	this->m_scrolledWindow4ConsoleWin.add(this->m_consoleWin);
	//end

	//begin bottom panel
	this->m_home_label.set_label("©tinyms.com 2011");
	this->m_home_eventbox.signal_button_press_event().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_gohome_clicked));
	this->m_home_eventbox.signal_enter_notify_event().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_gohome_enter));
	this->m_home_eventbox.add(this->m_home_label);
	this->m_bottom_hbox.pack_start(this->m_home_eventbox, false, false, 0);
	this->m_compress_btn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
	this->m_bottom_hbox.pack_end(this->m_compress_btn, false, false, 0);
	//end
	m_main_vbox.pack_start(this->m_top_hbox, false, false, 0);
	m_main_vbox.pack_start(this->m_center_head_hbox, true, true, 5);
	this->m_main_vbox.pack_start(this->m_center_foot_hbox, false, false, 0);
	this->m_main_vbox.pack_start(this->m_scrolledWindow4ConsoleWin, false,
			false, 5);
	m_main_vbox.pack_start(this->m_bottom_hbox, false, false, 0);
	this->add(m_main_vbox);
	this->set_default_size(520, 480);
	this->set_border_width(10);
	this->show_all();

}
void JsCompressorFrame::evt_executeBtn_clicked() {
	if (this->seletedPath.size() <= 0) {
		return;
	}
	this->init_logfile();
	Glib::ustring targetFiles;
	size_t length = files.size();
	for (size_t k = 0; k < length; k++) {
		targetFiles.append(";");
		targetFiles.append(files[k]);
	}

	Glib::ustring cmd;
	if (WITH_JRE) {
		cmd.append("\"");
		cmd.append(tinyms::FileUtils::__APSPATH__.c_str());
		cmd.append("/jre6/bin/javaw.exe\" -jar compressorhelper.jar");
	} else {
		cmd.append("javaw -jar compressorhelper.jar");
	}
	cmd.append(" -selected-folder ");
	cmd.append(this->m_root_path_entry.get_text());
	cmd.append(" -files ");
	cmd.append(targetFiles.substr(1, targetFiles.size()));
	cmd.append(" -type ");
	if (this->m_jsOrCssChkbox.get_active()) {
		cmd.append("css");
	} else {
		cmd.append("js");
	}
	cmd.append(" -aio ");
	cmd.append("true");
	system(cmd.c_str());
	std::cout << cmd << std::endl;

	this->read_logfile();

}
bool JsCompressorFrame::evt_gohome_clicked(GdkEventButton* eb) {
	system("explorer http://www.tinyms.com");
	return true;
}
bool JsCompressorFrame::evt_gohome_enter(GdkEventCrossing* eb) {
	Gdk::Cursor c(Gdk::HAND1);
	this->m_home_label.get_window()->set_cursor(c);
	return true;
}
void JsCompressorFrame::evt_jsOrCssChkbox_clicked() {
	this->scan_files();
}
bool JsCompressorFrame::evt_key_release(GdkEventKey* event) {
	std::cout << gdk_keyval_name(event->keyval) << std::endl;
	std::cout << event->string << std::endl;
	std::cout << GDK_uparrow << std::endl;

	return true;
}
bool JsCompressorFrame::evt_drag_motion(
		const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time) {
	std::cout << "zzz00" << std::endl;
	return true;
}
void JsCompressorFrame::evt_selectFolderBtn_clicked() {
	std::map<std::string, std::string> config;
	tinyms::FileUtils::config_read(config);
	Gtk::FileChooserDialog fcdlg("请选择一个文件夹",
			Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	if (config["preSelectedPath"].size() > 0) {
		fcdlg.set_current_folder(config["preSelectedPath"]);
	}
	fcdlg.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fcdlg.add_button("选择", Gtk::RESPONSE_OK);
	gint flag;
	flag = fcdlg.run();
	if (flag == Gtk::RESPONSE_OK) {
		this->m_root_path_entry.set_text(fcdlg.get_current_folder());
		this->seletedPath = fcdlg.get_current_folder();
		config["preSelectedPath"] = this->seletedPath;
		tinyms::FileUtils::config_write(config);
		this->scan_files();
		this->clear_log();
	}
}
void JsCompressorFrame::scan_files() {
	files.clear();
	this->m_filePreviewStore->clear();
	if (this->m_root_path_entry.get_text_length() <= 0) {
		return;
	}
	std::string path = this->m_root_path_entry.get_text();
	if (this->m_jsOrCssChkbox.get_active() == true) {
		tinyms::FileUtils::walkFiles(path, "*.css", "*.min.css", files);
	} else {
		tinyms::FileUtils::walkFiles(path, "*.js", "*.min.js", files);
	}
	size_t length = files.size();
	for (size_t k = 0; k < length; k++) {
		Gtk::TreeModel::Row row = *(this->m_filePreviewStore->append());
		row[this->m_filePreviewStore->m_colsDef.m_file_full_path] = files[k];
	}
}
void JsCompressorFrame::init_logfile() {
	std::string logfilePath = seletedPath + "/console.log";
	Glib::RefPtr<Gio::File> logfile = Gio::File::create_for_path(logfilePath);
	if (!logfile->query_exists()) {
		logfile->create_file();
	} else {
		logfile->remove();
		logfile->create_file();
	}
	//	logmonitor = logfile->monitor_file();
	//	logmonitor->signal_changed().connect(
	//			sigc::mem_fun(*this, &JsCompressorFrame::evt_logfile_changed));
}
void JsCompressorFrame::evt_logfile_changed(
		const Glib::RefPtr<Gio::File>& file,
		const Glib::RefPtr<Gio::File>& other_file,
		Gio::FileMonitorEvent event_type) {
	this->read_logfile();
}
void JsCompressorFrame::read_logfile() {
	Glib::ustring logfilePath = seletedPath + "/console.log";
	Glib::ustring info = tinyms::FileUtils::read(logfilePath);
	this->m_logBuffer = Gtk::TextBuffer::create();
	this->m_logBuffer->set_text(info);
	this->m_consoleWin.set_buffer(this->m_logBuffer);
}
void JsCompressorFrame::clear_log() {
	this->m_logBuffer = Gtk::TextBuffer::create();
	this->m_logBuffer->set_text("");
	this->m_consoleWin.set_buffer(this->m_logBuffer);
}
void JsCompressorFrame::evt_uptoolbtn_clicked() {
	Gtk::TreeModel::iterator current =
			this->m_filePreviewGrid.get_selection()->get_selected();
	if (!current)
		return;
	Gtk::TreeModel::iterator up = current--;
	if (up) {
		this->m_filePreviewStore->iter_swap(current, up);
	}
}
void JsCompressorFrame::evt_downtoolbtn_clicked() {
	Gtk::TreeModel::iterator current =
			this->m_filePreviewGrid.get_selection()->get_selected();
	if (!current)
		return;
	Gtk::TreeModel::iterator down = current++;
	if (down) {
		this->m_filePreviewStore->iter_swap(current, down);
	}
}
void JsCompressorFrame::evt_removetoolbtn_clicked() {
	Gtk::TreeModel::iterator current =
			this->m_filePreviewGrid.get_selection()->get_selected();
	if (!current)
		return;
	this->m_filePreviewStore->erase(current);
}
void JsCompressorFrame::bind_toolbutton4treeview_events() {
	this->m_up_image.set("go-up.png");
	this->m_down_image.set("go-down.png");
	this->m_remove_image.set("window-close.png");
	this->m_up_toolbtn.set_icon_widget(this->m_up_image);
	this->m_down_toolbtn.set_icon_widget(this->m_down_image);
	this->m_remove_toolbtn.set_icon_widget(this->m_remove_image);
	this->m_up_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_uptoolbtn_clicked));
	this->m_down_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_downtoolbtn_clicked));
	this->m_remove_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_removetoolbtn_clicked));
	this->m_toolbar4treeview_vbox.pack_start(this->m_up_toolbtn, false, false,
			0);
	this->m_toolbar4treeview_vbox.pack_start(this->m_down_toolbtn, false,
			false, 0);
	this->m_toolbar4treeview_vbox.pack_start(this->m_remove_toolbtn, false,
			false, 0);
}
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
