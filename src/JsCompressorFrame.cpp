/*
 * JsCompressorFrame.cpp
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#include "JsCompressorFrame.h"

JsCompressorFrame::JsCompressorFrame(Gtk::WindowType type) {
	// TODO Auto-generated constructor stub
	this->mainLayout=new Gtk::VBox(false,10);
	this->fileChooserBtn = new Gtk::FileChooserButton();
	this->executeBtn = new Gtk::Button("Execute");
	this->mainLayout->pack_start(*(this->fileChooserBtn),false,false,0);
	this->mainLayout->pack_start(*(this->executeBtn),false,false,0);
	this->add(*(this->mainLayout));
	this->show_all();
}

JsCompressorFrame::~JsCompressorFrame() {
	// TODO Auto-generated destructor stub
}
