/*
 * NewProjectDialog.cpp
 *
 *  Created on: 2011-7-8
 *      Author: tinyms
 */

#include "NewProjectDialog.h"
namespace tinyms {
NewProjectDialog::NewProjectDialog() :
		m_label1("选择文件夹:"), m_label2("项目名称:"), m_folder_chooserbtn(
				"选择一个文件夹", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER), m_option_panel_frame(
				"参数设置:") {
	// TODO Auto-generated constructor stub
	this->set_title("新建项目");
	this->set_modal(true);
	this->set_opacity(0.97);
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_size_request(280, 220);
	this->set_border_width(10);
	this->createUI();
	///
	this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	this->add_button("创建", Gtk::RESPONSE_OK);
}
void NewProjectDialog::createUI() {
	Gtk::VBox* main = this->get_vbox();
	this->m_label1.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	main->pack_start(this->m_label1, false, false, 0);
	main->pack_start(this->m_folder_chooserbtn, false, false, 5);
	this->create_option_panel_expander();
	main->pack_start(this->m_option_panel_frame, true, true, 5);
	this->m_label2.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	main->pack_start(this->m_label2, false, false, 0);
	main->pack_start(this->m_project_name_entry, false, false, 5);
	this->show_all();
}
void NewProjectDialog::create_option_panel_expander() {
	this->m_option_is_allinone.set_label("是否合并");
	this->m_option_is_compress.set_label("是否混淆");
	this->m_option_is_compress.set_active(true);
	this->m_option_panel_hbox.pack_start(this->m_option_is_compress, false,
			false, 5);
	this->m_option_panel_hbox.pack_start(this->m_option_is_allinone, false,
			false, 0);
	this->m_option_panel_frame.add(this->m_option_panel_hbox);
}
NewProjectDialog::~NewProjectDialog() {
	// TODO Auto-generated destructor stub
}
}

