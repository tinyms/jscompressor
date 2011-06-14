//============================================================================
// Name        : JsCompressor
// Author      : tinyms
// Version     :
// Copyright   : @tinyms.com 2011
// Description : copress js or css
//============================================================================
#include <stdlib.h>
#include <gtkmm.h>
#include <giomm/file.h>
#include <glibmm/ustring.h>
#include "Utils.h"
#include "FileUtils.h"
#include "JsCompressorFrame.h"
using namespace std;
using namespace tinyms;
int main(int argc, char *argv[]) {
	Gtk::Main main(argc, argv);
	tinyms::FileUtils fileUtils;
	Glib::ustring path("c:/abc cc/kkk/java.exe");
	fileUtils.escapeBlank(path);
	Utils::__APSPATH__=Gio::File::create_for_path(argv[0])->get_parent()->get_path();
	JsCompressorFrame mainFrame(Gtk::WINDOW_TOPLEVEL);
	Gtk::Main::run(mainFrame);
	return 0;
}
