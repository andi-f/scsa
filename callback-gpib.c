#define STATE
#define CMD

#include "sasc-structure.h"
#include "widget.h"
#include "gpib-functions.h"
#include "sa-define.h"

#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <gtk/gtk.h>

#define NODEBUG_LEVEL_3
#define NODEBUG_LEVEL_2
#define NODEBUG_LEVEL_1

static char ib_answer[16384];
static int ud;	
	
void set_frequency(GtkWidget *widget, sasc_data *data)	{
	char cmd_buf[20];
	gdouble set_frequency = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->widget_set_frequency));
	sprintf(cmd_buf,"CF%fMZ",set_frequency);
	ib_write(ud,cmd_buf);
	
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Change frequency %f\n\r", set_frequency);
#endif
}

void bnt_auto_callback(GtkWidget *widget, sasc_data *data)	{
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Auto\n\r");
#endif
	ib_write(ud,auto_rbw);
}

void bnt_auto_down_callback(GtkWidget *widget, sasc_data *data)	{
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Auto down\n\r");
#endif
	ib_write(ud,"WD");
}

void bnt_auto_up_callback(GtkWidget *widget, sasc_data *data)	{
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Auto up\n\r");
#endif
	ib_write(ud,"NR");
}

void set_rbw(GtkWidget *widget, sasc_data *data)	{
	gint rbw_index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->rbw_combo));
	ib_write(ud,rbw_cmd_4131[rbw_index]);
	
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Change RBW Index:%d %s\n\r", rbw_index,rbw_cmd_4131[rbw_index]);
#endif
}

void set_sp(GtkWidget *widget, sasc_data *data)	{
	gint sp_index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->sp_combo));
	ib_write(ud,sp_cmd_4131[sp_index]);
	
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Frequency span Index:%d %s\n\r", sp_index,sp_cmd_4131[sp_index]);;
#endif
}

void set_st(GtkWidget *widget, sasc_data *data)	{
	gint st_index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->st_combo));
	ib_write(ud,st_cmd_4131[st_index]);
	
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Sweep time Index:%d %s\n\r", st_index,st_cmd_4131[st_index]);;
#endif
}

void set_vf(GtkWidget *widget, sasc_data *data)	{
	gint vf_index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->vf_combo));
	ib_write(ud,vf_cmd_4131[vf_index]);

#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Video filter Index:%d %s\n\r", vf_index,vf_cmd_4131[vf_index]);;
#endif
}

void set_rl(GtkWidget *widget, sasc_data *data)	{
	gint rl_index = gtk_combo_box_get_active(GTK_COMBO_BOX(data->rl_combo));
	ib_write(ud,rl_cmd_4131[rl_index]);

#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Referenz Level Index:%d %s\n\r", rl_index,rl_cmd_4131[rl_index]);;
#endif
}

void bnt_att_down_callback(GtkWidget *widget, sasc_data *data)	{
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Input Attenture down\n\r");
#endif
	ib_write(ud,att_down);
}

void bnt_att_up_callback(GtkWidget *widget, sasc_data *data)	{
#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"Input Attenture up\n\r");
	ib_write(ud,att_up);
#endif
}

uint16_t swap_uint16( uint16_t val ) {
    return (val << 8) | (val >> 8 );
}

double strip_answer(char *answer, char *para) {
	double value;
	char header[3];	
	sscanf(answer, "%2s%le", header, &value);

	if(! strcmp(header,para)) {
#ifdef DEBUG_LEVEL_3		
		fprintf(stderr,"Answer: %s Header %s Value: %f \n\r", answer, header, value);
#endif		
		return value;
	}
	return 0;
}

uint capture (sasc_record *record)	{
	char buf[1402];			//Capture binary screendata

	ib_write(ud,"HD 1");
	usleep(10000);		

	record->record_counter = ib_query(ud,1403,"OPTBW",buf);
	
	int i;
	
#ifdef DEBUG_LEVEL1		
	fprintf(stderr,"%i Byte read\n\r\n\rS",record->record_counter);
#endif

	if (record->record_counter > 0)	{	
		
#ifdef DEBUG_LEVEL2				
		for(i = 0; i < record->record_counter; i++)	{
			fprintf(stderr,"%02x ",buf[i]);			
		}
#endif
		for(i = 0; i < record->record_counter/2; i++)	{
			record->value[i] = (uint16_t) (buf[2*i] << 8) | (uint8_t) (buf[2*i+1]);
			record->value[i] = record->value[i] -70;
			
#ifdef DEBUG_LEVEL2		
			fprintf(stderr,"%3d ",record->value[i]);
#endif		
		}
		
	}	
	return record->record_counter;
}

void status_sa (sasc_record *record)	{
	ib_write(ud,"HD 1");
	usleep(10000);		

	if (ib_query(ud, 19,"OPCF?", ib_answer) > 0)	{
		record->cf= strip_answer(ib_answer,"CF");
	}

	if (ib_query(ud, 19,"OPSP?", ib_answer) > 0)	{
			record->sp = strip_answer(ib_answer,"SP");
	}

	if (ib_query(ud, 19,"OPRB?", ib_answer) > 0)	{
		record->rbw = strip_answer(ib_answer,"RB");
	}	

	if (ib_query(ud, 19,"OPVF?", ib_answer) > 0)	{
		record->vf = strip_answer(ib_answer,"VF");
	}
		
	if (ib_query(ud, 19,"OPST?", ib_answer) > 0)	{
		record->st= strip_answer(ib_answer,"ST");
#ifdef DEBUG_LEVEL_1		
		fprintf(stderr,"Sweeptime %f\n\r", record->st);
#endif		
	}
	
	if (ib_query(ud, 19,"OPAT?", ib_answer) > 0){
		record->att = strip_answer(ib_answer,"AT");
	}
	
	if (ib_query(ud, 19,"OPRL?", ib_answer) > 0)	{
		record->rl = strip_answer(ib_answer,"DM");
	}
}

int set_sa(int controller, int device)	{
	ud = set_device(controller,device);	
	if (!ud)
		return -1;
		
	return ud;
}


void push_status_sa(sasc_data *data,sasc_record *record){
	
	int n = 0;

	while( record->sp <= sp_value[n]) {
		n ++;
	} 	

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"Step %.0f %.0f\n\r",sp_value[n-1], sp_step_size[n-1]);
#endif

	gtk_adjustment_set_step_increment( (GtkAdjustment *) data->adj_set_frequency,sp_step_size[n-1]/1E6);
	gtk_combo_box_set_active (GTK_COMBO_BOX(data->sp_combo), n-1);

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"Frequency  %.0f\n\r",record->cf);
#endif

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data->widget_set_frequency),record->cf/1E6);
	gtk_spin_button_set_digits(GTK_SPIN_BUTTON(data->widget_set_frequency),3);	

	n = 0;
	while( record->rbw <= rbw_value[n]) {
		n ++;
	} 	

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"RBW  %.0f\n\r",record->rbw);
#endif
	gtk_combo_box_set_active (GTK_COMBO_BOX(data->rbw_combo), n-1);

	n = 0;
	while( record->rl <= rl_value[n]) {
		n ++;
	} 	

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"Referenz level  %.0f\n\r",record->rl);
#endif
	gtk_combo_box_set_active (GTK_COMBO_BOX(data->rl_combo), n-1);
		
	n = 0;
	while( record->vf <= vf_value[n]) {
		n ++;
	} 	

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"Videofilter  %.0f\n\r",record->vf);
#endif
	gtk_combo_box_set_active (GTK_COMBO_BOX(data->vf_combo), n-1);
		
	n = 0;
	while( record->st <= st_value[n]) {
		n ++;
	} 	

#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"Sweep time %.3f index%d\n\r",record->st,n-1);
#endif
	gtk_combo_box_set_active (GTK_COMBO_BOX(data->st_combo), n-1);				
}

