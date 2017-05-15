#define WIDGET 1
#include "sasc-structure.h"
#include "callback-gpib.h"
#include "callback.h"
#include "sa-define.h"
#include <gtk/gtk.h>

#define HEIGHT  800
#define WIDTH	600
sasc_data data;

void wdg_main(sasc_data *data)	{
	
	data->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	data->vbox_main = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(data->main_window), data->vbox_main);

	data->menubar1 = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_main), data->menubar1, FALSE, FALSE, 2);

	data->hbox_widget = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(data->vbox_main), data->hbox_widget);

	data->statusbar = gtk_statusbar_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_main), data->statusbar, FALSE, TRUE, 1);
	
	data->darea = gtk_drawing_area_new();
	gtk_box_pack_start (GTK_BOX(data->hbox_widget), data->darea, TRUE, TRUE, 0);

	data->vbox_sidebar = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX(data->hbox_widget), data->vbox_sidebar, FALSE, TRUE, 10);
	//end of box packing

	gtk_window_set_position(GTK_WINDOW(data->main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(data->main_window), HEIGHT, WIDTH);

  	gtk_window_set_title(GTK_WINDOW(data->main_window), PROGRAM);
	g_timeout_add(5000, (GSourceFunc) time_handler, (gpointer*) data);

	g_signal_connect(data->darea, "expose-event", G_CALLBACK(drawing_screen),(gpointer*) data);
	gtk_widget_set_app_paintable(data->darea, TRUE);
}

void wdg_menu(sasc_data *data)	{
	//Quit
	data->menu_file = gtk_menu_new();

	data->menuitem_file = gtk_menu_item_new_with_label("Quit");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_file), "activate",
                     GTK_SIGNAL_FUNC(on_window_closed), NULL);
	gtk_menu_append(GTK_MENU(data->menu_file), data->menuitem_file);

	data->menuitem_file = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(data->menuitem_file),
			    data->menu_file);
	gtk_menu_bar_append(GTK_MENU_BAR(data->menubar1), data->menuitem_file);

	//Start
	data->menu_start = gtk_menu_new();

/*	data->menuitem_start = gtk_menu_item_new_with_label("single");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_start), "activate",
                     G_CALLBACK(toogle_signal),data->darea);
	gtk_menu_append(GTK_MENU(data->menu_start), data->menuitem_start);
*/
	data->menuitem_cont = gtk_menu_item_new_with_label("Cont");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_cont), "activate",
                     G_CALLBACK(toogle_signal),data->darea);
	gtk_menu_append(GTK_MENU(data->menu_start), data->menuitem_cont);
/*	
	data->menuitem_sheduler = gtk_menu_item_new_with_label("Sheduler");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_sheduler), "activate",
                     G_CALLBACK(toogle_signal),data->darea);
	gtk_menu_append(GTK_MENU(data->menu_start), data->menuitem_sheduler);
*/
	data->menuitem_start = gtk_menu_item_new_with_label("Get data");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(data->menuitem_start),
			    data->menu_start);
	gtk_menu_bar_append(GTK_MENU_BAR(data->menubar1), data->menuitem_start);

	//PNG
	data->menu_png = gtk_menu_new();

	data->menuitem_png = gtk_menu_item_new_with_label("Create PNG");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_png), "activate",
                     G_CALLBACK(create_png), NULL);
	gtk_menu_append(GTK_MENU(data->menu_png), data->menuitem_png);

	data->menuitem_pdf = gtk_menu_item_new_with_label("Create PDF");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_pdf), "activate",
                     G_CALLBACK(create_pdf), NULL);
	gtk_menu_append(GTK_MENU(data->menu_png), data->menuitem_pdf);
	

	data->menuitem_png = gtk_menu_item_new_with_label("Create file");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(data->menuitem_png),
			    data->menu_png);
	gtk_menu_bar_append(GTK_MENU_BAR(data->menubar1), data->menuitem_png);

	//About
	data->menu_about = gtk_menu_new();
	data->menuitem_about = gtk_menu_item_new_with_label("Info");
	gtk_signal_connect(GTK_OBJECT(data->menuitem_about), "activate",
                     GTK_SIGNAL_FUNC(about), "Info");
	gtk_menu_append(GTK_MENU(data->menu_about), data->menuitem_about);

	data->menuitem_about = gtk_menu_item_new_with_label("About");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(data->menuitem_about),
			    data->menu_about);
	gtk_menu_bar_append(GTK_MENU_BAR(data->menubar1), data->menuitem_about);
}

void wdg_sasettings(sasc_data *data)	{
	
	uint16_t cnt = 0;

	//CF
	data->label_set_frequency = gtk_label_new("Center frequency/[MHz]");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_set_frequency, FALSE, TRUE,1);
	
	data->adj_set_frequency = (GtkAdjustment *) gtk_adjustment_new (2000,0,4000,1,10,0);
	data->widget_set_frequency = gtk_spin_button_new(data->adj_set_frequency,0,0);
	
	gtk_signal_connect(GTK_OBJECT(data->widget_set_frequency), "value-changed",G_CALLBACK(set_frequency),(gpointer *) data);	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->widget_set_frequency, FALSE, TRUE,1);

	//Auto RBW/ST
	data->label_auto =  gtk_label_new("Auto"); 
	data->btn_auto = gtk_button_new_with_label("Auto");
	gtk_signal_connect(GTK_OBJECT(data->btn_auto), "clicked",G_CALLBACK (bnt_auto_callback), (gpointer*) data);
	data->btn_auto_up = gtk_button_new_with_label("<-->") ;
	gtk_signal_connect(GTK_OBJECT(data->btn_auto_up), "clicked",G_CALLBACK (bnt_auto_down_callback), (gpointer*) data);
	data->btn_auto_down = gtk_button_new_with_label("-><-") ;
	gtk_signal_connect(GTK_OBJECT(data->btn_auto_down), "clicked",G_CALLBACK (bnt_auto_up_callback), (gpointer*) data);
	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_auto, FALSE, TRUE,1);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->btn_auto, FALSE, TRUE,1);
	
	data->hbox_btn_auto = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->hbox_btn_auto, FALSE, TRUE,1);
	gtk_box_pack_start(GTK_BOX(data->hbox_btn_auto),data->btn_auto_down, TRUE, TRUE,1);
	gtk_box_pack_start(GTK_BOX(data->hbox_btn_auto),data->btn_auto_up, TRUE, TRUE,1);

	data->sep_auto = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_auto, FALSE, TRUE,5);

	//RBW
	data->label_rbw = gtk_label_new("RBW");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_rbw, FALSE, TRUE,1);
	
	data->rbw_combo = gtk_combo_box_text_new();
	for(cnt = 0; cnt < rbw_cnt_4131; cnt ++)		{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->rbw_combo), rbw_select_4131[cnt]);
	}
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(data->rbw_combo),0);
  	gtk_signal_connect(GTK_OBJECT(data->rbw_combo), "changed",GTK_SIGNAL_FUNC(set_rbw), (gpointer*) data);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->rbw_combo, FALSE, TRUE,1);
	data->sep_rbw = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_rbw, FALSE, TRUE,5);

	//SP
	data->label_sp = gtk_label_new("Frequency span");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_sp, FALSE, TRUE,1);
	
	data->sp_combo = gtk_combo_box_text_new();
	for(cnt = 0; cnt < sp_cnt_4131; cnt ++)		{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->sp_combo), sp_select_4131[cnt]);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(data->sp_combo),0);
  	gtk_signal_connect(GTK_OBJECT(data->sp_combo), "changed",GTK_SIGNAL_FUNC(set_sp), (gpointer*) data);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->sp_combo, FALSE, TRUE,1);
	data->sep_sp = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_sp, FALSE, TRUE,5);
	
	//ST
	data->label_st = gtk_label_new("Sweep time");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_st, FALSE, TRUE,1);
	
	data->st_combo = gtk_combo_box_text_new();
	for(cnt = 0; cnt < st_cnt_4131; cnt ++)		{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->st_combo), st_select_4131[cnt]);
	}
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(data->st_combo),0);
  	gtk_signal_connect(GTK_OBJECT(data->st_combo), "changed",GTK_SIGNAL_FUNC(set_st), (gpointer*) data);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->st_combo, FALSE, TRUE,1);
	data->sep_st = gtk_hseparator_new();	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_st, FALSE, TRUE,5);
		
	//VF
	data->label_vf = gtk_label_new("Video filter");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_vf, FALSE, TRUE,1);

	data->vf_combo = gtk_combo_box_text_new();
	for(cnt = 0; cnt < vf_cnt_4131; cnt ++)		{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->vf_combo), vf_select_4131[cnt]);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(data->vf_combo),0);
  	gtk_signal_connect(GTK_OBJECT(data->vf_combo), "changed",GTK_SIGNAL_FUNC(set_vf), (gpointer*) data);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->vf_combo, FALSE, TRUE,1);	
	data->sep_vf = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_vf, FALSE, TRUE,5);	

	//RL
	data->label_rl = gtk_label_new("Referenz level");	
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_rl, FALSE, TRUE,1);

	data->rl_combo = gtk_combo_box_text_new();
	for(cnt = 0; cnt < rl_cnt_4131; cnt ++)		{
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->rl_combo), rl_select_4131[cnt]);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(data->rl_combo),0);
  	gtk_signal_connect(GTK_OBJECT(data->rl_combo), "changed",GTK_SIGNAL_FUNC(set_rl), (gpointer*) data);
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->rl_combo, FALSE, TRUE,1);	
	data->sep_rl = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar),data->sep_rl, FALSE, TRUE,5);
	
	//ATT
	data->label_att =  gtk_label_new("Input Attenture"); 
	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->label_att, FALSE, TRUE,1);	
	data->btn_att_down = gtk_button_new_with_label("up") ;
	gtk_signal_connect(GTK_OBJECT(data->btn_att_down), "clicked",G_CALLBACK (bnt_att_down_callback), (gpointer*) data);
	data->btn_att_up = gtk_button_new_with_label("down") ;
	gtk_signal_connect(GTK_OBJECT(data->btn_att_up), "clicked",G_CALLBACK (bnt_att_up_callback), (gpointer*) data);

	data->hbox_btn_att = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(data->hbox_btn_att),data->btn_att_down, TRUE, TRUE,1);
	gtk_box_pack_start(GTK_BOX(data->hbox_btn_att),data->btn_att_up, TRUE, TRUE,1);	

	gtk_box_pack_start(GTK_BOX(data->vbox_sidebar), data->hbox_btn_att, FALSE, TRUE,1);	
}
