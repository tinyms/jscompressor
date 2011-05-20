//============================================================================
// Name        : JsCompressor.cpp
// Author      : tinyms
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <gtkmm.h>
#include "JsCompressorFrame.h"
int main(int argc,char *argv[]) {
	Gtk::Main main(argc,argv);
	JsCompressorFrame mainFrame(Gtk::WINDOW_TOPLEVEL);
	Gtk::Main::run(mainFrame);
	return 0;
}
