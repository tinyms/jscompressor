//============================================================================
// Name        : JsCompressor
// Author      : tinyms
// Version     :
// Copyright   : @tinyms.com 2011
// Description : copress js or css
//============================================================================
#include <gtkmm.h>
#include "FileUtils.h"
#include "JsCompressorFrame.h"
using namespace tinyms;
int main(int argc, char *argv[]) {

	Gtk::Main main(argc, argv);
	tinyms::FileUtils::__APSPATH__=tinyms::FileUtils::parent(argv[0])->get_path();

	JsCompressorFrame mainFrame(Gtk::WINDOW_TOPLEVEL);
	Gtk::Main::run(mainFrame);

	return 0;
}
