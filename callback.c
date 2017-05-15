#include "sasc-structure.h"

#include "callback-gpib.h"
#include "widget.h"
#include "callback.h"

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

#include <cairo.h>
#include <cairo-pdf.h>

#define NODEBUG_LEVEL_1

int handler_id;
struct sasc_record record;

void plot(cairo_t *cr, gint	width, gint height, sasc_record *record) {
	double		Y;						// actual value
	double 		T;
	
	double		X_DIV = 10.0;			// 10 div/x
	double		Y_DIV = 8.0;			// 10 div/y

	double		MAX_Y = 400.0;			// max Y scale
	double		MIN_Y = 0.0;			// min Y scale
	double		MAX_X = 700.0;			// max X scale
	double		MIN_X = 0.0;			// min X scale

	double 		XMAX;					// max dots x-scale
	double 		YMAX;					// max dots y-scale
	double 		XOFFSET;				// start of diagramm
	double		YOFFSET;				// start of diagramm
	double		x, y;					// actual plot postion
	double		x_alt,y_alt;			// last plot postion
	double		x_scale,y_scale;		// scale for axis
	double		x_zero,y_zero;			// point of origin
	char		string_buf[80];			// line buffer
	
	int			m = 0;					// counter Cario
	
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_fill(cr);

	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
 
	cairo_set_font_size(cr, 10.0);
	cairo_set_line_width(cr, 1.0);

	XMAX = 0.8 * width;
	YMAX = 0.8 * height;

	XOFFSET = 0.5 * (width-XMAX);
	YOFFSET = 0.5 * (height-YMAX);

	x_scale = XMAX / (MAX_X-MIN_X);
	y_scale = YMAX / (MAX_Y-MIN_Y);		
	
	x_zero = - MIN_X * x_scale + XOFFSET;
	y_zero = YMAX - MIN_Y * y_scale + YOFFSET;
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	sprintf(string_buf,"%s %s",PROGRAM,VERSION);
	cairo_move_to (cr, XOFFSET, 0.2* YOFFSET);
	cairo_show_text(cr, string_buf); 	
	
	sprintf(string_buf,"%2.0f dBm",record->rl);
	cairo_move_to (cr,XOFFSET, 0.5* YOFFSET);
	cairo_show_text(cr, string_buf);
	
	sprintf(string_buf,"%4.3f MHz",record->cf/1000000.0);
	cairo_move_to (cr,XMAX/2, 0.5 * YOFFSET);
	cairo_show_text(cr, string_buf)	;
	
	if(record->sp > 999999999)
		sprintf(string_buf,"%3.0f GHz",record->sp/1.0E9);
	else
	if(record->sp > 999999)
		sprintf(string_buf,"%3.0f MHz",record->sp/1.0E6);
	else
		sprintf(string_buf,"%3.0f kHz",record->sp/1.0E3);		
	cairo_move_to (cr, XMAX, 0.5 * YOFFSET);
	cairo_show_text(cr, string_buf);
	
	sprintf(string_buf,"ST  %6.0f ms",record->st*1000);
	cairo_move_to (cr,XOFFSET, 1.5 * YOFFSET + YMAX);
	cairo_show_text(cr, string_buf);

	sprintf(string_buf,"ATT %3.0f dB",record->att);
	cairo_move_to (cr,XMAX/2, 1.5 * YOFFSET+ YMAX);
	cairo_show_text(cr, string_buf)	;
		
	if(record->vf > 999999)
		sprintf(string_buf,"VF %3.0f MHz",record->vf/1.0E6);
	else
	if(record->vf > 999)
		sprintf(string_buf,"VF %3.0f kHz",record->vf/1.0E3);
	else
		sprintf(string_buf,"VF %3.0f Hz",record->vf);		
	cairo_move_to (cr,XMAX, 1.5* YOFFSET + YMAX);
	cairo_show_text(cr, string_buf);
		
	cairo_stroke(cr);

	for(m = 0; m < X_DIV+1;m ++)
	{
		x =  m * XMAX / X_DIV + XOFFSET;
		if( (x >= XOFFSET) && (x <= XOFFSET+XMAX) )
		{
			cairo_move_to(cr,x,YOFFSET);
			cairo_line_to(cr,x,YMAX+YOFFSET);
		}
	}

	for(m = 0; m < Y_DIV+1;m ++)
	{
		y = m * YMAX / Y_DIV + YOFFSET;

		cairo_move_to(cr,XOFFSET,y);
		cairo_line_to (cr,XMAX+XOFFSET,y);
	}

	cairo_stroke(cr);		
		
	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	if (record->record_counter != 0)	{
		m = 0;
		Y = (double) record->value[m];
		T = (double) m; 
	
		if(Y > MAX_Y)
		{
			Y = MAX_Y;
		}
		else
		if(Y < MIN_Y)
		{
			Y = MIN_Y;
		}
		x_alt =  x_zero + T * x_scale;
		y_alt =  y_zero - Y * y_scale;
		
		for(m = 1; m <= record->record_counter-1; m ++)
		{
			Y = (double) record->value[m];
			T = (double) m;
		
			if(Y > MAX_Y)
			{
				Y = MAX_Y;
			}
			else
			if(Y < MIN_Y)
			{
				Y = MIN_Y;
			}

			x =  x_zero + T * x_scale;
			y =  y_zero - Y * y_scale;
			
			if( (x_alt >= XOFFSET) && (x <= XOFFSET+XMAX) )
			{
				cairo_move_to(cr,x_alt,y_alt);
				cairo_line_to (cr,x,y);
			}				
			x_alt = x;
			y_alt = y;
		}
		cairo_stroke(cr);		
	}
	return;
}

gboolean drawing_screen(GtkWidget *widget, GdkEventExpose *event, sasc_data *data) {
	gint width,	height;						// Window width & height

	cairo_t *cr;
	
	cr = gdk_cairo_create(widget->window);

	gdk_drawable_get_size(widget->window, &width, &height);
	
	plot(cr, width,height,&record);
	
	cairo_destroy(cr);
	return TRUE;
}

void create_png(GtkWidget *widget, gpointer data) {

	gint width = 800, height = 800;					// Window width & height
	
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);

	plot(cr, width,height,&record);

	time_t      timeStamp;
	struct tm * timeInfo;
	char        buffer[80];
 
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );
 
	strftime( buffer, 60, "%Y%m%d%H%M%S_image.png", timeInfo );
    	
	cairo_surface_write_to_png(surface, buffer);
	
	cairo_surface_destroy(surface);

	cairo_destroy(cr);

  return;
}

void create_pdf(GtkWidget *widget, gpointer data) {
	gint width = 800, height = 800;					// Window width & height
	
	cairo_surface_t *surface;
	cairo_t *cr;

	time_t      timeStamp;
	struct tm * timeInfo;
	char        buffer[80];
 
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );
 
	strftime( buffer, 60, "%Y%m%d%H%M%S_image.pdf", timeInfo );
	
	surface = cairo_pdf_surface_create (buffer, 800,800);
	
	cr = cairo_create(surface);

	plot(cr, width,height,&record);

    	
	cairo_surface_write_to_png(surface, buffer);
	
	cairo_surface_destroy(surface);

	cairo_destroy(cr);

  return;
}	

gboolean time_handler(sasc_data *data) {

	if (data->main_window->window == NULL) {

		return FALSE;
	}
	
	//gtk_widget_queue_draw(data->main_window);
	if (handler_id == 0)	{
		gtk_statusbar_push(GTK_STATUSBAR(data->statusbar),gtk_statusbar_get_context_id(GTK_STATUSBAR(data->statusbar), "Standby"),"Standby");
		gtk_widget_queue_draw(data->main_window);		
		return TRUE;		
	} 
	
	fprintf(stderr,"Capture data\n\r");


	status_sa(&record);		
	capture(&record);
	gtk_widget_queue_draw(data->main_window);
	push_status_sa(data,&record);
	gtk_statusbar_push(GTK_STATUSBAR(data->statusbar),gtk_statusbar_get_context_id(GTK_STATUSBAR(data->statusbar), "Update data"),"Update data");
	gtk_widget_queue_draw(data->main_window);
	
	return TRUE;
}

void toogle_signal(GtkWidget *widget, gpointer window) {
	if (handler_id == 0) {
		handler_id = g_signal_connect(G_OBJECT(window), "expose-event", 
		G_CALLBACK(drawing_screen), NULL);
#ifdef DEBUG		           
		fprintf(stderr,"Connect handle\n\r");           
#endif		
	} 
	else {
		g_signal_handler_disconnect(window, handler_id);
		handler_id = 0;	
#ifdef DEBUG		
		fprintf(stderr,"Disconnect handle\n\r");		
#endif
	}
}

void on_window_closed (GtkWidget *widget, gpointer data)	{
    gtk_main_quit();
    fprintf(stderr,"main_quit");
	return;
}

void about(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), PROGRAM);
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), VERSION); 
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), COPYRIGHT);
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), COMMENT);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), URI);
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
 }
 
