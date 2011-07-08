/*
 * NewProjectDialog.h
 *
 *  Created on: 2011-7-8
 *      Author: tinyms
 */

#ifndef NEWPROJECTDIALOG_H_
#define NEWPROJECTDIALOG_H_
#include <gtkmm.h>
namespace tinyms {
	class NewProjectDialog: public Gtk::Dialog {
	public:
		NewProjectDialog();
		void createUI();
		void create_option_panel_expander();
		virtual ~NewProjectDialog();
	public:
		Gtk::Label m_label1,m_label2,m_label3;
		Gtk::FileChooserButton m_folder_chooserbtn;
		Gtk::Entry m_project_name_entry;
		Gtk::HBox m_option_panel_hbox;
		Gtk::CheckButton m_option_is_allinone,m_option_is_compress;
	};
}
#endif /* NEWPROJECTDIALOG_H_ */
