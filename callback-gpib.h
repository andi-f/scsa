extern void set_frequency(GtkWidget *widget, sasc_data data);
extern void set_rbw(GtkWidget *widget, sasc_data data);
extern void bnt_auto_callback(GtkWidget *widget, sasc_data data);
extern void bnt_auto_down_callback(GtkWidget *widget, sasc_data data);
extern void bnt_auto_up_callback(GtkWidget *widget, sasc_data data);
extern void set_sp(GtkWidget *widget, sasc_data data);
extern void set_rl(GtkWidget *widget, sasc_data data);
extern void set_vf(GtkWidget *widget, sasc_data data);
extern void set_st(GtkWidget *widget, sasc_data data);
extern void bnt_att_up_callback(GtkWidget *widget, sasc_data data);
extern void bnt_att_down_callback(GtkWidget *widget, sasc_data data);

extern uint16_t swap_uint16( uint16_t val );
extern double strip_answer(char *answer, char *para);
extern int capture (sasc_record *record);
extern int status_sa (sasc_record *record);
extern int set_sa();
extern void push_status_sa(sasc_data *data,sasc_record *record);
