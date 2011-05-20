/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) :
	mainLayout(false, 0), fileChooserBtn(),executeBtn("Execute") {
	this->executeBtn.signal_clicked().connect(sigc::mem_fun(*this,&JsCompressorFrame::evt_executeBtn_clicked));
	mainLayout.pack_start(fileChooserBtn, false, false, 0);
	mainLayout.pack_start(executeBtn, false, false, 5);
	this->add(mainLayout);
	this->set_default_size(250,-1);
	this->set_border_width(10);
	this->show_all();
}
void JsCompressorFrame::evt_executeBtn_clicked(){

	std::cout<<this->fileChooserBtn.get_filename()<<std::endl;
}
JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
