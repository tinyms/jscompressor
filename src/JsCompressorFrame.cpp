/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	m_main_vbox(false, 0), m_top_hbox(false, 0), centerLayout(false, 0),
			center2Layout(false, 0), m_bottom_hbox(false, 0),
			tipSelectFile("文件夹:"),
			m_tipConsoleWin("控制台 (如果有`WARNING`,可以忽略,但建议排除再压缩,直到控制台无任何提示)"),
			m_jsOrCssChkbox("CSS(默认过滤出JS)"), selectFolderBtn(" 浏览.. "),
			executeBtn(" 压缩&混淆 (DOS窗口消失则压缩完毕) ") {

	//for main window
	Glib::ustring m_appTitle("JsCompressor v");
	m_appTitle.append(JSCOMPRESSOR_VERSION);
	this->set_title(m_appTitle);
	Gtk::Image m_appIcon("compress.png");
	this->set_icon(m_appIcon.get_pixbuf());
	this->set_position(Gtk::WIN_POS_CENTER);

	//begin top panel
	this->m_top_hbox.pack_start(this->tipSelectFile, false, false, 0);
	this->m_top_hbox.pack_start(this->m_root_path_entry, true, true, 5);
	this->selectFolderBtn.signal_clicked().connect(
			sigc::mem_fun(*this,
					&JsCompressorFrame::evt_selectFolderBtn_clicked));
	this->m_top_hbox.pack_start(this->selectFolderBtn, false, false, 0);
	this->m_jsOrCssChkbox.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_jsOrCssChkbox_clicked));
	this->m_top_hbox.pack_start(this->m_jsOrCssChkbox, false, false, 5);
	//end

	//begin center panel
	this->m_filePreviewStore = Gtk::ListStore::create(this->m_column_def);
	this->m_filePreviewGrid.set_model(this->m_filePreviewStore);
	this->m_filePreviewGrid.append_column("文件名",
			this->m_column_def.m_file_full_path);
	this->m_ScrolledWindow4FilePreview.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_ScrolledWindow4FilePreview.set_policy(Gtk::POLICY_NEVER,
			Gtk::POLICY_AUTOMATIC);
	this->m_ScrolledWindow4FilePreview.add(this->m_filePreviewGrid);
	this->centerLayout.pack_start(this->m_ScrolledWindow4FilePreview, true,
			true, 0);
	//console window
	this->center2Layout.pack_start(this->m_tipConsoleWin, false, false, 0);
	this->m_consoleWin.set_size_request(-1, 150);
	this->m_consoleWin.set_editable(false);
	this->m_scrolledWindow4ConsoleWin.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	this->m_scrolledWindow4ConsoleWin.set_policy(Gtk::POLICY_NEVER,
			Gtk::POLICY_AUTOMATIC);
	this->m_scrolledWindow4ConsoleWin.add(this->m_consoleWin);
	//end

	//begin bottom panel
	this->executeBtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
	this->m_bottom_hbox.pack_end(this->executeBtn, false, false, 0);
	//end
	m_main_vbox.pack_start(this->m_top_hbox, false, false, 0);
	m_main_vbox.pack_start(this->centerLayout, true, true, 5);
	this->m_main_vbox.pack_start(this->center2Layout, false, false, 0);
	this->m_main_vbox.pack_start(this->m_scrolledWindow4ConsoleWin, false,
			false, 5);
	m_main_vbox.pack_start(this->m_bottom_hbox, false, false, 0);
	this->add(m_main_vbox);
	this->set_default_size(600, 480);
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
	if(WITH_JRE){
		cmd.append("\"");
		cmd.append(Utils::__APSPATH__.c_str());
		cmd.append("/jre6/bin/javaw.exe\" -jar compressorhelper.jar");
	}else{
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
void JsCompressorFrame::evt_jsOrCssChkbox_clicked() {
	this->scan_files();
}
void JsCompressorFrame::evt_selectFolderBtn_clicked() {
	Gtk::FileChooserDialog fcdlg("请选择一个文件夹",
			Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	fcdlg.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fcdlg.add_button("选择", Gtk::RESPONSE_OK);
	gint flag;
	flag = fcdlg.run();
	if (flag == Gtk::RESPONSE_OK) {
		this->m_root_path_entry.set_text(fcdlg.get_current_folder());
		this->seletedPath = fcdlg.get_current_folder();
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
		util.walkFiles(path, "*.css","*.min.css", files);
	} else {
		util.walkFiles(path, "*.js","*.min.js", files);
	}
	size_t length = files.size();
	for (size_t k = 0; k < length; k++) {
		Gtk::TreeModel::Row row = *(this->m_filePreviewStore->append());
		row[this->m_column_def.m_file_full_path] = files[k];
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
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
