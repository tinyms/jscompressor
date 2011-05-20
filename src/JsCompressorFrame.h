/*
 * JsCompressorFrame.h
 *
 *  Created on: 2011-5-20
 *      Author: tinyms
 */

#ifndef JSCOMPRESSORFRAME_H_
#define JSCOMPRESSORFRAME_H_

#include <gtkmm.h>

class JsCompressorFrame: public Gtk::Window {
public:
	JsCompressorFrame(Gtk::WindowType type);
	virtual ~JsCompressorFrame();
protected:
	Gtk::VBox* mainLayout;
	Gtk::FileChooserButton* fileChooserBtn;
	Gtk::Button* executeBtn;
};

#endif /* JSCOMPRESSORFRAME_H_ */
