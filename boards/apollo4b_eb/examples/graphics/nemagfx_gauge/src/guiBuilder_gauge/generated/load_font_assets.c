#include "nema_font.h"
#include "nema_utils.h"

#define NEMA_FONT_IMPLEMENTATION
#include "assets/fonts/arial8pt8b.h"
#include "assets/fonts/arial6pt8b.h"
#include "assets/fonts/arial14pt8b.h"
#undef NEMA_FONT_IMPLEMENTATION

nema_font_t *font_assets[3];

void load_font_assets(void) {
#if 0
    arial8pt8b.bo = nema_load_file("assets/fonts/arial8pt8b.bin", -1, 0);
    font_assets[0] = &arial8pt8b;
    arial6pt8b.bo = nema_load_file("assets/fonts/arial6pt8b.bin", -1, 0);
    font_assets[1] = &arial6pt8b;
    arial14pt8b.bo = nema_load_file("assets/fonts/arial14pt8b.bin", -1, 0);
    font_assets[2] = &arial14pt8b;
#else
    arial8pt8b.bo = LOAD_ARRAY(arial8pt8bBitmaps);
    font_assets[0] = &arial8pt8b;
    arial6pt8b.bo = LOAD_ARRAY(arial6pt8bBitmaps);
    font_assets[1] = &arial6pt8b;
    arial14pt8b.bo = LOAD_ARRAY(arial14pt8bBitmaps);
    font_assets[2] = &arial14pt8b;
#endif
}

