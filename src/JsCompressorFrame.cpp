/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	mainLayout(false, 0), topLayout(false, 0), centerLayout(false, 0),
			buttomLayout(false, 0), tipSelectFile("文件夹："),
			m_jsOrCssChkbox("CSS(默认过滤出JS)"),
			selectFolderBtn("浏 览.."),
			executeBtn("压缩混淆 (会弹出DOS窗口,自动关闭后则处理完毕)") {
	//for main window
	Gtk::Image appIcon("compress.png");
	this->set_title("JsCompressor v2.0");
	this->set_icon(appIcon.get_pixbuf());
	this->set_position(Gtk::WIN_POS_CENTER);

	//begin top panel
	this->topLayout.pack_start(this->tipSelectFile, false, false, 0);
	this->topLayout.pack_start(this->topPath, true, true, 5);
	this->selectFolderBtn.signal_clicked().connect(
			sigc::mem_fun(*this,
					&JsCompressorFrame::evt_selectFolderBtn_clicked));
	this->topLayout.pack_start(this->selectFolderBtn, false, false, 5);
	this->m_jsOrCssChkbox.signal_clicked().connect(
				sigc::mem_fun(*this,
						&JsCompressorFrame::evt_jsOrCssChkbox_clicked));
	this->topLayout.pack_start(this->m_jsOrCssChkbox, false, false, 5);
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
	//end

	//begin bottom panel
	this->executeBtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
	this->buttomLayout.pack_end(this->executeBtn,false,false,0);
	//end
	mainLayout.pack_start(this->topLayout, false, false, 0);
	mainLayout.pack_start(this->centerLayout, true, true, 5);
	mainLayout.pack_start(this->buttomLayout, false, false, 0);
	this->add(mainLayout);
	this->set_default_size(600, 480);
	this->set_border_width(10);
	this->show_all();
}
void JsCompressorFrame::evt_executeBtn_clicked() {
	Utils util;
	Glib::ustring javaPath;
	//javaPath.append(Utils::__APSPATH__.c_str());
	javaPath.append("java -jar yuicompressor.jar");
	javaPath.append(" ");
	javaPath.append(" -o ");
	javaPath.append("/min-");
	system(javaPath.c_str());
	std::cout << javaPath << std::endl;
}
void JsCompressorFrame::evt_jsOrCssChkbox_clicked(){
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
		this->topPath.set_text(fcdlg.get_current_folder());
		this->scan_files();
	}
}
void JsCompressorFrame::scan_files() {
	if(this->topPath.get_text_length()<=0){return;}
	std::string path = this->topPath.get_text();
	Utils util;
	std::vector<std::string> files;
	if (this->m_jsOrCssChkbox.get_active() == true) {
		util.walkFiles(path, "*.css", files);
	} else {
		util.walkFiles(path, "*.js", files);
	}
	this->m_filePreviewStore->clear();
	size_t length = files.size();
	for (size_t k = 0; k < length; k++) {
		Gtk::TreeModel::Row row = *(this->m_filePreviewStore->append());
		row[this->m_column_def.m_file_full_path] = files[k];
	}
}
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
