//Params for window-swipe / temporary animations
#define TEMP_ANIMATIONS_COUNT 10 //up to 10 temporary animations simultaneously
int dx_git = 0;
int dy_git = 0;
int dx_win[TEMP_ANIMATIONS_COUNT] = {0};
int dy_win[TEMP_ANIMATIONS_COUNT] = {0};
event_t animation_temp[TEMP_ANIMATIONS_COUNT] = {{0}};

gitem_t *popup_gitem    	    = 0;
tree_node_t *popup_node 	    = 0;
int popup_off_x         	    = 0;
int popup_off_y         	    = 0;

uint8_t animation_timer_running = 0;
int force_display               = 0;
int animation_timer;
int global_off_x         		= 0;
int global_off_y         		= 0;

//animation params
int doing_transition     			 = 0;
int do_popup            	    	 = 0;
float step               			 = 0.f;
uint8_t show_screen          	     = 0;
nema_transition_t show_screen_effect = 0;
int going_right          		     = 0;

nema_cmdlist_t cl, cl_screen;
uintptr_t cur_fb_base_phys;

bool TEX_BUFFER0_OCCUPIED = false;
bool TEX_BUFFER1_OCCUPIED = false;
#define ANIMATION_DURATION 500
#define ANIMATION_STEP_0_1 ((float)TIMER_ANIM_PERIOD/ANIMATION_DURATION)

#define left(scr)  (((scr)-1+NUM_SCREENS)%NUM_SCREENS)
#define right(scr) (((scr)+1)%NUM_SCREENS)

typedef struct _quad_t {
    float x0, y0;
    float x1, y1;
    float x2, y2;
    float x3, y3;
} quad_t;
