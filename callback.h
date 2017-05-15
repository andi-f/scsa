#include <gtk/gtk.h>

extern gboolean drawing_screen(GtkWidget *widget, GdkEventExpose *event, sasc_data *data);
extern void create_png(GtkWidget *widget, gpointer data);
extern void create_pdf(GtkWidget *widget, gpointer data);
extern gboolean time_handler(sasc_data *data);
extern void toogle_signal(GtkWidget *widget, gpointer window);
extern void on_window_closed (GtkWidget *widget, gpointer data);
extern void about(GtkWidget *widget, gpointer data);

#define PROGRAM "Spectrum anaylser screen capture"
#define VERSION  "v 1.0 GTK"
#define COPYRIGHT "Andreas Fischer 2017"
#define COMMENT "Screen capture from spectrum analyser via Linux-GPIP"
#define URI	"https://github.com/andi-f/sasc"
