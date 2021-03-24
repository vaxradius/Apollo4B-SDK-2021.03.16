const int event_list_size = 2;

#include "predefined_callbacks.c"
#include "custom_callbacks.c"

event_t event_list[2] = {
    //source_gitem | target_tree_node | Trigger | Action | Next | Callback | Easing | Pending | Progress | Type | Start Time | Duration | Period | Re-trigger| last pause| Effect
    {&_1269Horizontal_Slider1, &node_1244Gauge1, EVENT_VALUE_CHANGED, ACTION_NULL, NULL, callback_set_value, nema_ez_linear, EV_STATUS_STOPPED, 0.f, EVENT_ONESHOT, 0.f, 0.5, 1.f, EVENT_IGNORE, 0.f, EV_EFFECT_NONE},
    {&_1269Horizontal_Slider1, &node_1251Digital_Meter2, EVENT_VALUE_CHANGED, ACTION_NULL, NULL, callback_set_value, nema_ez_linear, EV_STATUS_STOPPED, 0.f, EVENT_ONESHOT, 0.f, 0.5, 1.f, EVENT_IGNORE, 0.f, EV_EFFECT_NONE}
};
