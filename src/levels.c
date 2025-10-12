#include "shared.h"

int levels_select_all(struct Levels *level) {
    return db_select_all("levels.db", level, sizeof(struct Levels));
}

int levels_insert(struct Levels *new_level) {
    return db_insert("levels.db", new_level, sizeof(struct Levels));
}

int levels_update(struct Levels *update_level) {
    return db_update("levels.db", update_level, sizeof(struct Levels));
}

int levels_delete(int id, int delete_type) {
    return db_delete("levels.db", id, sizeof(struct Levels), delete_type);
}

int levels_save_all(struct Levels *level, int count) {
    return db_save_all("levels.db", level, sizeof(struct Levels), count);
}