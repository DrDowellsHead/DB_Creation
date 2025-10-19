#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "shared.h"

int status_events_select_all(struct Status_Events *event);
int status_events_insert(struct Status_Events *new_event);
int status_events_update(struct Status_Events *update_event, int id);
int status_events_delete(int id, int delete_type);
int status_events_save_all(struct Status_Events *event, int count);

#endif