#ifndef __GITEM_H__
#define __GITEM_H__

#define GITEMF_ALWAYS     (1<< 0)
#define GITEMF_PRESS      (1<< 1)
#define GITEMF_RELEASE    (1<< 2)
#define GITEMF_HOLD       (1<< 3)
#define GITEMF_DRAG       (1<< 4)

#define GITEMF_STOP_RECUR   (1<< 8)
#define GITEMF_HIDDEN       (1<< 9)
#define GITEMF_ANIMATED     (1<< 10)
#define GITEMF_TEX_RENDERED (1<< 11)
#define GITEMF_TEX_BUFFER0  (1<< 12)

typedef enum {
    GITEM_SCREEN,             // 0
    GITEM_CONT,               // 1
    GITEM_CIRCLE,             // 2
    GITEM_RECT,               // 3
    GITEM_RRECT,              // 4
    GITEM_IMG,                // 5
    GITEM_LABEL,              // 6
    GITEM_LABEL_BUTTON,       // 7
    GITEM_CHECKBOX,           // 8
    GITEM_RADIO,              // 9
    GITEM_H_SLIDER,           //10
    GITEM_V_SLIDER,           //11
    GITEM_DIGIMETER,          //12
    GITEM_POPUP,              //13
    GITEM_ICON,               //14
    GITEM_MENU,               //15
    GITEM_PROGRESS_BAR,       //16
    GITEM_GAUGE,              //17
    GITEM_ROTATING_CONTAINER, //18
    GITEM_ICON_BUTTON,        //19
    GITEM_WINDOW,             //20
    GITEM_CIRCULAR_PROGRESS,  //21
    GITEM_WATCH_FACE,         //22
    GITEM_WATCH_FACE_HAND,    //23
    GITEM_DIGITAL_CLOCK       //24
} gitem_type_t;

#define true  1
#define false 0

typedef struct _gitem_t{
    struct _gitem_t *gitem;
    struct _event_t *event;
    struct _event_t *animation;
    char     *text;

    float     val;
    float     step;
    float     min;
    float     max;
    float     min_angle;
    float     max_angle;
    float     angle;
    const int id;
    uint32_t  color;
    uint32_t  color_const;
    uint32_t  color2;
    uint32_t  color2_const;
    int       x;
    int       x_const;
    int       y;
    int       y_const;

    uint16_t w;
    uint16_t w_const;
    uint16_t h;
    uint16_t h_const;
    uint16_t r;
    uint16_t r_const;
    int16_t  img_asset_id;
    int16_t  img_asset_id2;
    int16_t  font_asset_id;
    uint16_t penwidth;
    uint16_t x_rot;
    uint16_t y_rot;
    uint16_t gesture_flags;

    const uint8_t  type;
    uint8_t  text_alignment; //caution nema_font takes uint32_t
    uint8_t  precision;
    bool     fill;
    bool     checked;
    bool     highlighted;
    bool     bg_image; //draw bg image if needed
} gitem_t;

typedef struct tree_node_t_{
    gitem_t *this_;
    struct tree_node_t_ *parent;
    struct tree_node_t_ *first_child;
    struct tree_node_t_ *next;
} tree_node_t;

static nema_buffer_t create_bo_from_pointer(void *ptr, size_t size) {
    nema_buffer_t bo;

#ifdef UNIFIED_MEMORY
    bo.base_virt = ptr;
    bo.base_phys = (uintptr_t)ptr;
    bo.size      = size;
#else
    bo = nema_buffer_create(size);
    (void)nema_buffer_map(&bo);
    nema_memcpy(bo.base_virt, ptr, size);
#endif

    return bo;
}

#define LOAD_ARRAY(array) create_bo_from_pointer((void *)(array), sizeof(array))

#endif //__GITEM_H__

