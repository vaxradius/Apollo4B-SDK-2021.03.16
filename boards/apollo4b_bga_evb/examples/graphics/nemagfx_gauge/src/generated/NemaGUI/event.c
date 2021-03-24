#include "event_list.c"

#include "gitem.h"

void init_events(void) {
    int i;

    for (i = 0; i < event_list_size; ++i) {
        event_t **event = NULL;
        if(event_list[i].src_gitem)
            event = &event_list[i].src_gitem->event;

        if ( event_list[i].trigger_event >= EVENT_PRESS &&
             event_list[i].trigger_event <= EVENT_DRAG ) {

            event_list[i].src_gitem->gesture_flags |= 1 << event_list[i].trigger_event;
        }

        while (*event != NULL) {
            event = &(*event)->next;
        }

        *event = &event_list[i];
    }
}
