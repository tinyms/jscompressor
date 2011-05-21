/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	mainLayout(false, 0), fileChooserBtn(), executeBtn("Execute") {
	this->executeBtn.signal_clicked().connect(
			sigc::mem_fun(*this, &JsCompressorFrame::evt_executeBtn_clicked));
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
	javaPath.append(Utils::__APSPATH__.c_str());
	javaPath.append("/jre6/bin/javaw.exe -jar yuicompressor-2.4.6.jar");
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
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
