#define FRAME_BUFFERS 4
#define BACK_BUFFERS 2

#define RESX        224
#define RESY        224

img_obj_t fb[FRAME_BUFFERS];
nemadc_layer_t layer[FRAME_BUFFERS] = {{0}};

void load_objects(void){
    for (int i = 0; i < FRAME_BUFFERS; ++i) {
        int format = i < (FRAME_BUFFERS - BACK_BUFFERS) ? NEMA_TSC4 : NEMA_RGB565;

        fb[i].stride = nema_stride_size(format, 0, RESX);
        fb[i].w = RESX;
        fb[i].h = RESY;
        fb[i].format = format;

        if (format == NEMA_TSC4)
            fb[i].bo = nema_buffer_create(RESX*RESY/2);
        else
            fb[i].bo = nema_buffer_create(fb[i].stride*fb[i].h);

        nema_buffer_map(&fb[i].bo);

        if (i < FRAME_BUFFERS - BACK_BUFFERS) {
            layer[i].sizex         = layer[i].resx = fb[i].w;
            layer[i].sizey         = layer[i].resy = fb[i].h;
            layer[i].stride        = -1;
            layer[i].format        = NEMADC_TSC4;
            layer[i].blendmode     = NEMADC_BL_SRC;
            layer[i].baseaddr_phys = fb[i].bo.base_phys;
            layer[i].baseaddr_virt = fb[i].bo.base_virt;
        }

        PRINT_I("FB[%d]: V:%p P:0x%08x\n ", i, (void *)fb[i].bo.base_virt, fb[i].bo.base_phys);
    }
}