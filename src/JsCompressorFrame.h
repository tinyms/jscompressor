/*
 * JsCompressorFrame.h
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#ifndef JSCOMPRESSORFRAME_H_
#define JSCOMPRESSORFRAME_H_

#include <iostream>
using namespace std;
#include <gtkmm.h>
#include "Utils.h"
class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	Gtk::VBox mainLayout;
	Gtk::FileChooserButton fileChooserBtn;
	Gtk::Button executeBtn;
	Gtk::Button homeSiteBtn;
	Gtk::MessageDialog messager;
protected:
	virtual void evt_executeBtn_clicked();
	virtual void evt_homeSiteBtn_clicked();
};

#endif /* JSCOMPRESSORFRAME_H_ */
