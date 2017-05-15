#ifdef STATE
static char *rbw_cmd_4131[] = {"RB1MZ","RB300KZ","RB100KZ","RB30KZ","RB10KZ","RB3KZ","RB1KZ"};
static double rbw_value[] = {1E6,300E3,100E3,30E3,10E3,3E3,1E3,};

static char *sp_cmd_4131[] = {"SP4GZ","SP2GZ","SP1GZ","SP500MZ", "SP200MZ", "SP100MZ", "SP50MZ", "20MZ", "SP10MZ", "SP5MZ", "SP2MZ", "SP1MZ", "SP500KZ", "SP200KZ", "SP100KZ", "SP50KZ","ZS"};
static double sp_value[] = {	4E9,	2E9,	1E9,	500E6,	200E6,	100E6,	50E6,	20E6,	10E6,	5E6,	2E6,	1E6,	500E3,	200E3,	100E3,	50E3,	0};
static double sp_step_size[] = {20E6,	10E6,	5E6,	2E6,	1E6 ,	500E3,	200E3,	100E3,	50E3,	30E3,	10E3,	5E3,	2E3,	2E3,	1E3,	1E3,	25E3};

static char *st_cmd_4131[] = {"ST100S","ST50S","ST20S","ST10S","ST5S","ST2S","ST1S","ST500MS","ST200MS","ST100MS","ST50MS","ST20MS","ST10mS","ST5MS"};
static double st_value[] = {100,50,20,10,5,2,1,0.5,0.2,0.1,0.05,0.02,0.010,0.05};

static char *vf_cmd_4131[] = {"VF1MZ","VF300KZ","VF100KZ","VF10KZ","VF1KZ","VF100Hz","VF10Hz"};
static double vf_value[]={1000000,300000,100000,10000,1000,100,10};

static char *rl_cmd_4131[] = {"RL40DM","RL30DM","RL20DM","RL10DM","RL0DM","RL-10DM","RL-20DM","RL-30DM","RL-40DM","Rl-50DM"};
static double rl_value[]={40,30,20,10,0,-10,-20,-30,-40,-50};
#endif

#ifdef WIDGET
const char *rbw_select_4131[] = {"1 MHz","300 kHz","100 kHz","30 kHz","10 kHz","3 kHz","1 kHz"};
const uint rbw_cnt_4131 = 7;

const char *sp_select_4131[] = {"4 GHz","2 GHz","1 GHz","500 MHz", "200 MHz", "100 MHz", "50 MHz", "20 MHz", "10 MHz", "5 MHz", "2 MHz", "1 MHz", "500 kHz", "200 kHz", "100 kHz", "50 kHz", "ZEROSPAN"};
const uint sp_cnt_4131 = 16;
		
const char *st_select_4131[] = {"100s","50s","20s","10s","5s","2s","1s","500ms","200ms","100ms","50ms","20ms","10ms","5ms"};
const uint st_cnt_4131 = 14;

const char *vf_select_4131[] = {"1 MHz","300 kHz","100 kHz","10 kHz","1 kHz","100 Hz","10 Hz", };
const uint vf_cnt_4131 = 6;

const char *rl_select_4131[] = {"40dBm","30dBm","20dBm","10dBm","0dBm","-10dBm","-20dBm","-30dBm","-40dBm","-50dBm"};
const uint rl_cnt_4131 = 9;
#endif

#ifdef CMD
const char *rbw_auto_down="WD";
const char *rbw_auto_up="NR";
const char *att_down="AD";
const char *att_up="AU";
const char *auto_rbw="BA";
#endif

