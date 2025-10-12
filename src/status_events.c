#include "shared.h"

int status_events_select_all(struct Status_Events *event) {
    return db_select_all("status_events.db", event,
                         sizeof(struct Status_Events));
}

int status_events_insert(struct Status_Events *new_event) {
    return db_insert("status_events.db", new_event,
                     sizeof(struct Status_Events));
}

int status_events_update(struct Status_Events *update_event, int id) {
    return db_update("status_events.db", update_event,
                     sizeof(struct Status_Events), id);
}

int status_events_delete(int id, int delete_type) {
    return db_delete("status_events.db", id, sizeof(struct Status_Events),
                     delete_type);
}

int status_events_save_all(struct Status_Events *event, int count) {
    return db_save_all("status_events.db", event, sizeof(struct Status_Events),
                       count);
}