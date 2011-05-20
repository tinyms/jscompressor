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

class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	Gtk::VBox mainLayout;
	Gtk::FileChooserButton fileChooserBtn;
	Gtk::Button executeBtn;
protected:
	virtual void evt_executeBtn_clicked();
};

#endif /* JSCOMPRESSORFRAME_H_ */
