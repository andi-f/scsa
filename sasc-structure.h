#include <stdint.h>
#include <gtk/gtk.h>

typedef struct sasc_record	{
	uint controller;		//GPIB controller 0-
	uint device;			//GPIB address 0-31
	uint16_t value[702];
	char eot;
	uint record_counter;	//
	double cf;				// center frequency
	double sp;				// span width
	double rbw;				// RBW
	double vf;				// Video filter
	double rl;				// Ref. level
	double st;				// Sweep time
	double att;				// Attenture
	char para[10];			// Parameter
	}
sasc_record;

typedef struct {
	
	GtkWidget *main_window;
	GtkWidget *vbox_main;
	GtkWidget *hbox_widget;
	
	GtkWidget *vbox_sidebar;
		
	GtkWidget *darea;
	GtkWidget *menubar1;
		
	GtkWidget *menu_file;
	GtkWidget *menuitem_file;
	
	GtkWidget *menu_start;
	GtkWidget *menuitem_start;
	GtkWidget *menuitem_cont;
	GtkWidget *menuitem_sheduler;
	
	GtkWidget *menu_png;
	GtkWidget *menuitem_png;
	GtkWidget *menuitem_pdf;
	
	GtkWidget *menu_about;
	GtkWidget *menuitem_about;
	GtkWidget *statusbar;
	
	GtkWidget *label_set_frequency;	
	GtkWidget *widget_set_frequency;	
	GtkAdjustment *adj_set_frequency;
	
	GtkWidget *label_auto;
	GtkWidget *btn_auto;
	GtkWidget *btn_auto_up;
	GtkWidget *btn_auto_down;
	GtkWidget *hbox_btn_auto;
	GtkWidget *sep_auto;
	
	GtkWidget *label_rbw;
	GtkWidget *rbw_combo;
	GtkWidget *sep_rbw;

	GtkWidget *label_sp;
	GtkWidget *sp_combo;
	GtkWidget *sep_sp;
	
	GtkWidget *label_rl;
	GtkWidget *rl_combo;
	GtkWidget *sep_rl;	
	
	GtkWidget *label_vf;
	GtkWidget *vf_combo;
	GtkWidget *sep_vf;	

	GtkWidget *label_st;
	GtkWidget *st_combo;
	GtkWidget *sep_st;	

	GtkWidget *label_att;
	GtkWidget *att_combo;
	GtkWidget *btn_att_up;
	GtkWidget *btn_att_down;
	GtkWidget *hbox_btn_att;

} sasc_data;

#define GPIB_INTERFACE 0
#define GPIB_ADR 5
