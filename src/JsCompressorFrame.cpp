/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
			mainLayout(false, 0),
			tipSelectFile("请选择JS或者CSS文件："),
			fileChooserBtn(),
			executeBtn("压缩 (会弹出DOS窗口,消失则压缩完毕)") {
	Gtk::Image appIcon("compress.png");
	this->set_title("JsCompressor v1.0");
	this->set_icon(appIcon.get_pixbuf());
	this->set_position(Gtk::WIN_POS_CENTER);
	Gtk::FileFilter fileFilter;
	fileFilter.add_pattern("*.js");
	fileFilter.add_pattern("*.css");
	this->fileChooserBtn.set_filter(fileFilter);
	this->executeBtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
	mainLayout.pack_start(tipSelectFile,false,false,0);
	mainLayout.pack_start(fileChooserBtn, false, false, 0);
	mainLayout.pack_start(executeBtn, false, false, 5);
	this->add(mainLayout);
	this->set_default_size(250, -1);
	this->set_border_width(10);
	this->show_all();
}
void JsCompressorFrame::evt_executeBtn_clicked() {
	Utils util;
	std::string scriptPath = util.getParentPath(
			this->fileChooserBtn.get_filename().c_str());
	Glib::ustring javaPath;
	//javaPath.append(Utils::__APSPATH__.c_str());
	javaPath.append("java -jar yuicompressor.jar");
	javaPath.append(" ");
	javaPath.append(this->fileChooserBtn.get_filename());
	javaPath.append(" -o ");
	javaPath.append(scriptPath);
	javaPath.append("/min-");
	javaPath.append(
			util.getFileName(this->fileChooserBtn.get_filename().c_str()));
	system(javaPath.c_str());
	std::cout << javaPath << std::endl;
}
void JsCompressorFrame::evt_homeSiteBtn_clicked() {
	system("explorer http://www.tinyms.com");
}
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
