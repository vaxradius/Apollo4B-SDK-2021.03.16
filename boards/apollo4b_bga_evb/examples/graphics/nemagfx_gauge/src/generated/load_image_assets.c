#include "nema_core.h"

img_obj_t _speedo_needle_rgba;
img_obj_t _rpm_scaled_rgba;
img_obj_t _fuel2_rgba;
img_obj_t _circular_knob_rgba;

img_obj_t *image_assets[4];

#include "assets/images/speedo_needle_rgba.h"
#include "assets/images/rpm_scaled_rgba.h"
#include "assets/images/fuel2_rgba.h"
#include "assets/images/circular_knob_rgba.h"

void load_image_assets(void) {
    _speedo_needle_rgba.bo = nema_buffer_create(sizeof(speedo_needle_rgba));
    nema_buffer_map(&_speedo_needle_rgba.bo);
    nema_memcpy(_speedo_needle_rgba.bo.base_virt, speedo_needle_rgba, sizeof(speedo_needle_rgba));
    _speedo_needle_rgba.w = 58;
    _speedo_needle_rgba.h = 19;
    _speedo_needle_rgba.format = NEMA_RGBA8888;
    _speedo_needle_rgba.stride = -1;
    _speedo_needle_rgba.sampling_mode = NEMA_FILTER_BL;
    _speedo_needle_rgba.color = 0xff0000ff;
    image_assets[0] = &_speedo_needle_rgba;

    _rpm_scaled_rgba.bo = nema_buffer_create(sizeof(rpm_scaled_rgba));
    nema_buffer_map(&_rpm_scaled_rgba.bo);
    nema_memcpy(_rpm_scaled_rgba.bo.base_virt, rpm_scaled_rgba, sizeof(rpm_scaled_rgba));
    _rpm_scaled_rgba.w = 224;
    _rpm_scaled_rgba.h = 224;
    _rpm_scaled_rgba.format = NEMA_RGBA8888;
    _rpm_scaled_rgba.stride = -1;
    _rpm_scaled_rgba.sampling_mode = NEMA_FILTER_BL;
    _rpm_scaled_rgba.color = 0xff000000;
    image_assets[1] = &_rpm_scaled_rgba;

    _fuel2_rgba.bo = nema_buffer_create(sizeof(fuel2_rgba));
    nema_buffer_map(&_fuel2_rgba.bo);
    nema_memcpy(_fuel2_rgba.bo.base_virt, fuel2_rgba, sizeof(fuel2_rgba));
    _fuel2_rgba.w = 30;
    _fuel2_rgba.h = 30;
    _fuel2_rgba.format = NEMA_RGBA8888;
    _fuel2_rgba.stride = -1;
    _fuel2_rgba.sampling_mode = NEMA_FILTER_BL;
    _fuel2_rgba.color = 0xffffffff;
    image_assets[2] = &_fuel2_rgba;

    _circular_knob_rgba.bo = nema_buffer_create(sizeof(circular_knob_rgba));
    nema_buffer_map(&_circular_knob_rgba.bo);
    nema_memcpy(_circular_knob_rgba.bo.base_virt, circular_knob_rgba, sizeof(circular_knob_rgba));
    _circular_knob_rgba.w = 20;
    _circular_knob_rgba.h = 20;
    _circular_knob_rgba.format = NEMA_RGBA8888;
    _circular_knob_rgba.stride = -1;
    _circular_knob_rgba.sampling_mode = NEMA_FILTER_BL;
    _circular_knob_rgba.color = 0xff000000;
    image_assets[3] = &_circular_knob_rgba;

}
