/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	m_main_vbox(false, 0), m_toolbar_hbox(false, 0),
			m_center_head_hbox(false, 0), m_center_foot_hbox(false, 0),
			m_bottom_hbox(false, 0), m_selected_path_label("文件夹(不含中文和空格):"),
			m_tipConsoleWin("控制台 (如果有`WARNING`,可以忽略,但建议排除再压缩,直到控制台无任何提示)"),
			m_jsOrCssChkbox("CSS(默认过滤JS)"), m_select_folder_btn(" 浏览.. "),
			m_compress_btn(" 压缩&混淆  "), m_optionpanel_hbox(false, 0) {

	//for main window
	this->set_opacity(0.97);
	Glib::ustring m_appTitle("JsCompressor v");
	m_appTitle.append(JSCOMPRESSOR_VERSION);
	this->set_title(m_appTitle);
	Gtk::Image m_appIcon(tinyms::FileUtils::__APSPATH__ + "/compress.png");
	this->set_icon(m_appIcon.get_pixbuf());
	this->set_position(Gtk::WIN_POS_CENTER);

	//build toolbar


	//begin top panel
	this->m_select_folder_btn.signal_clicked().connect(
			sigc::mem_fun(*this,
					&JsCompressorFrame::evt_selectFolderBtn_clicked));

	//end
	this->create_option_panel_expander();
	//begin center panel
	this->m_filePreviewStore = tinyms::FilePreviewStore::create();
	this->m_filePreviewGrid.set_model(this->m_filePreviewStore);
	this->m_filePreviewGrid.set_rules_hint();
	this->m_filePreviewGrid.append_column("文件名",
			this->m_filePreviewStore->m_colsDef.m_file_full_path);

	//evt for grid
	this->m_ScrolledWindow4FilePreview.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_ScrolledWindow4FilePreview.set_policy(Gtk::POLICY_AUTOMATIC,
			Gtk::POLICY_AUTOMATIC);
	this->m_ScrolledWindow4FilePreview.add(this->m_filePreviewGrid);

	this->m_center_head_hbox.pack_start(this->m_ScrolledWindow4FilePreview,
			true, true, 0);

	this->bind_toolbutton4treeview_events();

	this->m_toolbar_hbox.set_size_request(-1, 30);
	this->m_main_vbox.pack_start(this->m_toolbar_hbox, false, false, 2);
	//console window
	this->m_center_foot_hbox.pack_start(this->m_tipConsoleWin, false, false, 0);
	this->m_consoleWin.set_size_request(-1, 150);
	this->m_consoleWin.set_editable(false);
	this->m_scrolledWindow4ConsoleWin.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_scrolledWindow4ConsoleWin.set_policy(Gtk::POLICY_AUTOMATIC,
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
	//this->m_compress_btn.signal_clicked().connect(
			//sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
	//this->m_bottom_hbox.pack_end(this->m_compress_btn, false, false, 0);
	//end
	m_main_vbox.pack_start(this->m_center_head_hbox, true, true, 5);
	m_main_vbox.pack_start(this->m_optionpanel_expander, false, false, 0);
	this->m_main_vbox.pack_start(this->m_center_foot_hbox, false, false, 0);
	this->m_main_vbox.pack_start(this->m_scrolledWindow4ConsoleWin, false,
			false, 5);
	m_main_vbox.pack_start(this->m_bottom_hbox, false, false, 0);
	this->add(m_main_vbox);
	this->set_default_size(600, 480);
	this->set_border_width(10);
	this->show_all();
	this->init();
}
void JsCompressorFrame::init() {
	//open prev path
	std::map<std::string, std::string> config;
	tinyms::FileUtils::config_read(config);
	if (config["preSelectedPath"].size() > 0) {
		this->seletedPath = config["preSelectedPath"];
		this->m_root_path_entry.set_text(config["preSelectedPath"]);
		this->scan_files(config["preSelectedPath"]);
	}
}
void JsCompressorFrame::evt_executeBtn_clicked() {
	if (this->m_root_path_entry.get_text_length() <= 0) {
		return;
	}
	this->init_logfile();
	this->iter_filelist();
	Glib::ustring targetFiles;
	size_t length = files.size();
	for (size_t k = 0; k < length; k++) {
		targetFiles.append(";");
		targetFiles.append(files[k]);
	}

	Glib::ustring cmd;
	if (OS_IS_WINDOWS) {
		cmd.append("\"");
		cmd.append(tinyms::FileUtils::__APSPATH__);
		cmd.append("/jre6/bin/javaw.exe\" -jar compressorhelper.jar");
	} else {
		cmd.append("java -jar compressorhelper.jar");
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
	if (OS_IS_WINDOWS) {
		ShellExecute(NULL, "open", "http://www.tinyms.com",  NULL, NULL, SW_HIDE);
	}
	return true;
}
bool JsCompressorFrame::evt_gohome_enter(GdkEventCrossing* eb) {
	Gdk::Cursor c(Gdk::HAND1);
	this->m_home_label.get_window()->set_cursor(c);
	return true;
}
void JsCompressorFrame::evt_jsOrCssChkbox_clicked() {
	this->scan_files(this->m_root_path_entry.get_text());
}
void JsCompressorFrame::evt_selectFolderBtn_clicked() {
	std::map<std::string, std::string> config;
	tinyms::FileUtils::config_read(config);
	Gtk::FileChooserDialog fcdlg("选择文件夹",
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
		this->scan_files(this->m_root_path_entry.get_text());
		this->clear_log();
	}
}
void JsCompressorFrame::scan_files(std::string path) {
	files.clear();
	this->m_filePreviewStore->clear();
	if (path.size() <= 0) {
		return;
	}
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
}
void JsCompressorFrame::iter_filelist() {
	this->files.clear();
	Gtk::TreeNodeChildren child = this->m_filePreviewStore->children();
	Gtk::TreeModel::iterator it;
	for (it = child.begin(); it != child.end(); it++) {
		Gtk::TreeRow row = *it;
		this->files.push_back(
				row[this->m_filePreviewStore->m_colsDef.m_file_full_path]);
	}
}
void JsCompressorFrame::read_logfile() {
	Glib::ustring logfilePath = this->seletedPath + "/console.log";
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
	current = this->m_filePreviewGrid.get_selection()->get_selected();
	if (!current)
		return;
	if (current == this->m_filePreviewStore->children().begin()) {
		return;
	}
	Gtk::TreeModel::iterator up = current--;
	if (up) {
		this->m_filePreviewStore->iter_swap(current, up);
	}
}
void JsCompressorFrame::evt_downtoolbtn_clicked() {
	current = this->m_filePreviewGrid.get_selection()->get_selected();
	if (!current)
		return;
	Gtk::TreeModel::iterator down = current;
	++down;
	if (down == this->m_filePreviewStore->children().end()) {
		return;
	}
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
void JsCompressorFrame::evt_refreshtoolbtn_clicked() {
	this->scan_files(this->m_root_path_entry.get_text());
}
void JsCompressorFrame::create_option_panel_expander() {
	this->m_optionpanel_expander.set_label("参数");
	this->m_option_isallinone.set_label("是否合并");
	this->m_option_iscompress.set_label("是否混淆");
	this->m_optionpanel_hbox.pack_start(this->m_option_iscompress, false,
			false, 5);
	this->m_optionpanel_hbox.pack_start(this->m_option_isallinone, false,
			false, 0);
	this->m_optionpanel_expander.add(this->m_optionpanel_hbox);
}
void JsCompressorFrame::bind_toolbutton4treeview_events() {
	this->m_folder_open_image.set(tinyms::FileUtils::__APSPATH__ + "/folder-open.png");
	this->m_up_image.set(tinyms::FileUtils::__APSPATH__ + "/go-up.png");
	this->m_down_image.set(tinyms::FileUtils::__APSPATH__ + "/go-down.png");
	this->m_remove_image.set(
			tinyms::FileUtils::__APSPATH__ + "/window-close.png");
	this->m_refresh_image.set(
			tinyms::FileUtils::__APSPATH__ + "/view-refresh.png");
	this->m_package_image.set(
				tinyms::FileUtils::__APSPATH__ + "/package_green.png");
	this->m_folder_open_toolbtn.set_icon_widget(this->m_folder_open_image);
	this->m_folder_open_toolbtn.set_tooltip_text("打开");
	this->m_folder_open_toolbtn.set_label("打开");
	this->m_up_toolbtn.set_icon_widget(this->m_up_image);
	this->m_up_toolbtn.set_tooltip_text("上移");
	this->m_up_toolbtn.set_label("上移");
	this->m_down_toolbtn.set_icon_widget(this->m_down_image);
	this->m_down_toolbtn.set_tooltip_text("下移");
	this->m_down_toolbtn.set_label("下移");
	this->m_remove_toolbtn.set_icon_widget(this->m_remove_image);
	this->m_remove_toolbtn.set_tooltip_text("移除(不会真正删除文件)");
	this->m_remove_toolbtn.set_label("移除");
	this->m_refresh_toolbtn.set_icon_widget(this->m_refresh_image);
	this->m_refresh_toolbtn.set_tooltip_text("刷新(重新加载文件)");
	this->m_refresh_toolbtn.set_label("刷新");
	this->m_package_toolbtn.set_icon_widget(this->m_package_image);
		this->m_package_toolbtn.set_tooltip_text("构建");
		this->m_package_toolbtn.set_label("构建");
	this->m_up_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_uptoolbtn_clicked));
	this->m_down_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_downtoolbtn_clicked));
	this->m_remove_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_removetoolbtn_clicked));
	this->m_refresh_toolbtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_refreshtoolbtn_clicked));

	//
	this->m_toolbar_hbox.pack_start(this->m_folder_open_toolbtn, false, false, 0);
	this->m_toolbar_hbox.pack_start(this->m_up_toolbtn, false, false, 0);
	this->m_toolbar_hbox.pack_start(this->m_down_toolbtn, false, false, 0);
	this->m_toolbar_hbox.pack_start(this->m_remove_toolbtn, false, false, 0);
	this->m_toolbar_hbox.pack_start(this->m_refresh_toolbtn, false, false, 0);
	this->m_toolbar_hbox.pack_start(this->m_package_toolbtn, false, false, 15);
}
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
